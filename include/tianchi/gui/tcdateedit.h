// **************************************************************************
// Tianchi C++ library for Qt (open source)
// ��ع���Դ���
// ��Ȩ���� (C) ��ع���Դ��⿪����
// ��ȨЭ�飺���Ķ���ع���Դ��⸽������ȨЭ��
// **************************************************************************
// �ĵ�˵��������Ϊ�յ�����ѡ��ؼ�
// ==========================================================================
// ������־��
// ����         ��Ա        ˵��
// --------------------------------------------------------------------------
// 2013.04.10   ʥ������    ����
//
// ==========================================================================
/// @file DateEdit.h ����Ϊ�յ�����ѡ��ؼ�
// ==========================================================================
#ifndef TIANCHI_TCDATEEDIT_H
#define TIANCHI_TCDATEEDIT_H

#include <tianchi/tcglobal.h>

#include <QComboBox>
#include <QCalendarWidget>

/// @brief �����������ʾΪ�յ�����ѡ��ؼ�
/// @author ʥ������ Jonix@qtcn.org
/// @date 2013-04-10
class TIANCHI_API TcDateEdit : public QComboBox
{
    Q_OBJECT

    Q_PROPERTY(QDate date READ date WRITE setDate RESET unsetDate)

private Q_SLOTS:
    void calendarClicked(QDate);

private:
    QCalendarWidget *m_calendar;

protected:
    void focusInEvent(QFocusEvent *e);
    void mousePressEvent(QMouseEvent *e);

public:
    TcDateEdit(QWidget *parent = 0);
    virtual ~TcDateEdit();

    QDate date() const;
    void setDate(QDate value);
    void unsetDate();

    inline void setDate(QDateTime value) { setDate(value.date()); }
};

#endif
