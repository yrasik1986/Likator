#include "mydb.h"

MyDb::MyDb(QObject *parent) : QObject(parent),

    PEOPLE_SQL(QLatin1String(R"(CREATE TABLE client(
                             id INTEGER  primary key,
                             client_phone varchar,
                             uid varchar,
                             name1 varchar,
                             name2 varchar,
                             name3 varchar,
                             adress varchar,
                             birthdate date,
                             number_card varchar,
                             summa_many REAL))")),


    WORK_SQL(R"(CREATE TABLE workefftable (
                    id INTEGER primary key,
                    work varchar,
                    date_work DATETIME,
                    time_work DATETIME,
                    price REAL,
                    id_client INTEGER,
                    FOREIGN KEY (id_client) REFERENCES client(id) ON DELETE CASCADE ON UPDATE CASCADE))"),

    TYPE_WORK_SQL(R"(CREATE TABLE service (
                    id INTEGER primary key,
                    id_cat_service INTEGER,
                    name_service varchar,
                    cost REAL,
                    FOREIGN KEY (id_cat_service) REFERENCES cat_service(id) ON DELETE CASCADE ON UPDATE CASCADE))"),

    CAT_SERVICE_SQL(R"(CREATE TABLE cat_service (
                    id INTEGER primary key,
                    cat_using varchar))"),

    POLICITY_DISCONT_SQL(R"(CREATE TABLE policity_discont (
                    id INTEGER primary key,
                    summa INTEGER,
                    text_sms varchar,
                    status INTEGER,
                    last_discont_code varchar))"),

    DISCONT_CODE_SQL(R"(CREATE TABLE discont (
                     id INTEGER primary key,
                     id_client INTEGER,
                     date_set_code DATETIME,
                     discont_code varchar,
                     status_sms varchar,
                     FOREIGN KEY (id_client) REFERENCES client(id) ON DELETE CASCADE ON UPDATE CASCADE))"),

    SETTING_SQL(R"(CREATE TABLE setting (
                    id INTEGER primary key,
                    name varchar,
                    val INTEGER))"),

    TIMETABLE_SALON_SQL(R"(CREATE TABLE timetable_salon (
                    id INTEGER primary key,
                    time_start DATETIME,
                    time_finish DATETIME,
                    day_in_week varchar))"),

    CAT_MASTERS_SQL(R"(CREATE TABLE cat_masters (
                    id INTEGER primary key,
                    name varchar))"),

    MASTERS_SQL(R"(CREATE TABLE masters (
                    id INTEGER primary key,
                    id_cat_master INTEGER,
                    name_master VARCHAR,
                    fam_master VARCHAR,
                    firstname_master VARCHAR,
                    birth_master DATE,
                    phone_master VARCHAR,
                    FOREIGN KEY (id_cat_master) REFERENCES cat_masters(id) ON DELETE CASCADE ON UPDATE CASCADE))"),

    DAY_MASTERS_SQL(R"(CREATE TABLE day_master (
                    id INTEGER primary key,
                    id_service,
                    id_client,
                    id_master,
                    cur_time DATETIME,
                    status VARCHAR,
                    FOREIGN KEY (id_service) REFERENCES service(id) ON DELETE CASCADE ON UPDATE CASCADE,
                    FOREIGN KEY (id_client) REFERENCES client(id) ON DELETE CASCADE ON UPDATE CASCADE,
                    FOREIGN KEY (id_master) REFERENCES masters(id) ON DELETE CASCADE ON UPDATE CASCADE))")

{


}

