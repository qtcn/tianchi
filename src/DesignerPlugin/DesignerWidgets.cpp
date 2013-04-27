#include <QtPlugin>
#include "DesignerWidgets.h"
#include "DateEditPlugin.h"
#include "LineEditPlugin.h"
#include "ClickLabelPlugin.h"
#include "MarqueeLabelPlugin.h"

namespace Tianchi
{
DesignerWidgets::DesignerWidgets(QObject *parent)
    : QObject(parent)
{
    m_plugins.append(new DateEditPlugin(this));
    m_plugins.append(new LineEditPlugin(this));
    m_plugins.append(new ClickLabelPlugin(this));
    m_plugins.append(new MarqueeLabelPlugin(this));
}

QList<QDesignerCustomWidgetInterface*> DesignerWidgets::customWidgets() 
    const
{
    return m_plugins;
}
}

#if (QT_VERSION < QT_VERSION_CHECK(5, 0, 0))
Q_EXPORT_PLUGIN(Tianchi::DesignerWidgets)
#endif
