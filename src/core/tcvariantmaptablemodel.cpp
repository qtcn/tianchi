// **************************************************************************
// Tianchi C++ library for Qt (open source)
// 天池共享源码库
// 版权所有 (C) 天池共享源码库开发组
// 授权协议：请阅读天池共享源码库附带的授权协议
// **************************************************************************
// 文档说明：以QVariantMap作为数据行的model,只可追加和清除,不可插入与删除
// ==========================================================================
// 开发日志：
// 日期         人员        说明
// --------------------------------------------------------------------------
// 2013.06.07   XChinux     建立
//
// ==========================================================================
/// @file tcvariantmaptablemodel.cpp
// ==========================================================================
#include <QLocale>
#if (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
#include <QVector>
#endif
#include <tianchi/core/tcvariantmaptablemodel.h>

class TcVariantMapTableModelPrivate
{
    Q_DECLARE_PUBLIC(TcVariantMapTableModel)
public:
    explicit TcVariantMapTableModelPrivate(
            TcVariantMapTableModel *qptr) : q_ptr(qptr) {}
    ~TcVariantMapTableModelPrivate(){}
    //--------------------------------------------
    // 保存标题设定,pair的first为filed(字段), second为title(显示名称)
    QList<QPair<QString, QString> > title;
    // 保存精度控制列信息, key为字段, value为精度
    QMap<QString, int> numberCols;
    // 保存实际数据行
    QList<QVariantMap> data;
    // 保存额外属性(通过setData()设定)
    QMap<QModelIndex, QMap<int, QVariant> > extra;
    // 保存flags设定
    QMap<QModelIndex, Qt::ItemFlags> flags;
    //--------------------------------------------
    TcVariantMapTableModel* const q_ptr;
};

TcVariantMapTableModel::TcVariantMapTableModel(QObject *parent) 
    : QAbstractTableModel(parent), 
    d_ptr(new TcVariantMapTableModelPrivate(this))
{
}

TcVariantMapTableModel::~TcVariantMapTableModel()
{
    delete d_ptr;
}

Qt::ItemFlags TcVariantMapTableModel::flags(const QModelIndex &index) const
{
    Q_D(const TcVariantMapTableModel);
    return d->flags.contains(index) ? 
        d->flags[index] : QAbstractTableModel::flags(index);
}

