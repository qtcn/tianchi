#include <tianchi/sql/tcdataaccess.h>
#include <QtCore>
#include <QtSql>

TcDataAccess::AttrCase TcDataAccess::_attrCase = TcDataAccess::CaseNatural;
TcDataAccess::AttrTrim TcDataAccess::_attrTrim = TcDataAccess::TrimNone;

TcDataAccess* TcDataAccess::db(const QString &strConn)
{
    if (QSqlDatabase::contains(strConn))
    {
        return new TcDataAccess(strConn);
    }
    return NULL;
}

TcDataAccess::TcDataAccess(const QString &connectionName) 
{
    _db = new QSqlDatabase();
    *_db = QSqlDatabase::database(connectionName);
    _query = new QSqlQuery(*_db);
}

TcDataAccess::TcDataAccess(const QSqlDatabase &other)
{
    _db = new QSqlDatabase(other);
    _query = new QSqlQuery(*_db);
}

TcDataAccess::~TcDataAccess()
{
    delete _query;
    if (_db->connectionName() 
            != QLatin1String(QSqlDatabase::defaultConnection))
    {
        if (_db->isOpen())
        {
            _db->close();
        }
    }
    delete _db;
}

QVariant TcDataAccess::_trim(const QVariant &val)
{
    if (val.type() == QVariant::String && !val.isNull() 
            && _attrTrim == TrimAll)
    {
        return val.toString().trimmed();
    }
    else
    {
        return val;
    }
}

QString TcDataAccess::_case(const QString &field)
{
    QString strV;
    switch (_attrCase)
    {
        case CaseLower:
            strV = field.toLower();
            break;
        case CaseUpper:
            strV = field.toUpper();
            break;
        case CaseNatural:
        default:
            strV = field;
    }
    return strV;
}

void TcDataAccess::_prepareExec(const QString &sql, 
        const QVariantList &bind)
{
    bool bOk;
    if (bind.isEmpty())
    {
        bOk = _query->exec(sql);
    }
    else
    {
        _query->prepare(sql);
        QListIterator<QVariant> it(bind);
        while (it.hasNext())
        {
            _query->addBindValue(it.next());
        }
        bOk = _query->exec();
    }
    if (!bOk)
    {
        qDebug() << _query->lastError();
    }
}

QList<QVariantMap> TcDataAccess::fetchAll(const QString &sql,
            const QVariantList &bind /* = QVariantList() */)
{
    _prepareExec(sql, bind);

    QList<QVariantMap> result;
    QVariantMap row;
    while (_query->next())
    {
        QSqlRecord rec = _query->record();
        for (int i = rec.count() - 1; i > -1; i--)
        {
            row[_case(rec.fieldName(i))] = _trim(rec.value(i));
        }
        result << row;
        row.clear();
    }
    return result;
}

QList<QVariantMap> TcDataAccess::fetchAll(const TcDataAccessStatement &stat,
            const QVariantList &bind /* = QVariantList() */)
{
    return fetchAll(stat.toString(), 
            QVariantList() << stat.bind() << bind);
}

QList<QVariantList> TcDataAccess::fetchAllList(const QString &sql,
            const QVariantList &bind /* = QVariantList() */)
{
    _prepareExec(sql, bind);

    QList<QVariantList> result;
    QVariantList row;
    QSqlRecord rec;
    while (_query->next())
    {
        rec = _query->record();
        if (result.isEmpty())
        {
            for (int i = 0; i < rec.count(); i++)
            {
                row << _case(rec.fieldName(i));
            }
            result << row;
            row.clear();
        }
        for (int i = 0; i < rec.count(); i++)
        {
            row << _trim(rec.value(i));
        }
        result << row;
        row.clear();
    }
    return result;
}

QList<QVariantList> TcDataAccess::fetchAllList(
        const TcDataAccessStatement &stat,
        const QVariantList &bind /* = QVariantList() */)
{
    return fetchAllList(stat.toString(), 
            QVariantList() << stat.bind() << bind);
}

