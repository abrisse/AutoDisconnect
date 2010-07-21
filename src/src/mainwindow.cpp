/*
@version: 0.4.7
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
  int coeff;

  /* General */

  /*
    0 : never
    1 : always
    2 : when not charging
    3 : when locked
    4 : when not charging AND locked
  */

  Utils::SetInteger("param_running_options",  ui->enabledList->currentIndex());
  Utils::SetBoolean("param_notifications",  ui->chkNotifications->checkState());

  /* Network */
  QString idle_network_infos = ui->networkModeList->currentText();
  QString idle_network_type = "none";
  QRegExp rx("(\\w+) - Switch lasts (\\d+)''$");
  int idle_network_duration = 0;

  if (idle_network_infos.contains(rx))
  {
    idle_network_type = rx.capturedTexts().at(1).toLower();
    idle_network_duration = rx.capturedTexts().at(2).toInt();
    ui->btnSave->setText(rx.capturedTexts().at(2).toLower());
  }

  Utils::SetString("param_idle_network_mode_type", idle_network_type);
  Utils::SetInteger("param_idle_network_mode_duration", idle_network_duration);

  Utils::SetBoolean("param_connection_wlan", ui->chkConnexionWLAN->checkState());
  Utils::SetBoolean("param_connection_gprs", ui->chkConnexionGPRS->checkState());

  Utils::SetBoolean("param_exception_ssh", ui->chkExceptionSSH->checkState());
  Utils::SetBoolean("param_exception_openvpn", ui->chkExceptionOpenVPN->checkState());
  Utils::SetBoolean("param_exception_im_accounts", ui->chkExceptionIMAccounts->checkState());
  Utils::SetBoolean("param_exception_voip", ui->chkExceptionVoIP->checkState());

  /* Network GPRS - Parameters */
  coeff = 1;
  switch (ui->unitListGPRS->currentIndex())
  {
  case 2:
    coeff *= 1024;

  case 1:
    coeff *= 1024;

  default:
    break;
  }

  Utils::SetInteger("param_gprs_interval", ui->spinIntervalGPRS->value());
  Utils::SetInteger("param_gprs_pre_interval", ui->spinPreIntervalGPRS->value());
  Utils::SetInteger("param_gprs_traffic", ui->spinMinBytesGPRS->value()*coeff);

  /* Network WLAN - Parameters */
  coeff = 1;
  switch (ui->unitListWLAN->currentIndex())
  {
  case 2:
    coeff *= 1024;

  case 1:
    coeff *= 1024;

  default:
    break;
  }

  Utils::SetInteger("param_wlan_interval", ui->spinIntervalWLAN->value());
  Utils::SetInteger("param_wlan_pre_interval", ui->spinPreIntervalWLAN->value());
  Utils::SetInteger("param_wlan_traffic", ui->spinMinBytesWLAN->value()*coeff);

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

  /* Version */
  QString version = "AutoDisconnect v" + Utils::GetString("version");
  this->setWindowTitle(version);
  //ui->label_version->setText(version);

  /* General */  
  ui->enabledList->setCurrentIndex(Utils::GetInteger("param_running_options"));
  ui->chkNotifications->setChecked(Utils::GetBoolean("param_notifications"));

  /* Network - GPRS */
  int min_bytes = Utils::GetInteger("param_gprs_traffic");
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

  ui->spinMinBytesGPRS->setValue(traffic_value);
  ui->unitListGPRS->setCurrentIndex(unit_index);
  ui->spinIntervalGPRS->setValue(Utils::GetInteger("param_gprs_interval"));
  ui->spinPreIntervalGPRS->setValue(Utils::GetInteger("param_gprs_pre_interval"));

  /* Network - WLAN */
  min_bytes = Utils::GetInteger("param_wlan_traffic");

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

  ui->spinMinBytesWLAN->setValue(traffic_value);
  ui->unitListWLAN->setCurrentIndex(unit_index);
  ui->spinIntervalWLAN->setValue(Utils::GetInteger("param_wlan_interval"));
  ui->spinPreIntervalWLAN->setValue(Utils::GetInteger("param_wlan_pre_interval"));

  /* Network */
  QString idle_network_type = Utils::GetString("param_idle_network_mode_type");
  int idle_network_duration = Utils::GetInteger("param_idle_network_mode_duration");

  for(int i=2; i<=10; i++)
    ui->networkModeList->addItem(QString("   3G - Switch lasts ") + QString::number(i) + "''");

  for(int i=4; i<=14; i++)
    ui->networkModeList->addItem(QString("   Dual - Switch lasts ") + QString::number(i) + "''");

  if (idle_network_type == "none")
  {
    ui->networkModeList->setCurrentIndex(0);
  }
  else if (idle_network_type == "3g")
  {    
    ui->networkModeList->setCurrentIndex(ui->networkModeList->findText(QString("   3G - Switch lasts ") + QString::number(idle_network_duration) + "''", Qt::MatchExactly));
  }
  else if (idle_network_type == "dual")
  {
    ui->networkModeList->setCurrentIndex(ui->networkModeList->findText(QString("   Dual - Switch lasts ") + QString::number(idle_network_duration) + "''", Qt::MatchExactly));
  }

  ui->chkConnexionWLAN->setChecked(Utils::GetBoolean("param_connection_wlan"));
  ui->chkConnexionGPRS->setChecked(Utils::GetBoolean("param_connection_gprs"));  

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
  QString aboutText = "\nAutoDisconnect is an application which closes your idle connections (Wifi + 3G/GPRS + Bluetooth)";
  aboutText += " and switches to 2G when 3G is not used, in order for your batteries to last much longer.\n\n";
  aboutText += "Aymeric Brisse (aymeric.brisse@gmail.com)\n";
  QMessageBox::about(this, "About", aboutText);
}
