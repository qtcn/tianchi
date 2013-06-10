// **************************************************************************
// Tianchi C++ library for Qt (open source)
// 天池共享源码库
// 版权所有 (C) 天池共享源码库开发组
// 授权协议：请阅读天池共享源码库附带的授权协议
// **************************************************************************
// 文档说明：依所设过滤参数(QVariantMap)来使用已设滤函数进行过滤的模型
// ==========================================================================
// 开发日志：
// 日期         人员        说明
// --------------------------------------------------------------------------
// 2013.06.07   XChinux     建立
//
// ==========================================================================
/// @file tcfunctionalsortfilterproxymodel.h
// ==========================================================================

#ifndef TIANCHI_TCFUNCTIONALSORTFILTERPROXYMODEL_H
#define TIANCHI_TCFUNCTIONALSORTFILTERPROXYMODEL_H

#include <tianchi/tcglobal.h>

//#include <functional> // TODO C++11
#include <QVariantMap>
#include <QSortFilterProxyModel>

/// @brief  过滤函数类型,第一个参数为过滤条件,第二个参数为sourceModel的对应行
///         第一列index
typedef bool (*TcFunctionalSortFilterProxyModelFilterFunction)( \
        const QVariantMap &, const QModelIndex &);

class TcFunctionalSortFilterProxyModelPrivate;

/// @brief  依所设过滤参数(QVariantMap)来使用已设滤函数进行过滤的
///         SortFilterProxyModel,使用时分三部分:
///             1. 定义过滤函数
///             2. 创建TcFunctionalSortFilterProxyModel实例，并设定过滤函数
///             3. 条件改变时，调用setFilterParam()应用过滤参数并使其生效
/// @brief  1.先定义过滤函数(示例为MyFilter)
/// @code
/// bool MyFilter(const QVariantMap &param, const QModelIndex &index)
/// {
///     QModelIndex idx1 = index;                       // 第一列
///     QModelIndex idx2 = idx1.sibling(idx1.row(), 1); // 第二列
///
///     QString str1 = param["col1"].toString();        // 第一列过滤内容
///     QString str2 = param["col2"].toString();        // 第二列过滤内容
///
///     // 如果第一个过滤参数不为空，那么要求第一列显示字符串必须以str1开头
///     if (!str1.isEmpty())
///     {
///         if (idx1.data(Qt::DisplayRole).toString().indexOf(str1) != 0)
///         {
///             return false;
///         }
///     }
///     
///     // 如果第二个过滤参数不为空，那么要求第二列显示字符串必须包含str2
///     if (!str2.isEmpty())
///     {
///         if (idx2.data(Qt::DisplayRole).toString().indexOf(str1) == -1)
///         {
///             return false;
///         }
///     }
///     return true;
/// }
/// @endcode
///
/// @brief  2.创建模型时，设置过滤函数
/// @code
/// model = new QStandardItemModel(this);
/// ......
/// TcFunctionalSortFilterProxyModel *proxy = 
///                                 new TcFunctionalSortFilterProxyModel(this);
/// proxy->setFilterFunction(&MyFilter);
/// proxy->setSourceModel(model);
/// @endcode
///
/// @brief  3.设置完过滤条件后，调用setFilterParam()来应用过滤参数
/// @code
/// QVariantMap param;
/// param["col1"] = "0102"; // 假设要求过滤以"0102"开头的字符串
/// param["col2"] = "HFX";  // 假设要求过滤包含"HFX"的字符串
/// proxy->setFilterParam(param);
/// @endcode
class TIANCHI_API TcFunctionalSortFilterProxyModel : 
    public QSortFilterProxyModel
{    
    Q_OBJECT
public:
    TcFunctionalSortFilterProxyModel(QObject * parent = 0);
    ~TcFunctionalSortFilterProxyModel();
    /// @brief  设定过滤函数
    void setFilterFunction(
            TcFunctionalSortFilterProxyModelFilterFunction func);
            //std::function<bool(const QVariantMap &, const QModelIndex &)> func);  // TODO C++11
public Q_SLOTS:
    /// @brief  设定过滤参数
    void setFilterParam(const QVariantMap &param);
protected:
    virtual bool filterAcceptsRow(int source_row, 
            const QModelIndex &source_parent) const;
private:
    Q_DISABLE_COPY(TcFunctionalSortFilterProxyModel)
    Q_DECLARE_PRIVATE(TcFunctionalSortFilterProxyModel)
    TcFunctionalSortFilterProxyModelPrivate* const d_ptr;
};

#endif  // TIANCHI_TCFUNCTIONALSORTFILTERPROXYMODEL_H
