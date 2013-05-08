// **************************************************************************
// Tianchi C++ library for Qt (open source)
// ��ع���Դ���
// ��Ȩ���� (C) ��ع���Դ��⿪����
// ��ȨЭ�飺���Ķ���ع���Դ��⸽������ȨЭ��
// **************************************************************************
// �ĵ�˵����UDP Э���ͨѶ��
// ==========================================================================
// ������־��
// ����         ��Ա        ˵��
// --------------------------------------------------------------------------
// 2013.05.03   ʥ������    ����
//
// ==========================================================================
/// @file Udp.h UDP Э���ͨѶ��
// ==========================================================================
/// @file jsk_Udp.h UDP Э���ͨѶ��

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

    /// @brief ��ָ���ķ������Ͷ˿ڷ����ַ���
    bool        sendMessage(QHostAddress host, int port, QByteArray S);
    /// @brief ��ָ���ķ������Ͷ˿ڷ����ַ���
    inline bool sendMessage(QHostAddress host, int port, QString S)
                           { return sendMessage(host, port, S.toUtf8()); }
    /// @brief ��ָ���Ķ˿ڷ��͹㲥�ַ���
    void        sendBroadcast(int port, QByteArray S);
    /// @brief ��ָ���Ķ˿ڷ��͹㲥�ַ���
    inline void sendBroadcast(int port, QString S)
                             { return sendBroadcast(port, S.toUtf8()); }

    /// @brief ���ûص������������� signals �Ľ��շ�ʽ
    inline void setRecvMethod(QObject* recvObject, QByteArray recvMethod)
                             { m_recvObject = recvObject; m_recvMethod = recvMethod; }

Q_SIGNALS:
    /// @brief �����źŽ��ղۣ�ֻ�лص�����δ����ʱ����Ч
    void recvMessage(QHostAddress client, QByteArray datagram);

protected slots:
    void udpRecv();

protected:
    QObject*    m_recvObject;
    QByteArray  m_recvMethod;
};

#endif // TIANCHI_TCUDP_H
