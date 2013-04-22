// ********************************************************************************************************************
// Tianchi C++ library for Qt (open source)
// ��ع���Դ���
// ��Ȩ���� (C) ��ع���Դ��⿪����
// ��ȨЭ�飺���Ķ���ع���Դ��⸽������ȨЭ��
// ********************************************************************************************************************
// �ĵ�˵����Ӧ�ó���ʵ����
//          ʹ���� QLocalSocket / QLocalServer ��ʽʵ�֣�Ϊ���ض�ʵ��Ӧ�ü�ͨѶ������չ�Ŀ��ܡ�
// ====================================================================================================================
// ������־��
// ����         ��Ա        ˵��
// --------------------------------------------------------------------------------------------------------------------
// 2013.04.19   ʥ������    ����
//
// ====================================================================================================================
/// @file SingleInstance.h Ӧ�ó���ʵ����
// ====================================================================================================================
#ifndef TIANCHI_SINGLEINSTANCE_H
#define TIANCHI_SINGLEINSTANCE_H

#include "Global.h"

#include <QLocalSocket>
#include <QLocalServer>

TIANCHI_BEGIN_NAMESPACE

/// @brief Ӧ�ó���ʵ����
/// @par ʾ��:
/// @code
/// #include "Network/SingleInstance.h"
///
/// int main(int argc, char *argv[])
/// {
///     QApplication app(argc, argv);
///
///     TIANCHI::SingleInstance si(app, "myApp");
///
///     if ( si.first() )
///     {
///         // �״�����
///     }else
///     {
///         // �Ѵ�������ʵ��
///     }
///     ...
/// }
/// @endcode
/// @author ʥ������ Jonix@qtcn.org
/// @date 2013-04-19
class TIANCHI_API SingleInstance
{
public:
    /// @brief ��ʼ������
    /// @param [in] instanceName ʶ���Ƿ��ظ�������ʵ������
    SingleInstance(QString instanceName)
    {
        init(0, instanceName);
    }
    /// @brief ��ʼ������
    /// @param [in] parent app����
    /// @param [in] instanceName ʶ���Ƿ��ظ�������ʵ������
    SingleInstance(QObject* parent, QString instanceName)
    {
        init(parent, instanceName);
    }
    /// @brief �Ƿ��״����е�ʵ��
    /// @return true: �״����е�ʵ��
    bool first() const { return m_first; }

protected:
    bool            m_first;        ///< �״�����ʵ��
    QString         m_instanceName; ///< ʵ������
    QLocalSocket    m_localSocket;  ///< ��� socket ���
    QLocalServer*   m_localServer;  ///< �ܷ� socket ���

private:
    void init(QObject* parent, QString instanceName);
};

TIANCHI_END_NAMESPACE

#endif // TIANCHI_SINGLEINSTANCE_H
