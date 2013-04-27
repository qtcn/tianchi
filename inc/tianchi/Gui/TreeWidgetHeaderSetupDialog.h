// **************************************************************************
// Tianchi C++ library for Qt (open source)
// ��ع���Դ���
// ��Ȩ���� (C) ��ع���Դ��⿪����
// ��ȨЭ�飺���Ķ���ع���Դ��⸽������ȨЭ��
// **************************************************************************
// �ĵ�˵�����޸� QTreeWidget �����õĶԻ���
// ==========================================================================
// ������־��
// ����         ��Ա        ˵��
// --------------------------------------------------------------------------
// 2013.04.10   ʥ������    ����
// ==========================================================================
/// @file TreeWidgetHeaderSetupDialog.h �޸� QTreeWidget �����õĶԻ���
#ifndef TIANCHI_DLGHEADERSETUP_H
#define TIANCHI_DLGHEADERSETUP_H

#include <tianchi/Global.h>

#include <QDialog>
#include <QTreeWidget>

namespace Tianchi
{
namespace Ui {class TreeWidgetHeaderSetupDialog;}

/// @brief ���� QTreeWidget ����ĶԻ���
/// @author ʥ������ Jonix@qtcn.org
/// @date 2013-04-10
class TIANCHI_API TreeWidgetHeaderSetupDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TreeWidgetHeaderSetupDialog(QWidget *parent = 0);
    ~TreeWidgetHeaderSetupDialog();

    /// @brief ָ�� QTreeView ����
    /// @param [in] view QTreeView ����
    /// @param [in] max ������õ��������������ֽ�������
    void setHeader(QTreeWidget* view, int max=-1);

private Q_SLOTS:
    void on_bnUpward_clicked();
    void on_bnDownawrd_clicked();

    void on_MasterView_itemClicked(QTreeWidgetItem *item, int column);
    void on_bnLeft_clicked();
    void on_bnCenter_clicked();
    void on_bnRight_clicked();

private:
    Ui::TreeWidgetHeaderSetupDialog *ui;

    QTreeWidget* m_view;
};
}

typedef ::Tianchi::TreeWidgetHeaderSetupDialog TcTreeWidgetHeaderSetupDialog;

#endif // TIANCHI_DLGHEADERSETUP_H
