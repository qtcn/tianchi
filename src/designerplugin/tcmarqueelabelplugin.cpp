#include <tianchi/gui/tcmarqueelabel.h>
#include <QtPlugin>
#include "tcmarqueelabelplugin.h"

TcMarqueeLabelPlugin::TcMarqueeLabelPlugin(QObject *parent)
    : QObject(parent), m_initialized(false)
{
}

QString TcMarqueeLabelPlugin::name() const
{
    return "TcMarqueeLabel";
}

QString TcMarqueeLabelPlugin::includeFile() const
{
    return "tianchi/gui/tcmarqueelabel.h";
}

QString TcMarqueeLabelPlugin::group() const
{
    return tr("Tianchi Widgets");
}

QIcon TcMarqueeLabelPlugin::icon() const
{
    return QIcon();
}

QString TcMarqueeLabelPlugin::toolTip() const
{
    return tr("a marquee label widget");
}

QString TcMarqueeLabelPlugin::whatsThis() const
{
    return tr("a marquee label widget");
}

bool TcMarqueeLabelPlugin::isContainer() const
{
    return false;
}

QWidget* TcMarqueeLabelPlugin::createWidget(QWidget *parent)
{
    return new TcMarqueeLabel(parent);
}

bool TcMarqueeLabelPlugin::isInitialized() const
{
    return m_initialized;
}

void TcMarqueeLabelPlugin::initialize(QDesignerFormEditorInterface * /*core*/)
{
    if (m_initialized)
        return;

    m_initialized = true;
}

QString TcMarqueeLabelPlugin::domXml() const
{
    return QString("\
    <ui language=\"c++\">\
        <widget class=\"TcMarqueeLabel\" name=\"tcMarqueeLabel\">\
            <property name=\"text\">\
                <string><![CDATA[<a href=\"http://www.qtcn.org\">qtcn.org</a>]]></string>\
            </property>\
        </widget>\
    </ui>");
}
