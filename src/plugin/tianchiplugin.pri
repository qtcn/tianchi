include($$PWD/../plugin.pri)

TARGET = tianchidesignerplugin
DEPENDPATH += .
greaterThan(QT_MAJOR_VERSION, 4) {

    greaterThan(QT_MAJOR_VERSION, 5) {
        QT += widgets designer concurrent
        PLUGIN_TYPE = designer
        CONFIG += tool_plugin c++17
        PLUGIN_CLASS_NAME = TcDesignerWidgets
    }
    else
    {
        QT += widgets designer concurrent
        PLUGIN_TYPE = designer
        CONFIG += tool_plugin
        PLUGIN_CLASS_NAME = TcDesignerWidgets
    }
} else {
    CONFIG += designer plugin
}


CONFIG(debug, debug|release) {
    TC_TMP = $${TC_OUTPUT}/debug_tianchiplugin
    TARGET = $${TARGET}d
} else {
    TC_TMP = $${TC_OUTPUT}/release_tianchiplugin
    target.path = $$[QT_INSTALL_PLUGINS]/designer
    INSTALLS += target
}

MOC_DIR = $$TC_TMP
OBJECTS_DIR = $$TC_TMP
UI_DIR = $$TC_TMP
RCC_DIR = $$TC_TMP



HEADERS += $$PWD/tclineeditplugin.h      $$TC_INCL/tianchi/gui/tclineedit.h \
            $$PWD/tcmarqueelabelplugin.h $$TC_INCL/tianchi/gui/tcmarqueelabel.h \
            $$PWD/tcclicklabelplugin.h   $$TC_INCL/tianchi/gui/tcclicklabel.h \
            $$PWD/tcdateeditplugin.h     $$TC_INCL/tianchi/gui/tcdateedit.h \
            $$TC_INCL/tianchi/core/tcutils.h \
            $$PWD/tcdesignerwidgets.h
SOURCES += $$PWD/tclineeditplugin.cpp      $$TC_SRC/gui/tclineedit.cpp \
            $$PWD/tcmarqueelabelplugin.cpp $$TC_SRC/gui/tcmarqueelabel.cpp \
            $$PWD/tcclicklabelplugin.cpp   $$TC_SRC/gui/tcclicklabel.cpp \
            $$PWD/tcdateeditplugin.cpp     $$TC_SRC/gui/tcdateedit.cpp \
            $$TC_SRC/core/tcutils.cpp \
            $$PWD/tcdesignerwidgets.cpp
