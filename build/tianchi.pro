# ===========================================================================
# Date          Qt / OS / Compiler              Name        Description
# ---------------------------------------------------------------------------
# 2013.04.15    Qt5.0.1-x32 / Win8 / VC2010     Jonix       编译dll成功
#               Qt5.0.2-x64 / Win8 / VC2012     Jonix       编译dll成功
# 2013.04.17    Qt5.0.2-x86 / Win7 / VC2010     XChinux     编译dll成功
#               Qt5.0.2-x86 / Win7 / MinGW      XChinux     编译dll成功
#               Qt4.8.4-x86 / Win7 / VC2010     XChinux     编译dll成功
#               Qt4.8.4-x86 / OpenSuse 12.3 / GCC 4.7.2    
#                                               XChinux     编译.so成功
#               Qt5.0.1-x86 / OpenSuse 12.3 / GCC 4.7.2
#                                               XChinux     编译.so成功
#
#
#
# ===========================================================================
CONFIG += shared
include($$PWD/../src/src.pri)
