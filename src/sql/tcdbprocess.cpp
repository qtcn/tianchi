// DBProcess.cpp :
/************************************************************************
*Description:                                                           *
*Author: realfan                                                        *
*Date of Created:                                                       *
*Date of Modified      Purpose of Modify       Person Name of Modify    *
*------------------  ----------------------  -------------------------  *
*                                                                       *
************************************************************************/
#include <tianchi/sql/tcdbprocess.h>

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlField>
#include <QSqlDriver>
#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include <QDir>
#include <QCoreApplication>
#include <QDebug>
#include <QMessageBox>
#include <QSqlError>
//=================================
const char * TcDBProcess::szEnd = "|";
TcDBProcess::TcDBProcess(const QString strType)
{
    __strDbType = strType.toUpper();
    QString dbType("SQLITE");
    if("SQLITE" == __strDbType)
        dbType = "QSQLITE"; //QTPLUGIN += qsqlite Q_IMPORT_PLUGIN(QSQLiteDriverPlugin)
    else if ("MYSQL" == __strDbType)
        dbType = "QMYSQL"; //QTPLUGIN += qsqlmysql Q_IMPORT_PLUGIN(QMYSQLDriverPlugin)
    else if ("SQLSERVER" == __strDbType)
        dbType = "QODBC"; //QTPLUGIN += qsqlodbc  Q_IMPORT_PLUGIN(QODBCDriverPlugin)
    else if("ACCESS" == __strDbType)
        dbType = "QODBC"; //QTPLUGIN += qsqlodbc  Q_IMPORT_PLUGIN(QODBCDriverPlugin)
    else
    {
        dbType = "";
        QMessageBox::critical(0, "ERROR", "DB type name invalid!");
        return;
    }
    m_mapQry.clear();
    int m_siConnIdx = 0;
    while(1)
    {
        __strConnName = QString("MyDBProcessConn%1").arg(m_siConnIdx++);
        QSqlDatabase dbConn = QSqlDatabase::database(__strConnName, false);

        if(dbConn.isValid())//存在连接
        {
            continue;
        }
        m_pDB = new QSqlDatabase(QSqlDatabase::addDatabase(dbType, __strConnName));
        break;
    }
}
TcDBProcess::~TcDBProcess()
{
    foreach(QSqlQuery* pQry, m_mapQry)
    {
        if(pQry)
        {
            pQry->clear();
            delete pQry;
        }
    }

    m_pDB->close();
    delete m_pDB;
    QSqlDatabase::removeDatabase(__strConnName);
}
bool TcDBProcess::openDB(const QString strSvrName,
                       const QString strDBname,
                       const QString strUserID,
                       const QString strUserPwd)
{
    __strDbName = strDBname;
    bool bRet = false;
    if("SQLITE" == __strDbType)
    {
        bRet = __openSqlite(strDBname);
    }
    else if("MYSQL" == __strDbType)
    {
        bRet = __openMySql(strSvrName, strDBname, strUserID, strUserPwd);
    }
    else if("SQLSERVER" == __strDbType)
    {
        bRet = __connectSqlServer(strSvrName, strDBname, strUserID, strUserPwd);
    }
    else if("ACCESS" == __strDbType)
    {
        if(strSvrName.length() < 1)
        {
            bRet = __openMDB(strDBname, strUserID, strUserPwd);
        }
        else
        {
            bRet = __openMDBByUDL(strSvrName); //here strSvrName is UDL file name
        }
    }

    return bRet;
}
bool TcDBProcess::__openMDB(const QString strMDBname, QString strUserID, const QString strPassword)
{
    QString strMDB = strMDBname.trimmed();
    if(strUserID.length() < 1) strUserID = "sa";
    if(strMDB.indexOf(":") < 0 && strMDB.indexOf("/") < 0 && strMDB.indexOf("\\") < 0)
    {//no path, only mdb file name
        strMDB = QString("%1/%2").arg( QCoreApplication::applicationDirPath() ).arg( strMDB );
    }
    //access  "Driver={microsoft access driver(*.mdb)};dbq=*.mdb;uid=admin;pwd=pass;"
    //"DRIVER={Microsoft Access Driver (*.mdb, *.accdb)};DBQ=c:/tt/b.accdb;UID=admin;PWD=a"
    //for win7
    //QString dsn = QString("DRIVER={Microsoft Access Driver (*.mdb, *.accdb)};DBQ=%1;UID=%2;PWD=%3").arg(strMDBname).arg(strUserID).arg(strPassword);
    //for winxp
    QString dsn = QString("DRIVER={Microsoft Access Driver (*.mdb)};FIL={MS Access};DBQ=%1;UID=%2;PWD=%3").arg(strMDB).arg(strUserID).arg(strPassword);
    m_pDB->setDatabaseName(dsn);
    bool b = m_pDB->open();
    if(false == b)
    {
        QMessageBox::critical(0, "ERROR", m_pDB->lastError().text());
    }
    return b;
}
bool TcDBProcess::__openMDBByUDL(const QString strUDL)
{
    QFile file(strUDL);
    if(!file.open(QIODevice::ReadOnly)) return false;

    QTextStream in(&file);
    in.setCodec("UTF-8");
    QString strAll = in.readAll();
    if(strAll.length()>3 && 0 == strAll[1])
    {
        in.setCodec("UTF-16");
        in.seek(0);
        strAll = in.readAll();
    }
    file.close();
    int idx1 = strAll.indexOf("=");
    idx1 = strAll.indexOf("=", idx1+1);
    int idx2 = strAll.indexOf(";", idx1+1);
    QString strMDB = strAll.mid(idx1+1, idx2-idx1-1);
    strMDB = strMDB.trimmed();

    if(strMDB.indexOf(":") < 0)
    {
        strMDB = QString("%1/%2").arg( QCoreApplication::applicationDirPath() ).arg( strMDB );
    }
    return __openMDB(strMDB);
}
bool TcDBProcess::__connectSqlServer(const QString strSvrName, const QString strDBname, const QString strUserID, const QString strUserPwd)
{
    QString dsn = QString("DRIVER={SQL Server};Server=%1;Database=%2;UID=%3;PWD=%4").arg(strSvrName).arg(strDBname).arg(strUserID).arg(strUserPwd);
    m_pDB->setDatabaseName(dsn);
    bool b = m_pDB->open();
    //if(!b)  QMessageBox::critical(0, "error", m_dbConn.lastError().text());// m_dbConn.lastError().text();

    return b;
}
bool TcDBProcess::__openSqlite(const QString & strDbName)
{
    QString strMDB = strDbName.trimmed();
    if(strMDB.indexOf(":") < 0 && strMDB.indexOf("/") < 0 && strMDB.indexOf("\\") < 0)
    {
        strMDB = QString("%1/%2").arg( QCoreApplication::applicationDirPath() ).arg( strMDB );
    }
    m_pDB->setDatabaseName(strMDB);
    if (!m_pDB->open())
    {
        //qDebug() << " can’t open database >>>>>> mydb.db";
        return false;
    }
    return true;
}
bool TcDBProcess::__openMySql(QString strSvrName,
                          QString strDBname,
                          QString strUserID,
                          const QString strUserPwd)
{
    if(strSvrName.length() < 1) strSvrName = "localhost";
    if(strUserID.length() < 1) strUserID = "root";
    if(strDBname.length() < 1) return false;

    m_pDB->setHostName(strSvrName);
    m_pDB->setDatabaseName(strDBname);
    m_pDB->setUserName(strUserID);//"root");
    m_pDB->setPassword(strUserPwd);
    m_pDB->exec("SET NAMES 'utf8'");
    if(false == m_pDB->open())
    {
        return false;
    }
    return true;
}

