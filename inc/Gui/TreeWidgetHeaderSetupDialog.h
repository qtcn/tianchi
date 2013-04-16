// ********************************************************************************************************************
// Tianchi share library for Qt (C++)
// 天池共享源码库
// 版权所有 (C) 天池共享源码库开发组
// 授权协议：请阅读天池共享源码库附带的授权协议
// ********************************************************************************************************************
// 文档说明：修改 QTreeWidget 列设置的对话框
// ====================================================================================================================
// 开发日志：
// 日期         人员        说明
// --------------------------------------------------------------------------------------------------------------------
// 2013.04.10   圣域天子    建立
// ====================================================================================================================
/// @file TreeWidgetHeaderSetupDialog.h 修改 QTreeWidget 列设置的对话框
#ifndef TIANCHI_DLGHEADERSETUP_H
#define TIANCHI_DLGHEADERSETUP_H

#include "Global.h"

#include <QDialog>
#include <QTreeWidget>

TIANCHI_BEGIN_NAMESPACE

namespace Ui {
class TreeWidgetHeaderSetupDialog;
}

/// @brief 设置 QTreeWidget 标题的对话框
class TIANCHI_API TreeWidgetHeaderSetupDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit TreeWidgetHeaderSetupDialog(QWidget *parent = 0);
    ~TreeWidgetHeaderSetupDialog();

    /// @brief 指定 QTreeView 对象
    /// @param [in] view QTreeView 对象
    /// @param [in] max 最大设置的列数，超过部分将被忽略
    void setHeader(QTreeWidget* view, int max=-1);
    
private slots:
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

TIANCHI_END_NAMESPACE

#endif // TIANCHI_DLGHEADERSETUP_H
