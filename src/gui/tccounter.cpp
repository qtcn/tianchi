#include <tianchi/gui/tccounter.h>
#include <tianchi/gui/tcarrowbutton.h>

#include <QEvent>
#include <QLineEdit>
#include <QHBoxLayout>

class TcCounterPrivate
{
    Q_DECLARE_PUBLIC(TcCounter)

public:
    explicit TcCounterPrivate(TcCounter *qptr);
    ~TcCounterPrivate();

    TcCounter* const q_ptr;
    enum Button
    {
        Button1,
        Button2,
        Button3,
        //按钮数量
        ButtonCnt
    };

    /// @brief 初始化
    void initcounter();

    /// @brief 更新arrowButton的状态
    void updateButtons();

    /// @brief 显示valueEdit的值
    void showNumbers(double value);

    /// @brief 点击按钮1增加的步数
    void setIncSteps(TcCounterPrivate::Button btn, int nSteps);
    int incSteps(TcCounterPrivate::Button btn) const;

    void incrementValue(int numSteps);



    TcArrowButton *downButton[ButtonCnt];
    TcArrowButton *upButton[ButtonCnt];
    QLineEdit *valueEdit;

    int buttonNum;
    double singleStep;
    double maximum;
    double minimum;
    double value;
    bool isValid;

    int increment[ButtonCnt];

};

void TcCounterPrivate::incrementValue(int numSteps)
{
    Q_Q(TcCounter);
    const double min = minimum;
    const double max = maximum;
    double stepSize = singleStep;

    if ( !isValid || min >= max || stepSize <= 0.0 )
        return;


#if 1
    stepSize = qMax( stepSize, 1.0e-10 * ( max - min ) );
#endif

    double value = TcCounterPrivate::value + numSteps * stepSize;

    const double range = max - min;

    if ( value < min )
    {
        value += ( ( min - value ) / range ) * range;
    }
    else if ( value > max )
    {
        value -= ( ( value - max ) / range ) * range;
    }

    value = min + qRound( ( value - min ) / stepSize ) * stepSize;
    if ( qFuzzyCompare( value, max ) )
        value = max;

    if ( qFuzzyCompare( value + 1.0, 1.0 ) )
        value = 0.0;

    if ( value != TcCounterPrivate::value )
    {
        TcCounterPrivate::value = value;
        TcCounterPrivate::showNumbers( TcCounterPrivate::value );
        TcCounterPrivate::updateButtons();

        Q_EMIT q->valueChanged( TcCounterPrivate::value );
    }
}

TcCounterPrivate::TcCounterPrivate(TcCounter *qptr): q_ptr(qptr)
{
    maximum = 1.0;
    minimum = 0.0;
    value = 0.0;
    singleStep = 1.0;
    isValid = false;

    increment[Button1] = 1;
    increment[Button2] = 10;
    increment[Button3] = 100;
}

TcCounterPrivate::~TcCounterPrivate()
{
}

/// @brief 构造函数。初始lineedit的值的范围是0.0-1.0，单长0.01，状态为不可用，
///        默认的按钮个数是两个。
/// @param parent
TcCounter::TcCounter(QWidget *parent)
    : QWidget(parent), d_ptr(new TcCounterPrivate(this))
{
    Q_D(TcCounter);
    d->initcounter();
}

TcCounter::~TcCounter()
{
    Q_D(TcCounter);
    delete d;
}

/// @brief 初始化组件
void TcCounterPrivate::initcounter()
{

    Q_Q(TcCounter);
    QHBoxLayout *layout = new QHBoxLayout(q);
    layout->setMargin(0);
    layout->setSpacing(0);

    //valueEdit左侧按钮
    for (int i = ButtonCnt - 1; i >= 0; i--)
    {
        TcArrowButton *lbtn = new TcArrowButton(i + 1, Qt::DownArrow, q);
        lbtn->setFocusPolicy(Qt::NoFocus);
        //lbtn->installEventFilter(this);
        lbtn->setMinimumWidth(12);
        lbtn->setMaximumWidth(12);
        lbtn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        layout->addWidget(lbtn);

        QObject::connect(lbtn, SIGNAL(released()),
                         q, SLOT(btnRelease()));
        QObject::connect(lbtn, SIGNAL(clicked()),
                         q, SLOT(btnClick()));

        downButton[i] = lbtn;
    }

    //中间的valueEdit
    valueEdit = new QLineEdit(q);
    valueEdit->setReadOnly(true);
    layout->addWidget(valueEdit);

    //valueEdit右侧按钮
    for (int i = 0; i <= ButtonCnt -1; i++)
    {
        TcArrowButton *rbtn = new TcArrowButton(i + 1, Qt::UpArrow, q);
        rbtn->setFocusPolicy(Qt::NoFocus);
        rbtn->setMinimumWidth(12);
        rbtn->setMaximumWidth(12);
        rbtn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        //rbtn->installEventFilter(this);
        layout->addWidget(rbtn);

        QObject::connect(rbtn, SIGNAL(released()),
                         q, SLOT(btnRelease()));
        QObject::connect(rbtn, SIGNAL(clicked()),
                         q, SLOT(btnClick()));

        upButton[i] = rbtn;
    }

    q->setButtonNum(2);
    q->setRange(0.0, 1.0);
    q->setSingleStep(0.001);
    q->setValue(0.0);


    //设置FocusProxy和FocusPolicy
    q->setFocusProxy(valueEdit);
    q->setFocusPolicy(Qt::StrongFocus);

    q->setSizePolicy(QSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed));
}

