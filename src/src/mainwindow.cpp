/*
@version: 0.4
@author: Aymeric Brisse <aymeric.brisse@gmail.com>
@license: GNU General Public License
*/

#include "utils.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  loadValues();
}

MainWindow::~MainWindow()
{
  delete ui;
  Utils::Unload();
}

void MainWindow::changeEvent(QEvent *e)
{
  QMainWindow::changeEvent(e);
  switch (e->type()) {
    case QEvent::LanguageChange:
      ui->retranslateUi(this);
      break;
    default:
      break;
  }
}

void MainWindow::on_btnSave_clicked()
{
  saveValues();
  close();
}

void MainWindow::on_btnAbout_clicked()
{
  about();
}

/**
 * Save parameters
 */
void MainWindow::saveValues()
{
  int coeff=1;
  int running_options;

  /* Running Options */
  if (ui->radioEnabledAlways->isChecked())
    running_options = 1;
  else if (ui->radioEnabledNotCharging->isChecked())
    running_options = 2;
  else
    running_options = 0;

  Utils::SetInteger("param_running_options",  running_options);
  Utils::SetBoolean("param_notifications",  ui->chkNotifications->checkState());

  /* Network - Connections */
  Utils::SetBoolean("param_connection_wlan", ui->chkConnexionWLAN->checkState());
  Utils::SetBoolean("param_connection_gprs", ui->chkConnexionGPRS->checkState());
  Utils::SetBoolean("param_use_2g", ui->chkUse2G->checkState());

  Utils::SetBoolean("param_exception_ssh", ui->chkExceptionSSH->checkState());
  Utils::SetBoolean("param_exception_openvpn", ui->chkExceptionOpenVPN->checkState());
  Utils::SetBoolean("param_exception_im_accounts", ui->chkExceptionIMAccounts->checkState());
  Utils::SetBoolean("param_exception_voip", ui->chkExceptionVoIP->checkState());

  /* Network - Parameters */
  switch (ui->unitList->currentIndex())
  {
  case 2:
    coeff *= 1024;

  case 1:
    coeff *= 1024;

  default:
    break;
  }

  Utils::SetInteger("param_interval", ui->spinInterval->value());
  Utils::SetInteger("param_min_bytes", ui->spinMinBytes->value()*coeff);  

  /* Bluetooth */
  Utils::SetBoolean("param_bluetooth_enable", ui->chkBluetooth->checkState());
  Utils::SetInteger("param_bluetooth_interval", ui->spinIntervalBluetooth->value());

  Utils::RunBluetoothChecker();

  Utils::displayNotification(this, "Settings have been saved and will be taken in account at the next reconnection");
}

/**
 * Load parameters
 */
void MainWindow::loadValues()
{
  Utils::Load();

  QString version = "AutoDisconnect v" + Utils::GetString("version");

  this->setWindowTitle(version);
  ui->label_version->setText(version);

  int min_bytes = Utils::GetInteger("param_min_bytes");

  /* Network - Parameters */
  int traffic_value;
  int unit_index;

  if (min_bytes<1024)
  {
    unit_index=0;
    traffic_value=min_bytes;
  }
  else if (min_bytes < 1048576)
  {
    unit_index=1;
    traffic_value=(int)(min_bytes/1024);
  }
  else
  {
    unit_index=2;
    traffic_value=(int)(min_bytes/1048576);
  }

  ui->spinMinBytes->setValue(traffic_value);
  ui->unitList->setCurrentIndex(unit_index);
  ui->spinInterval->setValue(Utils::GetInteger("param_interval"));

  /* Running Options */
  int running_options = Utils::GetInteger("param_running_options");

  switch(running_options)
  {
  case 0:
    ui->radioEnabledNever->setChecked(true);
    break;
  case 1:
    ui->radioEnabledAlways->setChecked(true);
    break;
  case 2:
    ui->radioEnabledNotCharging->setChecked(true);
    break;
  }

  ui->chkNotifications->setChecked(Utils::GetBoolean("param_notifications"));

  /* Network - Connections */
  ui->chkConnexionWLAN->setChecked(Utils::GetBoolean("param_connection_wlan"));
  ui->chkConnexionGPRS->setChecked(Utils::GetBoolean("param_connection_gprs"));  
  ui->chkUse2G->setChecked(Utils::GetBoolean("param_use_2g"));

  ui->chkExceptionSSH->setChecked(Utils::GetBoolean("param_exception_ssh"));
  ui->chkExceptionOpenVPN->setChecked(Utils::GetBoolean("param_exception_openvpn"));
  ui->chkExceptionIMAccounts->setChecked(Utils::GetBoolean("param_exception_im_accounts"));
  ui->chkExceptionVoIP->setChecked(Utils::GetBoolean("param_exception_voip"));

  /* Bluetooth */
  ui->chkBluetooth->setChecked(Utils::GetBoolean("param_bluetooth_enable"));
  ui->spinIntervalBluetooth->setValue(Utils::GetInteger("param_bluetooth_interval"));
}

/**
 * Display About Information
 */
void MainWindow::about()
{
  QString aboutText = "\nAutoDisconnect is an application which makes your batteries last much longer by closing your idle connections (Wifi + 3G/GPRS + Bluetooth)";
  aboutText += " and by switching to 2G when 3G is not required. You can custom a lot of parameters.\n\n";
  aboutText += "Written by Aymeric Brisse - aymeric.brisse@gmail.com\n";
  QMessageBox::about(this, "About", aboutText);
}
