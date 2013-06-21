#ifndef TIANCHI_TCDATAACCESS_H
#define TIANCHI_TCDATAACCESS_H

#include <tianchi/tcglobal.h>

#include <QString>
#include <QLatin1String>
#include <QVariant>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlDatabase>
#include <QVariantMap>
#include <QStringList>
#include <QVariantList>

class TcDataAccess;

// ���ݷ��������
class TIANCHI_API TcDataAccessStatement
{
public:
    TcDataAccessStatement();
    TcDataAccessStatement(const TcDataAccessStatement &da);
    // ʹ�ñ���table���ֶ��б�fields��ʼ��
    TcDataAccessStatement(const QString &table, 
            const QString &fields = QString("*"));
    ~TcDataAccessStatement();

    // ��������趨
    void clear();

    // ����ֶ��б�fields
    TcDataAccessStatement& select(const QString &fields = QString("*"));

    // ���from����tables
    TcDataAccessStatement& from(const QString &tables);

    // ���������ӱ�table, condΪ����,bindΪ�����е�"?"ֵ
    TcDataAccessStatement& leftJoin(const QString &table, 
            const QString &cond,
            const QVariantList &bind = QVariantList());

    // ���������Ӿ�expr(AND����), bindΪ�����е�"?"ֵ
    TcDataAccessStatement& where(const QString &expr, 
            const QVariantList &bind = QVariantList());

    // ���������Ӿ�expr(OR����), bindΪ�����е�"?"ֵ
    TcDataAccessStatement& orWhere(const QString &expr, 
            const QVariantList &bind = QVariantList());

    // ����group�ֶ�fields
    TcDataAccessStatement& group(const QString &fields);
    
    // ����order�ֶ�fields
    TcDataAccessStatement& order(const QString &fields);

    // ����limit����
    TcDataAccessStatement& limit(int count, int offset = 0);

    // ����limit����
    TcDataAccessStatement& limitPage(int page, int rowCount);

    // ����������SQL���
    QString toString() const;

    // ����WHERE�Ӿ�
    QString whereString() const;

    // ����WHERE��"?"��bind
    QVariantList whereBind() const;

    // ��������"?"��bind
    QVariantList bind() const;

    TcDataAccessStatement& operator=(const TcDataAccessStatement &da);
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
class TIANCHI_API TcDataAccess
{
public:
    enum AttrCase
    {
        CaseNatural,    // �ֶ������治��
        CaseLower,      // �ֶ���תΪСд
        CaseUpper       // �ֶ���תΪ��д
    };

    enum AttrTrim
    {
        TrimNone,       // �����ַ��������ֶ�ֵ����
        TrimAll         // �����ַ��������ֶ�ֵȥ��ǰ��ո�
    };

    TcDataAccess(const QString &connectionName 
            = QLatin1String(QSqlDatabase::defaultConnection));
    TcDataAccess(const QSqlDatabase &other);
    ~TcDataAccess();

    // �����ֶ�������ʽ
    static AttrCase attrCase() {return _attrCase;}
    // �����ַ��������ֶ�ֵ����ʽ
    static AttrTrim attrTrim() {return _attrTrim;}
    // �����ֶ�������ʽ
    static void setAttrCase(AttrCase attrCase){_attrCase = attrCase;}
    // �����ַ��������ֶ�ֵ����ʽ
    static void setAttrTrim(AttrTrim attrTrim){_attrTrim = attrTrim;}

    // ����һ��DataAccess�����������ʧ�ܣ�����NULL,ʹ�������delete
    static TcDataAccess* db(const QString &connectionName 
            = QLatin1String(QSqlDatabase::defaultConnection));

    // ����connectionName
    QString connectionName() const {return _db->connectionName();}

    // ����QSqlQuery����
    QSqlQuery sqlQuery() const {return QSqlQuery(*_db);}
    // ����QSqlDatabase����
    QSqlDatabase sqlDatabase() const {return *_db;}

