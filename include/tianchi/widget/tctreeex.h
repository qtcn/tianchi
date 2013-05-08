// **************************************************************************
// Tianchi C++ library for Qt (open source)
// 天池共享源码库
// 版权所有 (C) 天池共享源码库开发组
// 授权协议：请阅读天池共享源码库附带的授权协议
// **************************************************************************
// 文档说明：QTreeWidget 控件扩展
// ==========================================================================
// 开发日志：
// 日期         人员        说明
// --------------------------------------------------------------------------
// 2013.05.03   圣域天子    建立
//
// ==========================================================================
/// @file TreeEx.h QTreeWidget 控件扩展
// ==========================================================================
#ifndef TIANCHI_TCTREEEX_H
#define TIANCHI_TCTREEEX_H

#include <tianchi/tcglobal.h>
#include <tianchi/file/tcmsexcel.h>

#include <QTreeWidget>
#include <QLabel>
#include <QDoubleSpinBox>

class TcTreeExPrivate;

/// @brief 把 QTreeWidget 的扩展功能，可直接导出到 Excel 中
/// @author 圣域天子 Jonix@qtcn.org
class TIANCHI_API TcTreeEx
{
public:
    enum ExportType
    {
        TextFile = 1
      , MSExcel  = 2
    };
    /// @brief 构造函数
    /// @param [in] view 需要导出的 QTreeWidget 对象
    TcTreeEx(QTreeWidget* widget=0);

    /// @brief 设置导出模式
    /// @param [in] widget 需要导出的 QTreeWidget 对象
    void setWidget(QTreeWidget* widget);

    /// @brief 设置导出模式
    /// @param [in] type 需要导出的类型(enum ExportType)
    void setExportType(int type);

    /// @brief 设置导出模式
    /// @param [in] state 0 全部, 1 选中
    void setSelectedState(int state);

    /// @brief 设置导出的文本文件名
    /// @param [in] filename 导出的文本文件名
    void setTextFileName(const QString& filename);

    /// @brief 设置 Excel 的对象实例<br>
    /// 使用此方法后导出模式自动重置为 MSExcel
    void setMSExcelObject(TcMSExcel* excel, bool hasHeader=true, int startRow=1, int startCol=1);

    /// @brief 执行导出操作
    int  save();

private:
    Q_DISABLE_COPY(TcTreeEx)
    Q_DECLARE_PRIVATE(TcTreeEx)
    TcTreeExPrivate*   d_ptr;

public:
    static void createColumnMenu(QTreeWidget* widget, QWidget* object, const QString& methodName);

    static void setColumnBolds(QTreeWidget* widget);
    static void setColumnWidth(QTreeWidget* widget, int column, int width, bool hide=false);
    static void setColumnStyle(QTreeWidget* widget, int fontSize=8, const QString &fontName="Tahoma");

    static void CopyCellObject(QTreeWidget* view, int copyMode);
};

class TIANCHI_API TcTreeItem : public QTreeWidgetItem
{
public:
    void setCellFont(int col, bool bold=false, int alignment=Qt::AlignVCenter | Qt::AlignLeft);
    void setCellStyle(int startCol=-1, int endCol=-1,
                      bool bold=true, int alignment=Qt::AlignVCenter | Qt::AlignRight,
                      int cellHeight=25);
    void setCellColor(int col, QColor color);

    QLabel*         createLabel(int col, const QString& htmlText, const QVariant& data=QVariant());
    QDoubleSpinBox* createDoubleSpinBox(int col,
                                        int decimals, double min, double max, double step, double value);
    double          readDoubleSpinBoxValue(int col);

    void showValue(int column, const char* text, const QVariant& data=QVariant(), int size=0);
    void showValue(int column, const QString& text, const QVariant& data=QVariant(), int size=0);
    void showValue(int column, const QByteArray& text, const QVariant& data=QVariant(), int size=0);
    void showValue(int column, double value);
    void showValue(int column, double value, int digits);
    void showPrice(int column, double value, int digits=0);
    void showPercent(int column, double value=0.0, int digits=0);
};

#endif // TIANCHI_TCTREEEX_H
