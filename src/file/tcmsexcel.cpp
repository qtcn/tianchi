#include <tianchi/file/tcmsexcel.h>
#include <tianchi/core/tccommon.h>
#include <tianchi/core/tcutils.h>

#include <QList>

#if defined(Q_OS_WIN)
#include <ActiveQt/QAxObject>
#endif // Q_OS_WIN

class TcMSExcelPrivate
{
    Q_DECLARE_PUBLIC(TcMSExcel)
public:
    explicit TcMSExcelPrivate(TcMSExcel* qptr);
    ~TcMSExcelPrivate();

    void construct();
    void destory();

    TcMSExcel*  q_ptr;

    QAxObject*  excel;
    QAxObject*  books;
    QAxObject*  book;
    QAxObject*  sheets;
    QAxObject*  sheet;
    QString     filename;
    QString     sheetName;
};

TcMSExcelPrivate::TcMSExcelPrivate(TcMSExcel *qptr)
    : q_ptr(qptr)
#if defined(Q_OS_WIN)
    , excel(NULL)
    , books(NULL)
    , book(NULL)
    , sheets(NULL)
    , sheet(NULL)
#endif // Q_OS_WIN
    , filename("")
    , sheetName("")
{
}

TcMSExcelPrivate::~TcMSExcelPrivate()
{
#if defined(Q_OS_WIN)
    if ( !  excel->isNull() )
    {
        excel->dynamicCall("Quit()");
    }
    TC_FREE(sheet );
    TC_FREE(sheets);
    TC_FREE(book  );
    TC_FREE(books );
    TC_FREE(excel );
#endif // Q_OS_WIN
}

void TcMSExcelPrivate::construct()
{
#if defined(Q_OS_WIN)
    destory();
    excel->setControl("Excel.Application");
    if ( excel->isNull() )
    {
        excel->setControl("ET.Application");
    }
    if ( ! excel->isNull() )
    {
        books = excel->querySubObject("Workbooks");
    }
#endif // Q_OS_WIN
}

void TcMSExcelPrivate::destory()
{
#if defined(Q_OS_WIN)
    TC_FREE(sheet );
    TC_FREE(sheets);
    if ( book != NULL && ! book->isNull() )
    {
        book->dynamicCall("Close(Boolean)", false);
    }
    TC_FREE(book );
    TC_FREE(books);
    if ( excel != NULL && ! excel->isNull() )
    {
        excel->dynamicCall("Quit()");
    }
    TC_FREE(excel);
    filename  = "";
    sheetName = "";
#endif // Q_OS_WIN
}


TcMSExcel::TcMSExcel()
    : d_ptr(new TcMSExcelPrivate(this))
{
}

TcMSExcel::~TcMSExcel()
{
    close();
}

bool TcMSExcel::create(const QString& filename)
{
	bool ret = false;
#if defined(Q_OS_WIN)
    Q_D(TcMSExcel);
    d->construct();
    if ( d->books != NULL && ! d->books->isNull() )
    {
        d->books->dynamicCall("Add");
        d->book   = d->excel->querySubObject("ActiveWorkBook");
        d->sheets = d->book ->querySubObject("WorkSheets"    );
        currentSheet();
        d->filename = filename;
        ret = true;
    }
#endif // Q_OS_WIN
    return ret;
}

bool TcMSExcel::open(const QString& filename)
{
    bool ret = false;
#if defined(Q_OS_WIN)

    Q_D(TcMSExcel);
    d->construct();
    if ( d->books != NULL && ! d->books->isNull() )
    {
        d->book = d->books->querySubObject("Open(QString, QVariant)", filename, 0);
        ret = d->book != NULL && ! d->book->isNull();
        if ( ret )
        {
            d->sheets = d->book->querySubObject("WorkSheets");
            d->filename = filename;
            currentSheet();
        }
    }
#endif // Q_OS_WIN
    return ret;
}

void TcMSExcel::save(const QString& filename)
{
#if defined(Q_OS_WIN)
    Q_D(TcMSExcel);
    if ( d->books != NULL && ! d->books->isNull() )
    {
        d->filename = filename;
        d->books->dynamicCall("SaveAs(const QString&)", d->filename);
    }
#endif // Q_OS_WIN
}

void TcMSExcel::close()
{
#if defined(Q_OS_WIN)
    Q_D(TcMSExcel);
    d->destory();
#endif // Q_OS_WIN
}

void TcMSExcel::kick()
{
#if defined(Q_OS_WIN)
    Q_D(TcMSExcel);

    if ( d->excel != NULL && ! d->excel->isNull() )
    {
        d->excel->setProperty("Visible", true);
    }
    TC_FREE(d->sheet );
    TC_FREE(d->sheets);
    TC_FREE(d->book  );
    TC_FREE(d->books );
    TC_FREE(d->excel );
    d->destory();
#endif // Q_OS_WIN
}

QStringList TcMSExcel::sheetNames()
{
    QStringList ret;
#if defined(Q_OS_WIN)
    Q_D(TcMSExcel);
    if ( d->sheets != NULL && ! d->sheets->isNull() )
    {
        int sheetCount = d->sheets->property("Count").toInt();
        for( int i=1; i<=sheetCount; i++ )
        {
            QAxObject* sheet = d->sheets->querySubObject("Item(int)", i);
            ret.append(sheet->property("Name").toString());
        }
    }
#endif // Q_OS_WIN
    return ret;
}

