// 文档说明：实现中间带有三角箭头的button
// ==========================================================================
// 开发日志：
// 日期         人员        说明
// --------------------------------------------------------------------------
// 2013.10.14   younghz     建立
// 2013.10.15   XChinux     格式化代码
// ==========================================================================
/// @file tcarrowbutton.h 实现中间带有三角箭头的button
// ==========================================================================

#ifndef TIANCHI_TCARROWBUTTON_H
#define TIANCHI_TCARROWBUTTON_H

#include <tianchi/tcglobal.h>
#include <QPushButton>

class TcArrowButtonPrivate;

/// @brief 箭头按钮类
class TIANCHI_API TcArrowButton : public QPushButton
{
    Q_OBJECT
public:
    /// @brief 构造函数
    /// @param [in] num 按钮中箭头的数量
    /// @param [in] arrowType 控制箭头的方向(Qt::UpArrow/Qt::DownArrow/Qt::LeftArrow/Qt::DownArrow)
    /// @param [in] *parent
    explicit TcArrowButton(int num, Qt::ArrowType, QWidget *parent = 0);
    virtual ~TcArrowButton();

protected:
    virtual void paintEvent(QPaintEvent *event);
    virtual void keyPressEvent( QKeyEvent *event);
private:
    Q_DISABLE_COPY(TcArrowButton)
    Q_DECLARE_PRIVATE(TcArrowButton)
    TcArrowButtonPrivate* const d_ptr;
};

#endif // TCARROWBUTTON_H