/********************************************************************/
bool TcDBProcess::excuteSQL(const QString strExcutePara)
{
    QSqlQuery query(*m_pDB);
    query.clear();
    bool b = query.exec(strExcutePara);
    return b;
}
bool TcDBProcess::dropTable(const QString strTbl)
{
    return excuteSQL(QString("DROP TABLE %1").arg(strTbl));
}
/************************************************************************
*Function Name: isOpen                                                  *
*Description:   判断数据库是否关闭                                         *
*Param of Input:                                                        *
*               No                                                      *
*Param of Output:                                                       *
*               NO                                                      *
*Output:                                                                *
*               bool                                                    *
*Author: Donny Wang                                                     *
*Date of Created:                                                       *
*Date of Modified      Purpose of Modify       Person Name of Modify    *
*------------------  ----------------------  -------------------------  *
*                                                                       *
************************************************************************/
bool TcDBProcess::isOpen() const
{
    return m_pDB->isOpen();
}


/********************************************************************
*    Function Name: CloseDatabase                                   *
*    Function Description: 获取记录　　　　　　　                          *
*    Param In:      Void                                            *
*    Param Out:     Void                                            *
*    Return Value:  Void                                            *
*    Created:        10:15:2006   19:16                             *
*    Author:                                                        *
*    E-Mail:                                                        *
*    -----------------------------------------------------------    *
*    Purpose:                                                       *
********************************************************************/
void TcDBProcess::closeDB()
{
    m_pDB->close();
}

