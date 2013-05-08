// **************************************************************************
// Tianchi C++ library for Qt (open source)
// 天池共享源码库
// 版权所有 (C) 天池共享源码库开发组
// 授权协议：请阅读天池共享源码库附带的授权协议
// **************************************************************************
// 文档说明：通过 OLE 方式操作 Microsoft Excel（仅限 Windows 下使用，要求已安
//           装 Excel）
// ==========================================================================
// 开发日志：
// 日期         人员        说明
// --------------------------------------------------------------------------
// 2013.04.10   圣域天子    建立
//
// ==========================================================================
/// @file MSExcel.h 通过 OLE 方式操作 Microsoft Excel（仅限 Windows 下使用，
//                  要求已安装 Excel）
// ==========================================================================
#ifndef TIANCHI_TCMSEXCEL_H
#define TIANCHI_TCMSEXCEL_H

#include <tianchi/tcglobal.h>

#include <QString>
#include <QStringList>
#include <QVariant>

class TcMSExcelPrivate;

/// @brief 通过 OLE 方式操作 Microsoft Excel
/// @note 通过 OLE 方式操作 Microsoft Excel
/// @warning 只能在 Windows 下，并已安装了 Excel 时才能使用
/// @author 圣域天子 Jonix@qtcn.org
/// @date 2013-04-10
class TIANCHI_API TcMSExcel
{
public:
    /// @brief 构造方法
    TcMSExcel();
    /// @brief 析构方法
    virtual ~TcMSExcel();

private:
    Q_DISABLE_COPY(TcMSExcel)
    Q_DECLARE_PRIVATE(TcMSExcel)
    TcMSExcelPrivate*   d_ptr;

public:
    /// @brief 设置方向的常数
    enum Alignment
    {
        xlTop    = -4160, ///< 靠上
        xlLeft   = -4131, ///< 靠左
        xlRight  = -4152, ///< 靠右
        xlCenter = -4108, ///< 居中
        xlBottom = -4107  ///< 靠下
    };

    /// @brief 创建一个Microsoft Excel文件
    bool create(const QString& filename = QString());
    /// @brief 打开一个Microsoft Excel文件
    bool open(const QString& filename = QString());
    /// @brief 保存Microsoft Excel文件
    void save(const QString& filename = QString());
    /// @brief 关闭Microsoft Excel文件
    void close();
    /// @brief 踢出当前打开的 Microsoft Excel<br>
    /// @brief 放弃此对象对该 Excel 的控制权<br>
    /// @brief Excel 文件仍保持打开，但丧失了控制权
    void kick();

    /// @brief 设置当前打开的 Excel 是否可见
    void setVisible(bool value);
    /// @brief 设置 Excel 文档的标题
    void setCaption(const QString& value);

    /// @brief 新建一本 Excel 文档
    bool addBook();

    /// @brief 返回当前 Excel 的 Sheet 数量
    int sheetCount();

    /// @brief 返回当前打开的 Excel 全部 Sheet 名
    QStringList sheetNames();

    /// @brief 返回当前 Sheet.
    bool currentSheet();

    /// @brief 设置并指定当前 Sheet.
    /// @param [in] 当前 Sheet 索引，从 1 开始
    bool setCurrentSheet(int index);

    /// @brief 当前打开的 Excel 的 Sheet 名
    QString currentSheetName();

    /// @brief 读取单元格 Sheet 的内容
    /// @param [in] row 行号，从 1 开始
    /// @param [in] col 列号，从 1 开始
    /// @return 返回指定单元格的内容
    QVariant read(int row, int col);

    /// @brief 读取单元格 Sheet 的内容
    /// @param [in] row 行号，从 1 开始
    /// @param [in] col 列号，从 1 开始
    /// @return 返回指定单元格的内容
    inline QVariant cell(int row, int col) { return read(row, col); }

    /// @brief 写入单元格 Sheet 的内容
    /// @param [in] row 行号，从 1 开始
    /// @param [in] col 列号，从 1 开始
    /// @param [in] value 准备写入的内容
    void write(int row, int col, const QVariant& value);

    void cellFormat(int row, int col, const QString& format);
    void cellAlign(int row, int col, Alignment hAlign, Alignment vAlign);

    /// @brief 获取有效区域信息
    /// @see rowStart() const
    /// @see rowEnd() const
    /// @see colStart() const
    /// @see colEnd() const
    bool usedRange(int& rowStart, int& colStart, int &rowEnd, int &colEnd);
};

#endif // TIANCHI_MSEXCEL_H
