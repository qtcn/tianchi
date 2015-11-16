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
/// @file tcsortpaginationtableview.cpp
// ==========================================================================
#include <tianchi/gui/tcsortpaginationtableview.h>
#include <qmath.h>
#include <QLabel>
#include <QAction>
#include <QHeaderView>

class TcSortPaginationTableViewPrivate
{
    Q_DECLARE_PUBLIC(TcSortPaginationTableView)
public:
    explicit TcSortPaginationTableViewPrivate(
            TcSortPaginationTableView *qptr) 
        : q_ptr(qptr), paginator(NULL), pageRowCount(-1), totalCount(0), 
        page(1) {}
    ~TcSortPaginationTableViewPrivate(){}

    void _q_sortIndicatorChanged(int logicalIndex, Qt::SortOrder order);
    void _q_paginatorClicked(const QString &link);
    void _q_onColumnShown(bool checked);
    
    TcSortPaginationTableView* const q_ptr;

    QLabel *paginator;  // 分页符部件
    int pageRowCount;   // 每页显示条数, -1表示不分页
    int totalCount;     // 总共记录条数
    int page;           // 当前页码
};

void TcSortPaginationTableViewPrivate::_q_sortIndicatorChanged(
    int logicalIndex, Qt::SortOrder order)
{
    Q_UNUSED(logicalIndex)
    Q_UNUSED(order)
    Q_Q(TcSortPaginationTableView);
    if (!q->isSortingEnabled() || pageRowCount < 0)
    {
        return;
    }
    Q_EMIT q->fetchDataRequested();
}

void TcSortPaginationTableViewPrivate::_q_paginatorClicked(
        const QString &link)
{
    if (pageRowCount < 0)
    {
        return;
    }
    if (link.left(5) == "page:")
    {
        int iPage = link.mid(5).toInt();
        if (iPage > 0)
        {
            this->page = iPage;
            Q_Q(TcSortPaginationTableView);
            Q_EMIT q->fetchDataRequested();
        }
    }
}


void TcSortPaginationTableViewPrivate::_q_onColumnShown(bool checked)
{
    Q_Q(TcSortPaginationTableView);
    QAction *action = qobject_cast<QAction *>(q->sender());
    if (action)
    {
        int col = action->data().toInt();
        if (col > -1 && col < q->model()->columnCount())
        {
            q->horizontalHeader()->setSectionHidden(col, !checked); 
        }
    }
}

TcSortPaginationTableView::TcSortPaginationTableView(QWidget *parent)
    : QTableView(parent), d_ptr(new TcSortPaginationTableViewPrivate(this))
{
    //horizontalHeader()->setSectionsMovable(true);
    connect(horizontalHeader(), 
            SIGNAL(sortIndicatorChanged(int, Qt::SortOrder)),
            this, 
            SLOT(_q_sortIndicatorChanged(int, Qt::SortOrder)));
}

TcSortPaginationTableView::~TcSortPaginationTableView()
{
    delete d_ptr;
}

int TcSortPaginationTableView::pageRowCount() const
{
    Q_D(const TcSortPaginationTableView);
    return d->pageRowCount;
}

int TcSortPaginationTableView::page() const
{
    Q_D(const TcSortPaginationTableView);
    return d->page;
}

int TcSortPaginationTableView::sortSection() const
{
    return horizontalHeader()->sortIndicatorSection();
}

Qt::SortOrder TcSortPaginationTableView::sortOrder() const
{
    return horizontalHeader()->sortIndicatorOrder();
}

void TcSortPaginationTableView::setPageRowCount(int pageRowCount /* = -1 */)
{
    Q_D(TcSortPaginationTableView);
    d->pageRowCount = pageRowCount;
}

void TcSortPaginationTableView::fetchData(int page /* = -1 */, 
        int section /* = -1 */, 
        Qt::SortOrder order /* = Qt::AscendingOrder */)
{
    Q_D(TcSortPaginationTableView);
    if (page > 0)
    {
        d->page = page;
    }
    if (isSortingEnabled())
    {
        int iSection = section < 0 ? sortSection() : section;
        Qt::SortOrder iOrder = section < 0 ? sortOrder() : order;

        if (iSection == sortSection() && iOrder == sortOrder())
        {
            Q_EMIT fetchDataRequested();
        }
        else
        {
            horizontalHeader()->setSortIndicator(iSection, iOrder);
        }
    }
    else
    {
        Q_EMIT fetchDataRequested();
    }
}

