#include <tianchi/File/Json.h>

namespace Tianchi
{
// =====================================================================================================================

JSONObject::JSONObject(const QString& key)
{
    parent = NULL;
    m_index = 1;

    init();

    setKey(key);
}

void JSONObject::init()
{
    m_key  = "";
    m_type = vtfObject;
}

JSONObject::~JSONObject()
{
    clear();
}

QString JSONObject::quote(const QString& Text)
{
    QString ret;
    std::wstring ws = Text.toStdWString();
    const wchar_t* ptr = ws.c_str();
    while(*ptr)
    {
        switch(*ptr)
        {
        case L'\\': ret += "\\\\"; break;
        case L'\"': ret += "\\\""; break;
        case L'\b': ret += "\\b";  break;
        case L'\t': ret += "\\t";  break;
        case L'\n': ret += "\\n";  break;
        case L'\f': ret += "\\f";  break;
        case L'\r': ret += "\\r";  break;
        default:
            if ( *ptr > 255 )
            {
                quint16 v = *ptr;
                QString S = QString::number(v, 16);
                ret += "\\u" + S;
            }else
            {
                ret += *ptr;
            }
            break;
        }
        ptr++;
    }
    return ret;
}

QString JSONObject::dequote(const QString& text)
{
    QString s = text;
    int idx;
    while((idx=s.indexOf("\\u"))>=0)
    {
        int nHex = s.mid(idx+2, 4).toInt(0, 16);
        s.replace(idx, 6, QChar(nHex));
    }
    return s;
}

QString JSONObject::key() const
{
    return m_key;
}

void JSONObject::setKey(const QString& value)
{
    m_key = value.trimmed();
}

QVariant JSONObject::value() const
{
    if ( m_list.count() >0 )
    {
        return toString();
    }else
    {
        return m_value;
    }
}

bool JSONObject::value(const QString& key, QVariant& v) const
{
    bool ret = false;
    QMap<QString, JSONObject*>::const_iterator child = m_list.find(key);

    if ( child != m_list.constEnd() && child.key() == key )
    {
        v = child.value()->value();
        ret = true;
    }
    return ret;
}

QList<JSONObject*> JSONObject::children() const
{
    QList<JSONObject*> ret;
    for( QMap<QString, JSONObject*>::const_iterator it=m_list.begin();
         it!=m_list.end();
         it++ )
    {
        ret.append(it.value());
    }
    return ret;
}

QString JSONObject::jsonKey() const
{
    return "\"" + quote(m_key) + "\"";
}

QString JSONObject::jsonValue() const
{
    QString ret;
    switch(m_type)
    {
    default:
    case vtfString:
        ret = "\"" + quote(m_value.toString()) + "\"";
        break;
    case vtfInt:
        ret = QString::number(m_value.toInt());
        break;
    case vtfDouble:
        ret = QString::number(m_value.toDouble());
        break;
    case vtfBool:
        {
            QString v = m_value.toString().trimmed().toLower();
            ret = v == "ok" || v == "yes" || v == "true" || v.toInt() >0 ? "true" : "false";
        }
        break;
    case vtfDateTime:
        ret = m_value.toDateTime().toString("yyyy-MM-dd HH:mm:ss.zzz");
        break;
    }
    return ret;
}

JSONObject* JSONObject::addObject(const QString& key)
{
    JSONObject* ret = new JSONObject(key);
    ret->parent = this;
    ret->setType(vtfObject);
    m_list[ret->key().isEmpty() ? QString::number(m_index++) : ret->key()] = ret;
    return ret;
}

JSONObject* JSONObject::addArray(const QString& key)
{
    JSONObject* ret = new JSONObject(key);
    ret->parent = this;
    ret->setType(vtfArray);
    m_list[ret->key().isEmpty() ? QString::number(m_index++) : ret->key()] = ret;
    return ret;
}

JSONObject* JSONObject::addNull(const QString& key)
{
    JSONObject* ret = new JSONObject(key);
    ret->parent = this;
    ret->setType(vtfNull);
    m_list[ret->key().isEmpty() ? QString::number(m_index++) : ret->key()] = ret;
    return ret;
}

JSONObject* JSONObject::add(const QString& key, const QString& value)
{
    JSONObject* ret = new JSONObject(key);
    ret->parent = this;
    ret->setType(vtfString);
    ret->m_value = value;
    m_list[ret->key().isEmpty() ? QString::number(m_index++) : ret->key()] = ret;
    return ret;
}

JSONObject* JSONObject::add(const QString& key, int value)
{
    JSONObject* ret = new JSONObject(key);
    ret->parent = this;
    ret->setType(vtfInt);
    ret->m_value = value;
    m_list[ret->key().isEmpty() ? QString::number(m_index++) : ret->key()] = ret;
    return ret;
}

JSONObject* JSONObject::add(const QString& key, double value)
{
    JSONObject* ret = new JSONObject(key);
    ret->parent = this;
    ret->setType(vtfDouble);
    ret->m_value = value;
    m_list[ret->key().isEmpty() ? QString::number(m_index++) : ret->key()] = ret;
    return ret;
}

JSONObject* JSONObject::add(const QString& key, bool value)
{
    JSONObject* ret = new JSONObject(key);
    ret->parent = this;
    ret->setType(vtfBool);
    ret->m_value = value;
    m_list[ret->key().isEmpty() ? QString::number(m_index++) : ret->key()] = ret;
    return ret;
}

JSONObject* JSONObject::add(const QString& key, QDateTime value)
{
    JSONObject* ret = new JSONObject(key);
    ret->parent = this;
    ret->setType(vtfDateTime);
    ret->m_value = value;
    m_list[ret->key().isEmpty() ? QString::number(m_index++) : ret->key()] = ret;
    return ret;
}

void JSONObject::deleteChildren(const QString& key)
{
    JSONObject* ret = m_list.value(key);
    m_list.remove(key);
    if ( ret != NULL )
    {
        delete ret;
    }
}

void JSONObject::clearChildren()
{
    QMap<QString, JSONObject*>::iterator it;
    while(m_list.count()>0)
    {
        it = m_list.begin();
        delete it.value();
        m_list.remove(it.key());
    }
}

void JSONObject::clear()
{
    clearChildren();
    init();
}

QString JSONObject::toString() const
{
    QString values;
    if ( m_list.count() >0 )
    {
        for( QMap<QString, JSONObject*>::const_iterator it=m_list.begin();
             it!=m_list.end();
             it++ )
        {
            JSONObject* obj = it.value();

            values += "," + obj->toString();
        }
        if ( ! values.isEmpty() )
        {
            values.remove(0, 1);
        }
        if ( m_type == vtfArray )
        {
            values = "[" + values + "]";
        }else
        {
            values = "{" + values + "}";
        }
    }else
    {
        if ( m_type == vtfArray )
        {
            values = "[]";
        }else
        {
            values = jsonValue();
        }
    }
    return parent != NULL && parent->type() != vtfArray && ! key().isEmpty() ? jsonKey() + ":" + values : values;
}

bool JSONObject::fromString(QString jsonText)
{
    clear();

    std::wstring ws = jsonText.toStdWString();
    const wchar_t* ptr = ws.c_str();
    ptr=skip(ptr);
    switch(*ptr)
    {
    case L'{':
        ptr = fromObject("", ptr);
        break;

    case L'[':
        ptr = fromArray(ptr);
        break;
    }
    ptr = skip(ptr);
    if ( ! ptr )
    {
        clear();
    }
    return ptr != NULL;
}

const wchar_t* JSONObject::fromObject(const QString&, const wchar_t* ptr)
{
    ptr = skip(ptr);
    if ( *ptr == L'{' )
    {
        setType(vtfObject);
        do {
            ptr = skip(++ptr);
            QString Key;
            ptr = skip(parseKey(Key, ptr));
            if ( *ptr == L':' )
            {
                ptr = skip(++ptr);

                ptr = parseValue(Key, ptr);
            }
            ptr = skip(ptr);
        }while(ptr && *ptr && *ptr==',');
        if ( ptr && *ptr == L'}' )
        {
            ptr = skip(++ptr);
        }else
        {
            ptr = 0;
        }
    }
    return ptr;
}

const wchar_t* JSONObject::fromArray(const wchar_t* ptr)
{

    ptr = skip(ptr);
    if ( *ptr == L'[' )
    {
        setType(vtfArray);
        do {
            ptr = skip(++ptr);
            ptr = parseValue("", ptr);
            ptr = skip(ptr);
        }while(ptr && *ptr && *ptr==',');
        if ( ptr && *ptr == L']' )
        {
            ptr = skip(++ptr);
        }else
        {
            ptr = 0;
        }
    }
    return ptr;
}

const wchar_t* JSONObject::parseKey(QString& Value, const wchar_t* ptr)
{
    Value = "";
    ptr = skip(ptr);
    if ( *ptr==L'\"' )
    {
        ptr++;
        while(*ptr!=L'\"' && *ptr)
        {
            if ( *ptr == L'\\' )
            {
                ptr++;
                switch(*ptr)
                {
                case L'\"': Value += L'\"'; ptr++; break;
                case L'\\': Value += L'\\'; ptr++; break;
                case L'b' : Value += L'\b'; ptr++; break;
                case L'f' : Value += L'\f'; ptr++; break;
                case L'n' : Value += L'\n'; ptr++; break;
                case L'r' : Value += L'\r'; ptr++; break;
                case L't' : Value += L'\t'; ptr++; break;
                case L'u' :
                    {
                        ptr++;
                        QString s = QString::fromStdWString(std::wstring(ptr, 4));
                        Value += QChar(s.toUInt(NULL, 16));
                        ptr+=4;
                    }
                    break;
                }
            }else
            {
                Value += *ptr;
                ptr++;
            }
        }
        ++ptr;
    }
    return ptr;
}

const wchar_t* JSONObject::parseValue(QString Key, const wchar_t* ptr)
{
    ptr = skip(ptr);
    if ( *ptr )
    {
        if ( *ptr==L'\"' )
        {
            QString Value;
            ptr = skip(parseKey(Value, ptr));
            add(newKey(Key), Value);
        }else
        if ( *ptr==L'{' )
        {
            JSONObject* child = addObject(Key);
            ptr = skip(child->fromObject(Key, ptr));
        }else
        if ( *ptr==L'[' )
        {
            JSONObject* child = addArray(Key);
            ptr = skip(child->fromArray(ptr));
        }else
        if ( ptr && *ptr
            && (*ptr==L'+'||*ptr==L'-'||*ptr==L'.'||(*ptr>=L'0'&&*ptr<=L'9')||*ptr==L'E'||*ptr==L'e') )
        {
            QString Value;
            ptr = skip(parseNumber(Value, ptr));
            if ( Value.indexOf(".") >-1 )
            {
                add(newKey(Key), Value.toDouble() );
            }else
            {
                add(newKey(Key), Value.toInt() );
            }
        }else
        if ( std::wstring(ptr, 4).compare(L"true")==0 )
        {
            add(newKey(Key), true);
            ptr+=4;
        }else
        if ( std::wstring(ptr, 5).compare(L"false")==0 )
        {
            add(newKey(Key), false);
            ptr+=5;
        }else
        if ( std::wstring(ptr, 4).compare(L"null")==0 )
        {
            add(newKey(Key));
            ptr+=4;
        }
    }
    return ptr;
}

const wchar_t* JSONObject::parseNumber(QString& Value, const wchar_t* ptr)
{
    Value = "";
    ptr = skip(ptr);
    while(ptr && *ptr
        && (*ptr==L'+'||*ptr==L'-'||*ptr==L'.'||(*ptr>=L'0'&&*ptr<=L'9')||*ptr==L'E'||*ptr==L'e') )
    {
        Value += *ptr;
        ptr=skip(++ptr);
    }
    return ptr;
}

// =====================================================================================================================
}
