// **************************************************************************
// Tianchi C++ library for Qt (open source)
// ��ع���Դ���
// ��Ȩ���� (C) ��ع���Դ��⿪����
// ��ȨЭ�飺���Ķ���ع���Դ��⸽������ȨЭ��
// **************************************************************************
// �ĵ�˵�����ɷ���clicked�źŵ�Label����
// ==========================================================================
// ������־��
// ����         ��Ա        ˵��
// --------------------------------------------------------------------------
// 2013.04.17   XChinux     ����
//
// ==========================================================================
/// @file tcclicklabel.h �ɷ���clicked�źŵ�Label����
// ==========================================================================
#ifndef TIANCHI_TCCLICKLABEL_H
#define TIANCHI_TCCLICKLABEL_H

#include <tianchi/tcglobal.h>
#include <QLabel>

class TcClickLabelPrivate;

/// @brief emit clicked() signal's label while mouse clicked
class TIANCHI_API TcClickLabel : public QLabel
{
    Q_OBJECT
public:
    TcClickLabel(QWidget *parent = 0, Qt::WindowFlags f = 0);
    TcClickLabel(const QString &text, QWidget *parent = 0, 
            Qt::WindowFlags f = 0);
    virtual ~TcClickLabel();
Q_SIGNALS:
    /// @brief emit when mouse click label
    void clicked();
protected:
    virtual void mousePressEvent(QMouseEvent *e);
    virtual void mouseReleaseEvent(QMouseEvent *e);
private:
    Q_DISABLE_COPY(TcClickLabel)
    Q_DECLARE_PRIVATE(TcClickLabel)
    TcClickLabelPrivate* const d_ptr;
};

#endif