QVariant TcVariantMapTableModel::data(const QModelIndex &index, 
        int role) const
{
    Q_D(const TcVariantMapTableModel);
    QVariant v;
    int col = index.column();
    int row = index.row();
    if (!index.isValid() || row < 0 || row >= d->data.size()
            || col < 0 || col >= d->title.size())
    {
        return v;
    }

    switch (role)
    {
        case TcDataRole:
            v = d->data[row];
            break;
        case Qt::EditRole:
            {
                const QVariant &item = d->data[row][d->title[col].first];
                v = item;
                /*
                if (v.type() == QVariant::String)
                {
                    v = v.toString().trimmed();
                }
                */
            }
            break;
        case Qt::DisplayRole:
        case Qt::ToolTipRole:
        case Qt::StatusTipRole:
        case Qt::WhatsThisRole:
            if (d->extra.contains(index) && d->extra[index].contains(role))
            {
                v = d->extra[index][role];
            }
            else
            {
                const QString &strK = d->title[col].first;
                const QVariant &item = d->data[row][strK];
                if (d->numberCols.contains(strK) && d->numberCols[strK] > -1)
                {
                    // 以系统设定的数字显示格式返回
                    int prec = d->numberCols[strK];
                    if (!item.isNull())
                    {
                        switch (item.type())
                        {
                            case QVariant::Int:
                                if (prec > 0)
                                {
                                    v = QString("%L1%2%3")
                                        .arg(item.toInt())
                                        .arg(QLocale::system().decimalPoint())
                                        .arg(QString(prec, QChar('0')));
                                }
                                else
                                {
                                    v = QString("%L1").arg(item.toInt());
                                }
                                break;
                            case QVariant::LongLong:
                                if (prec > 0)
                                {
                                    v = QString("%L1%2%3")
                                        .arg(item.toLongLong())
                                        .arg(QLocale::system().decimalPoint())
                                        .arg(QString(prec, QChar('0')));
                                }
                                else
                                {
                                    v = QString("%L1").arg(item.toLongLong());
                                }
                                break;
                            case QVariant::Double:
                                v = QString("%L1").arg(item.toDouble(), 
                                        0, 'f', prec);
                                break;
                            case QVariant::UInt:
                                if (prec > 0)
                                {
                                    v = QString("%L1%2%3")
                                        .arg(item.toUInt())
                                        .arg(QLocale::system().decimalPoint())
                                        .arg(QString(prec, QChar('0')));
                                }
                                else
                                {
                                    v = QString("%L1").arg(item.toUInt());
                                }
                                break;
                            case QVariant::ULongLong:
                                if (prec > 0)
                                {
                                    v = QString("%L1%2%3")
                                        .arg(item.toULongLong())
                                        .arg(QLocale::system().decimalPoint())
                                        .arg(QString(prec, QChar('0')));
                                }
                                else
                                {
                                    v = QString("%L1").arg(item.toULongLong());
                                }
                                break;
                            default:
                                v = item;
                        }
                    }
                }
                else
                {
                    v = item;
                    /*
                    if (v.type() == QVariant::String && !v.isNull())
                    {
                        v = v.toString().trimmed();
                    }
                    */
                }
            }
            break;
        case Qt::TextAlignmentRole:
            if (d->extra.contains(index) && d->extra[index].contains(role))
            {
                v = d->extra[index][role];
            }
            else
            {
                if (d->numberCols.contains(d->title[col].first))
                {
                    v = Qt::AlignRight + Qt::AlignVCenter;
                }
                else
                {
                    // 数字右对齐,其它左对齐
                    const QVariant &item = d->data[row][d->title[col].first];
                    switch (item.type())
                    {
                        case QVariant::Int:
                        case QVariant::Double:
                        case QVariant::LongLong:
                        case QVariant::UInt:
                        case QVariant::ULongLong:
                            v = Qt::AlignRight + Qt::AlignVCenter;
                            break;
                        default:
                            v = Qt::AlignLeft + Qt::AlignVCenter;
                    }
                }
            }
            break;
        default:
            if (d->extra.contains(index) && d->extra[index].contains(role))
            {
                v = d->extra[index][role];
            }
    }
    return v;
}

// 横表头返回title设定显示值，纵表头返回索引(从1开始)
QVariant TcVariantMapTableModel::headerData(int section, 
        Qt::Orientation orientation, int role) const
{
    Q_D(const TcVariantMapTableModel);
    QVariant v;
    if (role == Qt::DisplayRole)
    {
        if (orientation == Qt::Horizontal)
        {
            if (section < d->title.size())
            {
                v = d->title[section].second;
            }
            else
            {
                v = section + 1;
            }
        }
        else
        {
            v = section + 1;
        }
    }
    return v;
}

int TcVariantMapTableModel::rowCount(const QModelIndex &parent) const
{
    Q_D(const TcVariantMapTableModel);
    return parent.isValid() ? 0  : d->data.size();
}

int TcVariantMapTableModel::columnCount(const QModelIndex &parent) const
{
    Q_D(const TcVariantMapTableModel);
    return parent.isValid() ? 0 : d->title.size();
}

