/*
@version: 0.3
@author: Aymeric Brisse <aymeric.brisse@gmail.com>
@license: GNU General Public License
*/

#include "utils.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <string.h>

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
  Utils::SetBoolean("param_exception_ssh", ui->chkExceptionSSH->checkState());

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

  Utils::displayNotification(this, "Settings have been saved and will be taken in account at the next reconnection!");
}

void MainWindow::loadValues()
{
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
  ui->chkExceptionSSH->setChecked(Utils::GetBoolean("param_exception_ssh"));

  /* Bluetooth */
  ui->chkBluetooth->setChecked(Utils::GetBoolean("param_bluetooth_enable"));
  ui->spinIntervalBluetooth->setValue(Utils::GetInteger("param_bluetooth_interval"));
}
