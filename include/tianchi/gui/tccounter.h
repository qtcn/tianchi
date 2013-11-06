// 文档说明：实现可用两边按钮调节大小的counter
// ==========================================================================
// 开发日志：
// 日期         人员        说明
// --------------------------------------------------------------------------
// 2013.10.31   younghz     建立
// ==========================================================================
/// @file tccounter.h 实现可用两边按钮调节大小的counter
// ==========================================================================

#ifndef TIANCHI_TCCOUNTER_H
#define TIANCHI_TCCOUNTER_H

#include <tianchi/tcglobal.h>
#include <QWidget>

/// @brief counter widget
/// 这个widget包含一个显示数字的lineedit和一个或者多个可以用来增加和减小显示的数字的值的
/// arrowbutton，按钮按下时增加或是减小的数值可以由setIncSteps()函数设定，lineedit两边
/// 的arrowbutton的个数可以由setNumButtons()函数设定。

class TcCounterPrivate;

/// @brief TcCounter类
class TIANCHI_API TcCounter : public QWidget
{
    Q_OBJECT
public:
    /// @brief 构造函数
    explicit TcCounter(QWidget *parent = 0);
    ~TcCounter();

    /// @brief 设置按钮数量
    /// @param [in] 按钮数量值
    void setButtonNum(int n);

    /// @brief 设置valueEdit显示数的范围
    /// @param [in] minnum 最小值
    /// @param [in] maxnum 最大值
    void setRange(double minnum, double maxnum);

    /// @brief 设置步长
    /// @param [in] 步长值
    void setSingleStep(double step);

    /// @return 步长大小
    double singleStep() const;

    /// @brief 设置counter的状态（有效、无效）
    ///        当设置为无效时，lineEdit中不会显示数字并且两边的arrowButton不可用
    /// @param [in] on 为true时状态的有效，否则无效
    void setValid(bool on);

    /// @brief 返回是否有效状态
    bool isValid() const;
Q_SIGNALS:

    /// @brief 当控件的值改变时发射
    /// @param value 新的值
    void valueChanged(double value);

private:
    Q_DISABLE_COPY(TcCounter)
    Q_DECLARE_PRIVATE(TcCounter)

    TcCounterPrivate* const d_ptr;
};

#endif // TIANCHI_TCCOUNTER_H
