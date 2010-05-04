/*
@version: 0.2
@author: Aymeric Brisse <aymeric.brisse@gmail.com>
@license: GNU General Public License
*/

#ifndef UTILS_H
#define UTILS_H

/* Include the prototypes for GConf client functions */
#include <gconf/gconf-client.h>

/* Include the prototypes for Libnotify */
/* See http://library.gnome.org/devel/libnotify/ */
#include <libnotify/notify.h>

#include <stdio.h>

/* The application name -part of the GConf namespace */
#define APP_NAME "autodisconnect"
/* This will be the root "directory" for our preferences */
#define GC_ROOT  "/apps/" APP_NAME "/"

class Utils
{
public:
    Utils();
    static void displayNotification(const char* value);

    static void SetInteger(const char* key, int value);
    static int GetInteger(const char* key);
    static void SetBoolean(const char* key, bool value);
    static bool GetBoolean(const char* key);

private:
};

#endif // UTILS_H
