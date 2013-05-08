// **************************************************************************
// Tianchi C++ library for Qt (open source)
// 天池共享源码库
// 版权所有 (C) 天池共享源码库开发组
// 授权协议：请阅读天池共享源码库附带的授权协议
// **************************************************************************
// 文档说明：数据库操作类
// ==========================================================================
// 开发日志：
// 日期         人员        说明
// --------------------------------------------------------------------------
// 2013.05.03   圣域天子    建立
//
// ==========================================================================
/// @file DatabaseInterface.h 数据库操作类
// ==========================================================================
#ifndef TIANCHI_TCDATABASE_H
#define TIANCHI_TCDATABASE_H

#include <tianchi/tcglobal.h>

#include <QVariant>
#include <QMultiHash>
#include <QStringList>
#include <QSqlDatabase>

typedef QHash<QString, QByteArray>  TcParams;
class TIANCHI_API TcDatabase
{
public:
    TcDatabase();
    virtual ~TcDatabase(void);

    enum DBType
    {
        SQLSERVER =  1,
        SQLITE    = 11
    };

    static  char     typeFrom(QVariant::Type type);

    static  int      dbType(const QString& typeName);
    static  TcParams addParams(const QStringList& keys, 
            const QList<QByteArray>& values);


    /// @brief 设置网络数据库
    void setDatabase(int dbType,
                     const QString& hostName, int hostPort,
                     const QString& dbName, const QString& username, 
                     const QString& password);
    /// @brief 设置网络数据库
    bool setDatabase(const QString& typeName,
                     const QString& hostName, int hostPort,
                     const QString& dbName, const QString& username, 
                     const QString& password);
    /// @brief 设置本地数据库
    void setDatabase(int dbType,
                     const QString& dbName, 
                     const QString& username = QString(), 
                     const QString& password = QString());
    /// @brief 设置本地数据库
    bool setDatabase(const QString& typeName,
                     const QString& dbName, 
                     const QString& username = QString(), 
                     const QString& password = QString());

    /// @brief 本地数据库不存在时，使用此DDL进行重建
    QString CreateDDL;

    QString SqlLibrary;

    /// @brief 数据库操作时的错误信息
    QStringList errors;

    QString lastError();

protected:
    int     m_dbType;
    QString m_typeName;
    QString m_hostName;
    int     m_hostPort;
    QString m_dbName;
    QString m_username;
    QString m_password;

    QSqlDatabase    m_handle;

    // 数据引擎
    QString m_engineFile;
    struct SQLContext
    {
        QString                         id;
        QString                         text;
        QMultiHash<QString, QString>    params;
    };
    QHash<QString, SQLContext>  m_sqls;
    void clearComment(QString& s);

    /// @brief 数据库操作准备, 注意 params 的 key 必须全小写
    QSqlQuery* prepare(const QString& sqlID, TcParams prams,
                       QString& error, int userNo = 0, 
                       const QString& userID = QString(), 
                       const QString& username = QString());
public:
    inline int      dbType()   const { return m_dbType;   }
    inline QString  typeName() const { return m_typeName; }
    inline QString  hostName() const { return m_hostName; }
    inline int      hostPort() const { return m_hostPort; }
    inline QString  dbName()   const { return m_dbName;   }

    inline QSqlDatabase handle() const { return m_handle; }
    inline int          sqlCount() const { return m_sqls.count(); }

public:
    /// 打开数据库
    /// @return 操作结果
    ///  1   操作成功
    ///  0   操作失败
    /// -1   数据库无法创建或更新
    /// -2   数据库不兼容
    /// -3   版本太新，程序不支持
    /// @see close
    int  open();

    /// @brief 关闭数据库
    /// @see open
    void close();

    /// @brief 数据库是否已打开
    inline bool isOpened() const { return m_handle.isOpen(); }

    /// @brief 重新载入数据库的操作SQL集
    void loadEngine();
    /// @brief 载入数据库的操作SQL集
    void loadEngine(const QString& filename);

    /// @brief 执行操作SQLID，无返回数据集
    bool exec(int& result, const QString& sqlID, 
            const TcParams& prams,
            int userNo = 0, 
            const QString& userID = QString(), 
            const QString& username = QString());
    /// @brief 执行操作SQLID，可返回数据集
    bool exec(QVariantList& list, 
            const QString& sqlID, 
            const TcParams& params,
            int userNo = 0, 
            const QString& userID = QString(), 
            const QString& username = QString());
    /// @brief 执行操作SQLID，可返回数据集
    int exec(int& result, QVariantList& list, 
            const QString& sqlID, const TcParams& params,
            int userNo = 0, 
            const QString& userID = QString(), 
            const QString& username = QString());
    /// @brief 执行操作SQLID，可返回数据集
    int exec(int& result, QList<QByteArray>& list, 
            const QString& sqlID, const TcParams& params,
            int userNo = 0, 
            const QString& userID = QString(), 
            const QString& username = QString());
};

#endif // TIANCHI_TCDATABASE_H