QString TcMSExcel::currentSheetName()
{
    Q_D(TcMSExcel);
    return d->sheetName;
}

void TcMSExcel::setVisible(bool value)
{
#if defined(Q_OS_WIN)
    Q_D(TcMSExcel);
    if ( d->excel != NULL && ! d->excel->isNull() )
    {
        d->excel->setProperty("Visible", value);
    }
#endif // Q_OS_WIN
}

void TcMSExcel::setCaption(const QString& value)
{
#if defined(Q_OS_WIN)
    Q_D(TcMSExcel);
    if ( d->excel != NULL && ! d->excel->isNull() )
    {
        d->excel->setProperty("Caption", value);
    }
#endif // Q_OS_WIN
}

bool TcMSExcel::addBook()
{
    bool ret = false;
#if defined(Q_OS_WIN)
    Q_D(TcMSExcel);
    if ( d->excel != NULL && ! d->excel->isNull() )
    {
        TC_FREE(d->sheet );
        TC_FREE(d->sheets);
        TC_FREE(d->book  );
        TC_FREE(d->books );
        d->books = d->excel->querySubObject("WorkBooks");
        ret = d->books != NULL && ! d->books->isNull();
    }
#endif // Q_OS_WIN
    return ret;
}

bool TcMSExcel::currentSheet()
{
    bool ret = false;
#if defined(Q_OS_WIN)
    Q_D(TcMSExcel);
    TC_FREE(d->sheet);
    if ( d->excel != NULL && ! d->excel->isNull() )
    {
        TC_FREE(d->sheet);
        d->sheet = d->excel->querySubObject("ActiveWorkBook");
        ret = d->sheet != NULL && ! d->sheet->isNull();
        d->sheetName = ret ? d->sheet->property("Name").toString() : "";
    }
#endif // Q_OS_WIN
    return ret;
}

bool TcMSExcel::setCurrentSheet(int index)
{
    bool ret = false;
#if defined(Q_OS_WIN)
    Q_D(TcMSExcel);
    if ( d->sheets != NULL && ! d->sheets->isNull() )
    {
        TC_FREE(d->sheet);
        d->sheet = d->sheets->querySubObject("Item(int)", index);
        ret = d->sheet != NULL && ! d->sheet->isNull();
        d->sheetName = ret ? d->sheet->property("Name").toString() : "";
    }
#endif // Q_OS_WIN
    return ret;
}

int TcMSExcel::sheetCount()
{
    int ret = 0;
#if defined(Q_OS_WIN)
    Q_D(TcMSExcel);
    if ( d->sheets != NULL && ! d->sheets->isNull() )
    {
        ret = d->sheets->property("Count").toInt();
    }
#endif // Q_OS_WIN
    return ret;
}

void TcMSExcel::cellFormat(int row, int col, const QString& format)
{
#if defined(Q_OS_WIN)
    Q_D(TcMSExcel);
    if ( d->sheet != NULL && ! d->sheet->isNull() )
    {
        QAxObject* range = d->sheet->querySubObject("Cells(int, int)", row, col);
        range->setProperty("NumberFormatLocal", format);
        delete range;
    }
#endif // Q_OS_WIN
}

void TcMSExcel::cellAlign(int row, int col, Alignment hAlign, Alignment vAlign)
{
#if defined(Q_OS_WIN)
    Q_D(TcMSExcel);
    if ( d->sheet != NULL && ! d->sheet->isNull() )
    {
        QAxObject* range = d->sheet->querySubObject("Cells(int, int)", row, col);
        range->setProperty("HorizontalAlignment", hAlign);
        range->setProperty("VerticalAlignment",   vAlign);
        delete range;
    }
#endif // Q_OS_WIN
}

QVariant TcMSExcel::read(int row, int col)
{
    QVariant ret;
#if defined(Q_OS_WIN)
    Q_D(TcMSExcel);
    if ( d->sheet != NULL && ! d->sheet->isNull() )
    {
        QAxObject* range = d->sheet->querySubObject("Cells(int, int)", row, col);
        //ret = range->property("Value");
        ret = range->dynamicCall("Value()");
        delete range;
    }
#endif // Q_OS_WIN
    return ret;
}

void TcMSExcel::write(int row, int col, const QVariant& value)
{
#if defined(Q_OS_WIN)
    Q_D(TcMSExcel);
    if ( d->sheet != NULL && ! d->sheet->isNull() )
    {
        QAxObject* range = d->sheet->querySubObject("Cells(int, int)", row, col);
        range->setProperty("Value", value);
        delete range;
    }
#endif // Q_OS_WIN
}

bool TcMSExcel::usedRange(int& rowStart, int& colStart, int& rowEnd, int& colEnd)
{
    bool ret = false;
#if defined(Q_OS_WIN)
    Q_D(TcMSExcel);
    if ( d->sheet != NULL && ! d->sheet->isNull() )
    {
        QAxObject* urange  = d->sheet->querySubObject("UsedRange");
        rowStart = urange->property("Row"   ).toInt();
        colStart = urange->property("Column").toInt();
        rowEnd   = urange->querySubObject("Rows"   )->property("Count").toInt();
        colEnd   = urange->querySubObject("Columns")->property("Count").toInt();
        delete urange;
        ret = true;
    }
#endif // Q_OS_WIN
    return ret;
}
