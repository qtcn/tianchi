//#include "tccounter.h"
//#include "tcarrowbutton.h"

#include <tianchi/gui/tccounter.h>
#include <tianchi/gui/tcarrowbutton.h>

#include <QHBoxLayout>
#include <QLineEdit>
#include <QEvent>

class TcCounterPrivate
{
    Q_DECLARE_PUBLIC(TcCounter)
public:
    explicit TcCounterPrivate(TcCounter *qptr);
    ~TcCounterPrivate();

    /// @brief 初始化
    void initcounter();

    /// @brief 更新arrowButton的状态
    void updateButtons();

    /// @brief 显示valueEdit的值
    void showNumbers(double value);

    TcCounter* const q_ptr;
    enum Button
    {
        Button1,
        Button2,
        Button3,
        //按钮数量
        ButtonCnt
    };

    TcArrowButton *downButton[ButtonCnt];
    TcArrowButton *upButton[ButtonCnt];
    QLineEdit *valueEdit;

    int buttonNum;
    double singleStep;
    double maximum;
    double minimum;
    double value;
    bool isValid;

};

TcCounterPrivate::TcCounterPrivate(TcCounter *qptr): q_ptr( qptr )
{

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
    d_ptr->initcounter();
}

TcCounter::~TcCounter()
{
    delete d_ptr;
}

/// @brief 初始化组件
void TcCounterPrivate::initcounter()
{
    QHBoxLayout *layout = new QHBoxLayout( q_ptr );
    layout->setMargin(0);
    layout->setSpacing(0);

    //valueEdit左侧按钮
    for(int i = ButtonCnt-1; i >= 0; i--)
    {
        TcArrowButton *lbtn = new TcArrowButton(i+1, Qt::DownArrow, q_ptr);
        lbtn->setFocusPolicy(Qt::NoFocus);
        //lbtn->installEventFilter(this);
        lbtn->setMinimumWidth(12);
        lbtn->setMaximumWidth(12);
        lbtn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        layout->addWidget(lbtn);

        downButton[i] = lbtn;
    }

    //中间的valueEdit
    valueEdit = new QLineEdit(q_ptr);
    valueEdit->setReadOnly(true);
    layout->addWidget(valueEdit);

    //valueEdit右侧按钮
    for(int i = 0; i <= ButtonCnt -1; i++)
    {
        TcArrowButton *rbtn = new TcArrowButton(i+1, Qt::UpArrow, q_ptr);
        rbtn->setFocusPolicy(Qt::NoFocus);
        rbtn->setMinimumWidth(12);
        rbtn->setMaximumWidth(12);
        rbtn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        //rbtn->installEventFilter(this);
        layout->addWidget(rbtn);

        upButton[i] = rbtn;
    }

    q_ptr->setButtonNum( 2 );
    q_ptr->setRange(0.0, 1.0);
    q_ptr->setSingleStep(0.001);

    //设置FocusProxy和FocusPolicy
    q_ptr->setFocusProxy(valueEdit);
    q_ptr->setFocusPolicy(Qt::StrongFocus);

    q_ptr->setSizePolicy(
        QSizePolicy( QSizePolicy::Preferred, QSizePolicy::Fixed ) );
}

/// @brief 设置按钮数量
void TcCounter::setButtonNum(int buttonNum)
{
    if(buttonNum < 0 || buttonNum > d_ptr->ButtonCnt)
    {
        return;
    }
    for(int i = 0; i < d_ptr->ButtonCnt; i++)
    {
        if( i < buttonNum )
        {
            d_ptr->downButton[i]->show();
            d_ptr->upButton[i]->show();
        }
        else
        {
            d_ptr->downButton[i]->hide();
            d_ptr->upButton[i]->hide();
        }
    }

    d_ptr->buttonNum = buttonNum;

}

/// @brief 设置valueEdit范围
void TcCounter::setRange(double minnum, double maxnum)
{
    maxnum = qMax(minnum, maxnum);
    if(d_ptr->minimum == minnum && d_ptr->maximum == maxnum)
    {
        return;
    }

    //更新最大最小值
    d_ptr->minimum = minnum;
    d_ptr->maximum = maxnum;

    //设置步长
    setSingleStep( singleStep() );

    const double value = qBound(minnum, d_ptr->value, maxnum);

    if(value != d_ptr->value)
    {
        //更新value值
        d_ptr->value = value;

        if( d_ptr->isValid )
        {
            d_ptr->showNumbers( d_ptr->value );
            Q_EMIT valuechanged( d_ptr->value );
        }

    }
}

/// @brief 设置步长
void TcCounter::setSingleStep(double step)
{
    d_ptr->singleStep = qMax(step, 0.0);
}

/// @brief 返回步长值
double TcCounter::singleStep() const
{
    return d_ptr->singleStep;
}

/// @brief 设置状态
void TcCounter::setValid(bool on)
{
    if( on == d_ptr->isValid )
    {
        return;
    }

    //更新isvalid的值
    d_ptr->isValid = on;

    d_ptr->updateButtons();

    if( d_ptr->isValid )
    {
        d_ptr->showNumbers(d_ptr->value);
        Q_EMIT valuechanged( d_ptr->value );
    }
    else
    {
        d_ptr->valueEdit->setText(QString::null);
    }
}

/// @brief 更新按钮状态
void TcCounterPrivate::updateButtons()
{
    if(isValid)
    {
        for(int i = 0; i < ButtonCnt; i++)
        {
            upButton[i]->setEnabled( value > minimum );
            downButton[i]->setEnabled( value < maximum );
        }
    }
    else
    {
        for(int i =0; i < ButtonCnt; i++ )
        {
            upButton[i]->setEnabled( false );
            downButton[i]->setEnabled( false );
        }
    }
}

/// @brief 显示valueEdit的值
void TcCounterPrivate::showNumbers(double value)
{
    QString text;
    text.setNum(value);
    valueEdit->setText( text );
}
