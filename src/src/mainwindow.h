/*
@version: 0.4.5
@author: Aymeric Brisse <aymeric.brisse@gmail.com>
@license: GNU General Public License
*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>

namespace Ui {
  class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT
public:
  MainWindow(QWidget *parent = 0);
  ~MainWindow();

protected:
  void changeEvent(QEvent *e);
  void loadValues();
  void saveValues();
  void about();

private:
  Ui::MainWindow *ui;



private slots:
  void on_btnAbout_clicked();
  void on_btnSave_clicked();
};

#endif // MAINWINDOW_H
