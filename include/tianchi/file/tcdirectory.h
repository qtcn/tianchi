// **************************************************************************
// Tianchi share library for Qt (C++)
// ��ع���Դ���
// ��Ȩ���� (C) ��ع���Դ��⿪����
// ��ȨЭ�飺���Ķ���ع���Դ��⸽������ȨЭ��
// **************************************************************************
// �ĵ�˵�������Ը���Ŀ¼�����࣬Ҳ���Բ����ļ��������е��ļ�
// ==========================================================================
// ������־��
// ����         ��Ա                  ˵��
// --------------------------------------------------------------------------
// 2013.04.21   cnhemiya@gmail.com    ����
//
// ==========================================================================
/// @file Directory.h ���Ը���Ŀ¼�����࣬Ҳ���Բ����ļ��������е��ļ�
// ==========================================================================
#ifndef TIANCHI_TCDIRECTORY_H
#define TIANCHI_TCDIRECTORY_H

#include <tianchi/tcglobal.h>

#include <QObject>
#include <QStringList>

/// @author �Ϲ��� cnhemiya@gmail.com
/// @date 2013-04-21
class TIANCHI_API TcDirectory : public QObject
{
    Q_OBJECT
public:
    explicit TcDirectory(QObject *parent = 0);

    /// @brief �����ļ��������е��ļ�
    /// @param path Ҫ���ҵ��ļ���
    /// @param nameFilters �ļ�����
    /// @return �ҵ����ļ��б�
    QStringList findFiles(const QString &path, 
            const QStringList &nameFilters = QStringList());

    /// @brief ����Ŀ¼�������е��ļ������ļ���
    /// @param fromPath Դ�ļ���
    /// @param toPath Ŀ���ļ���
    /// @param nameFilters �ļ�����
    /// @param overWrite �Ƿ񸲸�
    /// @return ���Ƶ��ļ�����
    int copyDirectories(const QString &fromPath, const QString &toPath,
                        const QStringList &nameFilters = QStringList(), 
                        bool overWrite = true);

    /// @brief �����ļ��б����ļ���
    /// @param files Դ�ļ��б�
    /// @param toPath Ŀ���ļ���
    /// @param overWrite �Ƿ񸲸�
    /// @return ���Ƶ��ļ�����
    int copyFiles(const QStringList &files, const QString &toPath, 
            bool overWrite = true);

    /// @brief ����m_copyFileCountΪ0
    void resetCopyFileCount();

Q_SIGNALS:
    /// @brief �źţ���ǰ���Ƶ��ļ��ļ������ļ���
    /// @param count �ڼ����ļ�
    /// @param name Դ�ļ���
    void currentFile(int count, const QString &name);

private:
    int m_copyFileCount;

    void doDirTree(const QString &fromPath, const QString &toPath,
                   const QStringList &nameFilters, bool overWrite,
                   QStringList &findFiles, bool isFind);
    QString formatPath(const QString &path);
};

#endif // TIANCHI_DIRECTORY_H
