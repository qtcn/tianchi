// **************************************************************************
// Tianchi C++ library for Qt (open source)
// ��ع���Դ���
// ��Ȩ���� (C) ��ع���Դ��⿪����
// ��ȨЭ�飺���Ķ���ع���Դ��⸽������ȨЭ��
// **************************************************************************
// �ĵ�˵���������Label,���ʱ�Զ�����ַ
// ==========================================================================
// ������־��
// ����         ��Ա        ˵��
// --------------------------------------------------------------------------
// 2013.04.18   XChinux     ����
// 2013.05.19   XChinux     �޸�ԭ�ƶ�Labelλ�õ�ʵ��Ϊʹ��contentsMargin��ʵ��
// 2013.05.22   XChinux     ����interval active���Լ�����źźͲۺ���
// ==========================================================================
/// @file MarqueeLabel.h �����Label,���ʱ�Զ�����ַ
// ==========================================================================
#ifndef TIANCHI_TCMARQUEELABEL_H
#define TIANCHI_TCMARQUEELABEL_H

#include <tianchi/tcglobal.h>

#include <QLabel>

QT_BEGIN_NAMESPACE
QT_END_NAMESPACE

class TcMarqueeLabelPrivate;
/// @brief �������MarqueeLabel,���ʱ�Զ�����ַ
/// @author XChinux XChinux@163.com
/// @date 2013-04-18
class TIANCHI_API TcMarqueeLabel : public QLabel
{
    Q_OBJECT

    Q_ENUMS(Direction)

    // @brief   �������ֹ�������
    Q_PROPERTY(Direction direction
            READ direction
            WRITE setDirection
            NOTIFY directionChanged
            DESIGNABLE true)

    /// @brief  ����ÿ�ƶ�һ��������ʱ��(����)
    Q_PROPERTY(int interval 
            READ interval 
            WRITE setInterval
            NOTIFY intervalChanged
            DESIGNABLE true)

    /// @brief  �����Ƿ������ƶ�״̬
    Q_PROPERTY(bool active
            READ isActive
            WRITE setActive
            NOTIFY activeChanged
            DESIGNABLE true)

    Q_PROPERTY(Qt::Alignment alignment 
            READ alignment 
            WRITE setAlignment
            DESIGNABLE true)
public:
    TcMarqueeLabel(QWidget * parent = 0, Qt::WindowFlags f = 0);
    TcMarqueeLabel(const QString &text, QWidget *parent = 0, 
            Qt::WindowFlags f = 0);
    virtual ~TcMarqueeLabel();
    /// @brief  ����interval
    int interval() const;
    /// @brief  ���ص�ǰ״̬
    bool isActive() const;

    enum Direction
    {
        RightToLeft = 0,
        BottomToTop = 1 
    };

    Direction direction() const;
    void setAlignment(Qt::Alignment align);
Q_SIGNALS:
    /// @brief  interval���Ա仯ʱ�������ź�
    void intervalChanged(int interval);
    /// @brief  active���Ա仯ʱ�������ź�
    void activeChanged(bool active);
    /// @brief  direction���Ա仯ʱ�������ź�
    void directionChanged(Direction direction);
public Q_SLOTS:
    /// @brief  ֹͣ�ƶ����Ҹ�λλ��Ϊ0
    /// @see    stop()
    void reset();
    /// @brief  ��������״̬
    /// @see    start(), stop()
    void setActive(bool active);
    /// @brief  ����ÿ�ƶ�һ��������ʱ��
    /// @see    interval()
    void setInterval(int msec);
    /// @brief  ��������
    /// @ses    setActive(bool active), stop()
    void start();
    /// @brief  ֹͣ����
    /// @see    setActive(bool active), start()
    void stop();
    /// @brief  �����ƶ�����
    /// @see    direction(), directionChagned(Direction direction)
    void setDirection(Direction direciton);
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
