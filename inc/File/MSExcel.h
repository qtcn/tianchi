// ********************************************************************************************************************
// Tianchi C++ library for Qt (open source)
// 天池共享源码库
// 版权所有 (C) 天池共享源码库开发组
// 授权协议：请阅读天池共享源码库附带的授权协议
// ********************************************************************************************************************
// 文档说明：通过 OLE 方式操作 Microsoft Excel（仅限 Windows 下使用，要求已安装 Excel）
// ====================================================================================================================
// 开发日志：
// 日期         人员        说明
// --------------------------------------------------------------------------------------------------------------------
// 2013.04.10   圣域天子    建立
//
// ====================================================================================================================
/// @file MSExcel.h 通过 OLE 方式操作 Microsoft Excel（仅限 Windows 下使用，要求已安装 Excel）
// ====================================================================================================================
#ifndef TIANCHI_MSEXCEL_H
#define TIANCHI_MSEXCEL_H

#include "Global.h"

#include <QString>
#include <QStringList>

#if defined(Q_OS_WIN)
#include <ActiveQt/QAxWidget>
#include <ActiveQt/QAxObject>

#ifdef QT_WIDGETS_LIB
#include <QTreeWidget>
#endif
#else
class QAxObject;
#endif // Q_OS_WIN

TIANCHI_BEGIN_NAMESPACE

/// @brief 通过 OLE 方式操作 Microsoft Excel
class TIANCHI_API MSExcel
{
public:
    MSExcel();
    virtual ~MSExcel();

private:
    QAxWidget*  m_excel;
    QAxObject*  m_books;
    QAxObject*  m_book;
    QAxObject*  m_sheets;
    QAxObject*  m_sheet;
    QString     m_filename;
    QString     m_sheetName;

    int m_rowStart;
    int m_colStart;
    int m_rowEnd;
    int m_colEnd;

public:
    enum Alignment
    {
        xlTop    = -4160,
        xlLeft   = -4131,
        xlRight  = -4152,
        xlCenter = -4108,
        xlBottom = -4107,
    };

    bool        create(const QString& filename="");
    bool        open(const QString& filename="");
    void        save(const QString& filename="");
    void        close();
    void        kick();

    void        setVisible(bool value);
    void        setCaption(const QString& value);

    QAxObject*  addBook();

    void        cellFormat(int row, int col, const QString& format);
    void        cellAlign(int row, int col, Alignment hAlign, Alignment vAlign);

    QVariant    read(int row, int col);
    void        write(int row, int col, const QVariant& value);

    int         sheetCount();
    QAxObject*  currentSheet();

    QAxObject*  sheet(int index);

    bool        usedRange();

    QStringList sheetNames();
    QString     sheetName() const { return m_sheetName; }

    inline int rowStart() const { return m_rowStart; }
    inline int colStart() const { return m_colStart; }
    inline int rowEnd() const { return m_rowEnd; }
    inline int colEnd() const { return m_colEnd; }

#ifdef QT_WIDGETS_LIB
    class TIANCHI_API Exporter
    {
    public:
        Exporter(QTreeWidget* view, int mode, TIANCHI_NAMESPACE::MSExcel* excel, int row=1, int col=1);

        void setStart(int row, int col) { m_row = row; m_col = col; }
        void setExcel(TIANCHI_NAMESPACE::MSExcel* excel) { m_excel = excel; }
        void setMode(int mode) { m_mode = mode; } // 0:all, 1:selected

        int  exec();

        QStringList     formats;
        QStringList     cellTypes;

    private:
        QTreeWidget*        m_view;
        TIANCHI_NAMESPACE::MSExcel*   m_excel;
        int                 m_row;
        int                 m_col;
        int                 m_mode;
    };
#endif
};

TIANCHI_END_NAMESPACE

#endif // TIANCHI_MSEXCEL_H
