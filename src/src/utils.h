/*
@version: 0.4.5
@author: Aymeric Brisse <aymeric.brisse@gmail.com>
@license: GNU General Public License
*/

#ifndef UTILS_H
#define UTILS_H

/* Include the prototypes for GConf client functions */
#include <gconf/gconf-client.h>

/* Banner - See http://doc.qt.nokia.com/qt-maemo-4.6/qmaemo5informationbox.html */
#include <QMaemo5InformationBox>
#include <QMainWindow>
#include <QProcess>

/* The application name -part of the GConf namespace */
#define APP_NAME "autodisconnect"
/* This will be the root "directory" for our preferences */
#define GC_ROOT  "/apps/" APP_NAME "/"

class Utils
{
public:
  Utils();
  static void displayNotification(QMainWindow* window, QString msg);
  static void Load();
  static void Unload();
  static void SetBoolean(QString key, bool value);
  static void SetInteger(QString key, int value);
  static void SetString(QString key, QString value);
  static bool GetBoolean(QString key);
  static int GetInteger(QString key);
  static QString GetString(QString key);
  static void RunBluetoothChecker();
private:
  static GConfClient* gconfClient;
};

#endif // UTILS_H
