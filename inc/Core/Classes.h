// ********************************************************************************************************************
// Tianchi C++ library for Qt (open source)
// 天池共享源码库
// 版权所有 (C) 天池共享源码库开发组
// 授权协议：请阅读天池共享源码库附带的授权协议
// ********************************************************************************************************************
// 文档说明：一些常用的小类
// ====================================================================================================================
// 开发日志：
// 日期         人员        说明
// --------------------------------------------------------------------------------------------------------------------
// 2013.04.10   圣域天子    建立
//
// ====================================================================================================================
/// @file Classes.h 一些常用的小类
#ifndef TIANCHI_CLASSES_H
#define TIANCHI_CLASSES_H

#include "Global.h"

#include <QDateTime>
#include <QObject>
#include <QString>
#include <QStringList>
#include <QElapsedTimer>
#include <QHash>

TIANCHI_BEGIN_NAMESPACE

QT_USE_NAMESPACE

/// @brief 玩家信息类，常用在 C/S 中的客户端用户信息保存
class TIANCHI_API Player : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int       userNo    READ userNo    WRITE setUserNo   ) ///< 用户序号
    Q_PROPERTY(QString   userID    READ userID    WRITE setUserID   ) ///< 用户ID
    Q_PROPERTY(QString   username  READ username  WRITE setUsername ) ///< 用户全名
    Q_PROPERTY(bool      loggedIn  READ loggedIn  WRITE setLoggedIn ) ///< 是否已登录
    Q_PROPERTY(QDateTime loginTime READ loginTime WRITE setLoginTime) ///< 登录时间

public:
    /// 用户权限
    typedef enum AuthLevel
    {
        AUTH_SYSADMIN = 999,  ///< 最高系统级管理员权限
        AUTH_ADMIN    = 888,  ///< 最高用户级管理员权限
        AUTH_MANAGER  =  99,  ///< 用户级：管理权限
        AUTH_USER     =   9,  ///< 用户级：普通用户权限
        AUTH_GUEST    =   1,  ///< 用户级：访客级权限
    };


    Player();
    Player &operator=(const Player&);

    inline int          userNo() const { return m_userNo; }
    /// @brief 指定用户的 No
    inline void         setUserNo(int value) { m_userNo = value; }
    inline QString      userID() const { return m_userID; }
    /// @brief 指定用户的 ID
    inline void         setUserID(const QString& value) { m_userID = value.trimmed(); }
    inline QString      username() const { return m_username; }
    /// @brief 指定用户的 username
    inline void         setUsername(const QString& value) { m_username = value.trimmed(); }
    inline int          userLevel() const { return m_userLevel; }
    /// @brief 指定用户的权限级别
    inline void         setUserLevel(int value) { m_userLevel = value; }

    int                 authority(const QString& key) const;
    /// @brief 指定用户的权限模块级别
    inline void         setAuthority(const QString& key, int auth) { m_authority[key] = auth; }
    /// @brief 快速设置用户的全部权限级别
    void                setAuthorityText(const QString& value);
    /// @brief 快速设置用户的全部权限级别
    void                setAuthorityText(const QStringList& value);

    inline QString      loginID() const { return m_loginID; }
    /// @brief 保存用户的登录名称
    inline void         setLoginID(const QString& value) { m_loginID = value.trimmed(); }
    inline QString      password() const { return m_password; }
    /// @brief 保存用户的登录密码
    inline void         setPassword(const QString& value) { m_password = value.trimmed(); }
    /// @brief 玩家是否已登录
    inline bool         loggedIn() const { return m_loggedIn; }
    /// @brief 指定玩家是否已登录
           void         setLoggedIn(bool value);
    /// @brief 将玩家设为已登录
    inline void         setLoggedIn() { setLoggedIn(true); }
    /// @brief 玩家的登录时间
    inline QDateTime    loginTime() const { return m_loginTime; }
    /// @brief 指定玩家的登录时间
    inline void         setLoginTime(QDateTime value) { m_loginTime = value; m_loggedIn = true; }

    /// @brief 返回玩家距今未登录的秒数
    /// 常用于意外断线后，显示已脱机的时间
    inline int          noLoginTime() { return m_loggedIn ? 0 : m_noLoginTimer.elapsed()/1000; }

    /// @brief 清除玩家的所有信息
    void clear();

