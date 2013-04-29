// **************************************************************************
// Tianchi C++ library for Qt (open source)
// 天池共享源码库
// 版权所有 (C) 天池共享源码库开发组
// 授权协议：请阅读天池共享源码库附带的授权协议
// **************************************************************************
// 文档说明：可发出clicked信号的Label部件
// ==========================================================================
// 开发日志：
// 日期         人员        说明
// --------------------------------------------------------------------------
// 2013.04.22   XChinux     建立
// 2013.04.29   XChinux     add LineEditPrivate::_q_editingFinished()
//                          add LineEdit::clear()
// ==========================================================================
/// @file LineEdit.cpp extended QLineEdit widget
// ==========================================================================
#include <tianchi/Gui/LineEdit.h>
#include <QPainter>
#include <QContextMenuEvent>
#include <QStyleOptionFrame>

namespace Tianchi
{
class LineEditPrivate
{
    Q_DECLARE_PUBLIC(LineEdit)
public:
    explicit LineEditPrivate(LineEdit *qptr);
    ~LineEditPrivate();

    /**
     * when editingFinsihed emitted, if text property is empty, then 
     * clear labelText and data property
     */
    void _q_editingFinished();
    LineEdit *q_ptr;

    QString labelText;
    QVariant userData;
};

LineEditPrivate::LineEditPrivate(LineEdit *qptr) : q_ptr(qptr)
{
    QObject::connect(q_ptr, SIGNAL(editingFinished()),
            q_ptr, SLOT(_q_openLink()));
}

LineEditPrivate::~LineEditPrivate()
{
}

void LineEditPrivate::_q_editingFinished()
{
    Q_Q(LineEdit);
    if (q->text().isEmpty())
    {
        q->setData(QVariant());
        q->setLabelText(QString());
    }
}

LineEdit::LineEdit(QWidget * parent)
    : QLineEdit(parent), d_ptr(new LineEditPrivate(this))
{
}

LineEdit::~LineEdit()
{
    delete d_ptr;
}

QString LineEdit::labelText() const
{
    Q_D(const LineEdit);
    return d->labelText;
}

QVariant LineEdit::data() const
{
    Q_D(const LineEdit);
    return d->userData;
}

void LineEdit::setLabelText(const QString &labelText)
{
    Q_D(LineEdit);
    if (d->labelText == labelText)
    {
        return;
    }
    d->labelText = labelText;
    update();
    Q_EMIT labelTextChanged(labelText);
}

void LineEdit::setData(const QVariant &userData)
{
    Q_D(LineEdit);
    if (d->userData == userData)
    {
        return;
    }
    d->userData = userData;
    Q_EMIT dataChanged(userData);
}

void LineEdit::clear()
{
    QLineEdit::clear();
    setLabelText(QString());
    setData(QVariant());
}

void LineEdit::paintEvent(QPaintEvent *event)
{
    if (hasFocus() && !isReadOnly() && isEnabled())
    {
        QLineEdit::paintEvent(event);
    }
    else
    {
        QPainter p(this);
        QRect r = rect();
        QPalette pal = palette();

        QStyleOptionFrameV2 panel;
        initStyleOption(&panel);
        style()->drawPrimitive(QStyle::PE_PanelButtonBevel, &panel, &p, this);
        r = style()->subElementRect(QStyle::SE_LineEditContents, &panel, this);

        QPen oldpen = p.pen();
        p.setPen(QColor(Qt::darkBlue));

        QFontMetrics fm = fontMetrics();

        Q_D(LineEdit);
        QString elidedText = fm.elidedText(d->labelText, 
                Qt::ElideRight, r.width());
        p.drawText(r, Qt::AlignLeft | Qt::AlignVCenter, elidedText);
        p.setPen(oldpen);
    }
}

void LineEdit::mouseDoubleClickEvent(QMouseEvent *event)
{
    QLineEdit::mouseDoubleClickEvent(event);
    Q_EMIT doubleClicked();
}

void LineEdit::contextMenuEvent(QContextMenuEvent *event)
{
    if (hasFocus() && !isReadOnly() && isEnabled())
    {
        QLineEdit::contextMenuEvent(event);
    }
    else
    {
        event->ignore();
    }
}
}
#include "moc_LineEdit.cpp"
