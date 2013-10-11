// **************************************************************************
// Tianchi share library for Qt (C++)
// ��ع���Դ���
// ��Ȩ���� (C) ��ع���Դ��⿪����
// ��ȨЭ�飺���Ķ���ع���Դ��⸽������ȨЭ��
// **************************************************************************
// �ĵ�˵���������Ի���
// ==========================================================================
// ������־��
// ����         ��Ա        ˵��
// --------------------------------------------------------------------------
// 2013.10.11   XChinux     ����
//
// ==========================================================================
/// @file tcscreencutdialog.cpp �����Ի���
// ==========================================================================
#include <tianchi/gui/tcscreencutdialog.h>
#include <QRect>
#include <QPoint>
#include <QPainter>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QApplication>
#include <QDesktopWidget>

class TcScreenCutDialogPrivate
{
    Q_DECLARE_PUBLIC(TcScreenCutDialog)
public:
    explicit TcScreenCutDialogPrivate(TcScreenCutDialog *qptr);
    ~TcScreenCutDialogPrivate();

    TcScreenCutDialog* const q_ptr;

    bool _bDrag;
    QPoint _pos;
    QRect _rect;
    QImage _image;
    QImage _darkImage;

};

TcScreenCutDialogPrivate::TcScreenCutDialogPrivate(TcScreenCutDialog *qptr)
    : q_ptr(qptr), _bDrag(false)
{
}

TcScreenCutDialogPrivate::~TcScreenCutDialogPrivate()
{
}

TcScreenCutDialog::TcScreenCutDialog(QWidget *parent, Qt::WindowFlags f)
    : QDialog(parent, f), d_ptr(new TcScreenCutDialogPrivate(this))
{
    setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint
            | Qt::WindowStaysOnTopHint);
    setWindowState(Qt::WindowFullScreen);
    setCursor(Qt::CrossCursor);
    QDesktopWidget *desk = QApplication::desktop();
    setGeometry(desk->availableGeometry());
    
    Q_D(TcScreenCutDialog);
    d->_image = QPixmap::grabWindow(desk->winId()).toImage();
    d->_darkImage = d->_image;
    int bytesPerLine = d->_darkImage.width() * d->_darkImage.depth() / 8;
    int h = d->_darkImage.height();
    for (int i = 0; i < h; i++)
    {
        unsigned char *lineBuf = d->_darkImage.scanLine(i);
        for (int x = 0; x < bytesPerLine; x++)
        {
            lineBuf[x] /= 2;
        }
    }
}

TcScreenCutDialog::~TcScreenCutDialog()
{
    delete d_ptr;
}


void TcScreenCutDialog::mousePressEvent(QMouseEvent *event)
{
    Q_D(TcScreenCutDialog);
    d->_bDrag = true;
    d->_pos = event->pos();
    d->_rect = QRect(d->_pos.x(), d->_pos.y(), 0, 0);
    QDialog::mousePressEvent(event);
}

void TcScreenCutDialog::mouseMoveEvent(QMouseEvent *event)
{
    Q_D(TcScreenCutDialog);
    if (d->_bDrag == true)
    {
        QPoint pos = event->pos();
        if (pos.x() > d->_pos.x())
        {
            if (pos.y() > d->_pos.y())
            {
                d->_rect = QRect(d->_pos, pos);
            }
            else
            {
                d->_rect = QRect(QPoint(d->_pos.x(), pos.y()),
                            QPoint(pos.x(), d->_pos.y()));
            }
        }
        else
        {
            if (pos.y() > d->_pos.y())
            {
                d->_rect = QRect(QPoint(pos.x(), d->_pos.y()),
                            QPoint(d->_pos.x(), pos.y()));
            }
            else
            {
                d->_rect = QRect(pos, d->_pos);
            }
        }
        update();
    }
    QDialog::mouseMoveEvent(event);
}

void TcScreenCutDialog::mouseReleaseEvent(QMouseEvent *event)
{
    Q_D(TcScreenCutDialog);
    d->_bDrag = false;
    QDialog::mouseReleaseEvent(event);
    accept();
}

void TcScreenCutDialog::mouseDoubleClickEvent(QMouseEvent *event)
{
    QDialog::mouseDoubleClickEvent(event);
    /*
    if (_rect.contains(event->pos()))
    {
        accept();
    }
    */
}
QPixmap TcScreenCutDialog::getPixmap() const
{
    Q_D(const TcScreenCutDialog);
    QPixmap px(d->_rect.size());
    QPainter p(&px);
    p.drawImage(QRect(0, 0, d->_rect.width(), d->_rect.height()),
            d->_image, d->_rect);
    p.end();
    return px;
}

void TcScreenCutDialog::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    Q_D(const TcScreenCutDialog);
    QPainter painter(this);
    painter.drawImage(0, 0, d->_darkImage);
    painter.drawImage(d->_rect, d->_image, d->_rect);
    painter.drawRect(d->_rect);
}

#include "moc_tcscreencutdialog.cpp"
