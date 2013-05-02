#include <tianchi/File/ExcelReader.h>
#ifdef Q_OS_WIN
#include <QAxObject>
#endif

namespace Tianchi
{
class ExcelReaderPrivate
{
    Q_DECLARE_PUBLIC(ExcelReader)
public:
    explicit ExcelReaderPrivate(ExcelReader *qptr);
    ~ExcelReaderPrivate();
    ExcelReader *q_ptr;
#ifdef Q_OS_WIN
    QAxObject *excel;
    QAxObject *workbooks;
    QAxObject *workbook;
    QAxObject *sheets;
    QAxObject *sheet;
#endif
    bool isNull;
};

ExcelReaderPrivate::ExcelReaderPrivate(ExcelReader *qptr) : q_ptr(qptr), 
#ifdef Q_OS_WIN
    excel(new QAxObject), 
    workbooks(NULL), workbook(NULL), sheets(NULL), sheet(NULL),
#endif
    isNull(true)
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

ExcelReaderPrivate::~ExcelReaderPrivate()
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
}

ExcelReader::ExcelReader() : d_ptr(new ExcelReaderPrivate(this))
{
}

ExcelReader::~ExcelReader()
{
    delete d_ptr;
}

bool ExcelReader::isNull() const
{
    Q_D(const ExcelReader);
    return d->isNull;
}

bool ExcelReader::open(const QString &file)
{
#ifdef Q_OS_WIN
    Q_D(ExcelReader);
    if (!d->workbooks)
    {
        return false;
    }
    d->workbook = d->workbooks->querySubObject(
            "Open(QString, QVariant)", file, 0);
    if (!d->workbook)
    {
        return false;
    }
    d->sheets = d->workbook->querySubObject("Sheets");
    if (!d->sheets)
    {
        return false;
    }
    if (d->sheets->dynamicCall("Count()").toInt() < 1)
    {
        return false;
    }
    d->sheet = d->sheets->querySubObject("Item(int)", 1);
    if (!d->sheet)
    {
        return false;
    }
    d->sheet->dynamicCall("Select()");
    return true;
#else
    return false;
#endif
}

QVariant ExcelReader::cell(int row, int col)
{
    QVariant v;
#ifdef Q_OS_WIN
    Q_D(ExcelReader);
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
}
