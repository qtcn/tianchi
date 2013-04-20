#include <Network/DownloadHttp.h>

TIANCHI_BEGIN_NAMESPACE

Download::Download(int index, QObject *parent)
    : QObject(parent), m_Index(index)
{
    m_HaveDoneBytes = 0;
    m_StartPoint = 0;
    m_EndPoint = 0;
    m_File = NULL;
}

void Download::StartDownload(const QUrl &url,
                             QFile *file,
                             qint64 startPoint/* =0 */,
                             qint64 endPoint/* =-1 */)
{
    if( NULL == file )
        return;

    m_HaveDoneBytes = 0;
    m_StartPoint = startPoint;
    m_EndPoint = endPoint;
    m_File = file;

    //根据HTTP协议，写入RANGE头部，说明请求文件的范围
    QNetworkRequest qheader;
    qheader.setUrl(url);
    QString range;
    range.sprintf("Bytes=%lld-%lld", m_StartPoint, m_EndPoint);
    qheader.setRawHeader("Range", range.toLocal8Bit());

    //开始下载
    m_Reply = m_Qnam.get(QNetworkRequest(qheader));
    connect(m_Reply, SIGNAL(finished()), this, SLOT(FinishedSlot()));
    connect(m_Reply, SIGNAL(readyRead()), this, SLOT(HttpReadyRead()));
}

//下载结束
void Download::FinishedSlot()
{
    m_File->flush();
    m_Reply->deleteLater();
    m_Reply = 0;
    m_File = 0;
    qDebug() << "Part " << m_Index << " download finished";
    emit DownloadFinished();
}

void Download::HttpReadyRead()
{
    if ( !m_File )
        return;

    //将读到的信息写入文件
    QByteArray buffer = m_Reply->readAll();
    m_File->seek( m_StartPoint + m_HaveDoneBytes );
    m_File->write(buffer);
    m_HaveDoneBytes += buffer.size();
}

//用阻塞的方式获取下载文件的长度
qint64 DownloadList::GetFileSize(QUrl url)
{
    QNetworkAccessManager manager;
    //qDebug() << "Getting the file size...";
    QEventLoop loop;
    //发出请求，获取目标地址的头部信息
    QNetworkReply *reply = manager.head(QNetworkRequest(url));
    QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()), Qt::DirectConnection);
    loop.exec();
    QVariant var = reply->header(QNetworkRequest::ContentLengthHeader);
    reply->deleteLater();
    qint64 size = var.toLongLong();
    //qDebug() << "The file size is: " << size;
    return size;
}

DownloadList::DownloadList(QObject *parent)
: QObject(parent)
{
    m_DownloadCount = 0;
    m_FinishedNum = 0;
    m_FileSize = 0;
    m_File = new QFile;
}

void DownloadList::StartFileDownload(const QString &url, int count)
{
    m_DownloadCount = count;
    m_FinishedNum = 0;
    m_Url = QUrl(url);
    m_FileSize = GetFileSize(m_Url);
    //先获得文件的名字
    QFileInfo fileInfo(m_Url.path());
    QString fileName = fileInfo.fileName();
    if (fileName.isEmpty())
        fileName = "index.html";

    m_File->setFileName(fileName);
    //打开文件
    m_File->open(QIODevice::WriteOnly);
    Download *tempDownload;

    //将文件分成PointCount段，用异步的方式下载
    //qDebug() << "Start download file from " << strUrl;
    for(int i=0; i<m_DownloadCount; i++)
    {
        //先算出每段的开头和结尾（HTTP协议所需要的信息）
        int start = m_FileSize * i / m_DownloadCount;
        int end = m_FileSize * (i+1) / m_DownloadCount;
        if( i != 0 )
            start--;

        //分段下载该文件
        tempDownload = new Download(i+1, this);
        connect(tempDownload, SIGNAL(DownloadFinished()), this, SLOT(SubPartFinished()));
        connect(tempDownload, SIGNAL(DownloadFinished()), tempDownload, SLOT(deleteLater()));
        tempDownload->StartDownload(m_Url, m_File, start, end);
    }
}

void DownloadList::SubPartFinished()
{
    m_FinishedNum++;
    //如果完成数等于文件段数，则说明文件下载完毕，关闭文件，发生信号
    if( m_FinishedNum == m_DownloadCount )
    {
        m_File->close();
        emit FileDownloadFinished();
        //qDebug() << "Download finished";
    }
}


#include "moc_DownloadHttp.cpp"
/*
#include "main.moc"

int main(int argc, char **argv)
{
    QCoreApplication app(argc, argv);
    //用阻塞的方式下载文件，完成后退出
    DownloadList *control = new DownloadList();
    QEventLoop loop;
    QObject::connect(control, SIGNAL(FileDownloadFinished()),
        &loop, SLOT(quit()));
    control->StartFileDownload(strUrl, PointCount);
    loop.exec();
    control->deleteLater();
    return 0;
}
*/

TIANCHI_END_NAMESPACE