/********************************************************************
*    Function Name: OpenRecordsetBySql                              *
*    Function Description: 获取记录　　　　　　　                          *
*    Param In:      Void                                            *
*    Param Out:     Void                                            *
*    Return Value:  Void                                            *
*    Created:        12:15:2006                                     *
*    Author:                                                        *
*    E-Mail:        wdg@163.com                                     *
*    -----------------------------------------------------------    *
*    Purpose:                                                       *
********************************************************************/
bool TcDBProcess::openRecordsetBySql(const QString strSql, int idx /* = -1 */)
{
    if (false == isOpen())
    {
        return false;
    }
    QSqlQuery *pQry = (QSqlQuery *)m_mapQry[idx];
    if(0 == pQry)
    {
        m_mapQry.remove(idx);

        pQry = new QSqlQuery(*m_pDB);
        m_mapQry.insert(idx, pQry);
    }
    pQry->clear();
    bool b = pQry->exec(QObject::tr("%1").arg(strSql));
    return b;
}
void TcDBProcess::closeRecordset(int idx /* = -1 */)
{
    QSqlQuery *pQry = m_mapQry.value(idx);
    if(pQry)
    {
        pQry->clear();

        delete pQry;
        m_mapQry.remove(idx);
    }
}
bool TcDBProcess::recEOF(int idx /*= -1*/) const
{
    QSqlQuery *pQry = m_mapQry.value(idx);
    if(0 == pQry)
        return true;
    return (QSql::AfterLastRow == pQry->at());
}
bool TcDBProcess::recBOF(int idx /*= -1*/) const
{
    QSqlQuery *pQry = m_mapQry.value(idx);
    if(0 == pQry)
        return true;
    return (QSql::BeforeFirstRow == pQry->at());
}
bool TcDBProcess::moveFirst(int idx /* = -1 */) const
{
    if (false == isOpen())
    {
        return false;
    }
    QSqlQuery *pQry = m_mapQry.value(idx);
    if(0 == pQry) return false;
    if(pQry->isActive())
    {
        return pQry->first();
    }
    else
    {
        return false;
    }
}

bool TcDBProcess::movePrevious(int idx /* = -1 */) const
{
    if (false == isOpen())
    {
        return false;
    }
    QSqlQuery *pQry = m_mapQry.value(idx);
    if(0 == pQry) return false;
    if(pQry->isActive())
    {
        return pQry->previous();
    }
    else
    {
        return false;
    }
}
bool TcDBProcess::moveNext(int idx /* = -1*/) const
{
    if (false == isOpen())
    {
        return false;
    }
    QSqlQuery *pQry = m_mapQry.value(idx);
    if(0 == pQry) return false;
    if(pQry->isActive())
    {
        return pQry->next();
    }
    else
    {
        return false;
    }
}
bool TcDBProcess::moveLast(int idx /* = -1 */) const
{
    if (false == isOpen())
    {
        return false;
    }
    QSqlQuery *pQry = m_mapQry.value(idx);
    if(0 == pQry) return false;
    if(pQry->isActive())
    {
        return pQry->last();
    }
    else
    {
        return false;
    }
}
bool TcDBProcess::moveTo(int n, int idx /* = -1 */) const
{
    if (false == isOpen())
    {
        return false;
    }
    QSqlQuery *pQry = m_mapQry.value(idx);
    if(0 == pQry) return false;
    if(pQry->isActive())
    {
        return pQry->seek(n);
    }
    else
    {
        return false;
    }
}

