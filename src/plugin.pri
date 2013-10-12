TEMPLATE = lib

TC_OUTPUT = $${PWD}/../output

TC_SPEC = qt$${QT_VERSION}

win32-g++*     : TC_SPEC = $${TC_SPEC}-mingw32
win32-msvc2005 : TC_SPEC = $${TC_SPEC}-vc2005_x86
win32-msvc2008 : TC_SPEC = $${TC_SPEC}-vc2008_x86
win32-msvc2010 : TC_SPEC = $${TC_SPEC}-vc2010_x86
win32-msvc2012 : TC_SPEC = $${TC_SPEC}-vc2012_x86

win32 {
    RC_FILE = $$PWD/plugin.rc
} else {
    VERSION = 0.0.2
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
