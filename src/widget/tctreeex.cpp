#include <tianchi/widget/tctreeex.h>
#include <tianchi/core/tcstring.h>

class TcTreeExPrivate
{
    Q_DECLARE_PUBLIC(TcTreeEx)
public:
    explicit TcTreeExPrivate(TcTreeEx* qptr);
    ~TcTreeExPrivate();

    TcTreeEx*       q_ptr;

    QTreeWidget*    widget;
    int             exportType;
    int             selectState;

    QString         filename;

    TcMSExcel*      excel;
    bool            hasHeader;
    int             startRow;
    int             startCol;
    int             row;
    int             col;
    QStringList     formats;
    QStringList     cellTypes;
};

TcTreeExPrivate::TcTreeExPrivate(TcTreeEx *qptr)
    : q_ptr(qptr)
    , widget(NULL)
    , exportType(TcTreeEx::TextFile)
    , selectState(0)
    , filename("")
    , excel(NULL)
    , hasHeader(true)
    , startRow(1)
    , startCol(1)
{
}

TcTreeEx::TcTreeEx(QTreeWidget* widget)
    : d_ptr(new TcTreeExPrivate(this))
{
    setWidget(widget);
}

void TcTreeEx::setWidget(QTreeWidget* widget)
{
    Q_D(TcTreeEx);
    d->widget = widget;

    d->formats.clear();
    d->cellTypes.clear();
    if ( widget != NULL )
    {
        QTreeWidgetItem* header = widget->headerItem();
        for( int i=0;i<header->columnCount();i++ )
        {
            d->formats<<"";
            d->cellTypes<<"t";
        }
    }
}

void TcTreeEx::setSelectedState(int state)
{
    Q_D(TcTreeEx);
    d->selectState = state;
}

void TcTreeEx::setTextFileName(const QString& filename)
{
    Q_D(TcTreeEx);
    d->filename = filename;
}

void TcTreeEx::setMSExcelObject(TcMSExcel* excel, bool hasHeader, int startRow, int startCol)
{
    Q_D(TcTreeEx);
    d->excel     = excel;
    d->hasHeader = hasHeader;
    d->startRow  = startRow;
    d->startCol  = startCol;
}

int TcTreeEx::save()
{
    int ret = 0;
    Q_D(TcTreeEx);

    QList<QTreeWidgetItem*> list;
    switch(d->selectState)
    {
    case 0:
        for( int i=0; i<d->widget->topLevelItemCount(); i++ )
        {
            list.append(d->widget->topLevelItem(i));
        }
        break;
    case 1:
        foreach(QTreeWidgetItem* item, d->widget->selectedItems())
        {
            list.append(item);
        }
        break;
    }
    if ( list.count() >0 )
    {
        switch(d->exportType)
        {
        case TextFile:
        {
            TcStringList ss;
            if ( d->hasHeader )
            {
                QTreeWidgetItem* header = d->widget->headerItem();
                QString s;
                for( int i=0;i<header->columnCount();i++ )
                {
                    s += "\t" + header->text(i);
                }
                if ( s.count() >0 )
                {
                    s.remove(1, 1);
                }
                ss.append(s);
            }
            foreach(QTreeWidgetItem* item, list)
            {
                QString s;
                for( int i=0; i<item->columnCount(); i++ )
                {
                    if ( d->cellTypes.at(i) == "t" )
                    {
                        s += "\t" + item->text(i);
                    }else
                    if ( d->cellTypes.at(i) == "d" )
                    {
                        s += "\t" + item->data(i, Qt::UserRole).toString();
                    }
                }
                if ( s.count() >0 )
                {
                    s.remove(1, 1);
                }
                ss.append(s);
                ret ++;
            }
            if ( ! ss.saveTo(d->filename) )
            {
                ret = -1;
            }
        }
            break;

        case MSExcel:
            if ( d->excel != NULL )
            {
                d->row = d->startRow;
                d->col = d->startCol;
                if ( d->hasHeader )
                {
                    QTreeWidgetItem* header = d->widget->headerItem();
                    for( int i=0;i<header->columnCount();i++ )
                    {
                        d->excel->cellAlign(d->row, d->col, TcMSExcel::xlCenter, TcMSExcel::xlCenter);
                        d->excel->write(d->row, d->col++, header->text(i));
                    }
                }
                foreach(QTreeWidgetItem* item, list)
                {
                    d->row ++;
                    d->col = 1;
                    for( int i=0; i<item->columnCount(); i++ )
                    {
                        if ( ! d->formats.at(i).isEmpty() )
                        {
                            d->excel->cellFormat(d->row, d->col+i, d->formats.at(i));
                        }
                        if ( d->cellTypes.at(i) == "t" )
                        {
                            d->excel->write(d->row, d->col+i, item->text(i));
                        }else
                        if ( d->cellTypes.at(i) == "d" )
                        {
                            d->excel->write(d->row, d->col+i, item->data(i, Qt::UserRole));
                        }
                        ret ++;
                    }
                }
            }
            break;
        }
    }
    return ret;
}

