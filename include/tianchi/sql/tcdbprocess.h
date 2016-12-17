#if __cplusplus >= 201103L
/************************************************************************
*Description:                                                           *
*Author: realfan                                                        *
*Date of Created:                                                       *
*Date of Modified      Purpose of Modify       Person Name of Modify    *
*------------------  ----------------------  -------------------------  *
* 2016-12-07
*                                                                       *
************************************************************************/
#ifndef TIANCHI_TCDBPROCESS_H
#define TIANCHI_TCDBPROCESS_H

#include <tianchi/tcglobal.h>

#include <QString>
#include <QVariant>
#include <QDateTime>
#include <QSqlQuery>

QT_BEGIN_NAMESPACE
class QSqlDatabase;
class QSqlQuery;
QT_END_NAMESPACE

class TIANCHI_API TcDBProcess
{
public:
    TcDBProcess(const QString strType = "sqlite"); //sqlite  mysql  access sqlserver
    virtual ~TcDBProcess();
    bool openDB(const QString strSvrName,
                const QString strDBname,
                const QString strUserID = "",
                const QString strUserPwd = "");
    bool openDB(const QString strDBname);
    void closeDB();
    bool excuteSQL(const QString);
    void *openRecordsetBySql(const QString strSql);
    void closeRecordset(void *);
    bool isOpen() const;
    bool recEOF(void *p) const;
    bool recBOF(void *p) const;
    bool isTableExist(const QString strTable);
    bool dropTable(const QString);
    //QStringList GetTableNames();
    //========∂¡»°==================================
    long getRecordCount(void *p) const;
    bool moveFirst(void *p) const;
    bool movePrevious(void *p) const;
    bool moveNext(void *p) const;
    bool moveLast(void *p) const;
    bool moveTo(int n, void *p) const;

    //bool execStoreProcOfArgList(int idx, const QString strStoreProc, const char *szFldsInfo, ...);
    //bool exexProc(const QString strStoreProc, QString str1, QString &str2);
    bool transaction();
    bool commit();
    bool rollback();
    QString getDbName() const
    {
        return __strDbName;
    }
public:
    template <typename T>
    bool readFieldsValueFromRec(const void *p, const QString str, T& t) const
    {
        const QSqlQuery *pQry = static_cast<const QSqlQuery *>(p);
        if (nullptr == pQry || false == pQry->isValid())
        {
            return false;
        }
        t = pQry->value(str).value<T>();
        return true;
    }

    template <typename T, typename ... Args>
    bool readFieldsValueFromRec(const void *p, const QString str, T & t, Args& ... args) const
    {
        const QSqlQuery *pQry = static_cast<const QSqlQuery *>(p);
        if (nullptr == pQry || false == pQry->isValid())
        {
            return false;
        }
        t = pQry->value(str).value<T>();
        bool bRet = readFieldsValueFromRec(p, args...);
        return bRet;
    }
    //---------------------------
private:
    template <typename T>
    void extractArg1(QStringList &lstFlds, QList<QVariant> &lstVars, const T &t) const
    {
        const QVariant var(t);
        if (lstFlds.size() == lstVars.size())
        {
            lstFlds << var.toString();
        }
        else
        {
            lstVars << var;
        }
    }
public:
    template<typename T, typename ... Args>
    bool addFieldsValueToTbl(const QString &strTbl, const QString &strFld, const T &t, const Args &... args)
    {
        QStringList lstFlds;
        QList<QVariant> lstVars;
        lstFlds << strFld;
        lstVars.push_back(t);
        std::initializer_list<int> {(extractArg1(lstFlds, lstVars, args), 0)...};
        //--------------------------------------
        QString strFlds;
        QString strPlaceholders;
        for (const QString &str : lstFlds)
        {
            strFlds += "," + str;
            strPlaceholders += ",:" + str;
        }
        QString strSql = QString("INSERT INTO %1(%2) VALUES (%3)").arg(strTbl).arg(strFlds.mid(1)).arg(strPlaceholders.mid(1));
        QSqlQuery qry(*m_pDB);
        qry.prepare(strSql);
        const int iCount = lstFlds.size();
        for(int i = 0; i < iCount; ++i)
        {
            qry.bindValue(":" + lstFlds.at(i), lstVars.at(i));
        }
        const bool bRet = qry.exec();
        //QSqlError lastError = qry.lastError();
        //QString strErr = lastError.driverText();
        return bRet;
    }

    //========================================
    template<typename T, typename ... Args>
    bool updateTblFieldsValue(const QString &strTbl, const QString &strWhere, const QString &strFld, const T &t, const Args &... args)
    {
        QStringList lstFlds;
        QList<QVariant> lstVars;
        lstFlds << strFld;
        lstVars << t;
        std::initializer_list<int> {(extractArg1(lstFlds, lstVars, args), 0)...};
        //---------------------------
        QString strFlds;
        for (const QString &str : lstFlds)
        {
            strFlds += "," + str + "=:" + str;
        }
        QString strSql = QString("UPDATE %1 SET %2 %3").arg(strTbl).arg(strFlds.mid(1)).arg(strWhere);
        QSqlQuery qry(*m_pDB);
        qry.prepare(strSql);
        //qDebug() << strSql;
        const int iCount = lstFlds.size();
        for(int i = 0; i < iCount; ++i)
        {
            qry.bindValue(":" + lstFlds.at(i), lstVars.at(i));
        }
        const bool bRet = qry.exec();
        //QSqlError lastError = qry.lastError();
        //QString strErr = lastError.driverText();
        return bRet;
    }
    //=================================================
    QSqlDatabase *m_pDB;
protected:
    bool __openMDB(const QString strMDBname, QString strUserID = "sa", const QString strPassword = "");
    bool __openMDBByUDL(const QString strUDL);
    bool __connectSqlServer(const QString strSvrName, const QString strDBname, const QString strUserID, const QString strUserPwd);
    bool __openSqlite(const QString &strDbName);
    bool __openMySql(QString strSvrName, const QString strDBname, QString strUserID, const QString strUserPwd);
private:

    QString __strConnName;
    QString __strDbType;
    QString __strDbName;
    QList<QSqlQuery *> __lstQrys;
};
#endif
#endif  // __cplusplus >= 201103L
