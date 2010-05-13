TEMPLATE = lib
SOURCES = plugin.c
TARGET = autodisconnect

CONFIG += plugin link_pkgconfig
PKGCONFIG += gtk+-2.0 libosso

INSTALLS += target
target.path = $$(DESTDIR)$$system(pkg-config hildon-control-panel --variable=pluginlibdir)
INSTALLS += desktop
desktop.path = $$(DESTDIR)$$system(pkg-config hildon-control-panel --variable=plugindesktopentrydir)
desktop.files = data/autodisconnect.desktop
