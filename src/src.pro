TARGET = autodisconnect
HEADERS += src/mainwindow.h \
    src/utils.h
SOURCES += src/qtmain.cpp \
    src/mainwindow.cpp \
    src/utils.cpp
FORMS += uis/mainwindow.ui

# LEXS#
LEXSOURCES += 

# YACCS#
YACCSOURCES += 
INCLUDEPATH +=
LIBS +=
DEFINES += 

# All generated files goes same directory
DEPENDPATH += 
VPATH += src \
    uis
CONFIG -= 
CONFIG += debug \
    link_pkgconfig
PKGCONFIG += gconf-2.0 \
    libnotify
QT = core \
    gui
	
PREFIX = /../../debian/autodisconnect/
	
INSTALLS += target
target.path = $$PREFIX/opt/autodisconnect
INSTALLS += desktop
desktop.path = $$PREFIX/usr/share/applications/hildon
desktop.files = data/autodisconnect.desktop
INSTALLS += service
service.path = $$PREFIX/usr/share/dbus-1/services
service.files = data/autodisconnect.service
INSTALLS += icon64
icon64.path = $$PREFIX/usr/share/icons/hicolor/64x64/apps
icon64.files = data/64x64/autodisconnect.png
INSTALLS += icon48
icon48.path = $$PREFIX/usr/share/icons/hicolor/48x48/apps
icon48.files = data/48x48/autodisconnect.png
INSTALLS += autodisconnect-up
autodisconnect-up.path = $$PREFIX/etc/network/if-up.d/
autodisconnect-up.files = data/scripts/if-up.d/99_autodisconnect
INSTALLS += autodisconnect-check
autodisconnect-check.path = $$PREFIX/opt/autodisconnect
autodisconnect-check.files = data/scripts/autodisconnect-check
