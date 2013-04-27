#include <tianchi/Gui/MarqueeLabel.h>
#include <QtPlugin>
#include "MarqueeLabelPlugin.h"

namespace Tianchi
{
MarqueeLabelPlugin::MarqueeLabelPlugin(QObject *parent)
    : QObject(parent), m_initialized(false)
{
}

QString MarqueeLabelPlugin::name() const
{
    return "Tianchi::MarqueeLabel";
}

QString MarqueeLabelPlugin::includeFile() const
{
    return "tianchi/Gui/MarqueeLabel.h";
}

QString MarqueeLabelPlugin::group() const
{
    return tr("Tianchi Widgets");
}

QIcon MarqueeLabelPlugin::icon() const
{
    return QIcon();
}

QString MarqueeLabelPlugin::toolTip() const
{
    return tr("a marquee label widget");
}

QString MarqueeLabelPlugin::whatsThis() const
{
    return tr("a marquee label widget");
}

bool MarqueeLabelPlugin::isContainer() const
{
    return false;
}

QWidget* MarqueeLabelPlugin::createWidget(QWidget *parent)
{
    return new MarqueeLabel(parent);
}

bool MarqueeLabelPlugin::isInitialized() const
{
    return m_initialized;
}

void MarqueeLabelPlugin::initialize(QDesignerFormEditorInterface * /*core*/)
{
    if (m_initialized)
        return;

    m_initialized = true;
}

QString MarqueeLabelPlugin::domXml() const
{
    return QString("\
    <ui language=\"c++\">\
        <widget class=\"Tianchi::MarqueeLabel\" name=\"tcMarqueeLabel\">\
            <property name=\"text\">\
                <string><![CDATA[<a href=\"http://www.qtcn.org\">qtcn.org</a>]]></string>\
            </property>\
        </widget>\
    </ui>");
}
}
