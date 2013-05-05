#include <QtCore>
#include <QtSql>
#include <tianchi/Sql/DataAccess.h>

namespace Tianchi
{
DataAccess* DataAccess::db(const QString &strConn)
{
    if (QSqlDatabase::contains(strConn))
    {
        return new DataAccess(strConn);
    }
    return NULL;
}

DataAccess::DataAccess(const QString &connectionName)
{
    _db = new QSqlDatabase(QSqlDatabase::database(connectionName));
}

DataAccess::~DataAccess()
{
    delete _db;
}

QSqlQuery* DataAccess::_prepareExec(const QString &sql, 
        const QVariantList &bind)
{
    QSqlQuery *q = new QSqlQuery(*_db);
    if (bind.isEmpty())
    {
        q->exec(sql);
    }
    else
    {
        q->prepare(sql);
        QListIterator<QVariant> it(bind);
        while (it.hasNext())
        {
            q->addBindValue(it.next());
        }
        q->exec();
    }

    qDebug() << q->lastError();
    return q;
}

QList<QVariantMap> DataAccess::fetchAll(const QString &sql,
            const QVariantList &bind /* = QVariantList() */)
{
    QSqlQuery *q = _prepareExec(sql, bind);

    QList<QVariantMap> result;
    QVariantMap row;
    while (q->next())
    {
        QSqlRecord rec = q->record();
        for (int i = rec.count() - 1; i > -1; i--)
        {
            row[rec.fieldName(i)] = rec.value(i);
        }
        result << row;
        row.clear();
    }
    delete q;
    return result;
}

QList<QVariantMap> DataAccess::fetchAll(const DataAccessStatement &stat,
            const QVariantList &bind /* = QVariantList() */)
{
    return fetchAll(stat.toString(), 
            QVariantList() << stat.bind() << bind);
}

QVariantMap DataAccess::fetchRow(const QString &sql,
            const QVariantList &bind /* = QVariantList() */)
{
    QSqlQuery *q = _prepareExec(sql, bind);

    QVariantMap row;
    if (q->next())
    {
        QSqlRecord rec = q->record();
        for (int i = rec.count() - 1; i > -1; i--)
        {
            row[rec.fieldName(i)] = rec.value(i);
        }
    }
    delete q;
    return row;
}

QVariantMap DataAccess::fetchRow(const DataAccessStatement &stat,
            const QVariantList &bind /* = QVariantList() */)
{
    return fetchRow(stat.toString(), 
            QVariantList() << stat.bind() << bind);
}

QVariantList DataAccess::fetchCol(const QString &sql,
            const QVariantList &bind /* = QVariantList() */)
{
    QSqlQuery *q = _prepareExec(sql, bind);

    QVariantList rows;
    while (q->next())
    {
        rows << q->value(0);
    }
    delete q;
    return rows;
}

QVariantList DataAccess::fetchCol(const DataAccessStatement &stat,
            const QVariantList &bind /* = QVariantList() */)
{
    return fetchCol(stat.toString(), 
            QVariantList() << stat.bind() << bind);
}

QVariant DataAccess::fetchOne(const QString &sql,
            const QVariantList &bind /* = QVariantList() */)
{
    QSqlQuery *q = _prepareExec(sql, bind);

    QVariant val;
    if (q->next())
    {
        val = q->value(0);
    }
    delete q;
    return val;
}

QVariant DataAccess::fetchOne(const DataAccessStatement &stat,
            const QVariantList &bind /* = QVariantList() */)
{
    return fetchOne(stat.toString(),
            QVariantList() << stat.bind() << bind);
}

QString DataAccess::limitPage(const QString &sql, int page, int rowCount)
{
    return QString("%1 LIMIT %2 OFFSET %3").arg(sql).arg(rowCount)
        .arg((page - 1) * rowCount);
}

QString DataAccess::limit(const QString &sql, int count, int offset/*=0*/)
{
    return QString("%1 LIMIT %2 OFFSET %3").arg(sql).arg(count).arg(offset);
}

QVariant DataAccess::lastInsertId(const QString &table, 
        const QString &primaryKey)
{
    return _lastInsertId;
}

int DataAccess::doDelete(const QString &table, const QString &where /* = QString() */, const QVariantList &bind /* = QVariantList() */)
{
    QString sql = "DELETE FROM " + table;
    if (!where.isEmpty())
    {
        sql += " WHERE " + where;
    }
    
    QSqlQuery *q = _prepareExec(sql, bind);
    int iNumRowsAffected = q->numRowsAffected();
    delete q;
    return iNumRowsAffected;
}

int DataAccess::doUpdate(const QString &table, const QVariantMap &field,
            const QString &where /*= QString() */,
            const QVariantList &bind /*= QVariantList() */)
{
    QSqlQuery q(*_db);


    QVariantList bind2;

    QStringList slField;
    {
        QMapIterator<QString, QVariant> it(field);
        while (it.hasNext())
        {
            it.next();
            slField << QString("%1 = ?").arg(it.key());
            bind2 << it.value();
        }
    }
    bind2 << bind;

    QString sql = QString("UPDATE %1 SET %2").arg(table)
        .arg(slField.join(", "));

    if (!where.isEmpty())
    {
        sql += " WHERE " + where;
    }

    q.prepare(sql);
    {
        QListIterator<QVariant> it(bind2);
        while (it.hasNext())
        {
            q.addBindValue(it.next());
        }
    }
    q.exec();

    qDebug() << q.lastError();

    return q.numRowsAffected();
}

int DataAccess::doInsert(const QString &table, const QVariantMap &field)
{
    QSqlQuery q(*_db);


    QVariantList bind2;

    QStringList slField;
    QStringList slField2;
    {
        QMapIterator<QString, QVariant> it(field);
        while (it.hasNext())
        {
            it.next();
            slField << it.key();
            slField2 << "?";
            bind2 << it.value();
        }
    }

    QString sql = QString("INSERT INTO %1(%2) VALUES(%3)").arg(table)
        .arg(slField.join(", ")).arg(slField2.join(", "));

    q.prepare(sql);
    {
        QListIterator<QVariant> it(bind2);
        while (it.hasNext())
        {
            q.addBindValue(it.next());
        }
    }
    q.exec();

    _lastInsertId = q.lastInsertId();
    qDebug() << q.lastError();

    return q.numRowsAffected();
}

DataAccessStatement::DataAccessStatement()
{
}

DataAccessStatement::DataAccessStatement(const QString &table, 
            const QString &fields /* = QString("*") */)
{
    _from << table;
    _select << fields;
}

DataAccessStatement::~DataAccessStatement()
{
}

DataAccessStatement& DataAccessStatement::select(const QString &fields 
        /* = QString("*") */)
{
    _select << fields;
    return *this;
}

DataAccessStatement& DataAccessStatement::from(const QString &tables)
{
    _from << tables;
    return *this;
}

DataAccessStatement& DataAccessStatement::leftJoin(const QString &table, 
        const QString &cond, const QVariantList &bind /*= QVariantList()*/)
{
    _leftJoin << QString("LEFT JOIN %1 ON %2").arg(table).arg(cond);
    _leftJoinBind << bind;
    return *this;
}

DataAccessStatement& DataAccessStatement::where(const QString &expr, 
            const QVariantList &bind /* = QVariantList() */)
{
    if (_where.isEmpty())
    {
        _where << QString("(%1)").arg(expr);
    }
    else
    {
        _where << QString("AND (%1)").arg(expr);
    }
    _whereBind << bind;
    return *this;
}

DataAccessStatement& DataAccessStatement::orWhere(const QString &expr, 
            const QVariantList &bind /* = QVariantList() */)
{
    _where << QString("OR (%1)").arg(expr);
    _whereBind << bind;
    return *this;
}

DataAccessStatement& DataAccessStatement::group(const QString &fields)
{
    _group << fields;
    return *this;
}

DataAccessStatement& DataAccessStatement::order(const QString &fields)
{
    _order << fields;
    return *this;
}

DataAccessStatement& DataAccessStatement::limit(int count, 
        int offset /* = 0 */)
{
    _limit = QString("%1 OFFSET %2").arg(count).arg(offset);
    return *this;
}

DataAccessStatement& DataAccessStatement::limitPage(int page, int rowCount)
{
    _limit = QString("%1 OFFSET %2").arg(rowCount)
        .arg((page - 1) * rowCount);
    return *this;
}

QString DataAccessStatement::toString() const
{
    QString sql = QString("SELECT %1 FROM %2 %3").arg(_select.join(","))
        .arg(_from.join(","))
        .arg(_leftJoin.join("\n"));
    if (!_where.isEmpty())
    {
        sql += "\nWHERE " + _where.join("\n");
    }
    if (!_group.isEmpty())
    {
        sql += "\nGROUP BY " + _group.join(", ");
    }
    if (!_order.isEmpty())
    {
        sql += "\nORDER BY " + _order.join(", ");
    }
    if (!_limit.isEmpty())
    {
        sql += "\nLIMIT " + _limit;
    }
    return sql;
}

QString DataAccessStatement::whereString() const
{
    QString sql;
    if (!_where.isEmpty())
    {
        sql += "\nWHERE " + _where.join("\n");
    }
    return sql;
}

QVariantList DataAccessStatement::whereBind() const 
{
    return _whereBind;
}

QVariantList DataAccessStatement::bind() const 
{
    QVariantList v;
    v << _leftJoinBind << _whereBind; 
    return v;
}

void DataAccessStatement::clear()
{
    _select.clear();
    _from.clear();
    _leftJoin.clear();
    _where.clear();
    _group.clear();
    _order.clear();

    _limit.clear();
    _leftJoinBind.clear();
    _whereBind.clear();
}
}
