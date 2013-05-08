#ifndef TIANCHI_TCDESIGNERWIDGETS_H
#define TIANCHI_TCDESIGNERWIDGETS_H

#include <QDesignerCustomWidgetCollectionInterface>

class TcDesignerWidgets : public QObject, 
    public QDesignerCustomWidgetCollectionInterface
{
    Q_OBJECT
#if (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
    Q_PLUGIN_METADATA(IID \
            "org.qt-project.Qt.QDesignerCustomWidgetCollectionInterface")
#endif
    Q_INTERFACES(QDesignerCustomWidgetCollectionInterface)
public:
    TcDesignerWidgets(QObject *parent = 0);
    virtual QList<QDesignerCustomWidgetInterface*> customWidgets() const;
private:
    QList<QDesignerCustomWidgetInterface*> m_plugins;
};

#endif
