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
#ifndef TIANCHI_EXCELREADER_H
#define TIANCHI_EXCELREADER_H

#include <tianchi/Global.h>

#include <QVariant>

namespace Tianchi
{
class ExcelReaderPrivate;

/// @brief  simple excel reader class, limit to read first sheet
/// @author XChinux xchinux@qtcn.org
/// @date   2013-05-02
class TIANCHI_API ExcelReader
{
public:
    ExcelReader();
    ~ExcelReader();
    /// @brief  if is null, it can do nothing
    bool isNull() const;
    /// @brief  open excel file, success to return true
    bool open(const QString &file);
    /// @brief  read cell's value
    /// @param [in] row, index of row, from 1 start
    /// @param [in] col, index of column, from 1 start
    QVariant cell(int row, int col);

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
    Q_DISABLE_COPY(ExcelReader)
    Q_DECLARE_PRIVATE(ExcelReader)
    ExcelReaderPrivate *d_ptr;
};
}

typedef ::Tianchi::ExcelReader TcExcelReader;

#endif
