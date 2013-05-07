#include <tianchi/network/tcsingleinstance.h>

void TcSingleInstance::init(QObject* parent, QString instanceName)
{
    m_first = false;
    m_instanceName = instanceName;
    m_localSocket.connectToServer(instanceName);
    m_localServer = NULL;
    if ( m_localSocket.waitForConnected(500) )
    {
        m_localServer = NULL;
    }else
    {
        m_localServer = new QLocalServer(parent);
        if ( m_localServer->listen(instanceName) )
        {
            m_first = true;
        }
    }
}
