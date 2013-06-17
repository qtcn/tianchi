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

/// @brief  可排序和分页的TableView,使用时主要分两步:
///             1. 初始化TcSortPaginationTableView
///             2. 处理获取数据请求(排序/分页/过滤)
/// @brief  1. 初始化TcSortPaginationTableView
/// @code
///     model = new QStandardItemModel(this);
///     ......
///     tableView->setModel(model);
///     tableView->setPaginator(labelPaginator);    // 设置显示分页符的label
///     tableView->setPageRowCount(20);             // 设置每页显示记录数
///     tableView->createTitleMenus();   // 创建标题行右键菜单,可显示/隐藏列
///     connect(tableView, SIGNAL(fetchDataRequested()),
///             this, SLOT(fetchData()));
/// @endcode
/// @brief  2. 处理获取数据请求(排序/分页/过滤)
/// @code
/// void XXXX::fetchData()
/// {
///     model->removeRows(0, model->rowCount());
///     QSqlQuery q;
///     QString strSql = "SELECT col1, col2, col3, col4 FROM table1 "
///                     "WHERE 1 = 1 ";
///     QString strSqlCnt = "SELECT COUNT(*) FROM table1 "
///                     "WHERE 1 = 1 ";
///     // 过滤条件
///     strSql += " AND col1 LIKE 'xxx%%'";
///     strSqlCnt += " AND col1 LIKE 'xxx%%'";
///     // 根据是否排序,设定order语句
///     if (tableView->isSortingEnabled())
///     {
///         switch (tableView->sortSection())
///         {
///             case 0:
///                 strSql += " ORDER BY col1";
///                 break;
///             case 1:
///                 strSql += " ORDER BY col2";
///                 break;
///             default:
///                 strSql += " ORDER BY col3";
///         }
///         if (tableView->sortOrder() == Qt::DescendingOrder)
///         {
///             strSql += " DESC";
///         }
///     }
///     else
///     {   // 如果不可排序,则使用默认排序
///         strSql += " ORDER BY col1";
///     }
///     int count = 0;  // 代表符合条件的总记录数
///     // 根据是否分页设定来读取当前页数据
///     if (tableView->pageRowCount() > 0)
///     {   // 分页
///         strSql += QString(" LIMIT %1 OFFSET %2")
///                         .arg(tableView->pageRowCount())
///                         .arg((tableView->page() - 1) 
///                                         * tableView->pageRowCount());
///         q.exec(strSql);
///         while (q.next())
///         {
///             .....// 获取当前页数据
///         }
///         // 获取符合条件的总数据条数
///         q.exec(strSqlCnt);
///         if (q.next())
///         {
///             count = q.value(0).toInt();
///         }
///     }
///     else
///     {   // 不分页
///         q.exec(strSql);
///         while (q.next())
///         {
///             ......// 不分页，所以获取所有符合条件的数据
///             count++;
///         }
///     }
///     // 最后设置分页信息
///     tableView->setPageInfo(tableView->page(), count);
/// @endcode
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
