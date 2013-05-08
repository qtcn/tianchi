#include <tianchi/gui/tcdateedit.h>
#include <QtPlugin>
#include "tcdateeditplugin.h"

TcDateEditPlugin::TcDateEditPlugin(QObject *parent)
    : QObject(parent), m_initialized(false)
{
}

QString TcDateEditPlugin::name() const
{
    return "TcDateEdit";
}

QString TcDateEditPlugin::includeFile() const
{
    return "tianchi/gui/tcdateedit.h";
}

QString TcDateEditPlugin::group() const
{
    return tr("Tianchi Widgets");
}

QIcon TcDateEditPlugin::icon() const
{
    return QIcon();
}

QString TcDateEditPlugin::toolTip() const
{
    return tr("a date edit widget that can been empty");
}

QString TcDateEditPlugin::whatsThis() const
{
    return tr("a date edit widget that can been empty");
}

bool TcDateEditPlugin::isContainer() const
{
    return false;
}

QWidget* TcDateEditPlugin::createWidget(QWidget *parent)
{
    return new TcDateEdit(parent);
}

bool TcDateEditPlugin::isInitialized() const
{
    return m_initialized;
}

void TcDateEditPlugin::initialize(QDesignerFormEditorInterface * /*core*/)
{
    if (m_initialized)
        return;

    m_initialized = true;
}

QString TcDateEditPlugin::domXml() const
{
    return QString("\
    <ui language=\"c++\">\
        <widget class=\"TcDateEdit\" name=\"tcDateEdit\">\
        </widget>\
    </ui>");
}
