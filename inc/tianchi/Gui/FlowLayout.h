// **************************************************************************
// Tianchi C++ library for Qt (open source)
// ��ع���Դ���
// ��Ȩ���� (C) ��ع���Դ��⿪����
// ��ȨЭ�飺���Ķ���ع���Դ��⸽������ȨЭ��
// **************************************************************************
// �ĵ�˵������ʽ����FlowLayout
// ==========================================================================
// ������־��
// ����         ��Ա        ˵��
// --------------------------------------------------------------------------
// 2013.04.21   XChinux     ����
//
// ==========================================================================
/// @file FlowLayout.h ��ʽ����FlowLayout
// ==========================================================================
#ifndef TIANCHI_FLOWLAYOUT_H
#define TIANCHI_FLOWLAYOUT_H

#include <tianchi/Global.h>
#include <QLayout>

TIANCHI_BEGIN_NAMESPACE

class FlowLayoutPrivate;

QT_USE_NAMESPACE

/// @brief ��ʽ����FlowLayout
class TIANCHI_API FlowLayout : public QLayout
{
public:
    FlowLayout(QWidget *parent, int margin = -1, int hSpacing = -1,
            int vSpacing = -1);
    FlowLayout(int margin = -1, int hSpacing = -1, int vSpacing = -1);
    virtual ~FlowLayout();

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
    Q_DISABLE_COPY(FlowLayout)
    Q_DECLARE_PRIVATE(FlowLayout)
    FlowLayoutPrivate *d_ptr;
};

TIANCHI_END_NAMESPACE

#if 0
class TIANCHI_API TcFlowLayout : public TIANCHI_PREPEND_NAMESPACE(FlowLayout)
{
public:
    TcFlowLayout(QT_PREPEND_NAMESPACE(QWidget) *parent, 
            int margin = -1, int hSpacing = -1, int vSpacing = -1)
        : TIANCHI_PREPEND_NAMESPACE(FlowLayout)(parent, margin, 
                hSpacing, vSpacing)
    {
    }

    TcFlowLayout(int margin = -1, int hSpacing = -1, int vSpacing = -1)
        : TIANCHI_PREPEND_NAMESPACE(FlowLayout)(margin, hSpacing, vSpacing)
    {
    }
};
#endif
typedef TIANCHI_PREPEND_NAMESPACE(FlowLayout) TcFlowLayout;

#endif