bool TcVariantMapTableModel::setData(const QModelIndex &index, 
        const QVariant &value,  int role)
{
    if (role == TcDataRole)
    {
        return false;
    }
    if (!index.isValid())
    {
        return false;
    }

    Q_D(TcVariantMapTableModel);

    int col = index.column();
    int row = index.row();
    if (row < 0 || row >= d->data.size() || col < 0 || col >= d->title.size())
    {
        return false;
    }

    if (role == Qt::EditRole)
    {
        if (d->data[row][d->title[col].first] != value)
        {
            d->data[row][d->title[col].first] = value;
            Q_EMIT dataChanged(index, index);
        }
    }
    else
    {
        if (value.isNull())
        {
            if (d->extra.contains(index))
            {
                if (d->extra[index].contains(role))
                {
                    if (d->extra[index][role] == value)
                    {
                        d->extra[index].remove(role);
                    }
                    else
                    {
                        d->extra[index].remove(role);
                        Q_EMIT dataChanged(index, index);
                    }
                    if (d->extra[index].isEmpty())
                    {
                        d->extra.remove(index);
                    }
                }
            }
        }
        else
        {
            if (!(d->extra.contains(index) && d->extra[index].contains(role)
                    && d->extra[index][role] == value))
            {
                d->extra[index][role] = value;
                Q_EMIT dataChanged(index, index);
            }
        }
    }
    return true;
}

// 不可设定值
bool TcVariantMapTableModel::setHeaderData(int section, 
        Qt::Orientation orientation, const QVariant &value, int role)
{
    Q_UNUSED(section)
    Q_UNUSED(orientation)
    Q_UNUSED(value)
    Q_UNUSED(role)
    return false;
}

//////////////////////////////////////////////////////////
void TcVariantMapTableModel::setFlags(const QModelIndex &index, 
        Qt::ItemFlags flags)
{
    Q_D(TcVariantMapTableModel);
    if (!(d->flags.contains(index) && d->flags[index] == flags))
    {
        d->flags[index] = flags;
        Q_EMIT dataChanged(index, index);
    }
}

void TcVariantMapTableModel::setCheckable(int row, int col, bool checkable)
{
    Q_D(TcVariantMapTableModel);
    QModelIndex idx = index(row, col);
    if (d->flags.contains(idx))
    {
        if (d->flags[idx].testFlag(Qt::ItemIsUserCheckable))
        {
            if (!checkable)
            {
                d->flags[idx] ^= Qt::ItemIsUserCheckable;
                Q_EMIT dataChanged(idx, idx
#if (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
                        ,QVector<int>() << Qt::CheckStateRole
#endif
                        );
            }
        }
        else
        {
            if (checkable)
            {
                d->flags[idx] |= Qt::ItemIsUserCheckable;
                Q_EMIT dataChanged(idx, idx
#if (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
                        ,QVector<int>() << Qt::CheckStateRole
#endif
                        );
            }
        }
    }
    else
    {
        if (checkable)
        {
            d->flags[idx] = Qt::ItemIsEnabled | Qt::ItemIsSelectable 
                | Qt::ItemIsUserCheckable;
            Q_EMIT dataChanged(idx, idx
#if (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
                        ,QVector<int>() << Qt::CheckStateRole
#endif
                        );
        }
    }
}

void TcVariantMapTableModel::setChecked(int row, int col, bool checked)
{
    Q_D(TcVariantMapTableModel);
    QModelIndex idx = index(row, col);
    if (d->extra.contains(idx) && d->extra[idx].contains(Qt::CheckStateRole))
    {
        if (d->extra[idx][Qt::CheckStateRole] == Qt::Checked)
        {
            if (!checked)
            {
                d->extra[idx][Qt::CheckStateRole] = Qt::Unchecked;
                Q_EMIT dataChanged(idx, idx
#if (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
                        ,QVector<int>() << Qt::CheckStateRole
#endif
                        );
            }
        }
        else
        {
            if (checked)
            {
                d->extra[idx][Qt::CheckStateRole] = Qt::Checked;
                Q_EMIT dataChanged(idx, idx
#if (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
                        ,QVector<int>() << Qt::CheckStateRole
#endif 
                        );
            }
        }
    }
    else
    {
        if (checked)
        {
            d->extra[idx][Qt::CheckStateRole] = Qt::Checked;
            Q_EMIT dataChanged(idx, idx
#if (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
                    ,QVector<int>() << Qt::CheckStateRole
#endif
                    );
        }
    }
}

