#ifndef TIANCHI_TCDATAACCESS_H
#define TIANCHI_TCDATAACCESS_H

#include <tianchi/tcglobal.h>

#include <QString>
#include <QLatin1String>
#include <QVariant>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlDatabase>
#include <QVariantMap>
#include <QStringList>
#include <QVariantList>

class TcDataAccess;

// 数据访问语句类
class TIANCHI_API TcDataAccessStatement
{
public:
    TcDataAccessStatement();
    // 使用表名table和字段列表fields初始化
    TcDataAccessStatement(const QString &table, 
            const QString &fields = QString("*"));
    ~TcDataAccessStatement();

    // 清除所有设定
    void clear();

    // 添加字段列表fields
    TcDataAccessStatement& select(const QString &fields = QString("*"));

    // 添加from表名tables
    TcDataAccessStatement& from(const QString &tables);

    // 增加左连接表table, cond为条件,bind为条件中的"?"值
    TcDataAccessStatement& leftJoin(const QString &table, 
            const QString &cond,
            const QVariantList &bind = QVariantList());

    // 增加条件子句expr(AND连接), bind为条件中的"?"值
    TcDataAccessStatement& where(const QString &expr, 
            const QVariantList &bind = QVariantList());

    // 增加条件子句expr(OR连接), bind为条件中的"?"值
    TcDataAccessStatement& orWhere(const QString &expr, 
            const QVariantList &bind = QVariantList());

    // 增加group字段fields
    TcDataAccessStatement& group(const QString &fields);
    
    // 增加order字段fields
    TcDataAccessStatement& order(const QString &fields);

    // 增加limit限制
    TcDataAccessStatement& limit(int count, int offset = 0);

    // 增加limit限制
    TcDataAccessStatement& limitPage(int page, int rowCount);

    // 返回完整的SQL语句
    QString toString() const;

    // 返回WHERE子句
    QString whereString() const;

    // 返回WHERE中"?"的bind
    QVariantList whereBind() const;

    // 返回所有"?"的bind
    QVariantList bind() const;
private:
    QStringList _select;
    QStringList _from;
    QStringList _leftJoin;
    QStringList _where;
    QStringList _group;
    QStringList _order;

    QString _limit;
    QVariantList _leftJoinBind;
    QVariantList _whereBind;
};


// 数据访问类
class TIANCHI_API TcDataAccess
{
public:
    TcDataAccess(const QString &connectionName 
            = QLatin1String(QSqlDatabase::defaultConnection));
    TcDataAccess(const QSqlDatabase &other);
    ~TcDataAccess();
    // 创建一个DataAccess对象，如果创建失败，返回NULL,使用完后请delete
    static TcDataAccess* db(const QString &connectionName 
            = QLatin1String(QSqlDatabase::defaultConnection));

    // 返回connectionName
    QString connectionName() const {return _db->connectionName();}

    // 返回QSqlQuery对象
    QSqlQuery sqlQuery() const {return QSqlQuery(*_db);}
    // 返回QSqlDatabase对象
    QSqlDatabase sqlDatabase() const {return *_db;}

    // 返回sql查询的所有记录集
    QList<QVariantMap> fetchAll(const QString &sql,
            const QVariantList &bind = QVariantList());
    QList<QVariantMap> fetchAll(const TcDataAccessStatement &stat,
            const QVariantList &bind = QVariantList());

    // 返回sql查询的第一行
    QVariantMap fetchRow(const QString &sql,
            const QVariantList &bind = QVariantList());
    QVariantMap fetchRow(const TcDataAccessStatement &stat,
            const QVariantList &bind = QVariantList());

    // 返回sql查询的第一列
    QVariantList fetchCol(const QString &sql,
            const QVariantList &bind = QVariantList());
    QVariantList fetchCol(const TcDataAccessStatement &stat,
            const QVariantList &bind = QVariantList());

    // 返回第一行第一列数据
    QVariant fetchOne(const QString &sql,
            const QVariantList &bind = QVariantList());
    QVariant fetchOne(const TcDataAccessStatement &stat,
            const QVariantList &bind = QVariantList());

    // 将第一列作为key,将第二列作为值返回
    template <typename T> QMap<T, QVariant> fetchPairs(
                const QString &sql,
                const QVariantList &bind = QVariantList())
    {
        _prepareExec(sql, bind);

        QMap<T,QVariant> rows;
        QVariant val;
        while (_query->next())
        {
            val = _query->value(0);
            if (val.type() == QVariant::String)
            {
                val = val.toString().trimmed();
            }
            rows[qvariant_cast<T>(val)] = _query->value(1);
        }
        return rows;
    }

    template <typename T> QMap<T, QVariant> fetchPairs(
                const TcDataAccessStatement &stat,
                const QVariantList &bind = QVariantList())
    {
        return fetchPairs<T>(stat.toString(),
                QVariantList() << stat.bind() << bind);
    }

    // 将第一列作为键，将每行作为值返回
    template <typename T> QMap<T, QVariantMap> fetchAssoc(
                const QString &sql, 
                const QVariantList &bind = QVariantList())
    {
        _prepareExec(sql, bind);

        QMap<T,QVariantMap> rows;
        QVariantMap row;
        QVariant val;
        while (_query->next())
        {
            QSqlRecord rec = _query->record();
            for (int i = rec.count() - 1; i > -1; i--)
            {
                row[rec.fieldName(i)] = rec.value(i);
            }
            val = rec.value(0);
            if (val.type() == QVariant::String)
            {
                val = val.toString().trimmed();
            }
            rows[qvariant_cast<T>(val)] = row;
            row.clear();
        }
        return rows;
    }

    template <typename T> QMap<T, QVariantMap> fetchAssoc(
                const TcDataAccessStatement &stat, 
                const QVariantList &bind = QVariantList())
    {
        return fetchAssoc<T>(stat.toString(),
                QVariantList() << stat.bind() << bind);
    }

    // 为sql语句添加limit参数,目前只支持MySQL、PGSQL、SQLite、MSSQL,对于不支持
    // 的数据库类型，直接返回空字符串
    QString limitPage(const QString &sql, int page, int rowCount) const;
    QString limit(const QString &sql, int count, int offset = 0) const;

    // 返回上次插入的ID,目前的实现无意义
    QVariant lastInsertId(const QString &table = QString(), 
            const QString &primaryKey = QString()) const;
    // 返回上次查询的错误信息
    QSqlError lastError() const;

    // 删除表table中的记录,条件为where, bind为"?"绑定
    int doDelete(const QString &table, 
            const QString &where = QString(),
            const QVariantList &bind = QVariantList());


    // 更新表table中的记录,字段及值为field, 条件为where, bind为"?"绑定
    int doUpdate(const QString &table, const QVariantMap &field,
            const QString &where = QString(),
            const QVariantList &bind = QVariantList());

    // 插入表table中的记录,字段及值为field
    int doInsert(const QString &table, const QVariantMap &field);
    TcDataAccess& operator=(const TcDataAccess &da);
    TcDataAccess& operator=(const QSqlDatabase &db);
private:
    QSqlDatabase *_db;
    QSqlQuery *_query;
    void _prepareExec(const QString &sql, const QVariantList &bind);
};

typedef TcDataAccess TcDA;
typedef TcDataAccessStatement TcDAS;

#endif
