#include <QtPlugin>
#include "tcdesignerwidgets.h"
#include "tcdateeditplugin.h"
#include "tclineeditplugin.h"
#include "tcclicklabelplugin.h"
#include "tcmarqueelabelplugin.h"

TcDesignerWidgets::TcDesignerWidgets(QObject *parent)
    : QObject(parent)
{
    m_plugins.append(new TcDateEditPlugin(this));
    m_plugins.append(new TcLineEditPlugin(this));
    m_plugins.append(new TcClickLabelPlugin(this));
    m_plugins.append(new TcMarqueeLabelPlugin(this));
}

QList<QDesignerCustomWidgetInterface*> TcDesignerWidgets::customWidgets() 
    const
{
    return m_plugins;
}

#if (QT_VERSION < QT_VERSION_CHECK(5, 0, 0))
Q_EXPORT_PLUGIN(TcDesignerWidgets)
#endif