bool TcVariantMapTableModel::isCheckable(int row, int col) const
{
    Q_D(const TcVariantMapTableModel);
    QModelIndex idx = index(row, col);
    return d->flags.contains(idx) ? 
        d->flags[idx].testFlag(Qt::ItemIsUserCheckable) : false;
}

bool TcVariantMapTableModel::isChecked(int row, int col) const
{
    Q_D(const TcVariantMapTableModel);
    QModelIndex idx = index(row, col);
    if (d->extra.contains(idx) && d->extra[idx].contains(Qt::CheckStateRole))
    {
        return d->extra[idx][Qt::CheckStateRole] == Qt::Checked;
    }
    else
    {
        return false;
    }
}

//////////////////////////////////////////////////////////////
void TcVariantMapTableModel::addTitle(const QString &field, 
        const QString &title, int precision /*= -1*/)
{
    Q_D(TcVariantMapTableModel);
    d->title << qMakePair(field, title);
    if (precision > -1)
    {
        d->numberCols[field] = precision;
    }
}

void TcVariantMapTableModel::addData(const QList<QVariantMap> &data)
{
    Q_D(TcVariantMapTableModel);
    beginInsertRows(QModelIndex(), d->data.size(), 
            d->data.size() + data.size() - 1);
    d->data << data;
    endInsertRows();
}

void TcVariantMapTableModel::addData(const QVariantMap &row)
{
    Q_D(TcVariantMapTableModel);
    beginInsertRows(QModelIndex(), d->data.size(), d->data.size());
    d->data << row;
    endInsertRows();
}
//----------------------------------------------------

const QList<QVariantMap>& TcVariantMapTableModel::data() const
{
    Q_D(const TcVariantMapTableModel);
    return d->data;
}

QVariantMap TcVariantMapTableModel::data(int row) const
{
    Q_D(const TcVariantMapTableModel);
    if (row > -1 && row < d->data.size())
    {
        return d->data[row];
    }
    else
    {
        return QVariantMap();
    }
}

const QList<QPair<QString, QString> >& TcVariantMapTableModel::title() const
{
    Q_D(const TcVariantMapTableModel);
    return d->title;
}

QPair<QString, QString> TcVariantMapTableModel::title(int column) const
{
    Q_D(const TcVariantMapTableModel);
    if (column > -1 && column < d->title.size())
    {
        return d->title[column];
    }
    else
    {
        return QPair<QString, QString>();
    }
}

void TcVariantMapTableModel::setNumberColumn(const QString &field, 
        int precision)
{
    Q_D(TcVariantMapTableModel);
    for (int i = d->title.size() - 1; i > -1; i--)
    {
        if (d->title[i].first == field)
        {
            d->numberCols[field] = precision;
            Q_EMIT dataChanged(index(0, i), 
                index(d->data.size() - 1, i)
#if (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
                ,QVector<int>() << Qt::DisplayRole
#endif
                );
            break;
        }
    }
}

void TcVariantMapTableModel::setNumberColumn(int column, int precision)
{
    Q_D(TcVariantMapTableModel);
    if (column > -1 && column < d->title.size())
    {
        d->numberCols[d->title[column].first] = precision;
        Q_EMIT dataChanged(index(0, column), 
                index(d->data.size() - 1, column)
#if (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
                ,QVector<int>() << Qt::DisplayRole
#endif                
                );
    }
}

void TcVariantMapTableModel::clearData()
{
    Q_D(TcVariantMapTableModel);
    beginRemoveRows(QModelIndex(), 0, d->data.size() - 1);
    d->data.clear();
    d->extra.clear();
    d->flags.clear();
    endRemoveRows();
}

void TcVariantMapTableModel::clear()
{
    Q_D(TcVariantMapTableModel);
    beginResetModel();
    d->title.clear();
    d->numberCols.clear();

    d->data.clear();
    d->extra.clear();
    d->flags.clear();
    endResetModel();
}

#include "moc_tcvariantmaptablemodel.cpp"
