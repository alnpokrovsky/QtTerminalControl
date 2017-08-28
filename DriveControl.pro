TEMPLATE = app

QT += qml quick serialport
CONFIG += c++11

SOURCES += main.cpp \
    src/driveproperties/serialproperties.cpp \
    src/serialcommunicator/serialcommunicator.cpp \
    src/buttonsmodel/buttonsmodel.cpp \
    src/buttonsmodel/buttonelement/buttonelement.cpp \
    src/fileio/fileio.cpp

RESOURCES += \
    qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    src/driveproperties/serialproperties.h \
    src/qqmlhelpers.h \
    src/serialcommunicator/serialcommunicator.h \
    src/buttonsmodel/buttonsmodel.h \
    src/buttonsmodel/buttonelement/buttonelement.h \
    src/fileio/fileio.h

TRANSLATIONS += QtLanguage_ru.ts
lupdate_only {
    SOURCES +=  qml/main.qml \
                qml/ButtonsModelList/ButtonModelList.qml \
                qml/ButtonsModelList/CreationDialog/CreationDialog.qml \
                qml/ButtonsModelList/CreationDialog/UserButton/UserButton.qml \
                qml/Properties/Properties.qml \
                qml/Terminal/Terminal.qml
}
