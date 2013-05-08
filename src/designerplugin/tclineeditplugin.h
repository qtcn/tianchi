#ifndef TIANCHI_TCLINEEDITPLUGIN_H
#define TIANCHI_TCLINEEDITPLUGIN_H

#include <QDesignerCustomWidgetInterface>

class TcLineEditPlugin : public QObject, public QDesignerCustomWidgetInterface
{
    Q_OBJECT
    Q_INTERFACES(QDesignerCustomWidgetInterface)
public:
    TcLineEditPlugin(QObject *parent = 0);
    virtual QString name() const;
    virtual QString includeFile() const;
    virtual QString group() const;
    virtual QIcon icon() const;
    virtual QString toolTip() const;
    virtual QString whatsThis() const;
    virtual bool isContainer() const;
    virtual QWidget *createWidget(QWidget *parent);

    virtual bool isInitialized() const;
    virtual QString domXml() const;
    virtual void initialize(QDesignerFormEditorInterface *formEditor);
private:
    bool m_initialized;
};

#endif