long TcDBProcess::getRecordCount(int idx /* = -1 */) const
{
    if (false == isOpen())
    {
        return -1;
    }
    QSqlQuery *pQry = m_mapQry.value(idx);
    if(0 == pQry) return -1;
    if(m_pDB->driver()->hasFeature(QSqlDriver::QuerySize))
    {
        return pQry->size();
    }
    else
    {
        int i = pQry->at();
        pQry->last();
        int iRows = pQry->at() + 1;
        pQry->seek(i);
        return iRows;
    }
}

//"id%+s|name%-s|age%-d|pret%*d", 15, pch, &i, &iRet
#if 1
bool TcDBProcess::exexProc(const QString strStoreProc, QString str1, QString& str2)
{
    QSqlQuery *pQry = (QSqlQuery *)m_mapQry[-1];
    if(0 == pQry)
    {
        m_mapQry.remove(-1);

        pQry = new QSqlQuery(*m_pDB);
        m_mapQry.insert(-1, pQry);
    }
    pQry->clear();
    QString strSql = "exec " + strStoreProc + " ?, ? output";
    pQry->prepare(strSql);
    pQry->bindValue(0, str1);
    pQry->bindValue(1, 0, QSql::Out);
    bool b = pQry->exec();
//    if(!b)
//    {
//        QString str = pQry->lastError().text();
//    }

    str2 = b ? pQry->boundValue(1).toString() : "";

    return b;
}

