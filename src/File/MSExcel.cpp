#include "File/MSExcel.h"
#include "Core/Utils.h"

#include <QList>

TIANCHI_BEGIN_NAMESPACE

#if defined(Q_OS_WIN)

MSExcel::MSExcel()
    : m_excel(NULL)
    , m_books(NULL)
    , m_book(NULL)
    , m_sheets(NULL)
    , m_sheet(NULL)
    , m_sheetName("")
{
//    excel = new QAxWidget("Excel.Application");

//    QAxObject* workbooks = excel->querySubObject("WorkBooks");
//    workbooks->dynamicCall("Add");
//    //workbooks->dynamicCall("New(const QString&)", QString("F:/QtProject/odbcTest/book.xls"));
//    QAxObject* workbook = excel.querySubObject("ActiveWorkBook");
//    //QAxObject * worksheets = workbook->querySubObject("WorkSheets");
//    QAxObject* worksheet = workbook->querySubObject("Worksheets(int)", 1);
//    while(query.next())
//    {
//        for( int i=1;i<=intCols;i++ )
//        {
//            QAxObject* range = worksheet->querySubObject("Cells(int,int)", i, j);
//            range->setProperty("Value", query.value(j-1));
//            qDebug() << i << j << range->property("Value");
//        }
//        i++;
//    }
}

MSExcel::~MSExcel()
{
    close();
}

bool MSExcel::create(const QString& filename)
{
    close();
    m_excel = new QAxWidget("Excel.Application");
    m_books = m_excel->querySubObject("WorkBooks");
    m_books->dynamicCall("Add");
    m_book   = m_excel->querySubObject("ActiveWorkBook");
    m_sheets = m_book ->querySubObject("WorkSheets");
    sheet(1);

    m_filename = filename;

    return true;
}

bool MSExcel::open(const QString& filename)
{
    close();
    m_excel  = new QAxWidget("Excel.Application");
    m_books  = m_excel->querySubObject("WorkBooks");
    m_book   = m_books->querySubObject("Open(const QString&)", filename);
    m_sheets = m_book ->querySubObject("WorkSheets");

    bool ret = m_book != NULL;
    if ( ret )
    {
        m_filename = filename;
    }
    return ret;
}

void MSExcel::save(const QString& filename)
{
    if ( ! filename.isEmpty() )
    {
        m_filename = filename;
    }
    m_books->dynamicCall("SaveAs(const QString&)", m_filename);
}

void MSExcel::close()
{
    m_sheet  = NULL;
    m_sheets = NULL;
    if ( m_book != NULL )
    {
        m_book->dynamicCall("Close(Boolean)", false);
        m_book = NULL;
    }
    m_books = NULL;
    if ( m_excel != NULL )
    {
        m_excel->dynamicCall("Quit(void)");
        m_excel = NULL;
    }
}

void MSExcel::kick()
{
    if ( m_excel != NULL )
    {
        m_excel->setProperty("Visible", true);
    }
    m_book  = NULL;
    m_excel = NULL;
    close();
}

QStringList MSExcel::sheetNames()
{
    QStringList ret;
    if ( m_sheets != NULL )
    {
        int sheetCount = m_sheets->property("Count").toInt();
        for( int i=1;i<=sheetCount;i++ )
        {
            QAxObject* sheet = m_sheets->querySubObject("Item(int)", i);
            ret.append(sheet->property("Name").toString());
        }
    }
    return ret;
}

void MSExcel::setVisible(bool value)
{
    m_excel->setProperty("Visible", value);
}

void MSExcel::setCaption(const QString& value)
{
    m_excel->setProperty("Caption", value);
}

QAxObject* MSExcel::addBook()
{
    return m_excel->querySubObject("WorkBooks");
}

QAxObject* MSExcel::currentSheet()
{
    return m_excel->querySubObject("ActiveWorkBook");
}

int MSExcel::sheetCount()
{
    int ret = 0;
    if ( m_sheets != NULL )
    {
        ret = m_sheets->property("Count").toInt();
    }
    return ret;
}

QAxObject* MSExcel::sheet(int index)
{
    m_sheet = NULL;
    if ( m_sheets != NULL )
    {
        m_sheet = m_sheets->querySubObject("Item(int)", index);
        m_sheetName = m_sheet->property("Name").toString();
    }
    return m_sheet;
}

