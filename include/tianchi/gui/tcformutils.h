#ifndef TIANCHI_TCFORMUTILS_H
#define TIANCHI_TCFORMUTILS_H

#include <tianchi/tcglobal.h>

#include <QWidget>

class TIANCHI_API TcFormUtils
{
public:
    TcFormUtils();

    inline QWidget* parentForm() const { return m_parentForm; }
    inline void     setParentForm(QWidget* value) { m_parentForm = value; }
private:
    QWidget*    m_parentForm;
};

#endif // TIANCHI_TCFORMUTILS_H
