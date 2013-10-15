// 文档说明：实现中间带有三角箭头的button
// ==========================================================================
// 开发日志：
// 日期         人员        说明
// --------------------------------------------------------------------------
// 2013.10.14  younghz
// ==========================================================================
/// @file tcarrowbutton.h 实现中间带有三角箭头的button
// ==========================================================================

#ifndef TCARROWBUTTON_H
#define TCARROWBUTTON_H

#include <tianchi/tcglobal.h>
#include <qpushbutton.h>

/// @brief 箭头按钮类
class TIANCHI_API TcArrowButton : public QPushButton
{
public:

    /// @brief 构造函数
    /// @param [in] num 按钮中箭头的数量
    /// @param [in] arrowType 控制箭头的方向(Qt::UpArrow/Qt::DownArrow/Qt::LeftArrow/Qt::DownArrow)
    /// @param [in] *parent
    explicit TcArrowButton(int num, Qt::ArrowType, QWidget *parent = NULL );
    virtual ~TcArrowButton();

protected:
    virtual void paintEvent( QPaintEvent *event );

    virtual void drawButtonLabel( QPainter *p );
    /// @brief 绘制箭头
    virtual void drawArrow( QPainter *,
        const QRect &, Qt::ArrowType ) const;
    virtual QRect labelRect() const;
    /// @brief 箭头大小
    virtual QSize arrowSize( Qt::ArrowType,
        const QSize &boundingSize ) const;

private:
    class PrivateData;
    PrivateData *d_data;
};

#endif // TCARROWBUTTON_H