/// @brief 设置按钮数量
void TcCounter::setButtonNum(int buttonNum)
{
    Q_D(TcCounter);
    if (buttonNum < 0 || buttonNum > d->ButtonCnt)
    {
        return;
    }
    for (int i = 0; i < d->ButtonCnt; i++)
    {
        if (i < buttonNum)
        {
            d->downButton[i]->show();
            d->upButton[i]->show();
        }
        else
        {
            d->downButton[i]->hide();
            d->upButton[i]->hide();
        }
    }

    d->buttonNum = buttonNum;
}

/// @brief 设置valueEdit范围
void TcCounter::setRange(double minnum, double maxnum)
{
    Q_D(TcCounter);
    maxnum = qMax(minnum, maxnum);
    if (d->minimum == minnum && d->maximum == maxnum)
    {
        return;
    }

    //更新最大最小值
    d->minimum = minnum;
    d->maximum = maxnum;

    //设置步长
    setSingleStep(singleStep());

    const double value = qBound(minnum, d->value, maxnum);

    if (value != d->value)
    {
        //更新value值
        d->value = value;

        if (d->isValid)
        {
            d->showNumbers(d->value);
            Q_EMIT valueChanged(d->value);
        }
    }
}

/// @brief 设置步长
void TcCounter::setSingleStep(double step)
{
    Q_D(TcCounter);
    d->singleStep = qMax(step, 0.0);
}

/// @brief 返回步长值
double TcCounter::singleStep() const
{
    Q_D(const TcCounter);
    return d->singleStep;
}

/// @brief 设置状态
void TcCounter::setValid(bool on)
{
    Q_D(TcCounter);
    if (on == d->isValid)
    {
        return;
    }

    //更新isValid的值
    d->isValid = on;

    d->updateButtons();

    if (d->isValid)
    {
        d->showNumbers(d->value);
        Q_EMIT valueChanged(d->value);
    }
    else
    {
        d->valueEdit->setText(QString::null);
    }
}

/// @brief 更新按钮状态
void TcCounterPrivate::updateButtons()
{
    Q_Q(TcCounter);
    if (isValid)
    {
        for (int i = 0; i < ButtonCnt; i++)
        {
            upButton[i]->setEnabled(value < q->maximum());
            downButton[i]->setEnabled(value > q->minimum());
        }
    }
    else
    {
        for (int i = 0; i < ButtonCnt; i++)
        {
            upButton[i]->setEnabled(false);
            downButton[i]->setEnabled(false);
        }
    }
}

/// @brief 显示valueEdit的值
void TcCounterPrivate::showNumbers(double value)
{
    QString text;
    text.setNum(value);
    valueEdit->setText(text);
}

void TcCounterPrivate::setIncSteps(TcCounterPrivate::Button btn, int nSteps)
{
    if (btn >= 0 && btn < TcCounterPrivate::ButtonCnt)
    {
        increment[btn] = nSteps;
    }
}

int TcCounterPrivate::incSteps(TcCounterPrivate::Button btn) const
{
    if (btn > 0 && btn < TcCounterPrivate::ButtonCnt)
    {
        return increment[btn];
    }
    return 0;
}

/// @brief 设置只读属性
void TcCounter::setReadOnly(bool on)
{
    Q_D(TcCounter);
    return d->valueEdit->setReadOnly( on );
}

bool TcCounter::isReadOnly() const
{
    Q_D(const TcCounter);
    return d->valueEdit->isReadOnly();
}

void TcCounter::setMinimum(double minValue)
{
    setRange(minValue, maximum());
}

double TcCounter::minimum() const
{
    Q_D(const TcCounter);
    return d->minimum;
}

void TcCounter::setMaximum(double maxValue)
{
    setRange(minimum(), maxValue);
}

double TcCounter::maximum() const
{
    Q_D(const TcCounter);
    return d->maximum;
}

double TcCounter::value() const
{
    Q_D(const TcCounter);
    return d->value;
}
void TcCounter::setValue(double value)
{
    Q_D(TcCounter);
    const double valuemin = qMin(d->minimum, d->maximum);
    const double valuemax = qMax(d->minimum, d->maximum);

    value = qBound(valuemin, value, valuemax);

    if (!d->isValid || value != d->value)
    {
        d->isValid = true;
        d->value = value;

        d->showNumbers(value);
        d->updateButtons();

        Q_EMIT valueChanged(value);
    }
}

void TcCounter::setStepButton1(int nSteps)
{
    Q_D(TcCounter);
    d->setIncSteps(d->Button1, nSteps);
}

int TcCounter::stepButton1() const
{
    Q_D(const TcCounter);
    return d->incSteps(TcCounterPrivate::Button1);
}

void TcCounter::setStepButton2(int nSteps)
{
    Q_D(TcCounter);
    d->setIncSteps(d->Button2, nSteps);
}

int TcCounter::stepButton2() const
{
    Q_D(const TcCounter);
    return d->incSteps(TcCounterPrivate::Button2);
}

void TcCounter::setStepButton3(int nSteps)
{
    Q_D(TcCounter);
    d->setIncSteps(d->Button3, nSteps);
}

int TcCounter::stepButton3() const
{
    Q_D(const TcCounter);
    return d->incSteps(TcCounterPrivate::Button3);
}

void TcCounter::btnRelease()
{
    Q_EMIT buttonReleased(value());
}

void TcCounter::btnClick()
{
    Q_D(TcCounter);

    for (int i = 0; i < d->ButtonCnt; i++)
    {
        if (d->upButton[i] == QObject::sender())
        {
            d->incrementValue(d->increment[i]);
        }
        if (d->downButton[i] == sender())
        {
            d->incrementValue(-d->increment[i]);
        }
    }
}

#include "moc_tccounter.cpp"
