#include <tianchi/gui/tclineedit.h>
#include <QtPlugin>
#include "tclineeditplugin.h"

TcLineEditPlugin::TcLineEditPlugin(QObject *parent)
    : QObject(parent), m_initialized(false)
{
}

QString TcLineEditPlugin::name() const
{
    return "TcLineEdit";
}

QString TcLineEditPlugin::includeFile() const
{
    return "tianchi/gui/tclineedit.h";
}

QString TcLineEditPlugin::group() const
{
    return tr("Tianchi Widgets");
}

QIcon TcLineEditPlugin::icon() const
{
    return QIcon();
}

QString TcLineEditPlugin::toolTip() const
{
    return tr("a extended QLineEdit widget");
}

QString TcLineEditPlugin::whatsThis() const
{
    return tr("a extended QLineEdit widget, can show labelText at non-focused");
}

bool TcLineEditPlugin::isContainer() const
{
    return false;
}

QWidget* TcLineEditPlugin::createWidget(QWidget *parent)
{
    return new TcLineEdit(parent);
}


bool TcLineEditPlugin::isInitialized() const
{
    return m_initialized;
}

void TcLineEditPlugin::initialize(QDesignerFormEditorInterface * /*core*/)
{
    if (m_initialized)
        return;

    m_initialized = true;
}

QString TcLineEditPlugin::domXml() const
{
    return QString("\
    <ui language=\"c++\">\
        <widget class=\"TcLineEdit\" name=\"tcLineEdit\">\
            <property name=\"labelText\">\
                <string>labelText</string>\
            </property>\
            <property name=\"text\">\
                <string>text</string>\
            </property>\
        </widget>\
    </ui>");
}
