// **************************************************************************
// Tianchi C++ library for Qt (open source)
// ��ع���Դ���
// ��Ȩ���� (C) ��ع���Դ��⿪����
// ��ȨЭ�飺���Ķ���ع���Դ��⸽������ȨЭ��
// **************************************************************************
// �ĵ�˵����ͨ�� OLE ��ʽ���� Microsoft Excel������ Windows ��ʹ�ã�Ҫ����
//           ��װ Excel��
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


QT_BEGIN_NAMESPACE

class QAxObject;
class QAxWidget;
#ifdef QT_WIDGETS_LIB
class QTreeWidget;
#endif

QT_END_NAMESPACE

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
    QAxWidget*  m_excel;
    QAxObject*  m_books;
    QAxObject*  m_book;
    QAxObject*  m_sheets;
    QAxObject*  m_sheet;
    QString     m_filename;
    QString     m_sheetName;

    int m_rowStart;
    int m_colStart;
    int m_rowEnd;
    int m_colEnd;

public:
    /// @brief ���÷���ĳ���
    enum Alignment
    {
        xlTop    = -4160, ///< ����
        xlLeft   = -4131, ///< ����
        xlRight  = -4152, ///< ����
        xlCenter = -4108, ///< ����
        xlBottom = -4107, ///< ����
    };

    /// @brief ����һ��Microsoft Excel�ļ�
    bool create(const QString& filename="");
    /// @brief ��һ��Microsoft Excel�ļ�
    bool open(const QString& filename="");
    /// @brief ����Microsoft Excel�ļ�
    void save(const QString& filename="");
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
    QAxObject* addBook();

    /// @brief ���ص�ǰ Excel �� Sheet ����
    int sheetCount();

    /// @brief ���ò�ָ����ǰ Sheet.
    /// @param [in] ��ǰ Sheet �������� 1 ��ʼ
    QAxObject* sheet(int index);

    /// @brief ���ص�ǰ Sheet.
    QAxObject* currentSheet();

    /// @brief ��ȡ��Ԫ�� Sheet ������
    /// @param [in] row �кţ��� 1 ��ʼ
    /// @param [in] col �кţ��� 1 ��ʼ
    /// @return ����ָ����Ԫ�������
    QVariant read(int row, int col);

    /// @brief д�뵥Ԫ�� Sheet ������
    /// @param [in] row �кţ��� 1 ��ʼ
    /// @param [in] col �кţ��� 1 ��ʼ
    /// @param [in] value ׼��д�������
    void write(int row, int col, const QVariant& value);


    void        cellFormat(int row, int col, const QString& format);
    void        cellAlign(int row, int col, Alignment hAlign, Alignment vAlign);


    /// @brief ��ȡ��Ч������Ϣ
    /// @see rowStart() const
    /// @see rowEnd() const
    /// @see colStart() const
    /// @see colEnd() const
    bool usedRange();

    /// @brief ���ص�ǰ�򿪵� Excel ȫ�� Sheet ��
    QStringList sheetNames();
    /// @brief ��ǰ�򿪵� Excel �� Sheet ��
    QString sheetName() const { return m_sheetName; }

    /// @brief ��ǰ Sheet ��Ч����Ŀ�ʼ��
    /// @note ��Ҫ��ִ�� usedRange() ��ȡ��Ч������Ϣ����ܷ���
    /// @see sheetName() const
    inline int rowStart() const { return m_rowStart; }
    /// @brief ��ǰ Sheet ��Ч����Ľ�����
    /// @note ��Ҫ��ִ�� usedRange() ��ȡ��Ч������Ϣ����ܷ���
    /// @see sheetName() const
    inline int rowEnd() const { return m_rowEnd; }
    /// @brief ��ǰ Sheet ��Ч����Ŀ�ʼ��
    /// @note ��Ҫ��ִ�� usedRange() ��ȡ��Ч������Ϣ����ܷ���
    /// @see sheetName() const
    inline int colStart() const { return m_colStart; }
    /// @brief ��ǰ Sheet ��Ч����Ľ�����
    /// @note ��Ҫ��ִ�� usedRange() ��ȡ��Ч������Ϣ����ܷ���
    /// @see sheetName() const
    inline int colEnd() const { return m_colEnd; }

#ifdef QT_WIDGETS_LIB
    /// @brief �� QTreeWidget �����ݣ�ֱ������� Excel ��
    /// @author ʥ������ Jonix@qtcn.org
    class TIANCHI_API Exporter
    {
    public:
        /// @brief ���캯��
        /// @param [in] view ��Ҫ������ QTreeWidget ����
        /// @param [in] mode 0:����ȫ��<br> 1:����ѡ�е���
        /// @param [in] excel Excel ����ʵ��
        /// @param [in] row ������ Excel �Ŀ�ʼ��
        /// @param [in] col ������ Excel �Ŀ�ʼ��
        Exporter(QTreeWidget* view, int mode, TcMSExcel* excel, int row=1, int col=1);

        /// @brief ���õ���ģʽ
        /// @param [in] mode 0:����ȫ��<br> 1:����ѡ�е���
        void setMode(int mode) { m_mode = mode; }
        /// @brief ���õ����� Excel �Ŀ�ʼ�кͿ�ʼ��
        void setStart(int row, int col) { m_row = row; m_col = col; }
        /// @brief ���� Excel �Ķ���ʵ��
        void setExcel(TcMSExcel* excel) { m_excel = excel; }

        /// @brief ִ�е�������
        int  exec();

    private:
        QTreeWidget*        m_view;
        int                 m_mode;
        TcMSExcel*   m_excel;
        int                 m_row;
        int                 m_col;

        QStringList     formats;
        QStringList     cellTypes;
    };
#endif
};

#endif // TIANCHI_MSEXCEL_H
