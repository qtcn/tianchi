// **************************************************************************
// Tianchi C++ library for Qt (open source)
// ��ع���Դ���
// ��Ȩ���� (C) ��ع���Դ��⿪����
// ��ȨЭ�飺���Ķ���ع���Դ��⸽������ȨЭ��
// **************************************************************************
// �ĵ�˵������QVariantMap��Ϊ�����е�model,ֻ��׷�Ӻ����,���ɲ�����ɾ��
// ==========================================================================
// ������־��
// ����         ��Ա        ˵��
// --------------------------------------------------------------------------
// 2013.06.07   XChinux     ����
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
    /// @brief  ���巵��ÿ������ʵ�����ݵĽ�ɫ
    TcDataRole = Qt::UserRole + 999
};

class TcVariantMapTableModelPrivate;

/// @brief  ��QVariantMap��Ϊ�����е�model,ֻ��׷�Ӻ����,�����������������
///         ɾ��,ʹ��ʱ��Ҫ�ֳ������֣�
///             1. ����TcVariantMapTableModel,����������������
///             2. �������(����������Լ����������)
///             3. ��ȡָ������������
/// @brief  1. ����model����������������
/// @code
///    TcVariantMapTableModel *model = new TcVariantMapTableModel(this);
///    model->addTitle("col1",    "Title 1"));
///    model->addTitle("col2",    "Title 2", 2));// �����У�������λС��
///    model->addTitle("col3",    "Title 3"));
///    model->addTitle("__col4",  "Title 4"));  // ��ԭʼ����
///    tableView->setModel(model);
/// @endcode
/// 
/// @brief  2. �������
/// @code
///     model->clearData(); // ���ԭ����������(�������ⲻ��)
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
/// @brief  3. ��ȡָ������������
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
///     // ��ȡѡ���е�col1�ֶ�ֵ
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

    // �̳�ʵ�ֲ��ֿ�ʼ-----------------
    virtual Qt::ItemFlags flags(const QModelIndex &index) const;

    virtual QVariant data(const QModelIndex &index, 
            int role = Qt::DisplayRole) const;

    virtual QVariant headerData(int section, Qt::Orientation orientation, 
            int role = Qt::DisplayRole) const;

    virtual int rowCount(
            const QModelIndex &parent = QModelIndex()) const;

    /// @brief  ���غ����ͷ(������)����
    virtual int columnCount(
            const QModelIndex &parent = QModelIndex()) const;

    virtual bool setData(const QModelIndex &index, const QVariant &value, 
            int role = Qt::EditRole);

    /// @brief  ֱ�ӷ���false,�������趨����������ͷ
    virtual bool setHeaderData(int section, Qt::Orientation orientation, 
            const QVariant &value, int role = Qt::EditRole);

    // �̳�ʵ�ֲ��ֽ���-----------------

    /// @brief  ����flags����
    void setFlags(const QModelIndex &index, Qt::ItemFlags flags);

    /// @brief  ����ĳһ���Ƿ��ѡ��
    void setCheckable(int row, int col, bool checkable);

    /// @brief  ����ĳһ���Ƿ�ѡ��
    void setChecked(int row, int col, bool checked);

    /// @brief  �ж�ĳһ���Ƿ��ѡ��
    bool isCheckable(int row, int col) const;

    /// @brief  �ж�ĳһ���Ƿ�ѡ��
    bool isChecked(int row, int col) const;

    /// @brief  ��ӱ���(�����ͷ)����
    /// @param  field   �ֶ���
    /// @param  title   ������ʾֵ
    /// @param  precision �����������,�趨����ʾ����(-1��ʾ��Ч)
    void addTitle(const QString &field, const QString &title, 
            int precision = -1);

    /// @brief  ���������(����)
    /// @param  data    ����������
    void addData(const QList<QVariantMap> &data);

    /// @brief  ���������(һ��)
    /// @param  row     һ��������
    void addData(const QVariantMap &row);

    /// @brief  �������������г�����
    const QList<QVariantMap>& data() const;

    /// @brief  ����ĳһ������(�����Ч�򷵻�QVariantMap())
    QVariantMap data(int row) const;

    /// @brief  �������б��ⶨ��(firstΪfield, secondΪtitle)
    const QList<QPair<QString, QString> >& title() const;

    /// @brief  ����ĳһ�б��ⶨ��(firstΪfield, secondΪtitle)
    QPair<QString, QString> title(int col) const;

    /// @brief  ����ĳ�ֶ�����ʾ����
    void setNumberColumn(const QString &field, int precision);
    
    /// @brief  ����ĳ����ʾ����
    void setNumberColumn(int column, int precision);

    /// @brief  �������������
    void clearData();

    /// @brief  ������������м������趨
    void clear();
private:
    Q_DISABLE_COPY(TcVariantMapTableModel)
    Q_DECLARE_PRIVATE(TcVariantMapTableModel)
    TcVariantMapTableModelPrivate* const d_ptr;
};

#endif  // TIANCHI_TCVARIANTMAPTABLEMODEL_H