bool TcDBProcess::execStoreProcOfArgList(int idx, const QString strStoreProc, const char* szFldsInfo, ...)
{
    if (0 == szFldsInfo)
    {
        return false;
    }
    QSqlQuery *pQry = (QSqlQuery *)m_mapQry[idx];
    if(0 == pQry)
    {
        m_mapQry.remove(idx);

        pQry = new QSqlQuery(*m_pDB);
        m_mapQry.insert(idx, pQry);
    }
    pQry->clear();

    QString strFlds(szFldsInfo);
    QStringList strlst = strFlds.split("|");
    //QString strSql = QString("CALL %1").arg(strStoreProc) ;
    QString strSql = QString("exec %1").arg(strStoreProc) ;
    for(int i = 0; i < strlst.size(); ++i)
    {
        if(0 == i)
            strSql += " ?";
        else if(strlst.size()-1 == i)
            strSql += ",?";
        else
            strSql += ",?";
    }
    pQry->prepare(strSql);


    va_list arg_ptr;
    va_start(arg_ptr, szFldsInfo);
    //pQry->prepare(strSql);//("INSERT INTO person (id, forename, surname) VALUES (:id, :forename, :surname)");
    //bool bExed = false;
    for (int i = 0; i < strlst.size(); ++i)
    {
        //-表示输出 +或无表示输入 *表示return  //"id%+s|name%-s|age%-d|pret%*d", 15, pch, &i, &iRet
        QString strFldInfo = strlst.at(i);
        QString strFldName = strFldInfo.mid(0, strFldInfo.indexOf('%'));//get field name
        QChar ch = (strFldInfo.mid(strFldInfo.indexOf('%') + 1, 1)).at(0);
        QSql::ParamTypeFlag eParamTypeFlag = QSql::In;
        switch (ch.toLatin1())
        {
        case L'-':
            eParamTypeFlag = QSql::Out;
            ch = (strFldInfo.mid(strFldInfo.indexOf('%') + 2, 1)).at(0);
            break;
        case '+':
            eParamTypeFlag = QSql::In;
            ch = (strFldInfo.mid(strFldInfo.indexOf('%') + 2, 1)).at(0);
            break;
        default:
            eParamTypeFlag = QSql::In;
        }
        if(QSql::In == eParamTypeFlag)
        {
            switch (ch.toLatin1())
            {
            case 'd':
            case 'u':
                {//整数
                    int k = va_arg(arg_ptr, int);
                    pQry->bindValue(i, k);
                    break;
                }
            case 'f':
            case 'g':
                {//小数double类型,无float类型
                    double d = va_arg(arg_ptr, double);
                    pQry->bindValue(i, d);
                    break;
                }
            case 's':
                {//文本
                    //char *pstr = va_arg(arg_ptr, char*);
                    QString * pch = va_arg(arg_ptr, QString *);
                    QString strVal = *pch;
                    pQry->bindValue(i, strVal);
                    break;
                }
            case 'b':
                {//二进制
                    QByteArray * pData = va_arg( arg_ptr, QByteArray * );
                    pQry->bindValue(i, *pData);
                    break;
                }
            case 't':
                {//时间日期
                    QDateTime * pdt = va_arg( arg_ptr, QDateTime* );
                    pQry->bindValue(i, *pdt);
                    break;
                }
            } //end of switch
        }
        else if (QSql::Out == eParamTypeFlag)
        {
            va_arg(arg_ptr, void*);//shift arg
            pQry->bindValue(i, 0, QSql::Out);
        }
    } //end of for
    va_end(arg_ptr);
    if(false == pQry->exec())
    {
        QSqlError err = pQry->lastError();
        QString str = err.text();
        return false;
    }
    va_start(arg_ptr, szFldsInfo);
    for (int i = 0; i < strlst.size(); ++i)
    {
        //-表示输出 +或无表示输入 *表示return  //"id%+s|name%-s|age%-d|pret%*d", 15, pch, &i, &iRet
        QString strFldInfo = strlst.at(i);
        QString strFldName = strFldInfo.mid(0, strFldInfo.indexOf('%'));//get field name
        QChar ch = (strFldInfo.mid(strFldInfo.indexOf('%') + 1, 1)).at(0);
        QSql::ParamTypeFlag eParamTypeFlag = QSql::In;
        switch (ch.toLatin1())
        {
        case L'-':
            eParamTypeFlag = QSql::Out;
            ch = (strFldInfo.mid(strFldInfo.indexOf('%') + 2, 1)).at(0);
            break;
        case '+':
            eParamTypeFlag = QSql::In;
            ch = (strFldInfo.mid(strFldInfo.indexOf('%') + 2, 1)).at(0);
            break;
        default:
            eParamTypeFlag = QSql::In;
        }
        if(QSql::In == eParamTypeFlag)
        {
            switch (ch.toLatin1())
            {
            case 'd':
            case 'u':
                {//整数
                    va_arg(arg_ptr, int);
                    //pQry->bindValue(i, k);
                    break;
                }
            case 'f':
            case 'g':
                {//小数double类型,无float类型
                    va_arg(arg_ptr, double);
                    //pQry->bindValue(i, d);
                    break;
                }
            case 's'://文本
            case 'b'://二进制
            case 't'://时间日期
                {
                    va_arg( arg_ptr, void* );
                    break;
                }
            } //end of switch
        }
        else if (QSql::Out == eParamTypeFlag)
        {//int i = query.boundValue(1).toInt(); // i is 65
            void* pRet = va_arg(arg_ptr, void*);//shift arg
            QVariant var = pQry->boundValue(i);
            switch (ch.toLatin1())
            {
                case 'd':
                case 'u':
                {//整数
                    int * pInt = (int*)pRet;
                    *pInt = var.toInt();
                    break;
                }
                case 'B':
                {
                    unsigned char * puc = (unsigned char *)pRet;
                    *puc = (unsigned char)var.toInt();
                    break;
                }
                case 'f':
                case 'g':
                {//小数double类型,无float类型
                    double * pD = (double*)pRet;
                    *pD = var.toDouble();
                    break;
                }
                case 's':
                {//文本
                    QString* pstr = (QString*)pRet;
                    *pstr = var.toString();
                    break;
                }
                case 'b':
                {//二进制
                    QByteArray * pData = va_arg( arg_ptr, QByteArray * );
                    *pData = var.toByteArray();
                    break;
                }
                case 't':
                {//时间日期
                    QDateTime * dt = va_arg( arg_ptr, QDateTime* );
                    *dt = var.toDateTime();
                    break;
                }
            } //end of switch
        }
    } //end of for

    return true;
}
#endif
//==============================================================