void TcSortPaginationTableView::setPaginator(QLabel *label)
{
    Q_D(TcSortPaginationTableView);
    if (d->paginator == label)
    {
        return;
    }
    if (d->paginator != NULL)
    {
        disconnect(d->paginator, SIGNAL(linkActivated(const QString &)),
                this, SLOT(_q_paginatorClicked(const QString &)));
    }
    d->paginator = label;
    if (d->paginator != NULL)
    {
        connect(d->paginator, SIGNAL(linkActivated(const QString &)),
                this, SLOT(_q_paginatorClicked(const QString &)));
    }
}

void TcSortPaginationTableView::setPageInfo(int page, int totalCount)
{
    Q_D(TcSortPaginationTableView);
    d->page = page;
    d->totalCount = totalCount;

    if (d->paginator == NULL)
    {
        return;
    }
    // 获取数量,生成分页符
    QStringList slHTML;
    if (d->pageRowCount < 1)
    {
        // 只显示数量
        slHTML << tr("<span>Total %1</span>").arg(totalCount);
    }
    else if (totalCount == 0)
    {
        // 查询无数据
        slHTML << tr("<span>Total %1</span>").arg(totalCount);
    }
    else
    {
        // 显示分页
        int iPageCount = qCeil((totalCount * 1.0) / d->pageRowCount);
        if (d->page > iPageCount)
        {
            d->page = iPageCount;
        }
        if (d->page <= 1)
        {
            slHTML << tr("<span>|&lt;</span>")
                << tr("<span>&lt;&lt;</span>");
        }
        else
        {
            slHTML << tr("<a href=\"page:1\">|&lt;</a>")
                << tr("<a href=\"page:%1\">&lt;&lt;</a>")
                .arg(d->page - 1);
        }

        {
            int iPageRange = 10;
            if (iPageRange > iPageCount)
            {
                iPageRange = iPageCount;
            }
            int delta = qCeil(iPageRange / 2.0);
            int iLowerBound;
            int iUpperBound;
            if (d->page - delta > iPageCount - iPageRange)
            {
                iLowerBound = iPageCount - iPageRange + 1;
                iUpperBound = iPageCount;
            }
            else
            {
                if (d->page - delta < 0)
                {
                    delta = d->page;
                }
                int iOffset = d->page - delta;
                iLowerBound = iOffset + 1;
                iUpperBound = iOffset + iPageRange;
            }
            for (int i = iLowerBound; i <= iUpperBound; i++)
            {
                if (i == d->page)
                {
                    slHTML << tr("<span>[%1]</span>").arg(i);
                }
                else
                {
                    slHTML << tr("<a href=\"page:%1\">"
                            "[%1]</a>").arg(i);
                }
            }
        }

        //....
        if (d->page >= iPageCount)
        {
            slHTML << tr("<span>&gt;&gt;</span>")
                << tr("<span>&gt;|</span>");
        }
        else
        {
            slHTML << tr("<a href=\"page:%1\">&gt;&gt;</a>")
                .arg(d->page + 1)
                << tr("<a href=\"page:%1\">&gt;|</a>")
                .arg(iPageCount);
        }
        slHTML << tr("Total %1 Pages, %2 Records")
            .arg(iPageCount).arg(totalCount);
    }
    d->paginator->setText(slHTML.join("&nbsp;"));
}

void TcSortPaginationTableView::createTitleMenus()
{
    QString strObjectNamePre = QString("action%1TitleMenu_")
        .arg(metaObject()->className());
    QHeaderView *view = horizontalHeader();
    QList<QAction*> actions = view->actions();
    for (int i = actions.size() - 1; i > -1; i--)
    {
        if (actions[i]->objectName().indexOf(strObjectNamePre) == 0)
        {
            view->removeAction(actions[i]);
        }
    }

    if (model())
    {
        for (int i = 0; i < view->count(); i++)
        {
            QAction *action = new QAction(model()->headerData(i, 
                        Qt::Horizontal).toString(), view);
            action->setObjectName(strObjectNamePre + QString::number(i));
            action->setData(i);
            action->setCheckable(true);
            action->setChecked(!view->isSectionHidden(i));
            connect(action, SIGNAL(triggered(bool)),
                    this, SLOT(_q_onColumnShown(bool)));
            view->addAction(action);
        }
        view->setContextMenuPolicy(Qt::ActionsContextMenu);
    }
}

#include "moc_tcsortpaginationtableview.cpp"
