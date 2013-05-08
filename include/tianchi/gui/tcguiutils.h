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
#ifndef TIANCHI_TCGUIUTILS_H
#define TIANCHI_TCGUIUTILS_H

#include <tianchi/tcglobal.h>

#include <QLabel>
#include <QCursor>
#include <QWidget>
#include <QToolBar>
#include <QToolButton>
#include <QTreeWidget>
#include <QDoubleSpinBox>
#if (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
#include <QGuiApplication>
#else
#include <QApplication>
#endif

/// @brief �����̬�仯��ĸ��࣬һ�㲻ֱ��ʹ��
/// @see class CursorWait
/// @see class CursorBusy
/// @author ʥ������ Jonix@qtcn.org
/// @date 2013-04-15
class TIANCHI_API TcCursorCustom
{
protected:
    TcCursorCustom(Qt::CursorShape shape)
    {
#if (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
        QGuiApplication::setOverrideCursor(QCursor(shape));
#else
        QApplication::setOverrideCursor(QCursor(shape));
#endif
    }
    virtual ~TcCursorCustom()
    {
        restore();
    }
    QWidget* m_parent;
    QCursor  m_cursor;
public:
    /// @brief �����ָ�����Ĺ��
    inline void restore()
    {
#if (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
        QGuiApplication::restoreOverrideCursor();
#else
        QApplication::restoreOverrideCursor();
#endif
    }
};

/// @brief �ȴ��������ú��Զ��ָ�������
/// @par ʾ��:
/// @code
/// void myForm::onClick()
/// {
///     TcCursorWait wait; // �Զ���ɵȴ����
///
///     ... ������� ...
///
/// } // �˳���ʱ��wait ���ͷţ�ʹ����Զ��ָ�Ϊԭ�ȵĹ����̬
/// @endcode
/// @see class CursorBusy
/// @author ʥ������ Jonix@qtcn.org
/// @date 2013-04-15
class TIANCHI_API TcCursorWait : public TcCursorCustom
{
public:
    TcCursorWait()
        : TcCursorCustom(Qt::WaitCursor)
    {
    }
};

/// @brief ��̨æ�������ú��Զ��ָ�������
/// @par ʾ��:
/// @code
/// void myForm::onClick()
/// {
///     TcCursorBusy busy; // �Զ���ɺ�̨æ���
///
///     ... ������� ...
///
///
/// } // �˳���ʱ��busy ���ͷţ�ʹ����Զ��ָ�Ϊԭ�ȵĹ����̬
/// @endcode
/// @see class CursorBusy
/// @author ʥ������ Jonix@qtcn.org
/// @date 2013-04-15
class TIANCHI_API TcCursorBusy : public TcCursorCustom
{
public:
    TcCursorBusy()
        : TcCursorCustom(Qt::BusyCursor)
    {
    }
};

namespace Tc
{

// �ڹ������ϴ���һ����ť
TIANCHI_API QToolButton* createButton(QToolBar* toolBar,
                                      QIcon icon, QString text, int width,
                                      Qt::ToolButtonStyle style=Qt::ToolButtonTextBesideIcon);

inline void setColumnBold(QTreeWidget* view)
{
    for( int i=0;i<view->headerItem()->columnCount();i++ )
    {
        QFont font = view->headerItem()->font(i);
        font.setBold(true);
        view->headerItem()->setFont(i, font);
    }
}

inline void setColumnWidth(QTreeWidget* view, int column, int width, bool hide=false)
{
    view->setColumnWidth(column, width);
    view->setColumnHidden(column, hide);
}

TIANCHI_API void createColumnMenu(QTreeWidget* view, QWidget* widget, const QString& ColumnSetupFunc);


TIANCHI_API void setColumnStyle(QTreeWidget* view, int fontSize=8, const QString &fontName="Tahoma");

TIANCHI_API void cellStyle(QTreeWidgetItem* item, int startCol=-1, int endCol=-1,
                              bool bold=true, int alignment=Qt::AlignVCenter | Qt::AlignRight,
                              int cellHeight=25);


TIANCHI_API void cellFont(QTreeWidgetItem* item, int col, bool bold=false, int alignment=Qt::AlignVCenter | Qt::AlignLeft);
TIANCHI_API void cellColor(QTreeWidgetItem* item, int col, QColor color);

TIANCHI_API void changeFont(QWidget* widget, const QString& fontName="Arial Narrow", int fontSize=8, bool bold=false);
TIANCHI_API void setFontTahoma(QWidget* widget, int fontSize=8, bool bold=false);
// �� QTreeWidgetItem ����ʾ��ֵ
TIANCHI_API void cellValue(QTreeWidgetItem* item, int column, const char* text, const QVariant& data=QVariant(), int size=0);
TIANCHI_API void cellValue(QTreeWidgetItem* item, int column, const QString& text, const QVariant& data=QVariant(), int size=0);
TIANCHI_API void cellValue(QTreeWidgetItem* item, int column, const QByteArray& text, const QVariant& data=QVariant(), int size=0);
TIANCHI_API void cellValue(QTreeWidgetItem* item, int column, double value);
TIANCHI_API void cellValue(QTreeWidgetItem* item, int column, double value, int digits);
TIANCHI_API void cellPrice(QTreeWidgetItem* item, int column, double value=0.0, int digits=0);
TIANCHI_API void cellPercent(QTreeWidgetItem* item, int column, double value=0.0, int digits=0);

TIANCHI_API QLabel* createLabel(QTreeWidgetItem* item, int col, const QString& htmlText, const QVariant& data=QVariant());

TIANCHI_API QDoubleSpinBox* createDoubleSpinBox(QTreeWidgetItem* item, int col,
                                                int decimals, double min, double max, double step, double value);
TIANCHI_API double          readDoubleSpinBoxValue(QTreeWidgetItem* item, int col);

TIANCHI_API void CopyCell(QTreeWidget* view);
TIANCHI_API void CopyLine(QTreeWidget* view);
TIANCHI_API void CopyTable(QTreeWidget* view);
}

#endif // TIANCHI_GUIUTILS_H
