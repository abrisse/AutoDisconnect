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
CONFIG += debug link_pkgconfig
PKGCONFIG += gconf-2.0
QT = core gui maemo5
		
INSTALLS += target
target.path = $$(DESTDIR)/opt/autodisconnect
INSTALLS += icon64
icon64.path = $$(DESTDIR)/usr/share/icons/hicolor/64x64/apps
icon64.files = data/64x64/autodisconnect.png
INSTALLS += icon48
icon48.path = $$(DESTDIR)/usr/share/icons/hicolor/48x48/apps
icon48.files = data/48x48/autodisconnect.png
INSTALLS += autodisconnect-network-runner
autodisconnect-network-runner.path = $$(DESTDIR)/opt/autodisconnect
autodisconnect-network-runner.files = data/scripts/autodisconnect_runner_network
INSTALLS += autodisconnect-network-check
autodisconnect-network-check.path = $$(DESTDIR)/opt/autodisconnect
autodisconnect-network-check.files = data/scripts/autodisconnect-network-check
INSTALLS += autodisconnect-network-pre-runner
autodisconnect-network-pre-runner.path = $$(DESTDIR)/opt/autodisconnect
autodisconnect-network-pre-runner.files = data/scripts/autodisconnect_runner_pre_network
INSTALLS += autodisconnect-pre-network-check
autodisconnect-pre-network-check.path = $$(DESTDIR)/opt/autodisconnect
autodisconnect-pre-network-check.files = data/scripts/autodisconnect-pre-network-check
INSTALLS += autodisconnect-network-post-runner
autodisconnect-network-post-runner.path = $$(DESTDIR)/opt/autodisconnect
autodisconnect-network-post-runner.files = data/scripts/autodisconnect_runner_post_network
INSTALLS += autodisconnect-post-network-check
autodisconnect-post-network-check.path = $$(DESTDIR)/opt/autodisconnect
autodisconnect-post-network-check.files = data/scripts/autodisconnect-post-network-check
INSTALLS += autodisconnect-bluetooth-runner
autodisconnect-bluetooth-runner.path = $$(DESTDIR)/opt/autodisconnect
autodisconnect-bluetooth-runner.files = data/scripts/autodisconnect_runner_bluetooth
INSTALLS += autodisconnect-network-bluetooth
autodisconnect-network-bluetooth.path = $$(DESTDIR)/opt/autodisconnect
autodisconnect-network-bluetooth.files = data/scripts/autodisconnect-bluetooth-check
