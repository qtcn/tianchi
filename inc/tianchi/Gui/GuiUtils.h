// **************************************************************************
// Tianchi C++ library for Qt (open source)
// ��ع���Դ���
// ��Ȩ���� (C) ��ع���Դ��⿪����
// ��ȨЭ�飺���Ķ���ع���Դ��⸽������ȨЭ��
// **************************************************************************
// �ĵ�˵����GUI��س��õ�Ԫ
// ==========================================================================
// ������־��
// ����         ��Ա        ˵��
// --------------------------------------------------------------------------
// 2013.04.15   ʥ������    ����
//
// ==========================================================================
/// @file GuiUtils.h GUI��س��õ�Ԫ
#ifndef TIANCHI_GUIUTILS_H
#define TIANCHI_GUIUTILS_H

#include <tianchi/Global.h>

#if defined(QT_GUI_LIB)
#include <QWidget>
#include <QCursor>

namespace Tianchi
{
/// @brief �����̬�仯��ĸ��࣬һ�㲻ֱ��ʹ��
/// @see class CursorWait
/// @see class CursorBusy
/// @author ʥ������ Jonix@qtcn.org
/// @date 2013-04-15
class TIANCHI_API CursorCustom
{
protected:
    CursorCustom(QWidget* parent, Qt::CursorShape shape)
    {
        m_parent = parent;
        m_cursor = m_parent->cursor();
        m_parent->setCursor(QCursor(shape));
    }
    virtual ~CursorCustom()
    {
        m_parent->setCursor(m_cursor);
    }
    QWidget* m_parent;
    QCursor  m_cursor;
};

/// @brief �ȴ��������ú��Զ��ָ�������
/// @par ʾ��:
/// @code
/// void myForm::onClick()
/// {
///     CursorWait wait; // �Զ���ɵȴ����
///
///     ... ������� ...
///
/// } // �˳���ʱ��wait ���ͷţ�ʹ����Զ��ָ�Ϊԭ�ȵĹ����̬
/// @endcode
/// @see class CursorBusy
/// @author ʥ������ Jonix@qtcn.org
/// @date 2013-04-15
class TIANCHI_API CursorWait : public CursorCustom
{
public:
    CursorWait(QWidget* parent = 0)
        : CursorCustom(parent, Qt::WaitCursor)
    {
    }
};

/// @brief ��̨æ�������ú��Զ��ָ�������
/// @par ʾ��:
/// @code
/// void myForm::onClick()
/// {
///     CursorBusy busy; // �Զ���ɺ�̨æ���
///
///     ... ������� ...
///
///
/// } // �˳���ʱ��busy ���ͷţ�ʹ����Զ��ָ�Ϊԭ�ȵĹ����̬
/// @endcode
/// @see class CursorBusy
/// @author ʥ������ Jonix@qtcn.org
/// @date 2013-04-15
class TIANCHI_API CursorBusy : public CursorCustom
{
public:
    CursorBusy(QWidget* parent = 0)
        : CursorCustom(parent, Qt::BusyCursor)
    {
    }
};
}

typedef ::Tianchi::CursorCustom     TcCursorCustom;
typedef ::Tianchi::CursorWait       TcCursorWait;
typedef ::Tianchi::CursorBusy       TcCursorBusy;

#endif // QT_GUI_LIB

#endif // TIANCHI_GUIUTILS_H
