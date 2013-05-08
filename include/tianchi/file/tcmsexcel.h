// **************************************************************************
// Tianchi C++ library for Qt (open source)
// ��ع���Դ���
// ��Ȩ���� (C) ��ع���Դ��⿪����
// ��ȨЭ�飺���Ķ���ع���Դ��⸽������ȨЭ��
// **************************************************************************
// �ĵ�˵����ͨ�� OLE ��ʽ���� Microsoft Excel������ Windows ��ʹ�ã�Ҫ���Ѱ�
//           װ Excel��
// ==========================================================================
// ������־��
// ����         ��Ա        ˵��
// --------------------------------------------------------------------------
// 2013.04.10   ʥ������    ����
//
// ==========================================================================
/// @file MSExcel.h ͨ�� OLE ��ʽ���� Microsoft Excel������ Windows ��ʹ�ã�
//                  Ҫ���Ѱ�װ Excel��
// ==========================================================================
#ifndef TIANCHI_TCMSEXCEL_H
#define TIANCHI_TCMSEXCEL_H

#include <tianchi/tcglobal.h>

#include <QString>
#include <QStringList>
#include <QVariant>

class TcMSExcelPrivate;

/// @brief ͨ�� OLE ��ʽ���� Microsoft Excel
/// @note ͨ�� OLE ��ʽ���� Microsoft Excel
/// @warning ֻ���� Windows �£����Ѱ�װ�� Excel ʱ����ʹ��
/// @author ʥ������ Jonix@qtcn.org
/// @date 2013-04-10
class TIANCHI_API TcMSExcel
{
public:
    /// @brief ���췽��
    TcMSExcel();
    /// @brief ��������
    virtual ~TcMSExcel();

private:
    Q_DISABLE_COPY(TcMSExcel)
    Q_DECLARE_PRIVATE(TcMSExcel)
    TcMSExcelPrivate* const d_ptr;

public:
    /// @brief ���÷���ĳ���
    enum Alignment
    {
        xlTop    = -4160, ///< ����
        xlLeft   = -4131, ///< ����
        xlRight  = -4152, ///< ����
        xlCenter = -4108, ///< ����
        xlBottom = -4107  ///< ����
    };

    /// @brief ����һ��Microsoft Excel�ļ�
    bool create(const QString& filename = QString());
    /// @brief ��һ��Microsoft Excel�ļ�
    bool open(const QString& filename = QString());
    /// @brief ����Microsoft Excel�ļ�
    void save(const QString& filename = QString());
    /// @brief �ر�Microsoft Excel�ļ�
    void close();
    /// @brief �߳���ǰ�򿪵� Microsoft Excel<br>
    /// @brief �����˶���Ը� Excel �Ŀ���Ȩ<br>
    /// @brief Excel �ļ��Ա��ִ򿪣���ɥʧ�˿���Ȩ
    void kick();

    /// @brief ���õ�ǰ�򿪵� Excel �Ƿ�ɼ�
    void setVisible(bool value);
    /// @brief ���� Excel �ĵ��ı���
    void setCaption(const QString& value);

    /// @brief �½�һ�� Excel �ĵ�
    bool addBook();

    /// @brief ���ص�ǰ Excel �� Sheet ����
    int sheetCount();

    /// @brief ���ص�ǰ�򿪵� Excel ȫ�� Sheet ��
    QStringList sheetNames();

    /// @brief ���ص�ǰ Sheet.
    bool currentSheet();

    /// @brief ���ò�ָ����ǰ Sheet.
    /// @param [in] ��ǰ Sheet �������� 1 ��ʼ
    bool setCurrentSheet(int index);

    /// @brief ��ǰ�򿪵� Excel �� Sheet ��
    QString currentSheetName();

    /// @brief ��ȡ��Ԫ�� Sheet ������
    /// @param [in] row �кţ��� 1 ��ʼ
    /// @param [in] col �кţ��� 1 ��ʼ
    /// @return ����ָ����Ԫ�������
    QVariant read(int row, int col);

    /// @brief ��ȡ��Ԫ�� Sheet ������
    /// @param [in] row �кţ��� 1 ��ʼ
    /// @param [in] col �кţ��� 1 ��ʼ
    /// @return ����ָ����Ԫ�������
    inline QVariant cell(int row, int col) { return read(row, col); }

    /// @brief д�뵥Ԫ�� Sheet ������
    /// @param [in] row �кţ��� 1 ��ʼ
    /// @param [in] col �кţ��� 1 ��ʼ
    /// @param [in] value ׼��д�������
    void write(int row, int col, const QVariant& value);

    void cellFormat(int row, int col, const QString& format);
    void cellAlign(int row, int col, Alignment hAlign, Alignment vAlign);

    /// @brief ��ȡ��Ч������Ϣ
    /// @see rowStart() const
    /// @see rowEnd() const
    /// @see colStart() const
    /// @see colEnd() const
    bool usedRange(int& rowStart, int& colStart, int &rowEnd, int &colEnd);
};

#endif // TIANCHI_MSEXCEL_H