QVariantMap TcDataAccess::fetchRow(const QString &sql,
            const QVariantList &bind /* = QVariantList() */)
{
    _prepareExec(sql, bind);

    QVariantMap row;
    if (_query->next())
    {
        QSqlRecord rec = _query->record();
        for (int i = rec.count() - 1; i > -1; i--)
        {
            row[_case(rec.fieldName(i))] = _trim(rec.value(i));
        }
    }
    return row;
}

QVariantMap TcDataAccess::fetchRow(const TcDataAccessStatement &stat,
            const QVariantList &bind /* = QVariantList() */)
{
    return fetchRow(stat.toString(), 
            QVariantList() << stat.bind() << bind);
}

QVariantList TcDataAccess::fetchCol(const QString &sql,
            const QVariantList &bind /* = QVariantList() */)
{
    _prepareExec(sql, bind);

    QVariantList rows;
    while (_query->next())
    {
        rows << _trim(_query->value(0));
    }
    return rows;
}

QVariantList TcDataAccess::fetchCol(const TcDataAccessStatement &stat,
            const QVariantList &bind /* = QVariantList() */)
{
    return fetchCol(stat.toString(), 
            QVariantList() << stat.bind() << bind);
}

QVariant TcDataAccess::fetchOne(const QString &sql,
            const QVariantList &bind /* = QVariantList() */)
{
    _prepareExec(sql, bind);
    QVariant val;
    if (_query->next())
    {
        val = _trim(_query->value(0));
    }
    return val;
}

QVariant TcDataAccess::fetchOne(const TcDataAccessStatement &stat,
            const QVariantList &bind /* = QVariantList() */)
{
    return fetchOne(stat.toString(),
            QVariantList() << stat.bind() << bind);
}

QString TcDataAccess::limitPage(const QString &sql, int page, 
        int rowCount) const
{
    int iPage = page < 1 ? 1 : page;
    int iRowCount = rowCount > 0 ? rowCount : 1;

    return this->limit(sql, iRowCount, iRowCount * (iPage - 1));
}

/**
 * 对于不支持的数据库类型，直接返回空字符串
 */
