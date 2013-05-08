#include <tianchi/core/tcutils.h>
#include <tianchi/sql/tcdatabase.h>

#include <QtSql/QtSql>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QDesktopServices>

TcDatabase::TcDatabase()
{
}

TcDatabase::~TcDatabase(void)
{
    close();
}

char TcDatabase::typeFrom(QVariant::Type type)
{
    char c = '\0';
    if (type == QVariant::Int
            || type == QVariant::UInt
            || type == QVariant::LongLong
            || type == QVariant::ULongLong)
    {
        c = 'i';
    }
    else if (type == QVariant::Double)
    {
        c = 'n';
    }
    else if (type == QVariant::String)
    {
        c = 's';
    }
    else if (type == QVariant::Date
            || type == QVariant::Time
            || type == QVariant::DateTime)
    {
        c = 't';
    }
    else if (type == QVariant::ByteArray)
    {
        c = 'm';
    }
    else
    {
    }
    return c;
}

int TcDatabase::dbType(const QString& typeName)
{
    int ret = 0;
    if (typeName.compare("MSSQL", Qt::CaseInsensitive) == 0
      || typeName.compare("SQLServer", Qt::CaseInsensitive) == 0
      || typeName.compare("SQL Server", Qt::CaseInsensitive) == 0)
    {
        ret = SQLSERVER;
    }
    else if (typeName.compare("SQLite", Qt::CaseInsensitive) == 0)
    {
        ret = SQLITE;
    }
    return ret;
}

TcParams TcDatabase::addParams(const QStringList& keys, 
        const QList<QByteArray>& values)
{
    TcParams ret;
    if (keys.count() == values.count())
    {
        for (int i=0; i < keys.count(); i++)
        {
            ret[keys.at(i).toLower()] = values.at(i);
        }
    }
    return ret;
}

QString TcDatabase::lastError()
{
    return errors.count() > 0 ? errors.takeLast() : QString();
}

void TcDatabase::setDatabase(int dbType, const QString& hostName, 
        int hostPort, const QString& dbName, const QString& username, 
        const QString& password)
{
    switch (dbType)
    {
    case SQLSERVER:
        m_dbType   = dbType;
        m_typeName = "SQL Server";
        m_hostName = hostName;
        m_hostPort = hostPort;
        m_dbName   = dbName  ;
        m_username = username;
        m_password = password;
        break;
    case SQLITE:
        m_dbType   = dbType;
        m_typeName = "SQLite";
        m_hostName = hostName;
        m_hostPort = hostPort;
        m_dbName   = dbName  ;
        m_username = username;
        m_password = password;
        break;
    default:
        m_dbType   =  0;
        m_typeName = "";
        m_hostName = "";
        m_hostPort =  0;
        m_dbName   = "";
        m_username = "";
        m_password = "";
        break;
    }
}

bool TcDatabase::setDatabase(const QString& typeName, 
        const QString& hostName, int hostPort, const QString& dbName, 
        const QString& username, const QString& password)
{
    bool ret = false;
    if (typeName.compare("MSSQL", Qt::CaseInsensitive) == 0
      || typeName.compare("SQLServer", Qt::CaseInsensitive) == 0
      || typeName.compare("SQL Server", Qt::CaseInsensitive) == 0)
    {
        m_dbType = SQLSERVER;
        m_typeName = "SQL Server";
    }
    else if (typeName.compare("SQLite", Qt::CaseInsensitive) == 0)
    {
        m_dbType = SQLITE;
        m_typeName = "SQLite";
    }
    else
    {
        m_dbType = 0;
    }
    if (m_dbType > 0)
    {
        m_hostName = hostName;
        m_hostPort = hostPort;
        m_dbName   = dbName  ;
        m_username = username;
        m_password = password;

        ret = true;
    }
    else
    {
        m_typeName = "";
        m_hostName = "";
        m_hostPort =  0;
        m_dbName   = "";
        m_username = "";
        m_password = "";
    }
    return ret;
}

void TcDatabase::setDatabase(int dbType, const QString& dbName, 
        const QString& username, const QString& password)
{
    switch (dbType)
    {
    case SQLSERVER:
        m_dbType   = dbType;
        m_typeName = "SQL Server";
        m_hostName = "localhost";
        m_hostPort = 0;
        m_dbName   = dbName  ;
        m_username = username;
        m_password = password;
        break;
    case SQLITE:
        m_dbType   = dbType;
        m_typeName = "SQLite";
        m_hostName = "localhost";
        m_hostPort = 0;
        m_dbName   = dbName  ;
        m_username = username;
        m_password = password;
        break;
    default:
        m_dbType   =  0;
        m_typeName = "";
        m_hostName = "";
        m_hostPort =  0;
        m_dbName   = "";
        m_username = "";
        m_password = "";
        break;
    }
}

