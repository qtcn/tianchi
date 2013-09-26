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

TC_INCL = $$PWD/../include

INCLUDEPATH += $$TC_INCL

# g++ pch header
win32-g++* : PRECOMPILED_HEADER = $$PWD/../src/tianchi_gcc_pch.h
linux-g++* : PRECOMPILED_HEADER = $$PWD/../src/tianchi_gcc_pch.h
macx-g++*  : PRECOMPILED_HEADER = $$PWD/../src/tianchi_gcc_pch.h

win32:LIBS += -lversion
win32-msvc*:LIBS += -ladvapi32 -lole32


HEADERS += \
    $$TC_INCL/tianchi.h \
    $$TC_INCL/tianchi/tcglobal.h \
    $$TC_INCL/tianchi/chinese/tcchinese.h \
    $$TC_INCL/tianchi/core/tcclasses.h \
    $$TC_INCL/tianchi/core/tccommon.h \
    $$TC_INCL/tianchi/core/tcstring.h \
    $$TC_INCL/tianchi/core/tcutils.h \
    $$TC_INCL/tianchi/core/tcvariantmaptablemodel.h \
    $$TC_INCL/tianchi/core/tcfunctionalsortfilterproxymodel.h \
    $$TC_INCL/tianchi/core/tcsingleton.hpp \
    $$TC_INCL/tianchi/core/tctuple.hpp \
    $$TC_INCL/tianchi/core/tcmath.h \
    $$TC_INCL/tianchi/file/tcjson.h \
    $$TC_INCL/tianchi/file/tclog.h \
    $$TC_INCL/tianchi/file/tcmsexcel.h \
    $$TC_INCL/tianchi/file/tcexcelreader.h \
    $$TC_INCL/tianchi/file/tcfile.h \
    $$TC_INCL/tianchi/file/tcfileio.h \
    $$TC_INCL/tianchi/file/tcdir.h \
    $$TC_INCL/tianchi/gui/tcclicklabel.h \
    $$TC_INCL/tianchi/gui/tclineedit.h \
    $$TC_INCL/tianchi/gui/tcformutils.h \
    $$TC_INCL/tianchi/gui/tcflowlayout.h \
    $$TC_INCL/tianchi/gui/tcmarqueelabel.h \
    $$TC_INCL/tianchi/gui/tcgloweffect.h \
    $$TC_INCL/tianchi/gui/tcdateedit.h \
    $$TC_INCL/tianchi/gui/tcguiutils.h \
    $$TC_INCL/tianchi/gui/tcheadersetupdialog.h \
    $$TC_INCL/tianchi/gui/tcsortpaginationtableview.h \
    $$TC_INCL/tianchi/network/tcdownloadhttp.h \
    $$TC_INCL/tianchi/network/tcsingleinstance.h \
    $$TC_INCL/tianchi/network/tcudp.h \
    $$TC_INCL/tianchi/os/tcos.h \
    $$TC_INCL/tianchi/sql/tcdataaccess.h \
    $$TC_INCL/tianchi/sql/tcmssql.h \
    $$TC_INCL/tianchi/sql/tcoracle.h \
    $$TC_INCL/tianchi/sql/tcdatabase.h \
    $$TC_INCL/tianchi/widget/tctreeex.h
SOURCES += \
    $$PWD/chinese/tcchinese.cpp \
    $$PWD/core/tcclasses.cpp \
    $$PWD/core/tcutils.cpp \
    $$PWD/core/tccommon.cpp \
    $$PWD/core/tcstring.cpp \
    $$PWD/core/tcvariantmaptablemodel.cpp \
    $$PWD/core/tcfunctionalsortfilterproxymodel.cpp \
    $$PWD/core/tcmath.cpp \
    $$PWD/file/tcjson.cpp \
    $$PWD/file/tclog.cpp \
    $$PWD/file/tcmsexcel.cpp \
    $$PWD/file/tcexcelreader.cpp \
    $$PWD/file/tcfile.cpp \
    $$PWD/file/tcfileio.cpp \
    $$PWD/file/tcdir.cpp \
    $$PWD/gui/tcclicklabel.cpp \
    $$PWD/gui/tclineedit.cpp \
    $$PWD/gui/tcflowlayout.cpp \
    $$PWD/gui/tcgloweffect.cpp \
    $$PWD/gui/tcmarqueelabel.cpp \
    $$PWD/gui/tcdateedit.cpp \
    $$PWD/gui/tcheadersetupdialog.cpp \
    $$PWD/gui/tcguiutils.cpp \
    $$PWD/gui/tcformutils.cpp \
    $$PWD/gui/tcsortpaginationtableview.cpp \
    $$PWD/network/tcdownloadhttp.cpp \
    $$PWD/network/tcsingleinstance.cpp \
    $$PWD/network/tcudp.cpp \
    $$PWD/os/tcos.cpp \
    $$PWD/sql/tcdataaccess.cpp \
    $$PWD/sql/tcdatabase.cpp \
    $$PWD/sql/tcmssql.cpp \
    $$PWD/sql/tcoracle.cpp \
    $$PWD/widget/tctreeex.cpp
FORMS += \
    $$PWD/gui/tcheadersetupdialog.ui

RESOURCES += \
    $$PWD/../res/tianchi.qrc

include($$PWD/3rdparty/3rdparty.pri)
