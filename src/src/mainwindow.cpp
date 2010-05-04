/*
@version: 0.2
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
   // Save values
  Utils::SetInteger("param_interval",       ui->spinInterval->value());
  Utils::SetInteger("param_min_bytes",      ui->spinMinBytes->value());
  Utils::SetBoolean("param_enabled",        ui->chkEnabled->checkState());
  Utils::SetBoolean("param_notifications",  ui->chkNotifications->checkState());
  Utils::SetBoolean("param_connection_wlan", ui->chkConnexionWLAN->checkState());
  Utils::SetBoolean("param_connection_gprs", ui->chkConnexionGPRS->checkState());

  Utils::displayNotification("Settings has been saved !");
}

void MainWindow::loadValues()
{
  ui->spinInterval->setValue(Utils::GetInteger("param_interval"));
  ui->spinMinBytes->setValue(Utils::GetInteger("param_min_bytes"));
  ui->chkEnabled->setChecked(Utils::GetBoolean("param_enabled"));
  ui->chkNotifications->setChecked(Utils::GetBoolean("param_notifications"));
  ui->chkConnexionWLAN->setChecked(Utils::GetBoolean("param_connection_wlan"));
  ui->chkConnexionGPRS->setChecked(Utils::GetBoolean("param_connection_gprs"));
}
