#include "Gui/TreeWidgetHeaderSetupDialog.h"
#include "ui_TreeWidgetHeaderSetupDialog.h"

TIANCHI_BEGIN_NAMESPACE

TreeWidgetHeaderSetupDialog::TreeWidgetHeaderSetupDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TreeWidgetHeaderSetupDialog)
{
    ui->setupUi(this);

    m_view = NULL;
}

TreeWidgetHeaderSetupDialog::~TreeWidgetHeaderSetupDialog()
{
    delete ui;
}

void TreeWidgetHeaderSetupDialog::setHeader(QTreeWidget* view, int max)
{
    m_view = view;

    QTreeWidgetItem* header = view->headerItem();
    for( int i=0;i<header->columnCount();i++ )
    {
        QTreeWidgetItem* item = new QTreeWidgetItem(ui->MasterView);
        item->setText(0, header->text(i));
        item->setTextAlignment(0, header->textAlignment(i));
        item->setCheckState(0, view->isColumnHidden(i) ? Qt::Unchecked : Qt::Checked);
    }
}

void TreeWidgetHeaderSetupDialog::on_MasterView_itemClicked(QTreeWidgetItem *item, int column)
{
    int index = ui->MasterView->indexOfTopLevelItem(item);
    m_view->setColumnHidden(index, item->checkState(0) == Qt::Unchecked);
}

void TreeWidgetHeaderSetupDialog::on_bnUpward_clicked()
{
    foreach(QTreeWidgetItem* item, ui->MasterView->selectedItems())
    {
        int index1 = ui->MasterView->indexOfTopLevelItem(item);
        if ( index1 >0 )
        {
            int index2 = index1-1;
            item = ui->MasterView->takeTopLevelItem(index1);
            ui->MasterView->insertTopLevelItem(index2, item);
            item->setSelected(true);

            m_view->header()->swapSections(index1, index2);
        }
    }
}

void TreeWidgetHeaderSetupDialog::on_bnDownawrd_clicked()
{
    foreach(QTreeWidgetItem* item, ui->MasterView->selectedItems())
    {
        int index1 = ui->MasterView->indexOfTopLevelItem(item);
        if ( index1 < (ui->MasterView->topLevelItemCount()-1) )
        {
            int index2 = index1+1;
            item = ui->MasterView->takeTopLevelItem(index1);
            ui->MasterView->insertTopLevelItem(index2, item);
            item->setSelected(true);

            m_view->header()->swapSections(index1, index2);
        }
    }
}

void TreeWidgetHeaderSetupDialog::on_bnLeft_clicked()
{
    foreach(QTreeWidgetItem* item, ui->MasterView->selectedItems())
    {
        item->setTextAlignment(0, Qt::AlignLeft | Qt::AlignVCenter);

        int index = ui->MasterView->indexOfTopLevelItem(item);

        QTreeWidgetItem* header = m_view->headerItem();
        header->setTextAlignment(index, Qt::AlignLeft | Qt::AlignVCenter);
    }
}

void TreeWidgetHeaderSetupDialog::on_bnCenter_clicked()
{
    foreach(QTreeWidgetItem* item, ui->MasterView->selectedItems())
    {
        item->setTextAlignment(0, Qt::AlignHCenter | Qt::AlignVCenter);

        int index = ui->MasterView->indexOfTopLevelItem(item);

        QTreeWidgetItem* header = m_view->headerItem();
        header->setTextAlignment(index, Qt::AlignHCenter | Qt::AlignVCenter);
    }
}

void TreeWidgetHeaderSetupDialog::on_bnRight_clicked()
{
    foreach(QTreeWidgetItem* item, ui->MasterView->selectedItems())
    {
        item->setTextAlignment(0, Qt::AlignRight | Qt::AlignVCenter);

        int index = ui->MasterView->indexOfTopLevelItem(item);

        QTreeWidgetItem* header = m_view->headerItem();
        header->setTextAlignment(index, Qt::AlignRight | Qt::AlignVCenter);
    }
}

TIANCHI_END_NAMESPACE
