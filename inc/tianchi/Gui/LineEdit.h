// **************************************************************************
// Tianchi C++ library for Qt (open source)
// ��ع���Դ���
// ��Ȩ���� (C) ��ع���Դ��⿪����
// ��ȨЭ�飺���Ķ���ع���Դ��⸽������ȨЭ��
// **************************************************************************
// �ĵ�˵����extended QLineEdit widget
// ==========================================================================
// ������־��
// ����         ��Ա        ˵��
// --------------------------------------------------------------------------
// 2013.04.22   XChinux     ����
//
// ==========================================================================
/// @file LineEdit.h extended QLineEdit widget
// ==========================================================================
#ifndef TIANCHI_LINEEDIT_H
#define TIANCHI_LINEEDIT_H

#include <tianchi/Global.h>
#include <QLineEdit>

QT_BEGIN_NAMESPACE
class QPaintEvent;
class QMouseEvent;
class QContextMenuEvent;
QT_END_NAMESPACE

namespace Tianchi
{
class LineEditPrivate;

/// @brief extended QLineEdit widget
/// @author XChinux XChinux@163.com
/// @date 2013-04-22
class TIANCHI_API LineEdit : public QLineEdit
{
    Q_OBJECT

    /// @brief labelText property, shown in non-edit mode
    Q_PROPERTY(QString labelText
            READ labelText
            WRITE setLabelText
            NOTIFY labelTextChanged
            DESIGNABLE true)
    /// @brief data property, save user's data
    Q_PROPERTY(QVariant data
            READ data
            WRITE setData
            NOTIFY dataChanged
            DESIGNABLE false)
public:
    LineEdit(QWidget *parent = 0);
    virtual ~LineEdit();
    QString labelText() const;
    QVariant data() const;
Q_SIGNALS:
    /// @brief emit this signal when labelText property changed
    void labelTextChanged(const QString &labelText);
    /// @brief emit this signal when data property changed
    void dataChanged(const QVariant &userData);
    /// @brief emit this signal when mouse double clicked
    void doubleClicked();
public Q_SLOTS:
    /// @brief set labelText property
    void setLabelText(const QString &labelText);
    /// @brief set data property
    void setData(const QVariant &userData);
protected:
    virtual void paintEvent(QPaintEvent *event);
    virtual void mouseDoubleClickEvent(QMouseEvent *event);
    virtual void contextMenuEvent(QContextMenuEvent *event);
private:
    Q_DISABLE_COPY(LineEdit)
    Q_DECLARE_PRIVATE(LineEdit)
    LineEditPrivate *d_ptr;
};
}

typedef ::Tianchi::LineEdit TcLineEdit;

#endif
