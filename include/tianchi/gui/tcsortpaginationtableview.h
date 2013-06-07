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

/// @brief  ������ͷ�ҳ��TableView
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
