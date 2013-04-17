// **************************************************************************
// Tianchi share library for Qt (C++)
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
/// @file ClickLabel.h �ɷ���clicked�źŵ�Label����
// ==========================================================================
#ifndef TIANCHI_CLICKLABEL_H
#define TIANCHI_CLICKLABEL_H

#include <Global.h>
#include <QLabel>

TIANCHI_BEGIN_HEADER

TIANCHI_BEGIN_NAMESPACE


QT_USE_NAMESPACE

class ClickLabelPrivate;


/// @brief �ɷ���clicked�źŵ�Label����
class TIANCHI_API ClickLabel : public QLabel
{
    Q_OBJECT
public:
    ClickLabel(QWidget *parent = 0, Qt::WindowFlags f = 0);
    ClickLabel(const QString &text, QWidget *parent = 0, 
            Qt::WindowFlags f = 0);
    ~ClickLabel();
Q_SIGNALS:
    /// @brief �������ʱ����clicked�ź�
    void clicked();
protected:
    virtual void mousePressEvent(QMouseEvent *e);
    virtual void mouseReleaseEvent(QMouseEvent *e);
private:
    Q_DISABLE_COPY(ClickLabel)
    Q_DECLARE_PRIVATE(ClickLabel)
    ClickLabelPrivate *d_ptr;
};

TIANCHI_END_NAMESPACE

TIANCHI_END_HEADER

#endif
