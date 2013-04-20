/**
 * MSSQL special classes and functions
 * @filename    MSSQL.h
 * @copyright   
 * @author      XChinux<XChinux@163.com>
 * @final       2013-04-18
 */
#ifndef TIANCHI_SQL_MSSQL_H
#define TIANCHI_SQL_MSSQL_H

#include <Global.h>
#include <QStringList>

TIANCHI_BEGIN_HEADER
TIANCHI_BEGIN_NAMESPACE

QT_USE_NAMESPACE

class TIANCHI_API MSSQL
{
public:
    /**
     * get MSSQL ODBC drivers name and version, every item such as:
     * -------------------------------------------------------------
     *     10.00/SQL Server Native Client 10.0
     *     09.00/SQL Native Client
     *     03.50/SQL Server
     * -------------------------------------------------------------
     * @author  XChinux<XChinux@163.com>
     * @final   2013-04-18
     * @return  QStringList         desc sorted ver/drivername lists
     */
    static QStringList availableODBCDrivers();
};

TIANCHI_END_HEADER
TIANCHI_END_NAMESPACE

#endif
