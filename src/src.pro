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
PKGCONFIG += gconf-2.0
QT = core \
    gui \
    maemo5
	
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
INSTALLS += autodisconnect-network-runner
autodisconnect-network-runner.path = $$PREFIX/opt/autodisconnect
autodisconnect-network-runner.files = data/scripts/autodisconnect_runner_network
INSTALLS += autodisconnect-network-check
autodisconnect-network-check.path = $$PREFIX/opt/autodisconnect
autodisconnect-network-check.files = data/scripts/autodisconnect-network-check
INSTALLS += autodisconnect-bluetooth-runner
autodisconnect-bluetooth-runner.path = $$PREFIX/opt/autodisconnect
autodisconnect-bluetooth-runner.files = data/scripts/autodisconnect_runner_bluetooth
INSTALLS += autodisconnect-network-bluetooth
autodisconnect-network-bluetooth.path = $$PREFIX/opt/autodisconnect
autodisconnect-network-bluetooth.files = data/scripts/autodisconnect-bluetooth-check
