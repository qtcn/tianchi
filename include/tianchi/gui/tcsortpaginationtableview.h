// **************************************************************************
// Tianchi C++ library for Qt (open source)
// 天池共享源码库
// 版权所有 (C) 天池共享源码库开发组
// 授权协议：请阅读天池共享源码库附带的授权协议
// **************************************************************************
// 文档说明：可排序和分页的TableView
// ==========================================================================
// 开发日志：
// 日期         人员        说明
// --------------------------------------------------------------------------
// 2013.06.07   XChinux     建立
// ==========================================================================
/// @file tcsortpaginationtableview.h 
// ==========================================================================
#ifndef TIANCHI_TCSORTPAGINATIONTABLEVIEW_H
#define TIANCHI_TCSORTPAGINATIONTABLEVIEW_H

#include <tianchi/tcglobal.h>
#include <QTableView>

class QLabel;

class TcSortPaginationTableViewPrivate;

/// @brief  可排序和分页的TableView
class TIANCHI_API TcSortPaginationTableView : public QTableView
{
    Q_OBJECT
public:
    TcSortPaginationTableView(QWidget *parent = 0);
    virtual ~TcSortPaginationTableView();

    /// @brief  返回每页显示记录条数
    int pageRowCount() const;
    /// @brief  返回当前请求页码
    int page() const;
    /// @brief  返回当前请求排序列
    int sortSection() const;
    /// @brief  返回当前请求排序方向
    Qt::SortOrder sortOrder() const;

    /// @brief  设置每页显示记录条数, -1表示不分页
    void setPageRowCount(int pageRowCount = -1);

    /// @brief  设置paginator分页符字符串
    /// @param  page        当前页码
    /// @param  totalCount  总记录数
    void setPageInfo(int page, int totalCount);

    /// @brief  设置分页部件
    void setPaginator(QLabel *label);

    /// @biref  为横标头创建右键关联菜单
    void createTitleMenus();
Q_SIGNALS:
    /// @brief　请求数据时发出,比如排序和换页
    void fetchDataRequested();
public Q_SLOTS:
    /// @brief  获取数据(实际上内部是发射fetchDataRequested()信号
    /// @param  page    指定页码(-1表示当前页码不变)
    /// @param  section 指定排序列(-1表示排序列不变)
    /// @param  order   指定排序方向(section为-1时无意义)
    void fetchData(int page = -1, int section = -1, 
            Qt::SortOrder order = Qt::AscendingOrder);
private:
    Q_DISABLE_COPY(TcSortPaginationTableView)
    Q_DECLARE_PRIVATE(TcSortPaginationTableView)
    Q_PRIVATE_SLOT(d_func(), void _q_sortIndicatorChanged(int, Qt::SortOrder))
    Q_PRIVATE_SLOT(d_func(), void _q_paginatorClicked(const QString &))
    Q_PRIVATE_SLOT(d_func(), void _q_onColumnShown(bool checked))
    TcSortPaginationTableViewPrivate* const d_ptr;
};

#endif // TIANCHI_TCSORTPAGETABLEVIEW_H
