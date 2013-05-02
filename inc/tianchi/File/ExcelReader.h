// **************************************************************************
// Tianchi C++ library for Qt (open source)
// ��ع���Դ���
// ��Ȩ���� (C) ��ع���Դ��⿪����
// ��ȨЭ�飺���Ķ���ع���Դ��⸽������ȨЭ��
// **************************************************************************
// �ĵ�˵����ͨ�� OLE ��ʽ���� Microsoft Excel������ Windows ��ʹ�ã�Ҫ����
//           ��װ Excel��
// ==========================================================================
// ������־��
// ����         ��Ա        ˵��
// --------------------------------------------------------------------------
// 2013.05.02   XChinux     ����
//
// ==========================================================================
/// @file ExcelReader.h ͨ�� OLE ��ʽ��ȡ Microsoft Excel������ Windows ��ʹ�ã�
//                  Ҫ���Ѱ�װ Excel��WPSOffice��
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
private:
    Q_DISABLE_COPY(ExcelReader)
    Q_DECLARE_PRIVATE(ExcelReader)
    ExcelReaderPrivate *d_ptr;
};
}

typedef ::Tianchi::ExcelReader TcExcelReader;

#endif
