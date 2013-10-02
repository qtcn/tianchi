#include <tianchi/chinese/tcchinese.h>

#include <QString>

#if defined(Q_OS_WIN)
#include "msime.h"
#endif


#if defined(Q_OS_WIN)
// --------------------------------------------------------------------------
class IMEEngine
{
private:
    BOOL	m_bCoInit;
    BOOL	m_bCoCreat;
    BOOL	m_bLangOpen;
    IFELanguage *m_pIFELanguage;
public:
    MORRSLT	*m_pmorrslt;
    DWORD	m_dwCaps;
    wchar_t	m_ImeName[32];
public:
    IMEEngine();
    ~IMEEngine();
    BOOL IsReady();
    //L"MSIME.China";
    //L"MSIME.Japan";
    //L"MSIME.Taiwan";
    //L"MSIME.Taiwan.ImeBbo";
    HRESULT SetIMEEngine( LPCWSTR msime = L"MSIME.China" );
    void UnsetIMEEngine( void );
    HRESULT GetJMorphResult( DWORD dwRequest, DWORD dwCMode, const WCHAR *pwchInput );
};

// ---------------------------------------------------------------------------------------------------------------------
// Construction/Destruction
IMEEngine::IMEEngine() : m_bCoInit(FALSE), m_bCoCreat(FALSE), m_bLangOpen(FALSE), m_pmorrslt(NULL)
{
    OleInitialize(NULL);
    m_bCoInit = TRUE;

    SetIMEEngine(L"MSIME.China");
}
// ---------------------------------------------------------------------------------------------------------------------
IMEEngine::~IMEEngine()
{
    UnsetIMEEngine();

//	if(m_bCoInit) {
//		CoUninitialize();
//	}
}
// ---------------------------------------------------------------------------------------------------------------------
BOOL IMEEngine::IsReady()
{
    return m_bLangOpen;
}
// ---------------------------------------------------------------------------------------------------------------------
HRESULT IMEEngine::GetJMorphResult(DWORD dwRequest, DWORD dwCMode, const WCHAR *pwchInput)
{
    if(!IsReady())
        return S_FALSE;
    if(m_pmorrslt) {
        CoTaskMemFree(m_pmorrslt);
        m_pmorrslt = NULL;
    }
    return m_pIFELanguage->GetJMorphResult(dwRequest, dwCMode,
        static_cast<INT>(wcslen(pwchInput)), const_cast<WCHAR*>(pwchInput),
        NULL, &m_pmorrslt);
}
// ---------------------------------------------------------------------------------------------------------------------
HRESULT IMEEngine::SetIMEEngine(LPCWSTR msime)
{
    static const IID IID_IFELanguage =
    {
        0x019f7152, 0xe6db, 0x11d0,
        { 0x83, 0xc3, 0x00, 0xc0, 0x4f, 0xdd, 0xb8, 0x2e }
    };

    UnsetIMEEngine();

    CLSID	clsid;
    if(CLSIDFromString(const_cast<LPWSTR>(msime), &clsid) != S_OK)
        return S_FALSE;

    if(CoCreateInstance(clsid, NULL, CLSCTX_SERVER,
            IID_IFELanguage, (LPVOID*)&m_pIFELanguage) != S_OK)
        return S_FALSE;

    m_bCoCreat = TRUE;

    if(m_pIFELanguage)
        if(m_pIFELanguage->Open() == S_OK)
            m_bLangOpen = TRUE;

    m_pIFELanguage->GetConversionModeCaps(&m_dwCaps);
    //wcsncpy_s(m_ImeName, msime, wcslen(m_ImeName));
    return S_OK;
}
// ---------------------------------------------------------------------------------------------------------------------
void IMEEngine::UnsetIMEEngine(void)
{
//	if(m_pmorrslt) {
//		CoTaskMemFree(m_pmorrslt);
//		m_pmorrslt = NULL;
//	}

    if(m_bLangOpen) {
        m_pIFELanguage->Close();
        m_bLangOpen = FALSE;
    }

    if(m_bCoCreat) {
        m_pIFELanguage->Release();
        m_bCoCreat = FALSE;
    }
    m_dwCaps = 0;
}
// ---------------------------------------------------------------------------------------------------------------------
#endif

