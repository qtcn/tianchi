#include <tianchi/Gui/LineEdit.h>
#include <QtPlugin>
#include "LineEditPlugin.h"

namespace Tianchi
{
LineEditPlugin::LineEditPlugin(QObject *parent)
    : QObject(parent), m_initialized(false)
{
}

QString LineEditPlugin::name() const
{
    return "Tianchi::LineEdit";
}

QString LineEditPlugin::includeFile() const
{
    return "tianchi/Gui/LineEdit.h";
}

QString LineEditPlugin::group() const
{
    return tr("Tianchi Widgets");
}

QIcon LineEditPlugin::icon() const
{
    return QIcon();
}

QString LineEditPlugin::toolTip() const
{
    return tr("a extended QLineEdit widget");
}

QString LineEditPlugin::whatsThis() const
{
    return tr("a extended QLineEdit widget, can show labelText at non-focused");
}

bool LineEditPlugin::isContainer() const
{
    return false;
}

QWidget* LineEditPlugin::createWidget(QWidget *parent)
{
    return new LineEdit(parent);
}


bool LineEditPlugin::isInitialized() const
{
    return m_initialized;
}

void LineEditPlugin::initialize(QDesignerFormEditorInterface * /*core*/)
{
    if (m_initialized)
        return;

    m_initialized = true;
}

QString LineEditPlugin::domXml() const
{
    return QString("\
    <ui language=\"c++\">\
        <widget class=\"Tianchi::LineEdit\" name=\"tcLineEdit\">\
            <property name=\"labelText\">\
                <string>labelText</string>\
            </property>\
            <property name=\"text\">\
                <string>text</string>\
            </property>\
        </widget>\
    </ui>");
}
}
