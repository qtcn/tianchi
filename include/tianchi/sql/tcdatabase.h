// **************************************************************************
// Tianchi C++ library for Qt (open source)
// ��ع���Դ���
// ��Ȩ���� (C) ��ع���Դ��⿪����
// ��ȨЭ�飺���Ķ���ع���Դ��⸽������ȨЭ��
// **************************************************************************
// �ĵ�˵�������ݿ������
// ==========================================================================
// ������־��
// ����         ��Ա        ˵��
// --------------------------------------------------------------------------
// 2013.05.03   ʥ������    ����
//
// ==========================================================================
/// @file DatabaseInterface.h ���ݿ������
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


    /// @brief �����������ݿ�
    void setDatabase(int dbType,
                     const QString& hostName, int hostPort,
                     const QString& dbName, const QString& username, 
                     const QString& password);
    /// @brief �����������ݿ�
    bool setDatabase(const QString& typeName,
                     const QString& hostName, int hostPort,
                     const QString& dbName, const QString& username, 
                     const QString& password);
    /// @brief ���ñ������ݿ�
    void setDatabase(int dbType,
                     const QString& dbName, 
                     const QString& username = QString(), 
                     const QString& password = QString());
    /// @brief ���ñ������ݿ�
    bool setDatabase(const QString& typeName,
                     const QString& dbName, 
                     const QString& username = QString(), 
                     const QString& password = QString());

    /// @brief �������ݿⲻ����ʱ��ʹ�ô�DDL�����ؽ�
    QString CreateDDL;

    QString SqlLibrary;

    /// @brief ���ݿ����ʱ�Ĵ�����Ϣ
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

    // ��������
    QString m_engineFile;
    struct SQLContext
    {
        QString                         id;
        QString                         text;
        QMultiHash<QString, QString>    params;
    };
    QHash<QString, SQLContext>  m_sqls;
    void clearComment(QString& s);

    /// @brief ���ݿ����׼��, ע�� params �� key ����ȫСд
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
    /// �����ݿ�
    /// @return �������
    ///  1   �����ɹ�
    ///  0   ����ʧ��
    /// -1   ���ݿ��޷����������
    /// -2   ���ݿⲻ����
    /// -3   �汾̫�£�����֧��
    /// @see close
    int  open();

    /// @brief �ر����ݿ�
    /// @see open
    void close();

    /// @brief ���ݿ��Ƿ��Ѵ�
    inline bool isOpened() const { return m_handle.isOpen(); }

    /// @brief �����������ݿ�Ĳ���SQL��
    void loadEngine();
    /// @brief �������ݿ�Ĳ���SQL��
    void loadEngine(const QString& filename);

    /// @brief ִ�в���SQLID���޷������ݼ�
    bool exec(int& result, const QString& sqlID, 
            const TcParams& prams,
            int userNo = 0, 
            const QString& userID = QString(), 
            const QString& username = QString());
    /// @brief ִ�в���SQLID���ɷ������ݼ�
    bool exec(QVariantList& list, 
            const QString& sqlID, 
            const TcParams& params,
            int userNo = 0, 
            const QString& userID = QString(), 
            const QString& username = QString());
    /// @brief ִ�в���SQLID���ɷ������ݼ�
    int exec(int& result, QVariantList& list, 
            const QString& sqlID, const TcParams& params,
            int userNo = 0, 
            const QString& userID = QString(), 
            const QString& username = QString());
    /// @brief ִ�в���SQLID���ɷ������ݼ�
    int exec(int& result, QList<QByteArray>& list, 
            const QString& sqlID, const TcParams& params,
            int userNo = 0, 
            const QString& userID = QString(), 
            const QString& username = QString());
};

#endif // TIANCHI_TCDATABASE_H
