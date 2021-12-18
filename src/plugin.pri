TEMPLATE = lib

TC_OUTPUT = $${PWD}/../output

TC_SPEC = qt$${QT_VERSION}
greaterThan(QT_MAJOR_VERSION, 5) {
    CONFIG += c++17
    QMAKE_CFLAGS_UTF8_SOURCE -= -utf-8
}

win32-g++*     : TC_SPEC = $${TC_SPEC}-mingw32
win32-msvc2005 : TC_SPEC = $${TC_SPEC}-vc2005_x86
win32-msvc2008 : TC_SPEC = $${TC_SPEC}-vc2008_x86
win32-msvc2010 : TC_SPEC = $${TC_SPEC}-vc2010_x86
win32-msvc2012 : TC_SPEC = $${TC_SPEC}-vc2012_x86
win32-msvc2013 : TC_SPEC = $${TC_SPEC}-vc2013_x86
win32-msvc2015 : TC_SPEC = $${TC_SPEC}-vc2015_x86
win32-msvc {
    greaterThan(QMAKE_MSC_VER, 1909) {
        greaterThan(QMAKE_MSC_VER, 1919) {
            TC_SPEC = $${TC_SPEC}-vc2019_x86
        } else {
            TC_SPEC = $${TC_SPEC}-vc2017_x86
        }
    }


}
contains(DEFINES, WIN64) : TC_SPEC = $${TC_SPEC}_64

win32 {
    RC_FILE = $$PWD/plugin.rc
} else {
    VERSION = 0.0.3
}

TC_OUTPUT = $${TC_OUTPUT}/$${TC_SPEC}/shared
DESTDIR = $$TC_OUTPUT

TC_INCL = $$PWD/../include
TC_SRC = $$PWD/../src

INCLUDEPATH += . $$TC_INCL

# g++ pch header
win32-g++* : PRECOMPILED_HEADER = $$PWD/../src/tianchi_gcc_pch.h
linux-g++* : PRECOMPILED_HEADER = $$PWD/../src/tianchi_gcc_pch.h
macx-g++*  : PRECOMPILED_HEADER = $$PWD/../src/tianchi_gcc_pch.h

include($$PWD/../src/3rdparty/libqqwry/qqwry.pri)