bool TcDatabase::setDatabase(const QString& typeName, const QString& dbName, 
        const QString& username, const QString& password)
{
    return setDatabase(typeName, "", 0, dbName, username, password);
}

int TcDatabase::open()
{
    int ret = 0;
    close();
    switch (dbType())
    {
    case SQLSERVER:
        QSqlDatabase::removeDatabase("FriendSafe");
        m_handle = QSqlDatabase::addDatabase("QODBC", "FriendSafe");
        {
            QString dsn = QString("DRIVER={SQL SERVER};SERVER=%1;DATABASE=%2;")
                .arg(hostName()).arg(dbName());
            m_handle.setDatabaseName(dsn);
            m_handle.setUserName(m_username);
            m_handle.setPassword(m_password);
        }
        ret = m_handle.open() ? 1 : 0;
        break;

    case SQLITE:
        QSqlDatabase::removeDatabase("FriendSafe");
        m_handle = QSqlDatabase::addDatabase("QSQLITE", "FriendSafe");

        QFileInfo dbFile(m_dbName);
        QDir dir(dbFile.absoluteDir());
        dir.mkpath(dbFile.absolutePath());
        m_handle.setDatabaseName(m_dbName);
        m_handle.setUserName(m_username);
        m_handle.setPassword(m_password);

        if ( m_handle.open() )
        {
            m_hostName = "localhost";
            m_hostPort = 0;
            QStringList tables = m_handle.tables();
            if (tables.count() <= 0)
            {
                // 没有任何表，这个库是新建的。
                errors.append("Database creating: " + dbFile.absoluteFilePath());
                QFile f(CreateDDL);
                if (f.open(QFile::Text | QFile::ReadOnly))
                {
                    QTextStream in(&f);
                    QString fileText = in.readAll();
                    f.close();

                    ret = 1;
                    QSqlQuery query = QSqlQuery(m_handle);
                    int pos;
                    while ((pos = fileText.indexOf(";")) > -1)
                    {
                        QString sqlText = fileText.mid(0, pos).trimmed();
                        fileText.remove(0, pos+1);
                        fileText = fileText.trimmed();

                        QStringList sqlLines = sqlText.split("\n", 
                                QString::SkipEmptyParts);
                        QString sql;
                        for (int i = 0; i < sqlLines.count(); i++)
                        {
                            QString s = sqlLines.at(i);
                            if (!s.startsWith("--"))
                            {
                                sql += s + "\n";
                            }
                        }
                        if (!sql.isEmpty() && !query.exec(sql))
                        {
                            ret = -1;
                        }
                    }
                    query.finish();
                }
                errors.append("Database creation is complete.");
            }else
            {
                ret = 1;
            }
        }
        break;
    }
    return ret;
}

void TcDatabase::close()
{
    if ( m_handle.isOpen() )
    {
        m_handle.close();
    }
    m_engineFile = "";
}

void TcDatabase::loadEngine()
{
    loadEngine(m_engineFile);
}

