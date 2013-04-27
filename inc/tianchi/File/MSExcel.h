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
// 2013.04.10   圣域天子    建立
//
// ==========================================================================
/// @file MSExcel.h 通过 OLE 方式操作 Microsoft Excel（仅限 Windows 下使用，
//                  要求已安装 Excel）
// ==========================================================================
#ifndef TIANCHI_MSEXCEL_H
#define TIANCHI_MSEXCEL_H

#include <tianchi/Global.h>

#include <QString>
#include <QStringList>


QT_BEGIN_NAMESPACE

class QAxObject;
class QAxWidget;
#ifdef QT_WIDGETS_LIB
class QTreeWidget;
#endif

QT_END_NAMESPACE

namespace Tianchi
{

/// @brief 通过 OLE 方式操作 Microsoft Excel
/// @note 通过 OLE 方式操作 Microsoft Excel
/// @warning 只能在 Windows 下，并已安装了 Excel 时才能使用
/// @author 圣域天子 Jonix@qtcn.org
/// @date 2013-04-10
class TIANCHI_API MSExcel
{
public:
    /// @brief 构造方法
    MSExcel();
    /// @brief 析构方法
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
    /// @brief 设置方向的常数
    enum Alignment
    {
        xlTop    = -4160, ///< 靠上
        xlLeft   = -4131, ///< 靠左
        xlRight  = -4152, ///< 靠右
        xlCenter = -4108, ///< 居中
        xlBottom = -4107, ///< 靠下
    };

    /// @brief 创建一个Microsoft Excel文件
    bool create(const QString& filename="");
    /// @brief 打开一个Microsoft Excel文件
    bool open(const QString& filename="");
    /// @brief 保存Microsoft Excel文件
    void save(const QString& filename="");
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
    QAxObject* addBook();

    /// @brief 返回当前 Excel 的 Sheet 数量
    int sheetCount();

    /// @brief 设置并指定当前 Sheet.
    /// @param [in] 当前 Sheet 索引，从 1 开始
    QAxObject* sheet(int index);

    /// @brief 返回当前 Sheet.
    QAxObject* currentSheet();

    /// @brief 读取单元格 Sheet 的内容
    /// @param [in] row 行号，从 1 开始
    /// @param [in] col 列号，从 1 开始
    /// @return 返回指定单元格的内容
    QVariant read(int row, int col);

    /// @brief 写入单元格 Sheet 的内容
    /// @param [in] row 行号，从 1 开始
    /// @param [in] col 列号，从 1 开始
    /// @param [in] value 准备写入的内容
    void write(int row, int col, const QVariant& value);


    void        cellFormat(int row, int col, const QString& format);
    void        cellAlign(int row, int col, Alignment hAlign, Alignment vAlign);


    /// @brief 获取有效区域信息
    /// @see rowStart() const
    /// @see rowEnd() const
    /// @see colStart() const
    /// @see colEnd() const
    bool usedRange();

    /// @brief 返回当前打开的 Excel 全部 Sheet 名
    QStringList sheetNames();
    /// @brief 当前打开的 Excel 的 Sheet 名
    QString sheetName() const { return m_sheetName; }

    /// @brief 当前 Sheet 有效区域的开始行
    /// @note 需要先执行 usedRange() 获取有效区域信息后才能访问
    /// @see sheetName() const
    inline int rowStart() const { return m_rowStart; }
    /// @brief 当前 Sheet 有效区域的结束行
    /// @note 需要先执行 usedRange() 获取有效区域信息后才能访问
    /// @see sheetName() const
    inline int rowEnd() const { return m_rowEnd; }
    /// @brief 当前 Sheet 有效区域的开始列
    /// @note 需要先执行 usedRange() 获取有效区域信息后才能访问
    /// @see sheetName() const
    inline int colStart() const { return m_colStart; }
    /// @brief 当前 Sheet 有效区域的结束列
    /// @note 需要先执行 usedRange() 获取有效区域信息后才能访问
    /// @see sheetName() const
    inline int colEnd() const { return m_colEnd; }

#ifdef QT_WIDGETS_LIB
    /// @brief 把 QTreeWidget 的内容，直接输出到 Excel 中
    /// @author 圣域天子 Jonix@qtcn.org
    class TIANCHI_API Exporter
    {
    public:
        /// @brief 构造函数
        /// @param [in] view 需要导出的 QTreeWidget 对象
        /// @param [in] mode 0:导出全部<br> 1:导出选中的行
        /// @param [in] excel Excel 对象实例
        /// @param [in] row 导出到 Excel 的开始行
        /// @param [in] col 导出到 Excel 的开始列
        Exporter(QTreeWidget* view, int mode, ::Tianchi::MSExcel* excel, int row=1, int col=1);

        /// @brief 重置导出模式
        /// @param [in] mode 0:导出全部<br> 1:导出选中的行
        void setMode(int mode) { m_mode = mode; }
        /// @brief 重置导出到 Excel 的开始行和开始列
        void setStart(int row, int col) { m_row = row; m_col = col; }
        /// @brief 重置 Excel 的对象实例
        void setExcel(::Tianchi::MSExcel* excel) { m_excel = excel; }

        /// @brief 执行导出操作
        int  exec();

    private:
        QTreeWidget*        m_view;
        int                 m_mode;
        ::Tianchi::MSExcel*   m_excel;
        int                 m_row;
        int                 m_col;

        QStringList     formats;
        QStringList     cellTypes;
    };
#endif
};

}
typedef ::Tianchi::MSExcel TcMSExcel;

#endif // TIANCHI_MSEXCEL_H
