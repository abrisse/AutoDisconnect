/*
@version: 0.4.0
@author: Aymeric Brisse <aymeric.brisse@gmail.com>
@license: GNU General Public License
*/

#include <string.h>
#include <stdlib.h>
#include <X11/Xlib.h>
#include <gdk/gdkx.h>
#include <gtk/gtk.h>
#include <libosso.h>

static const char binary[] = "/opt/autodisconnect/autodisconnect";

osso_return_t execute(osso_context_t *osso_context, gpointer parent, gboolean user_activated)
{
    char args[sizeof(binary) + 64];
    Window id = None;

    (void) osso_context;

    if (parent && GTK_WIDGET(parent) && GTK_WIDGET(parent)->window)
        id = gdk_x11_drawable_get_xid(GTK_WIDGET(parent)->window);

    sprintf(args, "%s --parent 0x%08x%s", binary, (unsigned int) id, user_activated ? " --user" : "");
    return system(args);
}

osso_return_t save_state(osso_context_t *osso_context, gpointer parent)
{
    (void) osso_context;
    (void) parent;

    return OSSO_OK;
}