QString TcDataAccess::limit(const QString &sql, int count, 
        int offset/*=0*/) const
{
    QString strSql = sql;
    QString strDriverName = _db->driverName();
    if (strDriverName.left(6) == "QMYSQL")
    {
        // OVER
        strSql = QString("%1 LIMIT %3, %2").arg(sql).arg(count).arg(offset);
    }
    else if (strDriverName.left(4) == "QOCI")
    {
        // OVER
        strSql = QString("SELECT tc2.* \
            FROM ( \
                SELECT tc1.*, ROWNUM AS \"__TCDA_INDEX__\" \
                FROM ( %1 ) tc1 \
            ) tc2 \
            WHERE tc2.\"__TCDA_INDEX__\" BETWEEN %2 AND %3")
                 .arg(strSql).arg(offset + 1).arg(offset + count); 
    }
    else if (strDriverName.left(5) == "QODBC")
    {
        QString strDSN = _db->databaseName();

        if (strDSN.indexOf("Oracle") != -1)
        {
            // OVER
            strSql = QString("SELECT tc2.* \
                FROM ( \
                    SELECT tc1.*, ROWNUM AS \"__TCDA_INDEX__\" \
                    FROM ( %1 ) tc1 \
                ) tc2 \
                WHERE tc2.\"__TCDA_INDEX__\" BETWEEN %2 AND %3")
                     .arg(strSql).arg(offset + 1).arg(offset + count); 
        }
        else if (strDSN.indexOf("SQL Server", Qt::CaseInsensitive) > -1
                || strDSN.indexOf("SQL Server Native Client", 
                    Qt::CaseInsensitive) > -1
                || strDSN.indexOf("SQL Native Client", 
                    Qt::CaseInsensitive) > -1)
        {
            // 待增加MSSQL支持
            if (offset == 0)
            {
                strSql.replace(QRegExp("^SELECT\\s", Qt::CaseInsensitive),
                        QString("SELECT TOP %1 ").arg(count));
            }
            else
            {
                int pos = strSql.indexOf("ORDER BY", 0, Qt::CaseInsensitive);
                QString orderby;
                if (pos > -1)
                {
                    orderby = strSql.mid(pos);
                }

                QString over;
                if (orderby.isEmpty())
                {
                    over = "ORDER BY (SELECT 0)";
                }
                else
                {
                    over = orderby;
                    over.replace(
                            QRegExp("\\\"[^,]*\\\".\\\"([^,]*)\\\"", 
                                Qt::CaseInsensitive),
                            QString("\"inner_tbl\".\"$1\""));
                }
                strSql.replace(QRegExp("\\s+ORDER BY(.*)", Qt::CaseInsensitive),
                        "");

                strSql = QString("SELECT *, ROW_NUMBER() OVER (%1) "
                        "AS __TCDA_INDEX__ FROM (%2) AS inner_tbl")
                    .arg(over).arg(strSql);

                int start = offset + 1;
                int end = offset + count;

                strSql = QString("WITH outer_tbl AS (%1) SELECT * FROM "
                        "outer_tbl WHERE __TCDA_INDEX__ BETWEEN %2 AND %3")
                    .arg(strSql).arg(start).arg(end);
            }
        }
        else
        {
            strSql.clear();
        }
    }
    else if (strDriverName.left(5) == "QPSQL" 
            || strDriverName.left(7) == "QSQLITE")
    {
        // OVER
        strSql = QString("%1 LIMIT %2 OFFSET %3")
            .arg(sql).arg(count).arg(offset);
    }
    else if (strDriverName.left(6) == "QIBASE")
    {
        // OVER
        strSql = strSql.replace(QRegExp("^SELECT\\s", Qt::CaseInsensitive),
                        QString("SELECT FIRST %1 SKIP %2 ")
                        .arg(count).arg(offset));
    }
    else if (strDriverName.left(4) == "QDB2")
    {
        // OVER
        if (offset <= 0)
        {
            strSql = QString("%1 FETCH FIRST %2 ROWS ONLY")
                .arg(strSql).arg(count);
        }
        else
        {
            strSql = QString("SELECT tc2.* \
            FROM ( \
                SELECT ROW_NUMBER() OVER() AS \"__TCDA_INDEX__\", tc1.* \
                FROM ( %1 ) tc1 \
            ) tc2 \
            WHERE tc2.__TCDA_INDEX__ BETWEEN %2 AND %3")
                     .arg(strSql)
                     .arg(offset + 1)
                     .arg(offset + count);
        }
    }
    else
    {
        strSql.clear();
    }
    return strSql;
}

QVariant TcDataAccess::lastInsertId(const QString &table, 
        const QString &primaryKey) const
{
    Q_UNUSED(table)
    Q_UNUSED(primaryKey)
    return _query->lastInsertId();
}

QSqlError TcDataAccess::lastError() const
{
    return _query->lastError();
}

int TcDataAccess::doDelete(const QString &table, 
        const QString &where /* = QString() */, 
        const QVariantList &bind /* = QVariantList() */)
{
    QString sql = "DELETE FROM " + table;
    if (!where.isEmpty())
    {
        sql += " WHERE " + where;
    }
    
    _prepareExec(sql, bind);
    return _query->numRowsAffected();
}

int TcDataAccess::doUpdate(const QString &table, const QVariantMap &field,
            const QString &where /*= QString() */,
            const QVariantList &bind /*= QVariantList() */)
{
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

    _query->prepare(sql);
    {
        QListIterator<QVariant> it(bind2);
        while (it.hasNext())
        {
            _query->addBindValue(it.next());
        }
    }
    _query->exec();
    return _query->numRowsAffected();
}

