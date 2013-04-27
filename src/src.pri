# ===========================================================================
# 2013.04.17    XChinux created
#
#
# ===========================================================================

TEMPLATE = lib
TARGET = tianchi
QT += gui sql network script
greaterThan(QT_MAJOR_VERSION, 4) {
    QT += widgets concurrent
    win32:QT += axcontainer
} else {
    win32:CONFIG += qaxcontainer
    DEFINES += QT_WIDGETS_LIB
}

TC_OUTPUT = $${PWD}/../output

TC_SPEC = qt$${QT_VERSION}

win32-g++*     : TC_SPEC = $${TC_SPEC}-mingw32
win32-msvc2005 : TC_SPEC = $${TC_SPEC}-vc2005_x86
win32-msvc2008 : TC_SPEC = $${TC_SPEC}-vc2008_x86
win32-msvc2010 : TC_SPEC = $${TC_SPEC}-vc2010_x86
win32-msvc2012 : TC_SPEC = $${TC_SPEC}-vc2012_x86


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
    win32 {
        RC_FILE = $$PWD/tianchi.rc
    } else {
        VERSION = 0.0.1
    }
}

CONFIG(debug, debug|release) {
    TC_TMP = $${TC_OUTPUT}/debug
} else {
    TC_TMP = $${TC_OUTPUT}/release
}

MOC_DIR = $$TC_TMP
OBJECTS_DIR = $$TC_TMP
UI_DIR = $$TC_TMP
RCC_DIR = $$TC_TMP

TC_INCL = $$PWD/../inc

INCLUDEPATH += $$TC_INCL

# g++ pch header
win32-g++* : PRECOMPILED_HEADER = $$PWD/../src/tianchi_gcc_pch.h
linux-g++* : PRECOMPILED_HEADER = $$PWD/../src/tianchi_gcc_pch.h
macx-g++*  : PRECOMPILED_HEADER = $$PWD/../src/tianchi_gcc_pch.h

win32:LIBS += -lversion
win32-msvc*:LIBS += -ladvapi32 -lole32

HEADERS += \
    $$TC_INCL/tianchi/Global.h \
    $$TC_INCL/tianchi.h \
    $$TC_INCL/tianchi/Chinese/Chinese.h \
    $$TC_INCL/tianchi/Core/Classes.h \
    $$TC_INCL/tianchi/Core/Common.h \
    $$TC_INCL/tianchi/Core/String.h \
    $$TC_INCL/tianchi/Core/Utils.h \
    $$TC_INCL/tianchi/File/Json.h \
    $$TC_INCL/tianchi/File/LogTiny.h \
    $$TC_INCL/tianchi/File/MSExcel.h \
    $$TC_INCL/tianchi/File/FileUtils.h \
    $$TC_INCL/tianchi/Gui/MarqueeLabel.h \
    $$TC_INCL/tianchi/Gui/ClickLabel.h \
    $$TC_INCL/tianchi/Gui/LineEdit.h \
    $$TC_INCL/tianchi/Gui/FlowLayout.h \
    $$TC_INCL/tianchi/Gui/GlowEffect.h \
    $$TC_INCL/tianchi/Gui/DateEdit.h \
    $$TC_INCL/tianchi/Gui/GuiUtils.h \
    $$TC_INCL/tianchi/Gui/TreeWidgetHeaderSetupDialog.h \
    $$TC_INCL/tianchi/Network/DownloadHttp.h \
    $$TC_INCL/tianchi/Network/SingleInstance.h \
    $$TC_INCL/tianchi/OS/OS.h \
    $$TC_INCL/tianchi/Sql/MSSQL.h \
    $$TC_INCL/tianchi/File/Directory.h

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
    $$PWD/Gui/LineEdit.cpp \
    $$PWD/Gui/FlowLayout.cpp \
    $$PWD/Gui/GlowEffect.cpp \
    $$PWD/Gui/DateEdit.cpp \
    $$PWD/Gui/TreeWidgetHeaderSetupDialog.cpp \
    $$PWD/Gui/GuiUtils.cpp \
    $$PWD/Network/DownloadHttp.cpp \
    $$PWD/Network/SingleInstance.cpp \
    $$PWD/OS/OS.cpp \
    $$PWD/Sql/MSSQL.cpp \
    $$PWD/File/Directory.cpp

FORMS += \
    $$PWD/Gui/TreeWidgetHeaderSetupDialog.ui

RESOURCES += \
    $$PWD/../res/tianchi.qrc
