/*
 * Created: 02/13/10-18:42:19
 * Author: Aymeric Brisse
 */
#include <QtGui/QApplication>
#include "mainwindow.h"
#include "utils.h"

#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
