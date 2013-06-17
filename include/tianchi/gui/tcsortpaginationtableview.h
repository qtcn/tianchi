// **************************************************************************
// Tianchi C++ library for Qt (open source)
// ��ع���Դ���
// ��Ȩ���� (C) ��ع���Դ��⿪����
// ��ȨЭ�飺���Ķ���ع���Դ��⸽������ȨЭ��
// **************************************************************************
// �ĵ�˵����������ͷ�ҳ��TableView
// ==========================================================================
// ������־��
// ����         ��Ա        ˵��
// --------------------------------------------------------------------------
// 2013.06.07   XChinux     ����
// ==========================================================================
/// @file tcsortpaginationtableview.h 
// ==========================================================================
#ifndef TIANCHI_TCSORTPAGINATIONTABLEVIEW_H
#define TIANCHI_TCSORTPAGINATIONTABLEVIEW_H

#include <tianchi/tcglobal.h>
#include <QTableView>

class QLabel;

class TcSortPaginationTableViewPrivate;

/// @brief  ������ͷ�ҳ��TableView,ʹ��ʱ��Ҫ������:
///             1. ��ʼ��TcSortPaginationTableView
///             2. �����ȡ��������(����/��ҳ/����)
/// @brief  1. ��ʼ��TcSortPaginationTableView
/// @code
///     model = new QStandardItemModel(this);
///     ......
///     tableView->setModel(model);
///     tableView->setPaginator(labelPaginator);    // ������ʾ��ҳ����label
///     tableView->setPageRowCount(20);             // ����ÿҳ��ʾ��¼��
///     tableView->createTitleMenus();   // �����������Ҽ��˵�,����ʾ/������
///     connect(tableView, SIGNAL(fetchDataRequested()),
///             this, SLOT(fetchData()));
/// @endcode
/// @brief  2. �����ȡ��������(����/��ҳ/����)
/// @code
/// void XXXX::fetchData()
/// {
///     model->removeRows(0, model->rowCount());
///     QSqlQuery q;
///     QString strSql = "SELECT col1, col2, col3, col4 FROM table1 "
///                     "WHERE 1 = 1 ";
///     QString strSqlCnt = "SELECT COUNT(*) FROM table1 "
///                     "WHERE 1 = 1 ";
///     // ��������
///     strSql += " AND col1 LIKE 'xxx%%'";
///     strSqlCnt += " AND col1 LIKE 'xxx%%'";
///     // �����Ƿ�����,�趨order���
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
///     {   // �����������,��ʹ��Ĭ������
///         strSql += " ORDER BY col1";
///     }
///     int count = 0;  // ��������������ܼ�¼��
///     // �����Ƿ��ҳ�趨����ȡ��ǰҳ����
///     if (tableView->pageRowCount() > 0)
///     {   // ��ҳ
///         strSql += QString(" LIMIT %1 OFFSET %2")
///                         .arg(tableView->pageRowCount())
///                         .arg((tableView->page() - 1) 
///                                         * tableView->pageRowCount());
///         q.exec(strSql);
///         while (q.next())
///         {
///             .....// ��ȡ��ǰҳ����
///         }
///         // ��ȡ��������������������
///         q.exec(strSqlCnt);
///         if (q.next())
///         {
///             count = q.value(0).toInt();
///         }
///     }
///     else
///     {   // ����ҳ
///         q.exec(strSql);
///         while (q.next())
///         {
///             ......// ����ҳ�����Ի�ȡ���з�������������
///             count++;
///         }
///     }
///     // ������÷�ҳ��Ϣ
///     tableView->setPageInfo(tableView->page(), count);
/// @endcode
class TIANCHI_API TcSortPaginationTableView : public QTableView
{
    Q_OBJECT
public:
    TcSortPaginationTableView(QWidget *parent = 0);
    virtual ~TcSortPaginationTableView();

    /// @brief  ����ÿҳ��ʾ��¼����
    int pageRowCount() const;
    /// @brief  ���ص�ǰ����ҳ��
    int page() const;
    /// @brief  ���ص�ǰ����������
    int sortSection() const;
    /// @brief  ���ص�ǰ����������
    Qt::SortOrder sortOrder() const;

    /// @brief  ����ÿҳ��ʾ��¼����, -1��ʾ����ҳ
    void setPageRowCount(int pageRowCount = -1);

    /// @brief  ����paginator��ҳ���ַ���
    /// @param  page        ��ǰҳ��
    /// @param  totalCount  �ܼ�¼��
    void setPageInfo(int page, int totalCount);

    /// @brief  ���÷�ҳ����
    void setPaginator(QLabel *label);

    /// @biref  Ϊ���ͷ�����Ҽ������˵�
    void createTitleMenus();
Q_SIGNALS:
    /// @brief����������ʱ����,��������ͻ�ҳ
    void fetchDataRequested();
public Q_SLOTS:
    /// @brief  ��ȡ����(ʵ�����ڲ��Ƿ���fetchDataRequested()�ź�
    /// @param  page    ָ��ҳ��(-1��ʾ��ǰҳ�벻��)
    /// @param  section ָ��������(-1��ʾ�����в���)
    /// @param  order   ָ��������(sectionΪ-1ʱ������)
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