QSqlError MyDb::initDb( const QString& nameBd){
    db = QSqlDatabase::addDatabase("QSQLITE");

    db.setDatabaseName(nameBd);

    if (!db.open())
        return db.lastError();

    QSqlQuery q;

    if (!q.exec("PRAGMA foreign_keys=on"))
        return q.lastError();

    QStringList tables = db.tables();
    if (tables.contains("client", Qt::CaseInsensitive))
        return QSqlError();

    if (tables.contains("workefftable", Qt::CaseInsensitive))
        return QSqlError();

    if (tables.contains("service", Qt::CaseInsensitive))
        return QSqlError();

    if (tables.contains("cat_service", Qt::CaseInsensitive))
        return QSqlError();

    if (tables.contains("policity_discont", Qt::CaseInsensitive))
        return QSqlError();

    if (tables.contains("discont", Qt::CaseInsensitive))
        return QSqlError();

    if (tables.contains("setting", Qt::CaseInsensitive))
        return QSqlError();

    if (tables.contains("timetable_salon", Qt::CaseInsensitive))
        return QSqlError();

    if (tables.contains("cat_masters", Qt::CaseInsensitive))
        return QSqlError();

    if (tables.contains("masters", Qt::CaseInsensitive))
        return QSqlError();

    if (tables.contains("day_master", Qt::CaseInsensitive))
        return QSqlError();


    if (!q.exec(PEOPLE_SQL))
        return q.lastError();

    if (!q.exec(WORK_SQL))
        return q.lastError();

    if (!q.exec(TYPE_WORK_SQL))
        return q.lastError();

    if (!q.exec(CAT_SERVICE_SQL))
        return q.lastError();

    if (!q.exec(POLICITY_DISCONT_SQL))
        return q.lastError();

    if (!q.exec(DISCONT_CODE_SQL))
        return q.lastError();

    if (!q.exec(SETTING_SQL))
        return q.lastError();

    if (!q.exec(TIMETABLE_SALON_SQL))
        return q.lastError();

    if (!q.exec(CAT_MASTERS_SQL))
        return q.lastError();

    if (!q.exec(MASTERS_SQL))
        return q.lastError();

    if (!q.exec(DAY_MASTERS_SQL))
        return q.lastError();

    q.prepare(R"(INSERT INTO policity_discont(summa,
                            text_sms, status, last_discont_code) values(?, ?, ?, ?))");
    q.addBindValue(10);
    q.addBindValue("Вы получили код розыгрыша!");
    q.addBindValue(0);
    q.addBindValue("3241");
    q.exec();

    q.prepare(R"(INSERT INTO setting(name, val) values(?, ?))");
    q.addBindValue("setting_adress");
    q.addBindValue(0);
    q.exec();

    q.prepare(R"(INSERT INTO cat_masters (name) values ("Парикмахер"), ("Мастер по маникюру"), ("Косметолог"))");
    q.exec();

    QVector<QPair<QString, QPair<QTime, QTime>>> timetable;
    timetable.push_back(qMakePair(QString("пн"), qMakePair(QTime(10,00), QTime(21,00))));
    timetable.push_back(qMakePair(QString("вт"), qMakePair(QTime(10,00), QTime(21,00))));
    timetable.push_back(qMakePair(QString("ср"), qMakePair(QTime(10,00), QTime(21,00))));
    timetable.push_back(qMakePair(QString("чт"), qMakePair(QTime(10,00), QTime(21,00))));
    timetable.push_back(qMakePair(QString("пт"), qMakePair(QTime(10,00), QTime(21,00))));
    timetable.push_back(qMakePair(QString("сб"), qMakePair(QTime(10,00), QTime(17,00))));
    timetable.push_back(qMakePair(QString("вс"), qMakePair(QTime(10,00), QTime(17,00))));

    for(auto item: timetable) {
        q.prepare(R"(INSERT INTO timetable_salon(time_start, time_finish, day_in_week ) values(?, ?, ?))");
        q.addBindValue(item.second.first);
        q.addBindValue(item.second.second);
        q.addBindValue(item.first);
        q.exec();
    }

    quint16 vendor_id;
    quint16 product_id;


    foreach(const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts()) {
           if(serialPortInfo.hasVendorIdentifier() && serialPortInfo.hasProductIdentifier()) {
               vendor_id = serialPortInfo.vendorIdentifier();
               product_id =  serialPortInfo.productIdentifier();
                  qDebug() <<   "vendor_id = " << vendor_id << "product_id = " << product_id;
         }
      }

    FirstDevice *firstDevice = new FirstDevice();
    firstDevice->SetVidPid(vendor_id, product_id);
    firstDevice->setModal(true);
    firstDevice->exec();

    return QSqlError();
}

QSqlDatabase MyDb::GetQSqlDatabase(){
    return db;
}

QSqlError MyDb::OpenDb(){
    db.open();
    if(db.isOpen()) {
        query = new QSqlQuery(db);
        isOpenDb = true;
        qDebug()<<"DataBase is open!";
    } else{
        isOpenDb = false;
        qDebug()<<"DataBase error open!";
    }
    return db.lastError();

}

bool MyDb::GetFlagIsOpen() const{
    return isOpenDb;
}