bool TcDBProcess::transaction()
{
    if (false == m_pDB->driver()->hasFeature(QSqlDriver::Transactions))
    {
        return false;
    }
    m_pDB->transaction();
    return true;
}
bool TcDBProcess::commit()
{
    if (false == m_pDB->driver()->hasFeature(QSqlDriver::Transactions))
    {
        return false;
    }
    m_pDB->commit();
    return true;
}
bool TcDBProcess::rollback()
{
    if (false == m_pDB->driver()->hasFeature(QSqlDriver::Transactions))
    {
        return false;
    }
    m_pDB->rollback();
    return true;
}
bool TcDBProcess::getFieldsValueFromRec(int idx, const char* szFldInfo, ...) const
{
    if (0 == szFldInfo)
    {
       return false;
    }
    va_list arg_ptr;
    va_start(arg_ptr, szFldInfo);
    QSqlQuery *pQry = m_mapQry.value(idx);
    if(0 == pQry)
    {
        return false;
    }
    if(false == pQry->isValid())
    {
        return false;
    }
    QString strFld(szFldInfo);
    while(szEnd != strFld)
    {
        void* pRet = va_arg(arg_ptr, void*);

        QStringList strlst = strFld.split("%", QString::SkipEmptyParts);
        int iFld = pQry->record().indexOf(strlst.at(0));
        QVariant var = pQry->value(iFld);
        if (false == var.isValid())
        {
            continue;
        }
        QChar ch('d'); //int is default
        if(strlst.size() > 1)
        {
            ch = strlst.at(1).at(0);
        }
        switch (ch.toLatin1())
        {
            case 'd':
            {
                int * pInt = (int*)pRet;
                *pInt = var.toInt();
                break;
            }
            case 'f':
            {
                double* pDbl = (double*)pRet;
                *pDbl = var.toDouble();
                break;
            }
            case 's':
            {
                QString * pstr = (QString*)pRet;
                *pstr = var.toString();
                break;
            }
            case 'b':
            {
                QByteArray *pData = (QByteArray*)pRet;
                pData->clear();
                *pData = var.toByteArray();
                break;
            }
            case 't':
            {
                QDateTime * pDateTime = (QDateTime*)pRet;
                *pDateTime = var.toDateTime();
                break;
            }
        } //end of switch
        char* pchFld = va_arg(arg_ptr, char*);
        strFld = pchFld;
    }

    va_end(arg_ptr);
    return true;
}

bool TcDBProcess::addFieldsValueToTbl(const QString strTbl, const char* szFldInfo, ...)
{
    QSqlQuery * pQry = new QSqlQuery(*m_pDB);

    va_list arg_ptr;
    va_start(arg_ptr, szFldInfo);

    QString strFld(szFldInfo);
    QString strSql = QString("INSERT INTO %1(").arg(strTbl) ;
    QString strSqlFlds("");
    while(szEnd != strFld)
    {
        QStringList strlst = strFld.split("%", QString::SkipEmptyParts);
        strSql += strlst.at(0) + ",";
        strSqlFlds += QString(":%1,").arg(strlst.at(0));
        QChar ch('d'); //int is default
        if(strlst.size() > 1)
        {
            ch = strlst.at(1).at(0);
        }
        switch (ch.toLatin1())
        {
            case 'd':
            {//整数
                va_arg(arg_ptr, int);
                break;
            }
            case 'f':
            {//小数double类型,无float类型
                va_arg(arg_ptr, double);
                break;
            }
            case 's':
            case 'b':
            case 't':
            {
                va_arg(arg_ptr, void*);
                break;
            }
        } // end of switch
        char* pchFld = va_arg(arg_ptr, char*);
        strFld = pchFld;
    }
    strSql = strSql.left(strSql.length() - 1) + ") VALUES ("; //remove last ,
    strSqlFlds = strSqlFlds.left((strSqlFlds.length()-1)) + ")";
    strSql += strSqlFlds;
    pQry->prepare(strSql);//("INSERT INTO person (id, forename, surname) VALUES (:id, :forename, :surname)");

    va_start(arg_ptr, szFldInfo);
    strFld = (szFldInfo);
    while(szEnd != strFld)
    {
        QStringList strlst = strFld.split("%", QString::SkipEmptyParts);
        QChar ch = strlst.at(1).at(0);
        QString strPlaceholder = QString(":%1").arg(strlst[0]);
        QVariant var;
        switch (ch.toLatin1())
        {
            case 'd':
            {//整数
                int k = va_arg(arg_ptr, int);
                var = k;
                break;
            }
            case 'f':
            {//小数double类型,无float类型
                double d = va_arg(arg_ptr, double);
                var = d;
                break;
            }
            case 's':
            {//文本
                QString * pch = va_arg(arg_ptr, QString*);
                var = *pch;
                break;
            }
            case 'b':
            {//二进制
                QByteArray *pData = va_arg(arg_ptr, QByteArray*);
                var = *pData;
                break;
            }
            case 't':
            {//时间日期
                QDateTime *pdt = va_arg(arg_ptr, QDateTime*);
                var = *pdt;
                break;
            }
        } // end of switch
        pQry->bindValue(strPlaceholder, var);
        char* pchFld = va_arg(arg_ptr, char*);
        strFld = pchFld;
    } //end of while

    va_end(arg_ptr);
    bool b = pQry->exec();
    //QSqlError lastError = pQry->lastError();
    //QString strErr = lastError.driverText();
    delete pQry;
    return b;
}

