// **************************************************************************
// Tianchi C++ library for Qt (open source)
// ��ع���Դ���
// ��Ȩ���� (C) Qt Project
// ��ȨЭ�飺LGPL
// **************************************************************************
// �ĵ�˵������ʽ����FlowLayout
// ==========================================================================
// ������־��
// ����         ��Ա        ˵��
// --------------------------------------------------------------------------
// 2013.04.21   XChinux     �޸���Qt examples&demos���flowlayoutʾ��
//
// ==========================================================================
/// @file FlowLayout.h ��ʽ����FlowLayout
// ==========================================================================
#ifndef TIANCHI_TCFLOWLAYOUT_H
#define TIANCHI_TCFLOWLAYOUT_H

#include <tianchi/tcglobal.h>
#include <QLayout>

class TcFlowLayoutPrivate;

/// @brief ��ʽ����FlowLayout
class TIANCHI_API TcFlowLayout : public QLayout
{
public:
    TcFlowLayout(QWidget *parent, int margin = -1, int hSpacing = -1,
            int vSpacing = -1);
    TcFlowLayout(int margin = -1, int hSpacing = -1, int vSpacing = -1);
    virtual ~TcFlowLayout();

    void addItem(QLayoutItem *item);
    int horizontalSpacing() const;
    int verticalSpacing() const;
    Qt::Orientations expandingDirections() const;
    bool hasHeightForWidth() const;
    int heightForWidth(int) const;
    int count() const;
    QLayoutItem *itemAt(int index) const;
    QSize minimumSize() const;
    void setGeometry(const QRect &rect);
    QSize sizeHint() const;
    QLayoutItem *takeAt(int index);

private:
    Q_DISABLE_COPY(TcFlowLayout)
    Q_DECLARE_PRIVATE(TcFlowLayout)
    TcFlowLayoutPrivate* const d_ptr;
};

#endif
