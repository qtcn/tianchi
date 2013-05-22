// **************************************************************************
// Tianchi C++ library for Qt (open source)
// 天池共享源码库
// 版权所有 (C) 天池共享源码库开发组
// 授权协议：请阅读天池共享源码库附带的授权协议
// **************************************************************************
// 文档说明：跑马灯Label,点击时自动打开网址
// ==========================================================================
// 开发日志：
// 日期         人员        说明
// --------------------------------------------------------------------------
// 2013.04.18   XChinux     建立
// 2013.05.19   XChinux     修改原移动Label位置的实现为使用contentsMargin来实现
// 2013.05.22   XChinux     增加interval active属性及相关信号和槽函数
// ==========================================================================
/// @file MarqueeLabel.h 跑马灯Label,点击时自动打开网址
// ==========================================================================
#ifndef TIANCHI_TCMARQUEELABEL_H
#define TIANCHI_TCMARQUEELABEL_H

#include <tianchi/tcglobal.h>

#include <QLabel>

QT_BEGIN_NAMESPACE
QT_END_NAMESPACE

class TcMarqueeLabelPrivate;
/// @brief 跑马灯类MarqueeLabel,点击时自动打开网址
/// @author XChinux XChinux@163.com
/// @date 2013-04-18
class TIANCHI_API TcMarqueeLabel : public QLabel
{
    Q_OBJECT
    /// @brief  设置每移动一像素所需时间(毫秒)
    Q_PROPERTY(int interval 
            READ interval 
            WRITE setInterval
            NOTIFY intervalChanged
            DESIGNABLE true)

    /// @brief  设置是否启动移动状态
    Q_PROPERTY(bool active
            READ isActive
            WRITE setActive
            NOTIFY activeChanged
            DESIGNABLE true)
public:
    TcMarqueeLabel(QWidget * parent = 0, Qt::WindowFlags f = 0);
    TcMarqueeLabel(const QString &text, QWidget *parent = 0, 
            Qt::WindowFlags f = 0);
    virtual ~TcMarqueeLabel();
    /// @brief  返回interval
    int interval() const;
    /// @brief  返回当前状态
    bool isActive() const;
Q_SIGNALS:
    /// @brief  interval属性变化时发出此信号
    void intervalChanged(int interval);
    /// @brief  active属性变化时发出错信号
    void activeChanged(bool active);
public Q_SLOTS:
    /// @brief  停止移动并且复位位置为0
    /// @see    stop()
    void reset();
    /// @brief  设置运行状态
    /// @see    start(), stop()
    void setActive(bool active);
    /// @brief  设置每移动一像素所需时间
    /// @see    interval()
    void setInterval(int msec);
    /// @brief  启动运行
    /// @ses    setActive(bool active), stop()
    void start();
    /// @brief  停止运行
    /// @see    setActive(bool active), start()
    void stop();
protected:
    virtual void enterEvent(QEvent *event);
    virtual void leaveEvent(QEvent *event);
    virtual void resizeEvent(QResizeEvent *event);
    virtual void timerEvent(QTimerEvent *event);
    virtual void paintEvent(QPaintEvent *event);
private:
    Q_DISABLE_COPY(TcMarqueeLabel)
    Q_DECLARE_PRIVATE(TcMarqueeLabel)
    Q_PRIVATE_SLOT(d_func(), void _q_openLink(const QString &))
    TcMarqueeLabelPrivate* const d_ptr;
};

#endif
