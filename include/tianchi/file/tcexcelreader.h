// **************************************************************************
// Tianchi C++ library for Qt (open source)
// 天池共享源码库
// 版权所有 (C) 天池共享源码库开发组
// 授权协议：请阅读天池共享源码库附带的授权协议
// **************************************************************************
// 文档说明：通过 OLE 方式操作 Microsoft Excel（仅限 Windows 下使用，要求已
//           安装 Excel）
// ==========================================================================
// 开发日志：
// 日期         人员        说明
// --------------------------------------------------------------------------
// 2013.05.02   XChinux     建立
//
// ==========================================================================
/// @file ExcelReader.h 通过 OLE 方式读取 Microsoft Excel（仅限 Windows 下使用，
//                  要求已安装 Excel或WPSOffice）
// ==========================================================================
#ifndef TIANCHI_TCEXCELREADER_H
#define TIANCHI_TCEXCELREADER_H

#include <tianchi/tcglobal.h>

#include <QVariant>
#include <QStringList>

class TcExcelReaderPrivate;

/// @brief  simple excel reader class, limit to read first sheet
/// @author XChinux xchinux@qtcn.org
/// @date   2013-05-02
class TIANCHI_API TcExcelReader
{
public:
    TcExcelReader();
    ~TcExcelReader();
    /// @brief  if is null, it can do nothing
    bool isNull() const;
    /// @brief  open excel file, success to return true
    bool open(const QString &file);
    /// @brief  read cell's value
    /// @param [in] rowIndex, index of row, from 1 start
    /// @param [in] columnIndex, index of column, from 1 start
    QVariant cell(int rowIndex, int columnIndex);
    /// @brief  read cell's value
    /// @param [in] colName, column name, from 'a' or 'AB' start
    /// @param [in] rowIndex, index of row, from 1 start
    QVariant cell(const QString &colName, int rowIndex);
    /// @brief  read cell's value
    /// @param [in] cellName, cell's name just like 'A2' or 'ac2'
    QVariant cell(const QString &cellName);

    /// @brief  get sheets count
    int         sheetCount();
    /// @brief  get sheets name list
    QStringList sheetNames();
    /// @brief  set current sheet by index(from 1 start)
    bool        setCurrentSheet(int index);
    /// @brief  set current sheet by name
    bool        setCurrentSheet(const QString &sheetName);
    /// @brief  get current sheet index(from 1 start)
    int         currentSheetIndex();
    /// @brief  get current sheet name
    QString     currentSheetName();
private:
    Q_DISABLE_COPY(TcExcelReader)
    Q_DECLARE_PRIVATE(TcExcelReader)
    TcExcelReaderPrivate* const d_ptr;
};

#endif
