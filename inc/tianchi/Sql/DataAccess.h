#ifndef TIANCHI_SQL_CTADATAACCESS_H
#define TIANCHI_SQL_CTADATAACCESS_H

#include <tianchi/Global.h>

#include <QString>
#include <QLatin1String>
#include <QVariant>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlDatabase>
#include <QVariantMap>
#include <QStringList>
#include <QVariantList>

namespace Tianchi
{
class DataAccess;

// ���ݷ��������
class TIANCHI_API DataAccessStatement
{
public:
    DataAccessStatement();
    // ʹ�ñ���table���ֶ��б�fields��ʼ��
    DataAccessStatement(const QString &table, 
            const QString &fields = QString("*"));
    ~DataAccessStatement();

    // ��������趨
    void clear();

    // ����ֶ��б�fields
    DataAccessStatement& select(const QString &fields = QString("*"));

    // ���from����tables
    DataAccessStatement& from(const QString &tables);

    // ���������ӱ�table, condΪ����,bindΪ�����е�"?"ֵ
    DataAccessStatement& leftJoin(const QString &table, 
            const QString &cond,
            const QVariantList &bind = QVariantList());

    // ���������Ӿ�expr(AND����), bindΪ�����е�"?"ֵ
    DataAccessStatement& where(const QString &expr, 
            const QVariantList &bind = QVariantList());

    // ���������Ӿ�expr(OR����), bindΪ�����е�"?"ֵ
    DataAccessStatement& orWhere(const QString &expr, 
            const QVariantList &bind = QVariantList());

    // ����group�ֶ�fields
    DataAccessStatement& group(const QString &fields);
    
    // ����order�ֶ�fields
    DataAccessStatement& order(const QString &fields);

    // ����limit����
    DataAccessStatement& limit(int count, int offset = 0);

    // ����limit����
    DataAccessStatement& limitPage(int page, int rowCount);

    // ����������SQL���
    QString toString() const;

    // ����WHERE�Ӿ�
    QString whereString() const;

    // ����WHERE��"?"��bind
    QVariantList whereBind() const;

    // ��������"?"��bind
    QVariantList bind() const;
private:
    QStringList _select;
    QStringList _from;
    QStringList _leftJoin;
    QStringList _where;
    QStringList _group;
    QStringList _order;

    QString _limit;
    QVariantList _leftJoinBind;
    QVariantList _whereBind;
};


// ���ݷ�����
class TIANCHI_API DataAccess
{
public:
    DataAccess(const QString &connectionName 
            = QLatin1String(QSqlDatabase::defaultConnection));
    ~DataAccess();
    // ����һ��DataAccess�����������ʧ�ܣ�����NULL,ʹ�������delete
    static DataAccess* db(const QString &connectionName 
            = QLatin1String(QSqlDatabase::defaultConnection));

    // ����sql��ѯ�����м�¼��
    QList<QVariantMap> fetchAll(const QString &sql,
            const QVariantList &bind = QVariantList());
    QList<QVariantMap> fetchAll(const DataAccessStatement &stat,
            const QVariantList &bind = QVariantList());

    // ����sql��ѯ�ĵ�һ��
    QVariantMap fetchRow(const QString &sql,
            const QVariantList &bind = QVariantList());
    QVariantMap fetchRow(const DataAccessStatement &stat,
            const QVariantList &bind = QVariantList());

    // ����sql��ѯ�ĵ�һ��
    QVariantList fetchCol(const QString &sql,
            const QVariantList &bind = QVariantList());
    QVariantList fetchCol(const DataAccessStatement &stat,
            const QVariantList &bind = QVariantList());

    // ���ص�һ�е�һ������
    QVariant fetchOne(const QString &sql,
            const QVariantList &bind = QVariantList());
    QVariant fetchOne(const DataAccessStatement &stat,
            const QVariantList &bind = QVariantList());

    // ����һ����Ϊkey,���ڶ�����Ϊֵ����
    template <typename T> QMap<T, QVariant> fetchPairs(
                const QString &sql,
                const QVariantList &bind = QVariantList())
    {
        QSqlQuery *q = _prepareExec(sql, bind);

        QMap<T,QVariant> rows;
        QVariant val;
        while (q->next())
        {
            val = q->value(0);
            if (val.type() == QVariant::String)
            {
                val = val.toString().trimmed();
            }
            rows[qvariant_cast<T>(val)] = q->value(1);
        }
        delete q;
        return rows;
    }

    template <typename T> QMap<T, QVariant> fetchPairs(
                const DataAccessStatement &stat,
                const QVariantList &bind = QVariantList())
    {
        return fetchPairs<T>(stat.toString(),
                QVariantList() << stat.bind() << bind);
    }

    // ����һ����Ϊ������ÿ����Ϊֵ����
    template <typename T> QMap<T, QVariantMap> fetchAssoc(
                const QString &sql, 
                const QVariantList &bind = QVariantList())
    {
        QSqlQuery *q = _prepareExec(sql, bind);

        QMap<T,QVariantMap> rows;
        QVariantMap row;
        QVariant val;
        while (q->next())
        {
            QSqlRecord rec = q->record();
            for (int i = rec.count() - 1; i > -1; i--)
            {
                row[rec.fieldName(i)] = rec.value(i);
            }
            val = rec.value(0);
            if (val.type() == QVariant::String)
            {
                val = val.toString().trimmed();
            }
            rows[qvariant_cast<T>(val)] = row;
            row.clear();
        }
        delete q;
        return rows;
    }

    template <typename T> QMap<T, QVariantMap> fetchAssoc(
                const DataAccessStatement &stat, 
                const QVariantList &bind = QVariantList())
    {
        return fetchAssoc<T>(stat.toString(),
                QVariantList() << stat.bind() << bind);
    }

    // Ϊsql������limit����,Ŀǰֻ֧��LIMIT OFFSET���
    QString limitPage(const QString &sql, int page, int rowCount);
    QString limit(const QString &sql, int count, int offset = 0);

    // �����ϴβ����ID,Ŀǰ��ʵ��������
    QVariant lastInsertId(const QString &table, const QString &primaryKey);

    // ɾ����table�еļ�¼,����Ϊwhere, bindΪ"?"��
    int doDelete(const QString &table, 
            const QString &where = QString(),
            const QVariantList &bind = QVariantList());


    // ���±�table�еļ�¼,�ֶμ�ֵΪfield, ����Ϊwhere, bindΪ"?"��
    int doUpdate(const QString &table, const QVariantMap &field,
            const QString &where = QString(),
            const QVariantList &bind = QVariantList());

    // �����table�еļ�¼,�ֶμ�ֵΪfield
    int doInsert(const QString &table, const QVariantMap &field);
private:
    QSqlDatabase *_db;
    QSqlQuery* _prepareExec(const QString &sql, const QVariantList &bind);
    QVariant _lastInsertId;
};

typedef DataAccess DA;
typedef DataAccessStatement DAS;
}
typedef ::Tianchi::DataAccess TcDA;
typedef ::Tianchi::DataAccessStatement TcDAS;

#endif
