/*
@version: 0.4
@author: Aymeric Brisse <aymeric.brisse@gmail.com>
@license: GNU General Public License
*/

#include "utils.h"

Utils::Utils()
{
}

/* Variable Declaration */
GConfClient* Utils::gconfClient;

/**
 * Display Notification
 */
void Utils::displayNotification(QMainWindow* window, QString msg)
{
  QString info = "<font color='#000000'>" + msg + "</font>";
  QMaemo5InformationBox::information(window, info, QMaemo5InformationBox::NoTimeout);
}

/**
 * Load gconf client
 */
void Utils::Load()
{
  gconfClient = gconf_client_get_default();
  g_assert(GCONF_IS_CLIENT(gconfClient));
}

/**
 * Unload gconf client
 */
void Utils::Unload()
{
  /* release GConf client */
  g_object_unref(gconfClient);
}

/**
 * Store an integer key
 */
void Utils::SetInteger(QString key, int value)
{
  key = GC_ROOT + key;

  if(!gconf_client_set_int(gconfClient, key.toStdString().c_str(), value, NULL))
    g_warning("failed to set key\n");
}

/**
 * Store a boolean key
 */
void Utils::SetBoolean(QString key, bool value)
{
  key = GC_ROOT + key;

  if(!gconf_client_set_bool(gconfClient, key.toStdString().c_str(), value, NULL))
    g_warning("failed to set key\n");
}

/**
 * Get a boolean value
 */
bool Utils::GetBoolean(QString key)
{
  key = GC_ROOT + key;
  bool val = NULL;

  GConfValue* gcValue = NULL;
  gcValue = gconf_client_get_without_default(gconfClient, key.toStdString().c_str(), NULL);

  /* if value pointer remains NULL, the key was not found */
  if(gcValue != NULL)
  {
    if (gcValue->type == GCONF_VALUE_BOOL)
      val = gconf_value_get_bool(gcValue);
    gconf_value_free(gcValue);
  }

  return val;
}

/**
 * Get an integer value
 */
int Utils::GetInteger(QString key)
{
  key = GC_ROOT + key;
  int val = NULL;

  GConfValue* gcValue = NULL;
  gcValue = gconf_client_get_without_default(gconfClient, key.toStdString().c_str(), NULL);

  /* if value pointer remains NULL, the key was not found */
  if(gcValue != NULL)
  {
    if (gcValue->type == GCONF_VALUE_INT)
      val = gconf_value_get_int(gcValue);
    gconf_value_free(gcValue);
  }

  return val;
}

/**
 * Get an string value
 */
QString Utils::GetString(QString key)
{
  key = GC_ROOT + key;
  QString val = "";

  GConfValue* gcValue = NULL;
  gcValue = gconf_client_get_without_default(gconfClient, key.toStdString().c_str(), NULL);

  /* if value pointer remains NULL, the key was not found */
  if(gcValue != NULL)
  {
    if (gcValue->type == GCONF_VALUE_STRING)
      val = QString(gconf_value_get_string(gcValue));
    gconf_value_free(gcValue);
  }

  return val;
}

/**
 * Run the bluetooth checker
 */
void Utils::RunBluetoothChecker()
{
  QProcess::startDetached("/opt/autodisconnect/autodisconnect-bluetooth-check");
}