void TcDatabase::loadEngine(const QString& filename)
{
    m_sqls.clear();
    if (m_handle.isOpen())
    {
        if (dbType() == SQLSERVER)
        {
            // 取出存储过程名
            QSqlQuery procedures_query = QSqlQuery(m_handle);
            QSqlQuery query = QSqlQuery(m_handle);
            if (procedures_query.exec("exec sp_procedures_rowset2"))
            {
                while (procedures_query.next())
                {
                    QSqlRecord procedures = procedures_query.record();
                    QSqlField  fieldSchema = procedures.field("PROCEDURE_SCHEMA");
                    if (fieldSchema.isValid() && fieldSchema.value() != "sys")
                    {
                        QSqlField  field = procedures.field("PROCEDURE_NAME");
                        if (field.isValid())
                        {
                            SQLContext cnt;
                            QString procedureID = field.value().toString();
                            int index = procedureID.indexOf(";");
                            if (index >= 0)
                            {
                                procedureID = procedureID.left(index);
                            }
                            cnt.id = procedureID;
                            QString paramsLine;
                            if (query.exec("exec sp_procedure_params_rowset '" 
                                        + procedureID + "'"))
                            {
                                while(query.next())
                                {
                                    QSqlRecord paramField = query.record();
                                    QSqlField  paramName = paramField.field("PARAMETER_NAME");
                                    QString pname = paramName.value().toString();

                                    if (pname.compare("@RETURN_VALUE", 
                                                Qt::CaseInsensitive) != 0)
                                    {
                                        QSqlField  paramType = 
                                            paramField.field("TYPE_NAME");
                                        pname.remove(0, 1);

                                        QString ptype = 
                                            paramType.value().toString().toLower();
                                        if (ptype == "nvarchar")
                                        {
                                            ptype = "string";
                                        }

                                        cnt.params.insert(pname, ptype);
                                        paramsLine += ", :" + pname;
                                    }
                                }
                                query.finish();

                                if (!paramsLine.isEmpty())
                                {
                                    paramsLine.remove(0, 2);
                                }
                            }
                            cnt.text = "exec " + procedureID + " " + paramsLine;
                            m_sqls[procedureID] = cnt;
                        }
                    }
                }
                procedures_query.finish();
            }
        }

        QFileInfo sqlsInfo(filename);
        if (sqlsInfo.exists())
        {
            QFile f(filename);
            if (f.open(QFile::Text | QFile::ReadOnly))
            {
                m_engineFile = filename;

                QTextStream in(&f);

                int                             rdType = 0;
                QString                         sqlId;
                QString                         sqlText;
                QMultiHash<QString, QString>    sqlParams;
                while (!in.atEnd())
                {
                    QString line = in.readLine().trimmed();
                    clearComment(line);
                    if (line.isEmpty())
                    {

                    }
                    else if (line.startsWith("SQL:", Qt::CaseInsensitive))
                    {
                        if (!sqlId.isEmpty() && !sqlText.isEmpty())
                        {
                            sqlText.replace("@", ":");

                            SQLContext cnt;
                            cnt.id     = sqlId;
                            cnt.text   = sqlText;
                            cnt.params = sqlParams;
                            m_sqls[sqlId] = cnt;
                        }
                        sqlId = line.mid(4).trimmed();
                        sqlText.clear();
                        sqlParams.clear();
                        rdType = 1;
                    }
                    else if (line.startsWith("Params:", Qt::CaseInsensitive))
                    {
                        rdType = 2;
                    }
                    else if (!sqlId.isEmpty())
                    {
                        switch(rdType)
                        {
                        case 1:
                            sqlText += line + "\n";
                            break;
                        case 2:
                        {
                            QString paramName;
                            QString paramType = "string";
                            int pos;
                            if ((pos = line.indexOf(" ")) > 0)
                            {
                                paramName = line.left(pos);
                                line = line.remove(0, pos).trimmed();
                                if ((pos=line.indexOf(" ")) > 0)
                                {
                                    paramType = line.left(pos);
                                }
                                else
                                {
                                    paramType = line;
                                }
                            }
                            else
                            {
                                paramName = line;
                            }
                            QChar c = paramName.at(0);
                            if (c == ':' || c == '@')
                            {
                                paramName.remove(0, 1);
                            }
                            sqlParams.insert(paramName, paramType.toLower());
                            break;
                        }
                        }
                    }
                }
                f.close();

                if (!sqlId.isEmpty() && !sqlText.isEmpty())
                {
                    SQLContext cnt;
                    cnt.id     = sqlId;
                    cnt.text   = sqlText;
                    cnt.params = sqlParams;
                    m_sqls[sqlId] = cnt;
                }
            }
        }
    }
}

void TcDatabase::clearComment(QString& s)
{
    int pos;
    if ((pos = s.indexOf("#")) >= 0)
    {
        s = s.mid(0, pos);
    }
    if ((pos = s.indexOf("--")) >= 0)
    {
        s = s.mid(0, pos);
    }
    if ((pos = s.indexOf("//")) >= 0)
    {
        s = s.mid(0, pos);
    }
    s = s.trimmed();
}

