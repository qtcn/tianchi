# ===========================================================================
# Date          Qt / OS / Compiler              Name        Description
# ---------------------------------------------------------------------------
# 2013.04.15    Qt5.0.1-x32 / Win8 / VC2010     Jonix       编译(dll/lib)成功
#               Qt5.0.2-x64 / Win8 / VC2012     Jonix       编译(dll/lib)成功
#
#
#
# ===========================================================================

TEMPLATE = lib
TARGET = tianchi
QT += sql network script
greaterThan(QT_MAJOR_VERSION, 4) { 
    QT += gui widgets
    win32:QT += axcontainer
} else {
    QT += gui
    win32:CONFIG += qaxcontainer
    DEFINES += QT_WIDGETS_LIB
}

TC_TMP = $$PWD/../tmp

CONFIG(debug, debug|release) {
    TARGET = $${TARGET}d
    TC_TMP = $${TC_TMP}/debug
} else {
    TC_TMP = $${TC_TMP}/release
}

CONFIG(static, static|shared) | CONFIG(staticlib, staticlib|shared) {
    DESTDIR = $$PWD/../dll_lib
    TARGET = $${TARGET}_s
} else { 
    DESTDIR = $$PWD/../dll_lib
    DEFINES += TIANCHI_EXPORT
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
    $$TC_INCL/Gui/ClickLabel.h \
    $$TC_INCL/Gui/DateEdit.h \
    $$TC_INCL/Gui/GuiUtils.h \
    $$TC_INCL/Gui/TreeWidgetHeaderSetupDialog.h \
    $$TC_INCL/OS/OS.h
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
    $$PWD/Gui/ClickLabel.cpp \
    $$PWD/Gui/DateEdit.cpp \
    $$PWD/Gui/TreeWidgetHeaderSetupDialog.cpp \
    $$PWD/Gui/GuiUtils.cpp \
    $$PWD/OS/OS.cpp
FORMS += \
    $$PWD/Gui/TreeWidgetHeaderSetupDialog.ui

RESOURCES += \
    $$PWD/../res/tianchi.qrc