void MSExcel::cellFormat(int row, int col, const QString& format)
{
    if ( m_sheet != NULL )
    {
        QAxObject* range = m_sheet->querySubObject("Cells(int, int)", row, col);
        range->setProperty("NumberFormatLocal", format);

//        m_books->dynamicCall("SaveAs(const QString&)", m_filename);


//        String RC1 = m_CurrSheet.OlePropertyGet("Cells", R1, C1).OlePropertyGet("Address", 0, 0);
//        String RC2 = m_CurrSheet.OlePropertyGet("Cells", R2, C2).OlePropertyGet("Address", 0, 0);
//        try {
//            Variant Range = m_CurrSheet.OlePropertyGet("Range", StringToOleStr(RC1+":"+RC2));
//            Range.OlePropertySet("NumberFormatLocal", StringToOleStr(Format));
//        } catch (...) {
//        }
    }
}

void MSExcel::cellAlign(int row, int col, Alignment hAlign, Alignment vAlign)
{
    if ( m_sheet != NULL )
    {
        QAxObject* range = m_sheet->querySubObject("Cells(int, int)", row, col);
        range->setProperty("HorizontalAlignment", hAlign);
        range->setProperty("VerticalAlignment",   vAlign);
    }
}

QVariant MSExcel::read(int row, int col)
{
    QVariant ret;
    if ( m_sheet != NULL )
    {
        QAxObject* range = m_sheet->querySubObject("Cells(int, int)", row, col);
        ret = range->property("Value");
    }
    return ret;
}

void MSExcel::write(int row, int col, const QVariant& value)
{
    QVariant ret;
    if ( m_sheet != NULL )
    {
        QAxObject* range = m_sheet->querySubObject("Cells(int, int)", row, col);
        range->setProperty("Value", value);
    }
}

bool MSExcel::usedRange()
{
    bool ret = false;
    if ( m_sheet != NULL )
    {
        QAxObject* urange  = m_sheet->querySubObject("UsedRange");
        m_rowStart = urange->property("Row").toInt();
        m_colStart = urange->property("Column").toInt();

        QAxObject* rows    = urange->querySubObject("Rows"   );
        QAxObject* columns = urange->querySubObject("Columns");
        m_rowEnd = rows   ->property("Count").toInt();
        m_colEnd = columns->property("Count").toInt();
        ret = true;
    }
    return ret;
}


#ifdef QT_WIDGETS_LIB
MSExcel::Exporter::Exporter(QTreeWidget* view, int mode, TIANCHI_NAMESPACE::MSExcel* excel, int row, int col)
{
    m_view  = view;
    m_mode  = mode;
    m_excel = excel;
    m_row   = row;
    m_col   = col;

    QTreeWidgetItem* header = m_view->headerItem();
    for( int i=0;i<header->columnCount();i++ )
    {
        formats<<"";
        cellTypes<<"t";
    }
}

int MSExcel::Exporter::exec()
{
    int ret = 0;

    QTreeWidgetItem* header = m_view->headerItem();
    for( int i=0;i<header->columnCount();i++ )
    {
        m_excel->cellAlign(m_row, m_col, TIANCHI_NAMESPACE::MSExcel::xlCenter, TIANCHI_NAMESPACE::MSExcel::xlCenter);
        m_excel->write(m_row, m_col++, header->text(i));
    }
    QList<QTreeWidgetItem*> list;
    switch(m_mode)
    {
    case 0:
        for( int i=0;i<m_view->topLevelItemCount();i++ )
        {
            list.append(m_view->topLevelItem(i));
        }
        break;
    case 1:
        foreach(QTreeWidgetItem* item, m_view->selectedItems())
        {
            list.append(item);
        }
        break;
    }
    foreach(QTreeWidgetItem* item, list)
    {
        m_row ++;
        m_col = 1;
        for( int i=0;i<item->columnCount();i++ )
        {
            if ( ! formats.at(i).isEmpty() )
            {
                m_excel->cellFormat(m_row, m_col+i, formats.at(i));
            }
            if ( cellTypes.at(i) == "t" )
            {
                m_excel->write(m_row, m_col+i, item->text(i));
            }else
            if ( cellTypes.at(i) == "d" )
            {
                m_excel->write(m_row, m_col+i, item->data(i, Qt::UserRole));
            }
            ret ++;
        }
    }
    return ret;
}
#endif // QT_WIDGETS_LIB

#endif // Q_OS_WIN

TIANCHI_END_NAMESPACE