QSqlQuery* TcDatabase::prepare(const QString& sqlID, TcParams prams,
        QString& error, int userNo, const QString& userID, const QString& username)
{
    QSqlQuery* ret = NULL;
    QSqlQuery* query = new QSqlQuery(m_handle);
    if (query != NULL)
    {
        QHash<QString, SQLContext>::const_iterator it = m_sqls.find(sqlID);
        if (it != m_sqls.constEnd() && it.key() == sqlID)
        {
            SQLContext sql = it.value();
            if (query->prepare(sql.text))
            {
                // SQL文中包括 ? 时，表示参数以序号赋值
                bool NonName = sql.text.indexOf("?") >= 0;
                int  ParamIndex = 0;
                QStringList dbKeys = sql.params.keys();
                foreach (QString dbKey, dbKeys)
                {
                    QString dbType  = sql.params.value(dbKey);

                    // 循环对照变量名，是为了确保大小写不统一时也能识别
                    QByteArray dbValue;
                    if ( dbKey.compare("UserNo"   , Qt::CaseInsensitive) == 0
                      || dbKey.compare("CreaterNo", Qt::CaseInsensitive) == 0
                      || dbKey.compare("CreatorNo", Qt::CaseInsensitive) == 0
                      || dbKey.compare("UpdaterNo", Qt::CaseInsensitive) == 0)
                    {
                        dbValue = QByteArray::number(userNo);
                    }
                    else if (dbKey.compare("UserID", Qt::CaseInsensitive) == 0
                      || dbKey.compare("CreaterID", Qt::CaseInsensitive) == 0
                      || dbKey.compare("CreatorID", Qt::CaseInsensitive) == 0
                      || dbKey.compare("UpdaterID", Qt::CaseInsensitive) == 0)
                    {
                        dbValue = userID.toUtf8();
                    }
                    else if (dbKey.compare("Username", Qt::CaseInsensitive) == 0
                      || dbKey.compare("Creater" , Qt::CaseInsensitive) == 0
                      || dbKey.compare("Creator" , Qt::CaseInsensitive) == 0
                      || dbKey.compare("Updater" , Qt::CaseInsensitive) == 0)
                    {
                        dbValue = username.toUtf8();
                    }
                    else
                    {
                        dbValue = prams[dbKey.toLower()];
                    }
                    QString aKey = ':' + dbKey;
                    if (dbType.compare("i", Qt::CaseInsensitive) == 0
                      || dbType.compare("int", Qt::CaseInsensitive) == 0)
                    {
                        int value = dbValue.toInt();
                        if (NonName)
                        {
                            query->bindValue(ParamIndex, value);
                        }
                        else if (aKey == ":RETURN_VALUE")
                        {
                        }
                        else
                        {
                            query->bindValue(aKey, value);
                        }
                    }
                    else if (dbType.compare("n", Qt::CaseInsensitive) == 0
                      || dbType.compare("double", Qt::CaseInsensitive) == 0
                      || dbType.compare("number", Qt::CaseInsensitive) == 0)
                    {
                        double value = dbValue.toDouble();
                        if (NonName)
                        {
                            query->bindValue(ParamIndex, value);
                        }
                        else if (aKey == ":RETURN_VALUE")
                        {
                        }
                        else
                        {
                            query->bindValue(aKey, value);
                        }
                    }
                    else if (dbType.compare("d", Qt::CaseInsensitive) == 0
                      || dbType.compare("date", Qt::CaseInsensitive) == 0
                      || dbType.compare("time", Qt::CaseInsensitive) == 0
                      || dbType.compare("time", Qt::CaseInsensitive) == 0
                      || dbType.compare("datetime", Qt::CaseInsensitive) == 0)
                    {
                        QDateTime value = TcUtils::toDateTime(QString(dbValue));
                        if (NonName)
                        {
                            if (dbValue.isEmpty())
                            {
                                query->bindValue(ParamIndex, QVariant()/*NULL*/);
                            }
                            else
                            {
                                query->bindValue(ParamIndex, value);
                            }
                        }
                        else if (aKey == ":RETURN_VALUE")
                        {
                        }
                        else
                        {
                            if (dbValue.isEmpty())
                            {
                                query->bindValue(aKey, QVariant()/*NULL*/);
                            }
                            else
                            {
                                query->bindValue(aKey, value);
                            }
                        }
                    }
                    else if (dbType.compare("b", Qt::CaseInsensitive) == 0
                      || dbType.compare("bool", Qt::CaseInsensitive) == 0
                      || dbType.compare("boolean", Qt::CaseInsensitive) == 0)
                    {
                        bool value = dbValue.toInt() > 0
                            || QString(dbValue).compare("ok", 
                                    Qt::CaseInsensitive) == 0
                            || QString(dbValue).compare("yes", 
                                    Qt::CaseInsensitive) == 0
                            || QString(dbValue).compare("true", 
                                    Qt::CaseInsensitive) == 0;
                        if (NonName)
                        {
                            query->bindValue(ParamIndex, value);
                        }
                        else if (aKey == ":RETURN_VALUE")
                        {
                        }
                        else
                        {
                            query->bindValue(aKey, value);
                        }
                    }
                    else if (dbType.compare("s", Qt::CaseInsensitive) == 0
                      || dbType.compare("str", Qt::CaseInsensitive) == 0
                      || dbType.compare("ntext", Qt::CaseInsensitive) == 0
                      || dbType.compare("string", Qt::CaseInsensitive) == 0)
                    {
                        QString value = dbValue;
                        if (NonName)
                        {
                            query->bindValue(ParamIndex, value);
                        }
                        else if (aKey == ":RETURN_VALUE")
                        {
                        }
                        else
                        {
                            query->bindValue(aKey, value);
                        }
                    }
                    else
                    {// 默认都是 bytes 型
                        if (NonName)
                        {
                            query->bindValue(ParamIndex, dbValue);
                        }
                        else if (aKey == ":RETURN_VALUE")
                        {
                        }
                        else
                        {
                            query->bindValue(aKey, dbValue);
                        }
                    }
                    ParamIndex++;
                }
                ret = query;
                query = NULL;
            }
            else
            {
                error = query->lastError().text();
                errors.append("SQL[" + sqlID + "] prepare error:" + error);
            }
        }
    }
    delete query;
    return ret;
}

