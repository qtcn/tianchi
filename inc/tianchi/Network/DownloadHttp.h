// **************************************************************************
// Tianchi C++ library for Qt (open source)
// 天池共享源码库
// 版权所有 (C) 天池共享源码库开发组
// 授权协议：请阅读天池共享源码库附带的授权协议
// **************************************************************************
// 文档说明：HTTP 文件多线程下载器
// ==========================================================================
// 开发日志：
// 日期         人员        说明
// --------------------------------------------------------------------------
// 2013.04.19   圣域天子    建立
//
// ==========================================================================
/// @file DownloadHttp.h HTTP 文件多线程下载器
#ifndef TIANCHI_DOWNLOADHTTP_H
#define TIANCHI_DOWNLOADHTTP_H

#include <tianchi/Global.h>
#include <QtCore>
#include <QtNetwork>

namespace Tianchi
{
/// @brief 用于下载文件（或文件的一部分）
/// 注意：此类尚未进行严格测试
/// @author 来自互联网
/// @date 2013-04-19
class TIANCHI_API Download : public QObject
{
    Q_OBJECT
public:
    Download(int index, QObject *parent = 0);
    void StartDownload(const QUrl &url, QFile* file, 
            qint64 startPoint=0, qint64 endPoint=-1);

Q_SIGNALS:
    void DownloadFinished();

public Q_SLOTS:
    void FinishedSlot();
    void HttpReadyRead();

private:
    QNetworkAccessManager   m_Qnam;
    QNetworkReply*          m_Reply;
    QFile*                  m_File;

    const int   m_Index;
    qint64      m_HaveDoneBytes;
    qint64      m_StartPoint;
    qint64      m_EndPoint;

};

// 用于管理文件的下载
/// @brief 用于管理文件的下载
class TIANCHI_API DownloadList : public QObject
{
    Q_OBJECT
public:
    DownloadList(QObject *parent = 0);

    void StartFileDownload(const QString &url, int count);
    qint64 GetFileSize(QUrl url);

Q_SIGNALS:
    void FileDownloadFinished();

private Q_SLOTS:
    void SubPartFinished();

private:
    int m_DownloadCount;
    int m_FinishedNum;
    int m_FileSize;
    QUrl m_Url;
    QFile *m_File;
};
}
typedef ::Tianchi::Download     TcDownload;
typedef ::Tianchi::DownloadList TcDownloadList;

#endif // TIANCHI_DOWNLOADHTTP_H
