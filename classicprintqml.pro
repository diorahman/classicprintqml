
TEMPLATE = app

CONFIG += debug

QT += declarative xml

OBJECTS_DIR = build
MOC_DIR = build
RCC_DIR = build

# Deployment on MeeGo Harmattan
target.path = /opt/classicprintqml/bin
INSTALLS += target

icon.path = /opt/classicprintqml
icon.files = classicprintqml.png
INSTALLS += icon

desktop.path = /usr/share/applications
desktop.files = classicprintqml.desktop
INSTALLS += desktop


# Main application
DEPENDPATH += .
INCLUDEPATH += .
HEADERS += $$files(*.h)
SOURCES += $$files(*.cpp)
RESOURCES += $$files(*.qrc)

# Qt Image Filters (ftp://ftp.trolltech.com/pub/qt/solutions/lgpl/)
DEPENDPATH += imagefilters-2.1/src
INCLUDEPATH += imagefilters-2.1/src
HEADERS += $$files(imagefilters-2.1/src/*.h)
SOURCES += $$files(imagefilters-2.1/src/*.cpp)

# ClassicPrint (https://garage.maemo.org/projects/classicprint/)
DEPENDPATH += classicprint-0.1
INCLUDEPATH += classicprint-0.1
HEADERS += $$files(classicprint-0.1/*.h)
SOURCES += $$files(classicprint-0.1/*.cpp)
RESOURCES += $$files(classicprint-0.1/*.qrc)

