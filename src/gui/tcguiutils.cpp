#include <tianchi/gui/tcguiutils.h>
#include <tianchi/core/tccommon.h>

#include <QMenu>
#include <QHeaderView>
#include <QClipboard>

namespace Tc
{

QToolButton* createButton(QToolBar* toolBar,
                          QIcon icon, QString text, int width,
                          Qt::ToolButtonStyle style)
{
    QToolButton* toolButton;
    toolButton = new QToolButton(toolBar);
    toolButton->setToolButtonStyle(style);
    toolButton->setIcon(icon);
    toolButton->setText(text);
    toolButton->setMinimumWidth(width);
    toolButton->setMaximumWidth(width);

    toolBar->addWidget(toolButton);

    return toolButton;
}

void createColumnMenu(QTreeWidget* view, QWidget* widget, 
        const QString& ColumnSetupFunc)
{
    QMenu popupMenu(view->header());

    QAction* action;
    action = popupMenu.addAction(QIcon(":/res/setupdialog.png"), QS("设置..."));
    action->setData(-1);
    QObject::connect(action, SIGNAL(triggered(bool)), widget, QString("1"+ColumnSetupFunc).toLocal8Bit());
    action = popupMenu.addAction(QS("恢复系统默认"));
    action->setData(-2);
    QObject::connect(action, SIGNAL(triggered(bool)), widget, QString("1"+ColumnSetupFunc).toLocal8Bit());
    action = popupMenu.addAction(QS("恢复用户默认"));
    action->setData(-3);
    //connect(action, SIGNAL(triggered(bool)), this, SLOT(slot_TradeView_header_ColumnSetup()));
    QObject::connect(action, SIGNAL(triggered(bool)), widget, QString("1"+ColumnSetupFunc).toLocal8Bit());
    popupMenu.addSeparator();

    QTreeWidgetItem* header = view->headerItem();
    for( int i=0;i<header->columnCount();i++ )
    {
        if ( ! header->text(i).isEmpty() )
        {
            action = popupMenu.addAction(header->text(i));
            action->setCheckable(true);
            action->setData(i);

            action->setChecked(! view->isColumnHidden(i));
            QObject::connect(action, SIGNAL(triggered(bool)), widget, QString("1"+ColumnSetupFunc).toLocal8Bit());
        }else
        {
            break;
        }
    }
    popupMenu.exec(QCursor::pos()); // 在当前鼠标位置显示
}

void setColumnStyle(QTreeWidget* view, int fontSize, const QString& fontName)
{
    for( int i=0;i<view->headerItem()->columnCount();i++ )
    {
        QFont font = view->headerItem()->font(i);
        font.setFamily(fontName);
        font.setPointSize(fontSize);
        font.setBold(true);
        view->headerItem()->setFont(i, font);
        view->headerItem()->setSizeHint(i, QSize(1, 25));
    }
}

void changeFont(QWidget* widget, const QString& fontName, int fontSize, bool bold)
{
    QFont font = widget->font();
    font.setFamily(fontName);
    font.setPointSize(fontSize);
    font.setBold(bold);
    widget->setFont(font);
}

void setFontTahoma(QWidget* widget, int fontSize, bool bold)
{
    QFont font = widget->font();
    font.setFamily("Tahoma");
    font.setPointSize(fontSize);
    font.setBold(bold);
    widget->setFont(font);
}

void cellStyle(QTreeWidgetItem* item,
               int startCol, int endCol, bool bold, int alignment,
               int cellHeight)
{
    if ( startCol < 0 )
    {
        startCol = 0;
    }
    if ( endCol < 0 )
    {
        endCol = item->columnCount() -1;
    }
    if ( item->columnCount() <= endCol )
    {
        item->setText(endCol, "");
    }
    for( int i=startCol;i<=endCol;i++ )
    {
        item->setTextAlignment(i, alignment);
        QFont font = item->font(i);
        font.setBold(bold);
        item->setFont(i, font);
        item->setSizeHint(i, QSize(1, cellHeight));
    }
}

void cellFont(QTreeWidgetItem* item, int col, bool bold, int alignment)
{
    QFont font = item->font(col);
    font.setBold(bold);
    item->setFont(0, font);
    item->setTextAlignment(col, alignment);
}

void cellColor(QTreeWidgetItem* item, int col, QColor color)
{
    item->setForeground(col, color);
}

void cellValue(QTreeWidgetItem* item, int column, const char* text, const QVariant& value, int size)
{
    cellValue(item, column, QS(text), value, size);
}

void cellValue(QTreeWidgetItem* item, int column, const QString& text, const QVariant& value, int size)
{
    item->setText(column, text);
    item->setData(column, Qt::UserRole, value);
    if ( size >0 && item->columnCount() <size )
    {
        item->setText(size -1, "");
    }
}

void cellValue(QTreeWidgetItem* item, int column, const QByteArray& text, const QVariant& value, int size)
{
    item->setText(column, text);
    item->setData(column, Qt::UserRole, value);
    if ( size >0 && item->columnCount() <size )
    {
        item->setText(size -1, "");
    }
}

void cellValue(QTreeWidgetItem* item, int column, double value)
{
    item->setData(column, Qt::UserRole, value);
    item->setText(column, QString::number(value));
}

void cellValue(QTreeWidgetItem* item, int column, double value, int digits)
{
    item->setData(column, Qt::UserRole, value);
    item->setText(column, value != 0.0 ? QString("%L1").arg(value, 0, 'f', digits) : "");
}

void cellPrice(QTreeWidgetItem* item, int column, double value, int digits)
{
    cellValue(item, column, value, digits);
    item->setTextColor(column, value < 0.0 ? Qt::red : Qt::blue);
}

void cellPercent(QTreeWidgetItem* item, int column, double value, int digits)
{
    item->setData(column, Qt::UserRole, value);
    item->setText(column, QString("%L1%").arg(value, 0, 'f', digits));
    item->setTextColor(column, value < 0.0 ? Qt::red : Qt::blue);
}

QLabel* createLabel(QTreeWidgetItem* item, int col, const QString& htmlText, const QVariant& data)
{
    QLabel* label = new QLabel(item->treeWidget());
    setFontTahoma(label, 9);
    label->setText(htmlText);
    item->treeWidget()->setItemWidget(item, col, label);
    item->setData(col, Qt::UserRole, data);
    return label;
}

QDoubleSpinBox* createDoubleSpinBox(QTreeWidgetItem* item, int col,
                                    int decimals, double min, double max, double step, double value)
{
    QDoubleSpinBox* editor = new QDoubleSpinBox(item->treeWidget());
    changeFont(editor, "Arial Narrow", 8);
    editor->setDecimals(decimals);
    editor->setMinimum(min);
    editor->setMaximum(max);
    editor->setSingleStep(step);
    editor->setValue(value);
    editor->setAlignment(Qt::AlignVCenter | Qt::AlignRight);
    item->treeWidget()->setItemWidget(item, col, editor);
    return editor;
}

double readDoubleSpinBoxValue(QTreeWidgetItem* item, int col)
{
    double ret = 0.0;
    QDoubleSpinBox* editor = qobject_cast<QDoubleSpinBox*>(item->treeWidget()->itemWidget(item, col));
    if ( editor != NULL )
    {
        ret = editor->value();
    }
    return ret;
}

void CopyCell(QTreeWidget* view)
{
    QStringList ss;
    foreach(QTreeWidgetItem* item, view->selectedItems())
    {
        ss.append(item->text(view->currentColumn()));
    }
#if (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
    QClipboard* clipboard = QGuiApplication::clipboard();
#else
    QClipboard* clipboard = QApplication::clipboard();
#endif
    clipboard->setText(ss.join("\r\n"));
}

void CopyLine(QTreeWidget* view)
{
    QString     s;
    QStringList ss;
    foreach(QTreeWidgetItem* item, view->selectedItems())
    {
        s.clear();
        for( int i=0;i<item->columnCount();i++ )
        {
            s += item->text(i) + "\t";
        }
        ss.append(s.trimmed());
    }

#if (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
    QClipboard* clipboard = QGuiApplication::clipboard();
#else
    QClipboard* clipboard = QApplication::clipboard();
#endif
    clipboard->setText(ss.join("\r\n"));
}

void CopyTable(QTreeWidget* view)
{
    QString     s;
    QStringList ss;
    for( int i=0;i<view->headerItem()->columnCount();i++ )
    {
        s += view->headerItem()->text(i) + "\t";
    }
    ss.append(s.trimmed());
    foreach(QTreeWidgetItem* item, view->selectedItems())
    {
        s.clear();
        for( int i=0;i<item->columnCount();i++ )
        {
            s += item->text(i) + "\t";
        }
        ss.append(s.trimmed());
    }

#if (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
    QClipboard* clipboard = QGuiApplication::clipboard();
#else
    QClipboard* clipboard = QApplication::clipboard();
#endif
    clipboard->setText(ss.join("\r\n"));
}


} // namespace Tc
