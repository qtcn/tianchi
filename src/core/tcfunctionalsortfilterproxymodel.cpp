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
/// @file tcfunctionalsortfilterproxymodel.cpp
// ==========================================================================
#include <tianchi/core/tcfunctionalsortfilterproxymodel.h>

class TcFunctionalSortFilterProxyModelPrivate
{
    Q_DECLARE_PUBLIC(TcFunctionalSortFilterProxyModel)
public:
    explicit TcFunctionalSortFilterProxyModelPrivate(
            TcFunctionalSortFilterProxyModel *qptr) : 
    func(NULL) // func(nullptr) // TODO C++11
    , q_ptr(qptr)
    {}
    ~TcFunctionalSortFilterProxyModelPrivate(){}

    QVariantMap param;
    // TODO C++11
    //std::function<bool(const QVariantMap &, const QModelIndex &)> func;
    TcFunctionalSortFilterProxyModelFilterFunction func;

    TcFunctionalSortFilterProxyModel* const q_ptr;
};

TcFunctionalSortFilterProxyModel::TcFunctionalSortFilterProxyModel(
        QObject * parent)
    : QSortFilterProxyModel(parent), 
    d_ptr(new TcFunctionalSortFilterProxyModelPrivate(this))
{
}

TcFunctionalSortFilterProxyModel::~TcFunctionalSortFilterProxyModel()
{
    delete d_ptr;
}

void TcFunctionalSortFilterProxyModel::setFilterFunction(
        TcFunctionalSortFilterProxyModelFilterFunction func)
        //std::function<bool(const QVariantMap &, const QModelIndex &)> func)
        // TODO C++11
{
    Q_D(TcFunctionalSortFilterProxyModel);
    d->func = func;
    invalidateFilter();
}

void TcFunctionalSortFilterProxyModel::setFilterParam(const QVariantMap &param)
{
    Q_D(TcFunctionalSortFilterProxyModel);
    d->param = param;
    invalidateFilter();
}

bool TcFunctionalSortFilterProxyModel::filterAcceptsRow(int source_row, 
        const QModelIndex &source_parent) const
{
    bool bOk = QSortFilterProxyModel::filterAcceptsRow(source_row, 
            source_parent);
    if (!bOk)
    {
        return bOk;
    }
    Q_D(const TcFunctionalSortFilterProxyModel);
    if (d->func)
    {
        bOk = d->func(d->param, 
                sourceModel()->index(source_row, 0, source_parent));
    }
    return bOk;
}

#include "moc_tcfunctionalsortfilterproxymodel.cpp"