private:
    int                 m_userNo;
    QString             m_userID;
    QString             m_username;
    int                 m_userLevel;
    QHash<QString, int> m_authority;

    QString             m_loginID;
    QString             m_password;

    bool                m_loggedIn;
    QDateTime           m_loginTime;
    QElapsedTimer       m_noLoginTimer;
};

/// @brief 映射执行对象类
class TIANCHI_API CInvokeObject
{
public:
    CInvokeObject(QObject* o=NULL, QByteArray m="")
            { init(o, m); }
    CInvokeObject &operator=(const CInvokeObject& from)
    {
        if ( this != &from )
        {
            this->m_object = from.m_object;
            this->m_method = from.m_method;
        }
        return *this;
    }
    inline void init(QObject* o, QByteArray m)
            { m_object = o; m_method = m; }

    inline bool queued(QGenericArgument val0 = QGenericArgument(0),
                       QGenericArgument val1 = QGenericArgument(),
                       QGenericArgument val2 = QGenericArgument(),
                       QGenericArgument val3 = QGenericArgument(),
                       QGenericArgument val4 = QGenericArgument(),
                       QGenericArgument val5 = QGenericArgument(),
                       QGenericArgument val6 = QGenericArgument(),
                       QGenericArgument val7 = QGenericArgument(),
                       QGenericArgument val8 = QGenericArgument(),
                       QGenericArgument val9 = QGenericArgument())
    {
        try {
            return m_object != NULL ? m_object->metaObject()->invokeMethod(m_object, m_method,
                                                                           Qt::QueuedConnection,
                                                                           val0, val1, val2, val3, val4,
                                                                           val5, val6, val7, val8, val9)
                                    : false;
        }catch(...)
        {
            return false;
        }
    }
    bool invoke(QGenericArgument val0 = QGenericArgument(0),
                       QGenericArgument val1 = QGenericArgument(),
                       QGenericArgument val2 = QGenericArgument(),
                       QGenericArgument val3 = QGenericArgument(),
                       QGenericArgument val4 = QGenericArgument(),
                       QGenericArgument val5 = QGenericArgument(),
                       QGenericArgument val6 = QGenericArgument(),
                       QGenericArgument val7 = QGenericArgument(),
                       QGenericArgument val8 = QGenericArgument(),
                       QGenericArgument val9 = QGenericArgument());

    inline bool isValid() const { return m_object != NULL && ! m_method.isEmpty(); }
private:
    QObject*    m_object;
    QByteArray  m_method;
};

/// @brief key=value 数据格式转换类
/// @note C/S 架构中，所以信息都以 key=value 格式传递，此类用于 k=v 信息的读取
class TIANCHI_API DBFields
{
public:
    DBFields() {}
    inline DBFields(QHash<QString, QByteArray> fields)
                    { setFields(fields); }

    static void addField(QByteArray& fieldBytes, const QString& name, const QVariant& value);
    static QHash<QString, QByteArray> getFields(const QByteArray& fieldBytes);

    void    setFields(QHash<QString, QByteArray> fields)
    {
        m_fields.clear();
        m_keys.clear();

        m_fields = fields;
        m_keys = m_fields.keys();
    }
    inline QByteArray value(const QString& key) const
    {
        return m_fields.value(key.trimmed().toLower());
    }

private:
    QHash<QString, QByteArray>  m_fields;
    QStringList m_keys;
};


TIANCHI_END_NAMESPACE

#endif // TIANCHI_CLASSES_H
