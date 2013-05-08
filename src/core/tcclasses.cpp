#include <tianchi/core/tcclasses.h>
#include <tianchi/core/tcutils.h>

TcPlayer::TcPlayer()
    : QObject()
{
    m_loggedIn  = false;
    m_userNo    = 0;
    m_userLevel = 0;
    m_noLoginTimer.start();
}

TcPlayer& TcPlayer::operator=(const TcPlayer & from)
{
    if ( this != &from )
    {
        m_userNo    = from.m_userNo;
        m_userID    = from.m_userID;
        m_username  = from.m_username;
        m_userLevel = from.m_userLevel;

        m_authority = from.m_authority;

        m_loginID   = from.m_loginID;
        m_password  = from.m_password;

        m_loggedIn  = from.m_loggedIn;
        m_loginTime = from.m_loginTime;
    }
    return *this;
}

void TcPlayer::setLoggedIn(bool value)
{
    m_loggedIn = value;
    m_loginTime = QDateTime::currentDateTime();
    if ( ! value )
    {
        m_noLoginTimer.restart();
    }
}

void TcPlayer::clear()
{
    m_userNo    = 0;
    m_userID    = "";
    m_username  = "";
    m_userLevel = 0;

    m_loginID  = "";
    m_password = "";

    m_loggedIn  = false;
    m_loginTime = QDateTime();

    m_noLoginTimer.restart();
}

int TcPlayer::authority(const QString& key) const
{
    int ret  = 0;
    if ( m_userLevel >= AUTH_ADMIN )
    {
        ret = m_userLevel;
    }else
    if ( m_userLevel >= AUTH_GUEST )
    {
        ret = m_authority.value(key);
    }
    return ret;
}

void TcPlayer::setAuthorityText(const QString& value)
{
    QHash<QString, QString> map = TcUtils::StringToMap(value);

    m_authority.clear();

    QStringList keys = map.keys();
    foreach(QString key, keys)
    {
        int value = map.value(key).toInt();
        if ( value >0 )
        {
            m_authority[key] = value;
        }
    }
}

void TcPlayer::setAuthorityText(const QStringList& value)
{
    QHash<QString, QString> map = TcUtils::StringToMap(value);

    m_authority.clear();

    QStringList keys = map.keys();
    foreach(QString key, keys)
    {
        int value = map.value(key).toInt();
        if ( value >0 )
        {
            m_authority[key] = value;
        }
    }
}

// ==========================================================================
bool TcInvoke::invoke(QGenericArgument val0,
                           QGenericArgument val1,
                           QGenericArgument val2,
                           QGenericArgument val3,
                           QGenericArgument val4,
                           QGenericArgument val5,
                           QGenericArgument val6,
                           QGenericArgument val7,
                           QGenericArgument val8,
                           QGenericArgument val9)
{
    try 
    {
        return m_object != NULL ? m_object->metaObject()->invokeMethod(m_object, m_method,
                                                                       val0, val1, val2, val3, val4,
                                                                       val5, val6, val7, val8, val9)
                                : false;
    }catch(...)
    {
        return false;
    }
}

// ==========================================================================
void TcDBFields::addField(QByteArray& fieldBytes, const QString& name, 
        const QVariant& value)
{
    QByteArray bytes = value.toByteArray();
    fieldBytes.append(name).append('\0')
            .append(TcUtils::typeFrom(value.type())).append('\0')
            .append(QByteArray::number(bytes.length())).append('\0')
            .append(bytes);
}

QHash<QString, QByteArray> TcDBFields::getFields(const QByteArray& fieldBytes)
{
    QHash<QString, QByteArray>  ret;

    int pos1 = 0;
    int pos2 = fieldBytes.indexOf('\0');
    while (pos2 >= 0)
    {
        QString key = fieldBytes.mid(pos1, pos2);
        pos1 = fieldBytes.indexOf('\0', ++pos2);
        QString type = fieldBytes.mid(pos2, pos1-pos2);
        pos2 = fieldBytes.indexOf('\0', ++pos1);
        int len = fieldBytes.mid(pos1, pos2-pos1).toInt();
        QByteArray value = fieldBytes.mid(++pos2, len);
        pos1 = pos2+len;
        ret[key] = value;
        pos2 = fieldBytes.indexOf('\0', pos1);
    }
    return ret;
}
