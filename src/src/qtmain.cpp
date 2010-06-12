/*
@version: 0.4.5
@author: Aymeric Brisse <aymeric.brisse@gmail.com>
@license: GNU General Public License
*/

#include <QtGui/QApplication>
#include "mainwindow.h"

/**
 * Main
 */
int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  MainWindow w;
  w.show();
  return a.exec();
}
