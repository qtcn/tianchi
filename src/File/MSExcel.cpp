#include "File/MSExcel.h"
#include "Core/Utils.h"

#ifdef Q_OS_WIN
#include <QAxObject>
#include <QAxWidget>
#endif

#ifdef QT_WIDGETS_LIB
#include <QTreeWidget>
#endif

#include <QList>

TIANCHI_BEGIN_NAMESPACE

MSExcel::MSExcel()
    : m_excel(NULL)
    , m_books(NULL)
    , m_book(NULL)
    , m_sheets(NULL)
    , m_sheet(NULL)
    , m_sheetName("")
{
}

MSExcel::~MSExcel()
{
    close();
}

bool MSExcel::create(const QString& filename)
{
	bool ret = false;
#if defined(Q_OS_WIN)
    close();
    m_excel = new QAxWidget("Excel.Application");
    m_books = m_excel->querySubObject("WorkBooks");
    m_books->dynamicCall("Add");
    m_book   = m_excel->querySubObject("ActiveWorkBook");
    m_sheets = m_book ->querySubObject("WorkSheets");
    sheet(1);

    m_filename = filename;

    ret = true;
#endif // Q_OS_WIN	
    return ret;
}

bool MSExcel::open(const QString& filename)
{
	bool ret = false;
#if defined(Q_OS_WIN)
    close();
    m_excel  = new QAxWidget("Excel.Application");
    m_books  = m_excel->querySubObject("WorkBooks");
    m_book   = m_books->querySubObject("Open(const QString&)", filename);
    m_sheets = m_book ->querySubObject("WorkSheets");

    ret = m_book != NULL;
    if ( ret )
    {
        m_filename = filename;
    }
#endif // Q_OS_WIN
    return ret;
}

void MSExcel::save(const QString& filename)
{
#if defined(Q_OS_WIN)
    if ( ! filename.isEmpty() )
    {
        m_filename = filename;
    }
    m_books->dynamicCall("SaveAs(const QString&)", m_filename);
#endif // Q_OS_WIN	
}

void MSExcel::close()
{
#if defined(Q_OS_WIN)
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
#endif // Q_OS_WIN	
}

void MSExcel::kick()
{
#if defined(Q_OS_WIN)
    if ( m_excel != NULL )
    {
        m_excel->setProperty("Visible", true);
    }
    m_book  = NULL;
    m_excel = NULL;
    close();
#endif // Q_OS_WIN	
}

QStringList MSExcel::sheetNames()
{
    QStringList ret;
#if defined(Q_OS_WIN)
    if ( m_sheets != NULL )
    {
        int sheetCount = m_sheets->property("Count").toInt();
        for( int i=1;i<=sheetCount;i++ )
        {
            QAxObject* sheet = m_sheets->querySubObject("Item(int)", i);
            ret.append(sheet->property("Name").toString());
        }
    }
#endif // Q_OS_WIN		
    return ret;
}

void MSExcel::setVisible(bool value)
{
#if defined(Q_OS_WIN)
    m_excel->setProperty("Visible", value);
#endif // Q_OS_WIN		
}

void MSExcel::setCaption(const QString& value)
{
#if defined(Q_OS_WIN)
    m_excel->setProperty("Caption", value);
#endif // Q_OS_WIN		
}

QAxObject* MSExcel::addBook()
{
#if defined(Q_OS_WIN)
    return m_excel->querySubObject("WorkBooks");
#else
    return NULL;
#endif // Q_OS_WIN		
}

QAxObject* MSExcel::currentSheet()
{
#if defined(Q_OS_WIN)
    return m_excel->querySubObject("ActiveWorkBook");
#else
    return NULL;
#endif // Q_OS_WIN		
}

int MSExcel::sheetCount()
{
    int ret = 0;
#if defined(Q_OS_WIN)
    if ( m_sheets != NULL )
    {
        ret = m_sheets->property("Count").toInt();
    }
#endif // Q_OS_WIN		
    return ret;
}

QAxObject* MSExcel::sheet(int index)
{
    m_sheet = NULL;
#if defined(Q_OS_WIN)
    if ( m_sheets != NULL )
    {
        m_sheet = m_sheets->querySubObject("Item(int)", index);
        m_sheetName = m_sheet->property("Name").toString();
    }
#endif // Q_OS_WIN		
    return m_sheet;
}

void MSExcel::cellFormat(int row, int col, const QString& format)
{
#if defined(Q_OS_WIN)
    if ( m_sheet != NULL )
    {
        QAxObject* range = m_sheet->querySubObject("Cells(int, int)", row, col);
        range->setProperty("NumberFormatLocal", format);
    }
#endif // Q_OS_WIN		
}

void MSExcel::cellAlign(int row, int col, Alignment hAlign, Alignment vAlign)
{
#if defined(Q_OS_WIN)
    if ( m_sheet != NULL )
    {
        QAxObject* range = m_sheet->querySubObject("Cells(int, int)", row, col);
        range->setProperty("HorizontalAlignment", hAlign);
        range->setProperty("VerticalAlignment",   vAlign);
    }
#endif // Q_OS_WIN		
}

QVariant MSExcel::read(int row, int col)
{
    QVariant ret;
#if defined(Q_OS_WIN)
    if ( m_sheet != NULL )
    {
        QAxObject* range = m_sheet->querySubObject("Cells(int, int)", row, col);
        ret = range->property("Value");
    }
#endif // Q_OS_WIN		
    return ret;
}

void MSExcel::write(int row, int col, const QVariant& value)
{
#if defined(Q_OS_WIN)
    QVariant ret;
    if ( m_sheet != NULL )
    {
        QAxObject* range = m_sheet->querySubObject("Cells(int, int)", row, col);
        range->setProperty("Value", value);
    }
#endif // Q_OS_WIN		
}

bool MSExcel::usedRange()
{
    bool ret = false;
#if defined(Q_OS_WIN)
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
#endif // Q_OS_WIN		
    return ret;
}


#ifdef QT_WIDGETS_LIB
MSExcel::Exporter::Exporter(QTreeWidget* view, int mode, TIANCHI::MSExcel* excel, int row, int col)
{
#if defined(Q_OS_WIN)
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
#endif // Q_OS_WIN		
}

int MSExcel::Exporter::exec()
{
    int ret = 0;
#if defined(Q_OS_WIN)
    QTreeWidgetItem* header = m_view->headerItem();
    for( int i=0;i<header->columnCount();i++ )
    {
        m_excel->cellAlign(m_row, m_col, TIANCHI::MSExcel::xlCenter, TIANCHI::MSExcel::xlCenter);
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
#endif // Q_OS_WIN		
    return ret;
}
#endif // QT_WIDGETS_LIB

TIANCHI_END_NAMESPACE
