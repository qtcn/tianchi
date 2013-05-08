#include <tianchi/gui/tcdateedit.h>
#include <tianchi/core/tcutils.h>
#include <QMouseEvent>

TcDateEdit::TcDateEdit(QWidget *parent)
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

TcDateEdit::~TcDateEdit()
{
    delete m_calendar;
}

void TcDateEdit::focusInEvent(QFocusEvent *e)
{
    Q_UNUSED(e)
    //���λ����¼�
}

void TcDateEdit::mousePressEvent(QMouseEvent *e)
{
    //��ȡ��굱ǰ���꼰ȫ������
    int x = e->x();
    int y = e->y();
    int globx = e->globalX();
    int globy = e->globalY();

    //�������ƶ�����Ӧ��Ļ����λ�á���ʾ
    //������Ļx - ��ǰ�ؼ�x��= ��ǰ�ؼ����x
    //y��������
    m_calendar->move(globx - x, globy + this->height() - y);
    m_calendar->setWindowFlags(Qt::Popup);
    m_calendar->setSelectedDate(this->date());
    m_calendar->show();
}

void TcDateEdit::calendarClicked(QDate _date)
{
    //�����ĵ����źŴ�����

    //�ж�combox�м�¼����
    //��֤����ֻ��һ������
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

QDate TcDateEdit::date() const
{
    return TcUtils::toDateTime(currentText().trimmed()).date();
}

void TcDateEdit::setDate(QDate value)
{
    setEditText(value.year() > 1900 ? value.toString("yyyy-MM-dd") : "");
}

void TcDateEdit::unsetDate()
{
    setEditText("");
}
