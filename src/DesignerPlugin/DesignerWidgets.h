#ifndef TIANCHI_DESIGNERWIDGETS_H
#define TIANCHI_DESIGNERWIDGETS_H

#include <QDesignerCustomWidgetCollectionInterface>

namespace Tianchi
{
class DesignerWidgets : public QObject, 
    public QDesignerCustomWidgetCollectionInterface
{
    Q_OBJECT
#if (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
    Q_PLUGIN_METADATA(IID \
            "org.qt-project.Qt.QDesignerCustomWidgetCollectionInterface")
#endif
    Q_INTERFACES(QDesignerCustomWidgetCollectionInterface)
public:
    DesignerWidgets(QObject *parent = 0);
    virtual QList<QDesignerCustomWidgetInterface*> customWidgets() const;
private:
    QList<QDesignerCustomWidgetInterface*> m_plugins;
};
}

#endif
