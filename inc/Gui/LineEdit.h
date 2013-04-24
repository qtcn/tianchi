// **************************************************************************
// Tianchi C++ library for Qt (open source)
// 天池共享源码库
// 版权所有 (C) 天池共享源码库开发组
// 授权协议：请阅读天池共享源码库附带的授权协议
// **************************************************************************
// 文档说明：extended QLineEdit widget
// ==========================================================================
// 开发日志：
// 日期         人员        说明
// --------------------------------------------------------------------------
// 2013.04.22   XChinux     建立
//
// ==========================================================================
/// @file LineEdit.h extended QLineEdit widget
// ==========================================================================
#ifndef TIANCHI_LINEEDIT_H
#define TIANCHI_LINEEDIT_H

#include <Global.h>
#include <QLineEdit>

QT_BEGIN_NAMESPACE
class QPaintEvent;
class QMouseEvent;
class QContextMenuEvent;
QT_END_NAMESPACE

TIANCHI_BEGIN_HEADER
TIANCHI_BEGIN_NAMESPACE

class LineEditPrivate;

QT_USE_NAMESPACE

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

TIANCHI_END_NAMESPACE
TIANCHI_END_HEADER

#endif
