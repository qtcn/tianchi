// **************************************************************************
// Tianchi C++ library for Qt (open source)
// ��ع���Դ���
// ��Ȩ���� (C) ��ع���Դ��⿪����
// ��ȨЭ�飺���Ķ���ع���Դ��⸽������ȨЭ��
// **************************************************************************
// �ĵ�˵����QTreeWidget �ؼ���չ
// ==========================================================================
// ������־��
// ����         ��Ա        ˵��
// --------------------------------------------------------------------------
// 2013.05.03   ʥ������    ����
//
// ==========================================================================
/// @file TreeEx.h QTreeWidget �ؼ���չ
// ==========================================================================
#ifndef TIANCHI_TCTREEEX_H
#define TIANCHI_TCTREEEX_H

#include <tianchi/tcglobal.h>
#include <tianchi/file/tcmsexcel.h>

#include <QTreeWidget>
#include <QLabel>
#include <QDoubleSpinBox>

class TcTreeExPrivate;

/// @brief �� QTreeWidget ����չ���ܣ���ֱ�ӵ����� Excel ��
/// @author ʥ������ Jonix@qtcn.org
class TIANCHI_API TcTreeEx
{
public:
    enum ExportType
    {
        TextFile = 1
      , MSExcel  = 2
    };
    /// @brief ���캯��
    /// @param [in] view ��Ҫ������ QTreeWidget ����
    TcTreeEx(QTreeWidget* widget=0);

    /// @brief ���õ���ģʽ
    /// @param [in] widget ��Ҫ������ QTreeWidget ����
    void setWidget(QTreeWidget* widget);

    /// @brief ���õ���ģʽ
    /// @param [in] type ��Ҫ����������(enum ExportType)
    void setExportType(int type);

    /// @brief ���õ���ģʽ
    /// @param [in] state 0 ȫ��, 1 ѡ��
    void setSelectedState(int state);

    /// @brief ���õ������ı��ļ���
    /// @param [in] filename �������ı��ļ���
    void setTextFileName(const QString& filename);

    /// @brief ���� Excel �Ķ���ʵ��<br>
    /// ʹ�ô˷����󵼳�ģʽ�Զ�����Ϊ MSExcel
    void setMSExcelObject(TcMSExcel* excel, bool hasHeader=true, int startRow=1, int startCol=1);

    /// @brief ִ�е�������
    int  save();

private:
    Q_DISABLE_COPY(TcTreeEx)
    Q_DECLARE_PRIVATE(TcTreeEx)
    TcTreeExPrivate*   d_ptr;

public:
    static void createColumnMenu(QTreeWidget* widget, QWidget* object, const QString& methodName);

    static void setColumnBolds(QTreeWidget* widget);
    static void setColumnWidth(QTreeWidget* widget, int column, int width, bool hide=false);
    static void setColumnStyle(QTreeWidget* widget, int fontSize=8, const QString &fontName="Tahoma");

    static void CopyCellObject(QTreeWidget* view, int copyMode);
};

class TIANCHI_API TcTreeItem : public QTreeWidgetItem
{
public:
    void setCellFont(int col, bool bold=false, int alignment=Qt::AlignVCenter | Qt::AlignLeft);
    void setCellStyle(int startCol=-1, int endCol=-1,
                      bool bold=true, int alignment=Qt::AlignVCenter | Qt::AlignRight,
                      int cellHeight=25);
    void setCellColor(int col, QColor color);

    QLabel*         createLabel(int col, const QString& htmlText, const QVariant& data=QVariant());
    QDoubleSpinBox* createDoubleSpinBox(int col,
                                        int decimals, double min, double max, double step, double value);
    double          readDoubleSpinBoxValue(int col);

    void showValue(int column, const char* text, const QVariant& data=QVariant(), int size=0);
    void showValue(int column, const QString& text, const QVariant& data=QVariant(), int size=0);
    void showValue(int column, const QByteArray& text, const QVariant& data=QVariant(), int size=0);
    void showValue(int column, double value);
    void showValue(int column, double value, int digits);
    void showPrice(int column, double value, int digits=0);
    void showPercent(int column, double value=0.0, int digits=0);
};

#endif // TIANCHI_TCTREEEX_H
