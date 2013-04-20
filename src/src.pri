# ===========================================================================
# 2013.04.17    XChinux created
#
#
# ===========================================================================

TEMPLATE = lib
TARGET = tianchi
QT += sql network script
greaterThan(QT_MAJOR_VERSION, 4) { 
    QT += gui widgets concurrent
    win32:QT += axcontainer
} else {
    QT += gui
    win32:CONFIG += qaxcontainer
    DEFINES += QT_WIDGETS_LIB
}

TC_OUTPUT = $${PWD}/../output

isEmpty(QMAKESPEC) {
win32-g++*     : QMAKESPEC = win32-g++
win32-msvc2005 : QMAKESPEC = win32-msvc2005
win32-msvc2008 : QMAKESPEC = win32-msvc2008
win32-msvc2010 : QMAKESPEC = win32-msvc2010
win32-msvc2012 : QMAKESPEC = win32-msvc2012
linux-g++*     : QMAKESPEC = linux-g++
}

TC_SPEC = $${QT_VERSION}-$${QMAKESPEC}

CONFIG(debug, debug|release) {
    TARGET = $${TARGET}d
}

CONFIG(static, static|shared) | CONFIG(staticlib, staticlib|shared) {
    TC_OUTPUT = $${TC_OUTPUT}/$${TC_SPEC}/static
    DESTDIR = $$TC_OUTPUT
} else { 
    TC_OUTPUT = $${TC_OUTPUT}/$${TC_SPEC}/shared
    DESTDIR = $$TC_OUTPUT
    DEFINES += TIANCHI_EXPORT
    win32:RC_FILE = $$PWD/tianchi.rc
}

CONFIG(debug, debug|release) {
    TC_TMP = $${TC_OUTPUT}/debug
} else {
    TC_TMP = $${TC_OUTPUT}/release
}

MOC_DIR = $$TC_TMP
OBJECTS_DIR = $$TC_TMP
UI_HEADERS_DIR = $$TC_TMP
RCC_DIR = $$TC_TMP

TC_INCL = $$PWD/../inc

INCLUDEPATH += $$TC_INCL

win32:!win32-g++{
    LIBS += -lversion -ladvapi32 -lole32
}

HEADERS += \
    $$TC_INCL/Global.h \
    $$TC_INCL/tianchi.h \
    $$TC_INCL/Chinese/Chinese.h \
    $$TC_INCL/Core/Classes.h \
    $$TC_INCL/Core/Common.h \
    $$TC_INCL/Core/String.h \
    $$TC_INCL/Core/Utils.h \
    $$TC_INCL/File/Json.h \
    $$TC_INCL/File/LogTiny.h \
    $$TC_INCL/File/MSExcel.h \
    $$TC_INCL/File/FileUtils.h \
    $$TC_INCL/Gui/MarqueeLabel.h \
    $$TC_INCL/Gui/ClickLabel.h \
    $$TC_INCL/Gui/DateEdit.h \
    $$TC_INCL/Gui/GuiUtils.h \
    $$TC_INCL/Gui/TreeWidgetHeaderSetupDialog.h \
    $$TC_INCL/Network/DownloadHttp.h \
    $$TC_INCL/Network/SingleInstance.h \
    $$TC_INCL/OS/OS.h \
    $$TC_INCL/Sql/MSSQL.h

SOURCES += \
    $$PWD/Chinese/Chinese.cpp \
    $$PWD/Core/Classes.cpp \
    $$PWD/Core/Utils.cpp \
    $$PWD/Core/Common.cpp \
    $$PWD/Core/String.cpp \
    $$PWD/File/Json.cpp \
    $$PWD/File/LogTiny.cpp \
    $$PWD/File/MSExcel.cpp \
    $$PWD/File/FileUtils.cpp \
    $$PWD/Gui/MarqueeLabel.cpp \
    $$PWD/Gui/ClickLabel.cpp \
    $$PWD/Gui/DateEdit.cpp \
    $$PWD/Gui/TreeWidgetHeaderSetupDialog.cpp \
    $$PWD/Gui/GuiUtils.cpp \
    $$PWD/Network/DownloadHttp.cpp \
    $$PWD/Network/SingleInstance.cpp \
    $$PWD/OS/OS.cpp \
    $$PWD/Sql/MSSQL.cpp
FORMS += \
    $$PWD/Gui/TreeWidgetHeaderSetupDialog.ui

RESOURCES += \
    $$PWD/../res/tianchi.qrc