bool TcDBProcess::updateTblFieldsValue(const QString strTbl, QString strWhere, const char * szFldInfo, ... )
{
    QSqlQuery * pQry = new QSqlQuery(*m_pDB);
    QString strSql = QString("UPDATE %1 SET ").arg(strTbl);

    va_list arg_ptr;
    va_start(arg_ptr, szFldInfo);

    QString strFld(szFldInfo);
    while(szEnd != strFld)
    {
        QStringList strlst = strFld.split("%", QString::SkipEmptyParts);
        strSql += strlst[0] + "=:" + strlst[0] + ",";

        QChar ch('d'); //int is default
        if(strlst.size() > 1)
        {
            ch = strlst.at(1).at(0);
        }
        //QChar ch = strlst.at(1).at(0);
        switch (ch.toLatin1())
        {
            case 'd':
            {//整数
                va_arg(arg_ptr, int);
                break;
            }
            case 'f':
            {//小数double类型,无float类型
                va_arg(arg_ptr, double);
                break;
            }
            case 's':
            case 'b':
            case 't':
            {
                va_arg(arg_ptr, void*);
                break;
            }
        } // end of switch
        char* pchFld = va_arg(arg_ptr, char*);
        strFld = pchFld;
    }
    strSql = strSql.left(strSql.length()-1) + " ";
    strSql += strWhere;
    pQry->prepare(strSql);//("INSERT INTO person (id, forename, surname) VALUES (:id, :forename, :surname)");
    va_start(arg_ptr, szFldInfo);
    strFld = (szFldInfo);
    while(szEnd != strFld)
    {
        QStringList strlst = strFld.split("%", QString::SkipEmptyParts);
        QChar ch('d'); //int is default
        if(strlst.size() > 1)
        {
            ch = strlst.at(1).at(0);
        }
        QString strPlaceholder = QString(":%1").arg(strlst[0]);
        QVariant var;
        switch (ch.toLatin1())
        {
            case 'd':
            {//整数
                int k = va_arg(arg_ptr, int);
                var = k;
                break;
            }
            case 'f':
            {
                double d = va_arg(arg_ptr, double);
                var = d;
                break;
            }
            case 's':
            {//文本
                QString * pch = va_arg(arg_ptr, QString*);
                var = *pch;
                break;
            }
            case 'b':
            {//二进制
                QByteArray *pData = va_arg(arg_ptr, QByteArray*);
                var = *pData;
                break;
            }
            case 't':
            {//时间日期
                QDateTime *pdt = va_arg(arg_ptr, QDateTime*);
                var = *pdt;
                break;
            }
        } // end of switch
        pQry->bindValue(strPlaceholder, var);
        char* pchFld = va_arg(arg_ptr, char*);
        strFld = pchFld;
    } //end of while

    va_end(arg_ptr);
    bool b = pQry->exec();

    delete pQry;
    return b;
}