bool TcDatabase::exec(int& result, const QString& sqlID, const TcParams &prams,
        int userNo, const QString& userID, const QString& username)
{
    bool ret = false;
    QString error;
    QSqlQuery* query = prepare(sqlID, prams, error, userNo, userID, username);
    if (query != NULL)
    {
        if (query->exec())
        {
            result = 0;
            if (query->isSelect())
            {
                while (query->next())
                {
                    result ++;
                }
            }
            else
            {
                int res = query->lastInsertId().toInt();
                if (res <= 0)
                {
                    res = query->numRowsAffected();
                }
                result = res;
            }
            ret = true;
        }
        query->finish();
        delete query;
    }
    return ret;
}

bool TcDatabase::exec(QVariantList& list, const QString& sqlID, 
        const TcParams &prams, int userNo, const QString& userID, 
        const QString& username)
{
    bool ret = false;
    QString error;
    QSqlQuery* query = prepare(sqlID, prams, error, userNo, userID, username);
    if (query != NULL)
    {
        if (query->exec())
        {
            if (query->isSelect())
            {
                while (query->next())
                {
                    QSqlRecord record = query->record();
                    QVariantMap map;
                    for (int i = 0; i < record.count(); i++)
                    {
                        QSqlField field = record.field(i);
                        QString  k = field.name().toLower();
                        QVariant v = field.value();
                        map[k] = v;
                    }
                    list.append(map);
                }
            }
            ret = true;
        }
        query->finish();
        delete query;
    }
    return ret;
}

int TcDatabase::exec(int& result, QVariantList& list, const QString& sqlID, 
        const TcParams& params, int userNo, const QString& userID , 
        const QString& username)
{
    int ret = 0;
    QString error;
    QSqlQuery* query = prepare(sqlID, params, error, userNo, userID, username);
    if (query != NULL)
    {
        if (query->exec())
        {
            result = 0;
            if (query->isSelect())
            {
                while (query->next())
                {
                    QSqlRecord record = query->record();
                    QVariantMap map;
                    for (int i = 0; i < record.count(); i++)
                    {
                        QSqlField field = record.field(i);
                        QString  k = field.name().toLower();
                        QVariant v = field.value();
                        map[k] = v;
                    }
                    list.append(map);
                }
                ret = 2;
            }
            else
            {
                result = query->lastInsertId().toInt();
                if (result <= 0)
                {
                    result = query->numRowsAffected();
                }
                ret = 1;
            }
        }
        else
        {
            ret = -1;
        }
        query->finish();
        delete query;
    }
    return ret;
}

int TcDatabase::exec(int& result, QList<QByteArray>& list, 
        const QString& sqlID, const TcParams& params, int userNo, 
        const QString& userID , const QString& username)
{
    int ret = 0;
    QString error;
    QSqlQuery* query = prepare(sqlID, params, error, userNo, userID, username);
    if (query != NULL)
    {
        if (query->exec())
        {
            result = 0;
            if (query->isSelect())
            {
                list.clear();
                while (query->next())
                {
                    QSqlRecord record = query->record();
                    QByteArray fieldBytes;
                    for (int i = 0; i < record.count(); i++)
                    {
                        QSqlField field = record.field(i);
                        QVariant value = field.value();

                        fieldBytes = TcUtils::addField(field.name(), 
                                field.value());

//                        QByteArray bytes = value.toByteArray();
//                        fieldBytes.append(field.name().toLower()).append('\0')
//                                .append(typeFrom(value.type())).append('\0')
//                                .append(QByteArray::number(bytes.length())).append('\0')
//                                .append(bytes);
                    }
                    list.append(fieldBytes);
                }
                ret = 2;
            }
            else
            {
                result = query->lastInsertId().toInt();
                if (result <= 0)
                {
                    result = query->numRowsAffected();
                }
                ret = 1;
            }
        }
        else
        {
            ret = -1;
        }
        query->finish();
        delete query;
    }
    return ret;
}
