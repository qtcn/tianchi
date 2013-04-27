// **************************************************************************
// Tianchi C++ library for Qt (open source)
// ��ع���Դ���
// ��Ȩ���� (C) ��ع���Դ��⿪����
// ��ȨЭ�飺���Ķ���ع���Դ��⸽������ȨЭ��
// **************************************************************************
// �ĵ�˵�����򵥵� Log �����
// ==========================================================================
// ������־��
// ����         ��Ա        ˵��
// --------------------------------------------------------------------------
// 2013.04.10   ʥ������    ����
//
// ==========================================================================
/// @file LogTiny.h �򵥵� Log �����
// ==========================================================================
#ifndef TIANCHI_LOGTINY_H
#define TIANCHI_LOGTINY_H

#include <tianchi/Global.h>

#include <QString>

namespace Tianchi 
{
/// @brief �򵥵��ı��ļ������־��
/// @author ʥ������ Jonix@qtcn.org
/// @date 2013-04-10
class TIANCHI_API LogTiny
{
public:
    /// @brief ָ��ȫ·����ִ���ļ������Զ�������ִ���ļ�ͬĿ¼��ͬ�����Һ�׺Ϊ .log ����־�ļ���
    /// @param [in] AppFile ִ���ļ�����
    /// @par ʾ��:
    /// @code
    /// QApplication app(argc, argv);
    ///
    /// LogTiny log;
    ///
    /// // �����ִ���ļ�����Ϊ����
    /// log.setAppFile(app.applicationFilePath());
    /// @endcode
    /// @see setLogFile
    void setAppFile(const QString& AppFile);

    /// @brief ָ��ȫ·������־�ļ�����
    /// @param [in] LogFile ��־�ļ�����
    /// @par ʾ��:
    /// @code
    /// log.setLogFile("C:\\Temp\\app.log");
    /// @endcode
    /// @see setAppFile
    void setLogFile(const QString& LogFile);

    /// @brief д��־
    /// @param [in] S ��־���ݡ�
    /// @param [in] SourceName Դ�ļ�����������__FILE__��Ϊ������
    /// @param [in] SourceLine Դ�ļ��У�������__LINE__��Ϊ������
    void write(const QString& S, const QString& SourceName="", int SourceLine=0);

    /// @brief ����ģʽ(Debug)�������־���� Release ģʽ��û�����á�
    /// @param [in] S ��־���ݡ�
    /// @param [in] SourceName Դ�ļ�����������__FILE__��Ϊ������
    /// @param [in] SourceLine Դ�ļ��У�������__LINE__��Ϊ������
    inline void debug(const QString& S, const QString& SourceName="", int SourceLine=0)
    {
      #ifdef _DEBUG
        write(S, SourceName, SourceLine);
      #endif
    }

private:
    QString m_FileName;
};
}

/// @brief ����־������������ļ����кţ���������ʱ����ִ�в��衣
#define Log_Step ::Tianchi::Log.write("<<STEP>>", __FILE__, __LINE__);

/// @brief ����ģʽ�������־���Զ���Ӵ��������ļ����кš�
#ifdef _DEBUG
    #define Debug_Log(s)   ::Tianchi::Log.write(s, __FILE__, __LINE__);
#else
    #define Debug_Log(s)
#endif

typedef ::Tianchi::LogTiny TcLogTiny;

#endif // TIANCHI_LOGTINY_H
