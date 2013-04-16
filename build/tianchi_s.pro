# ======================================================================================================================
# Date          Qt / OS / Compiler              Name        Description
# ----------------------------------------------------------------------------------------------------------------------
# 2013.04.15    Qt5.0.1-x32 / Win8 / VC2010     Jonix       ±‡“Îæ≤Ã¨¡¥Ω”ø‚(.lib)≥…π¶
#               Qt5.0.2-x64 / Win8 / VC2012     Jonix       ±‡“Îæ≤Ã¨¡¥Ω”ø‚(.lib)≥…π¶
#
#
#
# ======================================================================================================================
QT += sql network script
greaterThan(QT_MAJOR_VERSION, 4) { 
    QT += widgets
    win32:QT += axcontainer
} else {
    QT += gui
    win32:CONFIG += qaxcontainer
    DEFINES += QT_WIDGETS_LIB
}

DESTDIR = ../staticlib
TARGET = tianchi
TEMPLATE = lib

# …˙≥…æ≤Ã¨¡¥Ω”ø‚
CONFIG += staticlib

DEFINES -= TIANCHI_EXPORT TIANCHI_IMPORT

INCLUDEPATH += ../inc

win32:!win32-g++{
    LIBS += -lversion -ladvapi32 -lole32
}

HEADERS +=\
    ../inc/Chinese/msime.h \
    ../inc/Core/Classes.h \
    ../inc/Core/Global.h \
    ../inc/Core/Utils.h \
    ../inc/File/Json.h \
    ../inc/File/LogTiny.h \
    ../inc/File/MSExcel.h \
    ../inc/Gui/DateEdit.h \
    ../inc/Gui/TreeWidgetHeaderSetupDialog.h \
    ../inc/Chinese/Chinese.h \
    ../inc/OS/OS.h \
    ../inc/Global.h \
    ../inc/Core/Common.h \
    ../inc/Gui/GuiUtils.h \
    ../inc/File/FileUtils.h \
    ../inc/tianchi.h \
    ../inc/Core/String.h

SOURCES += \
    ../src/Core/Classes.cpp \
    ../src/Core/Utils.cpp \
    ../src/File/Json.cpp \
    ../src/File/LogTiny.cpp \
    ../src/File/MSExcel.cpp \
    ../src/Gui/DateEdit.cpp \
    ../src/Gui/TreeWidgetHeaderSetupDialog.cpp \
    ../src/OS/OS.cpp \
    ../src/Chinese/Chinese.cpp \
    ../src/Core/Common.cpp \
    ../src/Gui/GuiUtils.cpp \
    ../src/File/FileUtils.cpp \
    ../src/Core/String.cpp

FORMS += \
    ../src/Gui/TreeWidgetHeaderSetupDialog.ui

RESOURCES += \
    ../res/tianchi.qrc

#symbian {
#    MMP_RULES += EXPORTUNFROZEN
#    TARGET.UID3 = 0xEEA5DB7F
#    TARGET.CAPABILITY =
#    TARGET.EPOCALLOWDLLDATA = 1
#    addFiles.sources = TianChi.dll
#    addFiles.path = !:/sys/bin
#    DEPLOYMENT += addFiles
#}

#unix:!symbian {
#    maemo5 {
#        target.path = /opt/usr/lib
#    } else {
#        target.path = /usr/lib
#    }
#    INSTALLS += target
#}