    // ����sql��ѯ�����м�¼��
    QList<QVariantMap> fetchAll(const QString &sql,
            const QVariantList &bind = QVariantList());
    QList<QVariantMap> fetchAll(const TcDataAccessStatement &stat,
            const QVariantList &bind = QVariantList());

    // ����SQL��ѯ�����м�¼����
    // ����м�¼�����һ�б����ֶ�������¼�ӵڶ��п�ʼ
    QList<QVariantList> fetchAllList(const QString &sql,
            const QVariantList &bind = QVariantList());
    QList<QVariantList> fetchAllList(const TcDataAccessStatement &stat,
            const QVariantList &bind = QVariantList());


    // ����sql��ѯ�ĵ�һ��
    QVariantMap fetchRow(const QString &sql,
            const QVariantList &bind = QVariantList());
    QVariantMap fetchRow(const TcDataAccessStatement &stat,
            const QVariantList &bind = QVariantList());


    // ����sql��ѯ�ĵ�һ��
    QVariantList fetchCol(const QString &sql,
            const QVariantList &bind = QVariantList());
    QVariantList fetchCol(const TcDataAccessStatement &stat,
            const QVariantList &bind = QVariantList());

    // ���ص�һ�е�һ������
    QVariant fetchOne(const QString &sql,
            const QVariantList &bind = QVariantList());
    QVariant fetchOne(const TcDataAccessStatement &stat,
            const QVariantList &bind = QVariantList());

    // ����һ����Ϊkey,���ڶ�����Ϊֵ����
    template <typename T> QMap<T, QVariant> fetchPairs(
                const QString &sql,
                const QVariantList &bind = QVariantList())
    {
        _prepareExec(sql, bind);

        QMap<T,QVariant> rows;
        while (_query->next())
        {
            rows[qvariant_cast<T>(_trim(_query->value(0)))] = 
                _trim(_query->value(1));
        }
        return rows;
    }

    template <typename T> QMap<T, QVariant> fetchPairs(
                const TcDataAccessStatement &stat,
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
        _prepareExec(sql, bind);

        QMap<T,QVariantMap> rows;
        QVariantMap row;
        QVariant val;
        while (_query->next())
        {
            QSqlRecord rec = _query->record();
            for (int i = rec.count() - 1; i > -1; i--)
            {
                row[_case(rec.fieldName(i))] = _trim(rec.value(i));
            }
            rows[qvariant_cast<T>(_trim(rec.value(0)))] = row;
            row.clear();
        }
        return rows;
    }

    template <typename T> QMap<T, QVariantMap> fetchAssoc(
                const TcDataAccessStatement &stat, 
                const QVariantList &bind = QVariantList())
    {
        return fetchAssoc<T>(stat.toString(),
                QVariantList() << stat.bind() << bind);
    }

    // Ϊsql������limit����,Ŀǰֻ֧��MySQL��PGSQL��SQLite��MSSQL,���ڲ�֧��
    // �����ݿ����ͣ�ֱ�ӷ��ؿ��ַ���
    QString limitPage(const QString &sql, int page, int rowCount) const;
    QString limit(const QString &sql, int count, int offset = 0) const;

    // �����ϴβ����ID,Ŀǰ��ʵ��������
    QVariant lastInsertId(const QString &table = QString(), 
            const QString &primaryKey = QString()) const;
    // �����ϴβ�ѯ�Ĵ�����Ϣ
    QSqlError lastError() const;

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
    TcDataAccess& operator=(const TcDataAccess &da);
    TcDataAccess& operator=(const QSqlDatabase &db);
private:
    QVariant _trim(const QVariant &val);
    QString _case(const QString &field);
private:
    static AttrCase _attrCase;
    static AttrTrim _attrTrim;
    QSqlDatabase *_db;
    QSqlQuery *_query;
    void _prepareExec(const QString &sql, const QVariantList &bind);
};

typedef TcDataAccess TcDA;
typedef TcDataAccessStatement TcDAS;

#endif
