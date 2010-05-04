/*
@version: 0.2
@author: Aymeric Brisse <aymeric.brisse@gmail.com>
@license: GNU General Public License
*/

#include <QtGui/QApplication>
#include "mainwindow.h"

#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
