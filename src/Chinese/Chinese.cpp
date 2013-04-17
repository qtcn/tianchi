#include "Chinese/Chinese.h"

//#include "IMEEngine.h"
#include <qglobal.h>

#include <QString>

#if defined(Q_OS_WIN)
#include "msime.h"
#endif

TIANCHI_BEGIN_NAMESPACE

#if defined(Q_OS_WIN)
// ---------------------------------------------------------------------------------------------------------------------
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
/*
QString chineseToPinyin(const QString& Str, bool Tonality)
{
    QString ret;
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
            //const QString Initial1 = QString::fromWCharArray(L"����������������������������������������������������������������");
            const QString Initial1 = QString::fromLocal8Bit("����������������������������������������������������������������");
            const QString Initial2 = "aaaaooooeeeeiiiiuuuuvvvvveamnnng";
            for( int i=0;i<Initial1.length();i++ )
            {
                ret.replace(Initial1.at(i), Initial2.at(i));
            }
        }
    }
    return ret;
}

QString chineseToChars(const QString& Str, bool Tonality)
{
    QString ret = "";
    for( int i=0;i<Str.length();i++ )
    {
        QString s = Str[i];
        if ( s.size() >0 )
        {
            ret += chineseToPinyin(s, Tonality);
        }else
        {
            ret += s;
        }
    }
    return ret;
}

QString firstPinyins(const QString& HzString)
{
    QString ret;
    foreach(QChar c, HzString)
    {
        QString s(c);
        s = chineseToPinyin(s, false).trimmed();
        if ( ! s.isEmpty() )
        {
            ret += s.mid(0, 1);
        }
    }
    return ret;
}

QString firstPinyins(const QString& HzString)
{
    static int   li_SecPosValue[]  = {1601,1637,1833,2078,2274,2302,2433,2594,2787,3106,3212,3472,3635,3722,3730,3858,4027,4086,4390,4558,4684,4925,5249};
    static char* lc_FirstLetter[]  = {"a",   "b","c","d","e","f","g","h","j","k","l","m","n","o","p","q","r","s","t","w","x","y","z"};
    static char* ls_SecondSecTable =
    "cjwgnspgcgne[y[btyyzdxykygt[jnnjqmbsgzscyjsyy[pgkbzgy[ywjkgkljywkpjqhy[w[dzlsgmrypywwcckznkyygttnjjnykkzytcjnmcylqlypyqfqrpzslwbtgkjfyxjwzltbncxjjjjtxdttsqzycdxxhgck[phffss[ybgxlppbyll[hlxs[zm[jhsojnghdzqyklgjhsgqzhxqgkezzwyscscjxyeyxadzpmdssmzjzqjyzc[j[wqjbyzpxgznzcpwhkxhqkmwfbpbydtjzzkqhy"
    "lygxfptyjyyzpszlfchmqshgmxxsxj[[dcsbbqbefsjyhxwgzkpylqbgldlcctnmayddkssngycsgxlyzaybnptsdkdylhgymylcxpy[jndqjwxqxfyyfjlejpzrxccqwqqsbnkymgplbmjrqcflnymyqmsqyrbcjthztqfrxqhxmjjcjlxqgjmshzkbswyemyltxfsydswlycjqxsjnqbsctyhbftdcyzdjwyghqfrxwckqkxebptlpxjzsrmebwhjlbjslyysmdxlclqkxlhxjrzjmfqhxhwy"
    "wsbhtrxxglhqhfnm[ykldyxzpylgg[mtcfpajjzyljtyanjgbjplqgdzyqyaxbkysecjsznslyzhsxlzcghpxzhznytdsbcjkdlzayfmydlebbgqyzkxgldndnyskjshdlyxbcghxypkdjmmzngmmclgwzszxzjfznmlzzthcsydbdllscddnlkjykjsycjlkwhqasdknhcsganhdaashtcplcpqybsdmpjlpzjoqlcdhjjysprchn[nnlhlyyqyhwzptczgwwmzffjqqqqyxaclbhkdjxdgmmy"
    "djxzllsygxgkjrywzwyclzmssjzldbyd[fcxyhlxchyzjq[[qagmnyxpfrkssbjlyxysyglnscmhzwwmnzjjlxxhchsy[[ttxrycyxbyhcsmxjsznpwgpxxtaybgajcxly[dccwzocwkccsbnhcpdyznfcyytyckxkybsqkkytqqxfcwchcykelzqbsqyjqcclmthsywhmktlkjlycxwheqqhtqh[pq[qscfymndmgbwhwlgsllysdlmlxpthmjhwljzyhzjxhtxjlhxrswlwzjcbxmhzqxsdzp"
    "mgfcsglsxymjshxpjxwmyqksmyplrthbxftpmhyxlchlhlzylxgsssstclsldclrpbhzhxyyfhb[gdmycnqqwlqhjj[ywjzyejjdhpblqxtqkwhlchqxagtlxljxmsl[htzkzjecxjcjnmfby[sfywybjzgnysdzsqyrsljpclpwxsdwejbjcbcnaytwgmpapclyqpclzxsbnmsggfnzjjbzsfzyndxhplqkzczwalsbccjx[yzgwkypsgxfzfcdkhjgxdlqfsgdslqwzkxtmhsbgzmjzrglyjb"
    "pmlmsxlzjqqhzyjczydjwbmyklddpmjegxyhylxhlqyqhkycwcjmyyxnatjhyccxzpcqlbzwwytwbqcmlpmyrjcccxfpznzzljplxxyztzlgdldcklyrzzgqtgjhhgjljaxfgfjzslcfdqzlclgjdjcsnzlljpjqdcclcjxmyzftsxgcgsbrzxjqqctzhgyqtjqqlzxjylylbcyamcstylpdjbyregklzyzhlyszqlznwczcllwjqjjjkdgjzolbbzppglghtgzxyghzmycnqsycyhbhgxkamtx"
    "yxnbskyzzgjzlqjdfcjxdygjqjjpmgwgjjjpkqsbgbmmcjssclpqpdxcdyyky[cjddyygywrhjrtgznyqldkljszzgzqzjgdykshpzmtlcpwnjafyzdjcnmwescyglbtzcgmssllyxqsxsbsjsbbsgghfjlypmzjnlyywdqshzxtyywhmzyhywdbxbtlmsyyyfsxjc[dxxlhjhf[sxzqhfzmzcztqcxzxrttdjhnnyzqqmnqdmmg[ydxmjgdhcdyzbffallztdltfxmxqzdngwqdbdczjdxbzgs"
    "qqddjcmbkzffxmkdmdsyyszcmljdsynsbrskmkmpcklgdbqtfzswtfgglyplljzhgj[gypzltcsmcnbtjbqfkthbyzgkpbbymtdssxtbnpdkleycjnyddykzddhqhsdzsctarlltkzlgecllkjlqjaqnbdkkghpjtzqksecshalqfmmgjnlyjbbtmlyzxdcjpldlpcqdhzycbzsczbzmsljflkrzjsnfrgjhxpdhyjybzgdlqcsezgxlblgyxtwmabchecmwyjyzlljjyhlg[djlslygkdzpzxj"
    "yyzlwcxszfgwyydlyhcljscmbjhblyzlycblydpdqysxqzbytdkyxjy[cnrjmpdjgklcljbctbjddbblblczqrppxjcjlzcshltoljnmdddlngkaqhqhjgykheznmshrp[qqjchgmfprxhjgdychghlyrzqlcyqjnzsqtkqjymszswlcfqqqxyfggyptqwlmcrnfkkfsyylqbmqammmyxctpshcptxxzzsmphpshmclmldqfyqxszyydyjzzhqpdszglstjbckbxyqzjsgpsxqzqzrqtbdkyxzk"
    "hhgflbcsmdldgdzdblzyycxnncsybzbfglzzxswmsccmqnjqsbdqsjtxxmbltxzclzshzcxrqjgjylxzfjphymzqqydfqjjlzznzjcdgzygctxmzysctlkphtxhtlbjxjlxscdqxcbbtjfqzfsltjbtkqbxxjjljchczdbzjdczjdcprnpqcjpfczlclzxzdmxmphjsgzgszzqlylwtjpfsyasmcjbtzkycwmytcsjjljcqlwzmalbxyfbpnlsfhtgjwejjxxglljstgshjqlzfkcgnnnszfdeq"
    "fhbsaqtgylbxmmygszldydqmjjrgbjtkgdhgkblqkbdmbylxwcxyttybkmrtjzxqjbhlmhmjjzmqasldcyxyqdlqcafywyxqhz";
    QByteArray ret;

//    unsigned stringlen = HzString.length();
    const char* ptrHz = HzString.toAscii().data();
    while(*ptrHz)
    {
        int H = (int)(*ptrHz);
        int L = (int)(*(ptrHz+1));
        if ( H < 0xA1 || L < 0xA1 )
        {
            ret += *ptrHz;
        }else
        {
            int W = (H-160)*100+L-160;
            if ( W > 1600 && W < 5590 )
            {
                for ( int j=22;j>=0;j-- )
                {
                    if ( W >= li_SecPosValue[j] )
                    {
                        ret += lc_FirstLetter[j];
                    }
                }
           }else
           {
                W = (H-160-56)*94+L-161;
                if ( W >= 0 && W <= 3007 )
                {
                    ret += ls_SecondSecTable[W];
                }else
                {
                    ret += (char)H;
                    ret += (char)L;
                }
            }
        }
        ptrHz++;
    }
    return QString(ret);
}
*/