QString TcChinese::firstPinyins(const QString& HzString)
{
    QString ret;
    foreach(QChar c, HzString)
    {
        QString s(c);
        s = toPinyin(s, false).trimmed();
        if ( ! s.isEmpty() )
        {
            ret += s.mid(0, 1);
        }
    }
    return ret;
}

QString TcChinese::toChars(const QString& Str, bool Tonality)
{
    QString ret = "";
    for( int i=0;i<Str.length();i++ )
    {
        QString s = Str[i];
        if ( s.length() < s.toLocal8Bit().length() )
        {
            ret += toPinyin(s, Tonality);
        }else
        {
            ret += s;
        }
    }
    return ret;
}

QString TcChinese::toPinyin(const QString& Str, bool Tonality)
{
    QString ret;
#ifdef Q_OS_WIN
    IMEEngine imee;
    imee.GetJMorphResult(FELANG_REQ_REV,
                         FELANG_CMODE_PINYIN | FELANG_CMODE_NOINVISIBLECHAR, // ������ʾƴ�����м䲻��ʾ�ո�ָ���
                         Str.toStdWString().c_str());
    if ( imee.m_pmorrslt ) // && imee.m_pmorrslt->cchOutput >0 )
    {
        wchar_t*  wsptr = imee.m_pmorrslt->pwchOutput;
        int       len   = imee.m_pmorrslt->cchOutput -1;

        for( int i=0;i<=len;i++ )
        {
            ret += QChar(uint(*wsptr));
            wsptr++;
        }
        if ( ! Tonality )
        {
            const QString Initial1 = QString::fromLocal8Bit("����������������������������������������������������������������");
            const QString Initial2 = "aaaaooooeeeeiiiiuuuuvvvvveamnnng";
            for( int i=0;i<Initial1.length();i++ )
            {
                ret.replace(Initial1.at(i), Initial2.at(i));
            }
        }
    }

#else
    Q_UNUSED(Str)
    Q_UNUSED(Tonality)
#endif
    return ret;
}

QString TcChinese::toEnglishName(const QString& Str, bool style, bool capitalization,
        bool hyphenatedname)
{
    QString ret = "";
    QString firstname = "";//����
    QString lastname = "";//����
    //���ֺ����Ϸֿ�����
    if ( hyphenatedname )//�Ǹ���
    {
        for(int i=2;i<Str.length();i++)
        {
            //��������
            QString st = Str[i];
            firstname += toPinyin(st, false);
        }
        QString left = firstname.left(1).toUpper();
        QString right = firstname.right(firstname.length() -1);
        firstname = left + right;

        //���ִ����꣬��������
        lastname += toPinyin(Str[0], false);
        lastname += toPinyin(Str[1], false);

        //�ж������Ƿ�Ҫ��д
        if (! capitalization)//ֻ������ĸ��д
        {
            QString left = lastname.left(1).toUpper();
            QString right = lastname.right(lastname.length() -1);
            lastname = left + right;
        }
        else//������ĸȫ����д
        {
            lastname = lastname.toUpper();
        }

    }
    else//���Ǹ��մ�������
    {
        for(int i=1;i<Str.length();i++)
        {
            //��������
            QString st = Str[i];
            firstname += toPinyin(st, false);
    }
        QString left = firstname.left(1).toUpper();
        QString right = firstname.right(firstname.length() -1);
        firstname = left + right;
        //���ִ����꣬��������
        lastname += toPinyin(Str[0], false);

        //�ж������Ƿ�Ҫ��д
        if (! capitalization)//ֻ������ĸ��д
        {
            QString left = lastname.left(1).toUpper();
            QString right = lastname.right(lastname.length() -1);
            lastname = left + right;
        }
        else//������ĸȫ����д
        {
            lastname = lastname.toUpper();
        }
    }

    //�жϺ���ϰ�߻���Ӣ��ϰ�ߣ������Ϻ�����˳��
    if (! style) //����ϰ��
    {
        ret = lastname + " " + firstname;
    }
    else
    {
        ret = firstname + " " + lastname;
    }

    return ret;
}
