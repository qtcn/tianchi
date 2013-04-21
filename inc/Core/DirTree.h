// ********************************************************************************************************************
// Tianchi share library for Qt (C++)
// ��ع���Դ���
// ��Ȩ���� (C) ��ع���Դ��⿪����
// ��ȨЭ�飺���Ķ���ع���Դ��⸽������ȨЭ��
// ********************************************************************************************************************
// �ĵ�˵�������Ը���Ŀ¼�����࣬Ҳ���Բ����ļ��������е��ļ�
// ====================================================================================================================
// ������־��
// ����         ��Ա                  ˵��
// --------------------------------------------------------------------------------------------------------------------
// 2013.04.21   cnhemiya@gmail.com    ����
//
// ====================================================================================================================
/// @file DirTree.h ���Ը���Ŀ¼�����࣬Ҳ���Բ����ļ��������е��ļ�
// ====================================================================================================================
#ifndef TIANCHI_DIRTREE_H
#define TIANCHI_DIRTREE_H

#include "Global.h"
#include <QObject>
#include <QStringList>

TIANCHI_BEGIN_NAMESPACE

QT_USE_NAMESPACE

class TIANCHI_API DirTree : public QObject
{
    Q_OBJECT

public:
	explicit DirTree(QObject *parent = 0);

	/**
	 * @brief �����ļ��������е��ļ�
	 * @param path Ҫ���ҵ��ļ���
	 * @param nameFilters �ļ�����
	 * @return �ҵ����ļ��б�
	 */
	QStringList findFiles(const QString &path, const QStringList &nameFilters = QStringList());

	/**
	 * @brief ����Ŀ¼�������е��ļ������ļ���
	 * @param fromPath Դ�ļ���
	 * @param toPath Ŀ���ļ���
	 * @param nameFilters �ļ�����
	 * @param overWrite �Ƿ񸲸�
	 * @return ���Ƶ��ļ�����
	 */
    int copyDirTree(const QString &fromPath, const QString &toPath,
					const QStringList &nameFilters = QStringList(), bool overWrite = true);

	/**
	 * @brief �����ļ��б����ļ���
	 * @param files Դ�ļ��б�
	 * @param toPath Ŀ���ļ���
	 * @param overWrite �Ƿ񸲸�
	 * @return ���Ƶ��ļ�����
	 */
    int copyFiles(const QStringList &files, const QString &toPath, bool overWrite = true);

	/**
	 * @brief ����m_copyFileCountΪ0
	 */
    void resetCopyFileCount();

Q_SIGNALS:
	/**
	 * @brief �źţ���ǰ���Ƶ��ļ��ļ������ļ���
	 * @param count �ڼ����ļ�
	 * @param name Դ�ļ���
	 */
	void currentFile(int count, const QString &name);
    
private:
	void doDirTree(const QString &fromPath, const QString &toPath,
				   const QStringList &nameFilters, bool overWrite,
				   QStringList &findFiles, bool isFind);
    QString formatPath(const QString &path);

    QString m_pathSymbol;    
    int m_copyFileCount;
};

TIANCHI_END_NAMESPACE

#endif // DIRTREE_H