//wchar_t GetFirstPinyin(String HzString)
//{
//    wchar_t Result = '\0';
//    String Pinyin = ChineseToPinyin(HzString, false);
//    if ( ! Pinyin.IsEmpty() )
//    {
//        Result = Pinyin.UpperCase()[1];
//    }
//    return Result;
//}
//String FirstPinyin(String HzString)
//{
//    String Result;
//    String Pinyin = ChineseToPinyin(HzString, false);
//    if ( ! Pinyin.IsEmpty() )
//    {
//        Result = Pinyin.UpperCase()[1];
//    }
//    return Result;
//}

#endif

QString Chinese::toChars(const QString& Str, bool Tonality)
{
    QString ret = "";
    for( int i=0;i<Str.length();i++ )
    {
        QString s = Str[i];
        if ( s.size() >0 )
        {
            ret += toPinyin(s, Tonality);
        }else
        {
            ret += s;
        }
    }
    return ret;
}

QString Chinese::toPinyin(const QString& Str, bool Tonality)
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
            //const QString Initial1 = QString::fromWCharArray(L"����������������������������������������������������������������");
            const QString Initial1 = QString::fromLocal8Bit("����������������������������������������������������������������");
            const QString Initial2 = "aaaaooooeeeeiiiiuuuuvvvvveamnnng";
            for( int i=0;i<Initial1.length();i++ )
            {
                ret.replace(Initial1.at(i), Initial2.at(i));
            }
        }
    }
#endif
    return ret;
}

QString Chinese::firstPinyins(const QString& HzString)
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

TIANCHI_END_NAMESPACE
