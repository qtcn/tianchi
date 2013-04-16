#include "Gui/DateEdit.h"

#include "Core/Utils.h"

#include <QMouseEvent>

TIANCHI_BEGIN_NAMESPACE

DateEdit::DateEdit(QWidget *parent)
    : QComboBox(parent)
{
    setEditable(true);

    m_calendar = new QCalendarWidget(this);
    QFont _font;
    _font.setPixelSize(12);
    m_calendar->setFont(_font);
    m_calendar->setContentsMargins(0, 0, 0, 0);
    m_calendar->resize(350, 170);
    m_calendar->hide();

    connect(m_calendar, SIGNAL(clicked(QDate)), this, SLOT(calendarClicked(QDate)));
}

DateEdit::~DateEdit()
{
    delete m_calendar;
}

void DateEdit::focusInEvent(QFocusEvent *e)
{
    //屏蔽基类事件
}

void DateEdit::mousePressEvent(QMouseEvent *e)
{
    //获取鼠标当前坐标及全局坐标
    int x = e->x();
    int y = e->y();
    int globx = e->globalX();
    int globy = e->globalY();

    //把日历移动到对应屏幕坐标位置、显示
    //即（屏幕x - 当前控件x）= 当前控件左端x
    //y坐标类似
    m_calendar->move(globx - x, globy + this->height() - y);
    m_calendar->setWindowFlags(Qt::Popup);
    m_calendar->setSelectedDate(this->date());
    m_calendar->show();
}

void DateEdit::calendarClicked(QDate _date)
{
    //日历的单击信号处理函数

    //判断combox中记录数量
    //保证其中只有一条数据
    if ( this->count() == 0 )
    {
        this->addItem(_date.toString("yyyy-MM-dd"));
    }
    else
    {
        this->setItemData(0, QVariant::fromValue(_date.toString("yyyy-MM-dd")), Qt::DisplayRole);
    }
    this->setCurrentIndex(0);
    m_calendar->hide();
}

QDate DateEdit::date() const
{
    return Utils::toDateTime(currentText().trimmed()).date();
}

void DateEdit::setDate(QDate value)
{
    setEditText(value.year() > 1900 ? value.toString("yyyy-MM-dd") : "");
}

void DateEdit::unsetDate()
{
    setEditText("");
}

TIANCHI_END_NAMESPACE
