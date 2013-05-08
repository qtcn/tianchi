// **************************************************************************
// Tianchi C++ library for Qt (open source)
// 天池共享源码库
// 版权所有 (C) 天池共享源码库开发组
// 授权协议：请阅读天池共享源码库附带的授权协议
// **************************************************************************
// 文档说明：UDP 协议的通讯器
// ==========================================================================
// 开发日志：
// 日期         人员        说明
// --------------------------------------------------------------------------
// 2013.05.03   圣域天子    建立
//
// ==========================================================================
/// @file Udp.h UDP 协议的通讯器
// ==========================================================================
/// @file jsk_Udp.h UDP 协议的通讯器

#ifndef TIANCHI_TCUDP_H
#define TIANCHI_TCUDP_H

#include <tianchi/tcglobal.h>

#include <QtNetwork>

class TIANCHI_API TcUdp : public QUdpSocket
{
    Q_OBJECT
    typedef QUdpSocket inherited;
public:
    TcUdp();
    virtual ~TcUdp();

    int         start(int Port);
    void        stop();

    /// @brief 向指定的服务器和端口发送字符集
    bool        sendMessage(QHostAddress host, int port, QByteArray S);
    /// @brief 向指定的服务器和端口发送字符串
    inline bool sendMessage(QHostAddress host, int port, QString S)
                           { return sendMessage(host, port, S.toUtf8()); }
    /// @brief 向指定的端口发送广播字符集
    void        sendBroadcast(int port, QByteArray S);
    /// @brief 向指定的端口发送广播字符串
    inline void sendBroadcast(int port, QString S)
                             { return sendBroadcast(port, S.toUtf8()); }

    /// @brief 设置回调方法，优先于 signals 的接收方式
    inline void setRecvMethod(QObject* recvObject, QByteArray recvMethod)
                             { m_recvObject = recvObject; m_recvMethod = recvMethod; }

Q_SIGNALS:
    /// @brief 设置信号接收槽，只有回调方法未设置时才有效
    void recvMessage(QHostAddress client, QByteArray datagram);

protected slots:
    void udpRecv();

protected:
    QObject*    m_recvObject;
    QByteArray  m_recvMethod;
};

#endif // TIANCHI_TCUDP_H
