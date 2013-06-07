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

// �˺�������,��һ������Ϊ��������,�ڶ�������ΪsourceModel�Ķ�Ӧ�е�һ��index
typedef bool (*TcFunctionalSortFilterProxyModelFilterFunction)( \
        const QVariantMap &, const QModelIndex &);

class TcFunctionalSortFilterProxyModelPrivate;

// ��������˲���(QVariantMap)��ʹ�������˺������й��˵�ģ��
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
