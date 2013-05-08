#include <tianchi/gui/tcclicklabel.h>
#include <QtPlugin>
#include "tcclicklabelplugin.h"

TcClickLabelPlugin::TcClickLabelPlugin(QObject *parent)
    : QObject(parent), m_initialized(false)
{
}

QString TcClickLabelPlugin::name() const
{
    return "TcClickLabel";
}

QString TcClickLabelPlugin::includeFile() const
{
    return "tianchi/gui/tcclicklabel.h";
}

QString TcClickLabelPlugin::group() const
{
    return tr("Tianchi Widgets");
}

QIcon TcClickLabelPlugin::icon() const
{
    return QIcon();
}

QString TcClickLabelPlugin::toolTip() const
{
    return tr("a clickable label widget");
}

QString TcClickLabelPlugin::whatsThis() const
{
    return tr("emit clicked() label widget when mouse clicked");
}

bool TcClickLabelPlugin::isContainer() const
{
    return false;
}

QWidget* TcClickLabelPlugin::createWidget(QWidget *parent)
{
    return new TcClickLabel(parent);
}

bool TcClickLabelPlugin::isInitialized() const
{
    return m_initialized;
}

void TcClickLabelPlugin::initialize(QDesignerFormEditorInterface * /*core*/)
{
    if (m_initialized)
        return;

    m_initialized = true;
}

QString TcClickLabelPlugin::domXml() const
{
    return QString("\
    <ui language=\"c++\">\
        <widget class=\"TcClickLabel\" name=\"tcClickLabel\">\
            <property name=\"text\">\
                <string>clickText</string>\
            </property>\
        </widget>\
    </ui>");
}
