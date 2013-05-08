#include <tianchi/file/tcexcelreader.h>
#include <QFile>
#ifdef Q_OS_WIN
#include <QDateTime>
#include <QAxObject>
#if (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
#include <QStandardPaths>
#else
#include <QDesktopServices>
#endif
#endif

class TcExcelReaderPrivate
{
    Q_DECLARE_PUBLIC(TcExcelReader)
public:
    explicit TcExcelReaderPrivate(TcExcelReader *qptr);
    ~TcExcelReaderPrivate();
    TcExcelReader *q_ptr;
#ifdef Q_OS_WIN
    QAxObject *excel;
    QAxObject *workbooks;
    QAxObject *workbook;
    QAxObject *sheets;
    QAxObject *sheet;
#endif
    QString tmpFile;;
    bool isNull;
    QStringList sheetNames;
    int currentSheetIndex;
};

TcExcelReaderPrivate::TcExcelReaderPrivate(TcExcelReader *qptr) : q_ptr(qptr), 
#ifdef Q_OS_WIN
    excel(new QAxObject), 
    workbooks(NULL), workbook(NULL), sheets(NULL), sheet(NULL),
#endif
    isNull(true), currentSheetIndex(-1)
{
#ifdef Q_OS_WIN
    excel->setControl("Excel.Application");
    if (excel->isNull())
    {
        excel->setControl("ET.Application");
    }
    if (!excel->isNull())
    {
        isNull = false;
        excel->dynamicCall("SetVisible(bool)", false);
        workbooks = excel->querySubObject("Workbooks");
    }
#endif
}

TcExcelReaderPrivate::~TcExcelReaderPrivate()
{
#ifdef Q_OS_WIN
    if (!isNull)
    {
        excel->dynamicCall("Quit()");
    }
    if (sheet)
    {
        delete sheet;
    }
    if (sheets)
    {
        delete sheets;
    }
    if (workbook)
    {
        delete workbook;
    }
    if (workbooks)
    {
        delete workbooks;
    }
    delete excel;
#endif
    if (!tmpFile.isEmpty() && QFile::exists(tmpFile))
    {
        QFile::remove(tmpFile);
    }
}

TcExcelReader::TcExcelReader() : d_ptr(new TcExcelReaderPrivate(this))
{
}

TcExcelReader::~TcExcelReader()
{
    delete d_ptr;
}

bool TcExcelReader::isNull() const
{
    Q_D(const TcExcelReader);
    return d->isNull;
}

bool TcExcelReader::open(const QString &file)
{
#ifdef Q_OS_WIN
    Q_D(TcExcelReader);
    if (!d->workbooks)
    {
        return false;
    }
    ///////////////////////////////////////////////////
    // 下面这段内容是判断并关闭之前打开的excel的

    if (d->tmpFile.isEmpty() == false)
    {
        if (QFile::exists(d->tmpFile))
        {
            if (!QFile::remove(d->tmpFile))
            {
                return false;
            }
        }
        d->tmpFile.clear();
    }
    if (d->sheet)
    {
        delete d->sheet;
        d->sheet = NULL;
    }
    if (d->sheets)
    {
        delete d->sheets;
        d->sheets = NULL;
    }
    if (d->workbook)
    {
        delete d->workbook;
        d->workbook = NULL;
    }

    d->currentSheetIndex = -1;
    d->sheetNames.clear();

    ///////////////////////////////////////////////////

    d->tmpFile = QString("%1/tmp_%2.%3")
#if (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
        .arg(QStandardPaths::writableLocation(
                    QStandardPaths::TempLocation))
#else
        .arg(QDesktopServices::storageLocation(
                    QDesktopServices::TempLocation))
#endif
        .arg(QDateTime::currentDateTime().toString("yyyyMMddhhmmsszzz"))
        .arg(file.section(".", -1, -1));

    if (QFile::exists(d->tmpFile))
    {
        if (!QFile::remove(d->tmpFile))
        {
            d->tmpFile.clear();
            return false;
        }
    }
    if (!QFile::copy(file, d->tmpFile))
    {
        d->tmpFile.clear();
        return false;
    }

    d->workbook = d->workbooks->querySubObject(
            "Open(QString, QVariant)", d->tmpFile, 0);
    if (!d->workbook)
    {
        QFile::remove(d->tmpFile);
        d->tmpFile.clear();
        return false;
    }
    d->sheets = d->workbook->querySubObject("Sheets");
    if (!d->sheets)
    {
        QFile::remove(d->tmpFile);
        d->tmpFile.clear();
        return false;
    }
    int iCnt = d->sheets->dynamicCall("Count()").toInt();
    for (int i = 1; i <= iCnt; i++)
    {
        d->sheet = d->sheets->querySubObject("Item(int)", i);
        d->sheetNames << d->sheet->dynamicCall("Name").toString();
        delete d->sheet;
        d->sheet = NULL;
    }
    return true;
#else
    return false;
#endif
}

int TcExcelReader::sheetCount()
{
    Q_D(TcExcelReader);
    return d->sheetNames.size();
}

QStringList TcExcelReader::sheetNames()
{
    Q_D(TcExcelReader);
    return d->sheetNames;
}

int TcExcelReader::currentSheetIndex()
{
    Q_D(TcExcelReader);
    return d->currentSheetIndex;
}

QString TcExcelReader::currentSheetName()
{
    Q_D(TcExcelReader);
    if (d->currentSheetIndex > 0 
            && d->currentSheetIndex <= d->sheetNames.size())
    {
        return d->sheetNames[d->currentSheetIndex - 1];
    }
    else
    {
        return QString();
    }
}

bool TcExcelReader::setCurrentSheet(int index)
{
    Q_D(TcExcelReader);
    if (index < 1 || index > d->sheetNames.size())
    {
        return false;
    }
    if (index == d->currentSheetIndex)
    {
        return true;
    }
#ifdef Q_OS_WIN
    if (d->sheet)
    {
        delete d->sheet;
        d->sheet = NULL;
        d->currentSheetIndex = -1;
    }
    d->sheet = d->sheets->querySubObject("Item(int)", index);
    if (!d->sheet)
    {
        return false;
    }
    d->sheet->dynamicCall("Select()");
    d->currentSheetIndex = index;
    return true;
#else
    return false;
#endif
}

bool TcExcelReader::setCurrentSheet(const QString &sheetName)
{
    Q_D(TcExcelReader);
    int index = d->sheetNames.indexOf(sheetName);
    if (index == -1)
    {
        return false;
    }
    return setCurrentSheet(index);
}

QVariant TcExcelReader::cell(int row, int col)
{
    QVariant v;
#ifdef Q_OS_WIN
    Q_D(TcExcelReader);
    if (!d->sheet)
    {
        return v;
    }
    QAxObject *range = d->sheet->querySubObject("Cells(int, int)", row, col);
    if (!range)
    {
        return v;
    }
    v = range->dynamicCall("Value()");
    delete range;
#endif
    return v;
}
