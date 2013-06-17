// **************************************************************************
// Tianchi C++ library for Qt (open source)
// 天池共享源码库
// 版权所有 (C) 天池共享源码库开发组
// 授权协议：请阅读天池共享源码库附带的授权协议
// **************************************************************************
// 文档说明：以QVariantMap作为数据行的model,只可追加和清除,不可插入与删除
// ==========================================================================
// 开发日志：
// 日期         人员        说明
// --------------------------------------------------------------------------
// 2013.06.07   XChinux     建立
//
// ==========================================================================
/// @file tcvariantmaptablemodel.h
// ==========================================================================
#ifndef TIANCHI_TCVARIANTMAPTABLEMODEL_H
#define TIANCHI_TCVARIANTMAPTABLEMODEL_H

#include <tianchi/tcglobal.h>

#include <QVariantMap>
#include <QAbstractTableModel>

enum 
{
    /// @brief  定义返回每行所有实际数据的角色
    TcDataRole = Qt::UserRole + 999
};

class TcVariantMapTableModelPrivate;

/// @brief  以QVariantMap作为数据行的model,只可追加和清除,不可任意插入与任意
///         删除,使用时主要分成三部分：
///             1. 创建TcVariantMapTableModel,并定义标题和列属性
///             2. 填充数据(即清除数据以及添加数据行)
///             3. 获取指定数据行数据
/// @brief  1. 创建model及定义标题和列属性
/// @code
///    TcVariantMapTableModel *model = new TcVariantMapTableModel(this);
///    model->addTitle("col1",    "Title 1"));
///    model->addTitle("col2",    "Title 2", 2));// 数字列，保留两位小数
///    model->addTitle("col3",    "Title 3"));
///    model->addTitle("__col4",  "Title 4"));  // 非原始数据
///    tableView->setModel(model);
/// @endcode
/// 
/// @brief  2. 填充数据
/// @code
///     model->clearData(); // 清除原来的数据行(保留标题不变)
///     QSqlQuery q;
///     q.exec("SELECT col1, col2, col3, col4 FROM table1");
///     QList<QVariantMap> rows;
///     QVariantMap row;
///     while (q.next())
///     {
///         row["col1"] = q.value(0);
///         row["col2"] = q.value(1);
///         row["col3"] = q.value(2);
///         row["col4"] = q.value(3);
///         row["__col4"] = row["col4"].toInt() == 1 ? "Yes" : "No";
///         rows << row;
///         row.clear();
///     }
///     model->addData(rows);
/// @endcode
///
/// @brief  3. 获取指定数据行数据
/// @code
/// void XXXX::on_actionYYY_triggered()
/// {
///     QModelIndexList idxs = tableView->selectionModel()->selectedRows();
///     if (idxs.isEmpty())
///     {
///         return;
///     }
///     int row = idxs.first().row();
///     const QList<QVariantMap> &data = model->data();
///     // 获取选定行的col1字段值
///     QString strCol1 = data[row]["col1"].toString().trimmed();
///     ......
/// }
/// @endcode
class TIANCHI_API TcVariantMapTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    TcVariantMapTableModel(QObject *parent = 0);
    virtual ~TcVariantMapTableModel();

    // 继承实现部分开始-----------------
    virtual Qt::ItemFlags flags(const QModelIndex &index) const;

    virtual QVariant data(const QModelIndex &index, 
            int role = Qt::DisplayRole) const;

    virtual QVariant headerData(int section, Qt::Orientation orientation, 
            int role = Qt::DisplayRole) const;

    virtual int rowCount(
            const QModelIndex &parent = QModelIndex()) const;

    /// @brief  返回横向表头(即标题)数量
    virtual int columnCount(
            const QModelIndex &parent = QModelIndex()) const;

    virtual bool setData(const QModelIndex &index, const QVariant &value, 
            int role = Qt::EditRole);

    /// @brief  直接返回false,即不可设定横向和竖向表头
    virtual bool setHeaderData(int section, Qt::Orientation orientation, 
            const QVariant &value, int role = Qt::EditRole);

    // 继承实现部分结束-----------------

    /// @brief  设置flags属性
    void setFlags(const QModelIndex &index, Qt::ItemFlags flags);

    /// @brief  设置某一项是否可选中
    void setCheckable(int row, int col, bool checkable);

    /// @brief  设置某一项是否选中
    void setChecked(int row, int col, bool checked);

    /// @brief  判断某一项是否可选中
    bool isCheckable(int row, int col) const;

    /// @brief  判断某一项是否选中
    bool isChecked(int row, int col) const;

    /// @brief  添加标题(即横表头)定义
    /// @param  field   字段名
    /// @param  title   标题显示值
    /// @param  precision 如果是数字列,设定其显示精度(-1表示无效)
    void addTitle(const QString &field, const QString &title, 
            int precision = -1);

    /// @brief  添加数据行(多条)
    /// @param  data    多条数据行
    void addData(const QList<QVariantMap> &data);

    /// @brief  添加数据行(一条)
    /// @param  row     一条数据行
    void addData(const QVariantMap &row);

    /// @brief  返回所有数据行常引用
    const QList<QVariantMap>& data() const;

    /// @brief  返回某一行数据(如果无效则返回QVariantMap())
    QVariantMap data(int row) const;

    /// @brief  返回所有标题定义(first为field, second为title)
    const QList<QPair<QString, QString> >& title() const;

    /// @brief  返回某一列标题定义(first为field, second为title)
    QPair<QString, QString> title(int col) const;

    /// @brief  设置某字段列显示精度
    void setNumberColumn(const QString &field, int precision);
    
    /// @brief  设置某列显示精度
    void setNumberColumn(int column, int precision);

    /// @brief  清除所有数据行
    void clearData();

    /// @brief  清除所有数据行及标题设定
    void clear();
private:
    Q_DISABLE_COPY(TcVariantMapTableModel)
    Q_DECLARE_PRIVATE(TcVariantMapTableModel)
    TcVariantMapTableModelPrivate* const d_ptr;
};

#endif  // TIANCHI_TCVARIANTMAPTABLEMODEL_H
