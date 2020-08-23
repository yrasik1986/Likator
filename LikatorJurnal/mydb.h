#ifndef MYDB_H
#define MYDB_H

#include <QtSql>
#include "humaninfo.h"
#include <QSerialPort>
#include <QSerialPortInfo>
#include "firstdevice.h"

class MyDb : public QObject
{
    Q_OBJECT
public:
    explicit MyDb(QObject *parent = nullptr);
    QSqlError initDb( const QString& nameBd);
    QSqlDatabase GetQSqlDatabase();
    QSqlError OpenDb();
    bool GetFlagIsOpen() const;

signals:
private:
    const QLatin1String PEOPLE_SQL;
    const QString WORK_SQL;
    const QString TYPE_WORK_SQL;
    const QString CAT_SERVICE_SQL;
    const QString POLICITY_DISCONT_SQL;
    const QString DISCONT_CODE_SQL;
    const QString SETTING_SQL;
    const QString TIMETABLE_SALON_SQL;
    const QString CAT_MASTERS_SQL;
    const QString MASTERS_SQL;
    const QString DAY_MASTERS_SQL;
    const QString TIMETABLE_MASTERS_SQL;
    const QString TIMETABLE_MASTER_CAT_ID_SQL;
    QSqlQuery *query;
    QSqlDatabase db;
    bool isOpenDb;

};

#endif // MYDB_H
