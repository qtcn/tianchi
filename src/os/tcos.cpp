#include <tianchi/os/tcos.h>

#include <QSettings>

#if defined(Q_OS_WIN)
  #include <windows.h>
#endif


QString TcOS::name()
{
    QString ret;
#if defined(Q_OS_WIN)
    const QString RegPath("HKEY_LOCAL_MACHINE\\Software\\Microsoft\\"
            "Windows NT\\CurrentVersion");
    QSettings reg(RegPath, QSettings::NativeFormat);
    ret = reg.value("ProductName").toString();
#endif

#if defined(Q_OS_LINUX)
    QFile file("/etc/hostname");
      if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
          return ret;
    ret.append(file.readLine());
#endif
    return ret;
}

QString TcOS::language()
{
    QString ret;
#if defined(Q_OS_WIN)
    LANGID  LangID = GetSystemDefaultLangID();
    wchar_t LanguageName[100];
    VerLanguageName(LangID, LanguageName, 100);
    ret = QString::fromWCharArray(LanguageName);
#endif
    return ret;
}

bool TcOS::login(const QString& Domain, const QString& UserID, 
        const QString& Password)
{
    bool ret = false;
#if defined(Q_OS_WIN)
    wchar_t* domain = new wchar_t[Domain.length() + 1];
    wmemset(domain, L'\0', sizeof(domain));
    Domain.toWCharArray(domain);

    wchar_t* userID = new wchar_t[UserID.length() + 1];
    wmemset(userID, L'\0', sizeof(userID));
    UserID.toWCharArray(userID);

    wchar_t* password = new wchar_t[Password.length() + 1];
    wmemset(password, L'\0', sizeof(password));
    Password.toWCharArray(password);

    HANDLE hUser;
    ret = LogonUser(userID,
                    domain,
                    password,
                    LOGON32_LOGON_NETWORK,
                    LOGON32_PROVIDER_DEFAULT,
                    &hUser);
    delete domain;
    delete userID;
    delete password;
#else
    Q_UNUSED(Domain)
    Q_UNUSED(UserID)
    Q_UNUSED(Password)
#endif
    return ret;
}
