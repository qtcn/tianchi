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

// 滤函数类型,第一个参数为过滤条件,第二个参数为sourceModel的对应行第一列index
typedef bool (*TcFunctionalSortFilterProxyModelFilterFunction)( \
        const QVariantMap &, const QModelIndex &);

class TcFunctionalSortFilterProxyModelPrivate;

// 依所设过滤参数(QVariantMap)来使用已设滤函数进行过滤的模型
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
