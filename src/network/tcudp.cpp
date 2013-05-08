#include <tianchi/network/tcudp.h>

#include <QByteArray>

TcUdp::TcUdp()
    : QUdpSocket()
{
    m_recvObject = NULL;
}

TcUdp::~TcUdp()
{
    close();
}

int TcUdp::start(int Port)
{
    close();
    if ( bind(Port, QUdpSocket::ShareAddress) )
    {
        connect(this, SIGNAL(readyRead()), this, SLOT(udpRecv()));
    }
    return isValid() ? this->localPort() : 0;
}

void TcUdp::udpRecv()
{
    while( hasPendingDatagrams() )
    {
        QByteArray datagram;
        datagram.resize(pendingDatagramSize());
        QHostAddress client;
        readDatagram(datagram.data(), datagram.size(), &client);

        if ( m_recvObject != NULL
          && m_recvObject->metaObject()->invokeMethod(m_recvObject, m_recvMethod.data(),
                                                      Q_ARG(TcUdp*, this),
                                                      Q_ARG(QHostAddress, client),
                                                      Q_ARG(QByteArray, datagram)) )
        {
        }else
        {
            Q_EMIT recvMessage(client, datagram);
        }
    }
}

bool TcUdp::sendMessage(QHostAddress host, int port, QByteArray S)
{
    qint64 len = S.size();
    return writeDatagram(S.constData(), S.size(), host, port) == len;
}

void TcUdp::sendBroadcast(int port, QByteArray S)
{
    writeDatagram(S, QHostAddress::Broadcast, port);
}

