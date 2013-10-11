// **************************************************************************
// Tianchi C++ library for Qt (open source)
// ��ع���Դ���
// ��Ȩ���� (C) ��ع���Դ��⿪����
// ��ȨЭ�飺���Ķ���ع���Դ��⸽������ȨЭ��
// **************************************************************************
// �ĵ�˵���������Ի���
// ==========================================================================
// ������־��
// ����         ��Ա        ˵��
// --------------------------------------------------------------------------
// 2013.10.11   XChinux     ����
//
// ==========================================================================
/// @file tcscreencutdialog.h �����Ի���
// ==========================================================================
#ifndef TIANCHI_TCSCREENCUTDIALOG_H
#define TIANCHI_TCSCREENCUTDIALOG_H

#include <tianchi/tcglobal.h>
#include <QPixmap>
#include <QDialog>

class QMouseEvent;
class QPaintEvent;
class TcScreenCutDialogPrivate;

/// @brief  screen cut dialog
/// @code
///     TcScreenCutDialog dlg;
///     dlg.exec();
///     QPixmap image = dlg.getPixmap();
/// @endcode
class TcScreenCutDialog : public QDialog
{
    Q_OBJECT
public:
    TcScreenCutDialog(QWidget *parent = 0, Qt::WindowFlags f = 0);
    virtual ~TcScreenCutDialog();
    /// @brief  get cutted screen pixmap
    QPixmap getPixmap() const;
protected:
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void mouseDoubleClickEvent(QMouseEvent *event);
    virtual void paintEvent(QPaintEvent *event);
private:
    Q_DISABLE_COPY(TcScreenCutDialog)
    Q_DECLARE_PRIVATE(TcScreenCutDialog)
    TcScreenCutDialogPrivate* const d_ptr;
};

#endif
