/*
@version: 0.3
@author: Aymeric Brisse <aymeric.brisse@gmail.com>
@license: GNU General Public License
*/

#include "utils.h"

Utils::Utils()
{
}

void Utils::displayNotification(QMainWindow* window, const char* value)
{
  char buffer[500];
  sprintf(buffer,"%s%s%s","<font color='#000000'>",value, "</font>");
  QMaemo5InformationBox::information(window, buffer, QMaemo5InformationBox::DefaultTimeout);
}

/**
 * Store an integer key
 */
void Utils::SetInteger(const char* key, int value)
{
  GConfClient* gconfClient = gconf_client_get_default();
  g_assert(GCONF_IS_CLIENT(gconfClient));
  char path[100];
  sprintf(path, "%s%s", GC_ROOT, key);

  if(!gconf_client_set_int(gconfClient, path, value, NULL))
    g_warning(" failed to set %smykey (%d)\n", GC_ROOT, value);

  /* release GConf client */
  g_object_unref(gconfClient);
}

/**
 * Store a boolean key
 */
void Utils::SetBoolean(const char* key, bool value)
{
  GConfClient* gconfClient = gconf_client_get_default();
  g_assert(GCONF_IS_CLIENT(gconfClient));
  char path[100];
  sprintf(path, "%s%s", GC_ROOT, key);

  if(!gconf_client_set_bool(gconfClient, path, value, NULL))
    g_warning(" failed to set %smykey (%d)\n", GC_ROOT, value);

  /* release GConf client */
  g_object_unref(gconfClient);
}

/**
 * Get a boolean value
 */
bool Utils::GetBoolean(const char* key)
{
  GConfClient* gconfClient = gconf_client_get_default();
  g_assert(GCONF_IS_CLIENT(gconfClient));
  char path[100];
  sprintf(path, "%s%s", GC_ROOT, key);

  GConfValue* gcValue = NULL;
  gcValue = gconf_client_get_without_default(gconfClient, path, NULL);

  bool value;

  /* if value pointer remains NULL, the key was not found */
  if(gcValue == NULL)
  {
    g_warning(" key %smykey not found\n", GC_ROOT);
    g_object_unref(gconfClient);
    return NULL;
  }

  /* Check if value type is integer */
  if(gcValue->type == GCONF_VALUE_BOOL)
  {
    value = gconf_value_get_bool(gcValue);
  }
  else
  {
    g_warning(" key %smykey is not integer\n", GC_ROOT);
  }

  /* Release resources */
  gconf_value_free(gcValue);
  g_object_unref(gconfClient);

  return value;
}

/**
 * Get an integer value
 */
int Utils::GetInteger(const char* key)
{
  GConfClient* gconfClient = gconf_client_get_default();
  g_assert(GCONF_IS_CLIENT(gconfClient));
  char path[100];
  sprintf(path, "%s%s", GC_ROOT, key);

  GConfValue* gcValue = NULL;
  gcValue = gconf_client_get_without_default(gconfClient, path, NULL);

   int value;

  /* if value pointer remains NULL, the key was not found */
  if(gcValue == NULL)
  {
    g_warning(" key %smykey not found\n", GC_ROOT);
    g_object_unref(gconfClient);
    return NULL;
  }

  /* Check if value type is integer */
  if(gcValue->type == GCONF_VALUE_INT)
  {
    value = gconf_value_get_int(gcValue);
  }
  else
  {
    g_warning(" key %smykey is not integer\n", GC_ROOT);
  }

  /* Release resources */
  gconf_value_free(gcValue);
  g_object_unref(gconfClient);

  return value;
}