int TcDataAccess::doInsert(const QString &table, const QVariantMap &field)
{
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

    _query->prepare(sql);
    {
        QListIterator<QVariant> it(bind2);
        while (it.hasNext())
        {
            _query->addBindValue(it.next());
        }
    }
    if (!_query->exec())
    {
        qDebug() << _query->lastError();
    }
    return _query->numRowsAffected();
}

TcDataAccess& TcDataAccess::operator=(const TcDataAccess &da)
{
    *_db = *(da._db);
    *_query = *(da._query);
    return *this;
}

TcDataAccess& TcDataAccess::operator=(const QSqlDatabase &db)
{
    *_db = db;
    *_query = QSqlQuery(*_db);
    return *this;
}

TcDataAccessStatement::TcDataAccessStatement()
{
}

TcDataAccessStatement::TcDataAccessStatement(const TcDataAccessStatement &da)
{
    _select = da._select;
    _from = da._from;
    _leftJoin = da._leftJoin;
    _where = da._where;
    _group = da._group;
    _order = da._order;

    _limit = da._limit;
    _leftJoinBind = da._leftJoinBind;
    _whereBind = da._whereBind;
}

TcDataAccessStatement::TcDataAccessStatement(const QString &table, 
            const QString &fields /* = QString("*") */)
{
    _from << table;
    _select << fields;
}

TcDataAccessStatement::~TcDataAccessStatement()
{
}

TcDataAccessStatement& TcDataAccessStatement::select(const QString &fields 
        /* = QString("*") */)
{
    _select << fields;
    return *this;
}

TcDataAccessStatement& TcDataAccessStatement::from(const QString &tables)
{
    _from << tables;
    return *this;
}

TcDataAccessStatement& TcDataAccessStatement::leftJoin(const QString &table, 
        const QString &cond, const QVariantList &bind /*= QVariantList()*/)
{
    _leftJoin << QString("LEFT JOIN %1 ON %2").arg(table).arg(cond);
    _leftJoinBind << bind;
    return *this;
}

TcDataAccessStatement& TcDataAccessStatement::where(const QString &expr, 
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

TcDataAccessStatement& TcDataAccessStatement::orWhere(const QString &expr, 
            const QVariantList &bind /* = QVariantList() */)
{
    _where << QString("OR (%1)").arg(expr);
    _whereBind << bind;
    return *this;
}

TcDataAccessStatement& TcDataAccessStatement::group(const QString &fields)
{
    _group << fields;
    return *this;
}

TcDataAccessStatement& TcDataAccessStatement::order(const QString &fields)
{
    _order << fields;
    return *this;
}

TcDataAccessStatement& TcDataAccessStatement::limit(int count, 
        int offset /* = 0 */)
{
    _limit = QString("%1 OFFSET %2").arg(count).arg(offset);
    return *this;
}

TcDataAccessStatement& TcDataAccessStatement::limitPage(int page, int rowCount)
{
    _limit = QString("%1 OFFSET %2").arg(rowCount)
        .arg((page - 1) * rowCount);
    return *this;
}

QString TcDataAccessStatement::toString() const
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

QString TcDataAccessStatement::whereString() const
{
    QString sql;
    if (!_where.isEmpty())
    {
        sql += "\nWHERE " + _where.join("\n");
    }
    return sql;
}

QVariantList TcDataAccessStatement::whereBind() const 
{
    return _whereBind;
}

QVariantList TcDataAccessStatement::bind() const 
{
    QVariantList v;
    v << _leftJoinBind << _whereBind; 
    return v;
}

void TcDataAccessStatement::clear()
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

TcDataAccessStatement& TcDataAccessStatement::operator=(const TcDataAccessStatement &da)
{
    _select = da._select;
    _from = da._from;
    _leftJoin = da._leftJoin;
    _where = da._where;
    _group = da._group;
    _order = da._order;

    _limit = da._limit;
    _leftJoinBind = da._leftJoinBind;
    _whereBind = da._whereBind;

    return *this;
}
