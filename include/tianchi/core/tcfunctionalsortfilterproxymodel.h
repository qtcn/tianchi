// **************************************************************************
// Tianchi C++ library for Qt (open source)
// ��ع���Դ���
// ��Ȩ���� (C) ��ع���Դ��⿪����
// ��ȨЭ�飺���Ķ���ع���Դ��⸽������ȨЭ��
// **************************************************************************
// �ĵ�˵������������˲���(QVariantMap)��ʹ�������˺������й��˵�ģ��
// ==========================================================================
// ������־��
// ����         ��Ա        ˵��
// --------------------------------------------------------------------------
// 2013.06.07   XChinux     ����
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

/// @brief  ���˺�������,��һ������Ϊ��������,�ڶ�������ΪsourceModel�Ķ�Ӧ��
///         ��һ��index
typedef bool (*TcFunctionalSortFilterProxyModelFilterFunction)( \
        const QVariantMap &, const QModelIndex &);

class TcFunctionalSortFilterProxyModelPrivate;

/// @brief  ��������˲���(QVariantMap)��ʹ�������˺������й��˵�
///         SortFilterProxyModel,ʹ��ʱ��������:
///             1. ������˺���
///             2. ����TcFunctionalSortFilterProxyModelʵ�������趨���˺���
///             3. �����ı�ʱ������setFilterParam()Ӧ�ù��˲�����ʹ����Ч
/// @brief  1.�ȶ�����˺���(ʾ��ΪMyFilter)
/// @code
/// bool MyFilter(const QVariantMap &param, const QModelIndex &index)
/// {
///     QModelIndex idx1 = index;                       // ��һ��
///     QModelIndex idx2 = idx1.sibling(idx1.row(), 1); // �ڶ���
///
///     QString str1 = param["col1"].toString();        // ��һ�й�������
///     QString str2 = param["col2"].toString();        // �ڶ��й�������
///
///     // �����һ�����˲�����Ϊ�գ���ôҪ���һ����ʾ�ַ���������str1��ͷ
///     if (!str1.isEmpty())
///     {
///         if (idx1.data(Qt::DisplayRole).toString().indexOf(str1) != 0)
///         {
///             return false;
///         }
///     }
///     
///     // ����ڶ������˲�����Ϊ�գ���ôҪ��ڶ�����ʾ�ַ����������str2
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
/// @brief  2.����ģ��ʱ�����ù��˺���
/// @code
/// model = new QStandardItemModel(this);
/// ......
/// TcFunctionalSortFilterProxyModel *proxy = 
///                                 new TcFunctionalSortFilterProxyModel(this);
/// proxy->setFilterFunction(&MyFilter);
/// proxy->setSourceModel(model);
/// @endcode
///
/// @brief  3.��������������󣬵���setFilterParam()��Ӧ�ù��˲���
/// @code
/// QVariantMap param;
/// param["col1"] = "0102"; // ����Ҫ�������"0102"��ͷ���ַ���
/// param["col2"] = "HFX";  // ����Ҫ����˰���"HFX"���ַ���
/// proxy->setFilterParam(param);
/// @endcode
class TIANCHI_API TcFunctionalSortFilterProxyModel : 
    public QSortFilterProxyModel
{    
    Q_OBJECT
public:
    TcFunctionalSortFilterProxyModel(QObject * parent = 0);
    ~TcFunctionalSortFilterProxyModel();
    /// @brief  �趨���˺���
    void setFilterFunction(
            TcFunctionalSortFilterProxyModelFilterFunction func);
            //std::function<bool(const QVariantMap &, const QModelIndex &)> func);  // TODO C++11
public Q_SLOTS:
    /// @brief  �趨���˲���
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
