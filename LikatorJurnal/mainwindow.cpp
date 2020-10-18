#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "humaninfo.h"
#include "ui_humaninfo.h"
#include <QMessageBox>
#include "insertwork.h"
#include <QNetworkConfigurationManager>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>
#include <QPair>
QT_CHARTS_USE_NAMESPACE

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow){
    ui->setupUi(this);

    deviceConnection = false;
    networkConnection = false;
    statusSMS = false;

    createActions();
    createMenus();

    restclient = new QNetworkAccessManager(this); //constructor

    QTimer *timer = new QTimer(this);// таймер для проверки интернета и девайса
        connect(timer, &QTimer::timeout, this, &MainWindow::SetNetworkConnection);
        timer->start(5000);


 // проверяем наличие драйвера для работы с базой даннных
    if (!QSqlDatabase::drivers().contains("QSQLITE")){
        QMessageBox::critical(this,"Unable to load database",
                    "This demo needs the SQLITE driver");
    }

     myDb = new MyDb();// отдельный объект для работы с базой данных
     //const QString nameBd = "db_name.sqlite";

#if defined(Q_OS_MAC)
    QString prefix = QDir::homePath();
#elif defined(Q_OS_WIN)
    QString prefix = "C:\\User\\...\\Code\\Database\\";
#endif

//const QString nameBd = prefix + "db_name.sqlite";
    const QString nameBd = prefix + "/db_name.sqlite";

    // Initialize the database:
    qDebug() <<  nameBd;
    QSqlError err = myDb->initDb(nameBd);
    if (err.type() != QSqlError::NoError) {
        showError(err);
        return;
    }

    // Open the database:
    err = myDb->OpenDb();
    if (err.type() != QSqlError::NoError) {
        showError(err);
        return;
    }

    service = new Service();
    catService = new CatService();

    info = new HumanInfo(); // форма для работы с данными о клиенте
    updateFindLine();
    QSqlQuery q;
    q.prepare("SELECT val FROM setting where name = ? ");
    q.addBindValue("vendor_id");
    if (q.exec()) {
        q.next();
        _vendor_id = q.value(0).toInt();
        qDebug() << _vendor_id;
    }
    q.prepare("SELECT val FROM setting where name = ? ");
    q.addBindValue("product_id");
    if (q.exec()) {
        q.next();
        _product_id = q.value(0).toInt();
        qDebug() << _product_id;
    }


    DeviseConnect(_vendor_id, _product_id);
    politicDiscont = new PoliticDiscont();


//Настройка событийной модели

    connect(this, &MainWindow::comeUid, info, &HumanInfo::comeUid);
    connect(this, &MainWindow::openService, service, &Service::openService);
    connect(info, &HumanInfo::discontInsert, this, &MainWindow::discontInsertSlot);
    connect(info, &HumanInfo::addClient, this, &MainWindow::updateFindLine);
    connect(this, &MainWindow::loadCatService, catService, &CatService::LoadCatService);
   // connect(this, &MainWindow::loadCatService, catService, &CatService::LoadCatService);




}

void MainWindow::readData() {
    bufUid += device->GetPort()->readAll();
    if (bufUid.back()== '\n') {
        bufUid.remove(8,2);
        QString str = bufUid;
        bufUid.clear();
        emit comeUid(str);
     }
}

void MainWindow::showError(const QSqlError &err){
    QMessageBox::critical(this, "Unable to initialize Database",
                "Error initializing database: " + err.text());
}


MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::on_pushButton_clicked(){

}



void MainWindow::replyFinished(QNetworkReply *reply){
    qDebug() << "Привет";
    QJsonDocument jsdoc;
    jsdoc = QJsonDocument::fromJson(reply->readAll());
    QJsonObject jsob_1 = jsdoc.object();
    qDebug() << jsob_1["id"].toInt();
    qDebug() << jsob_1["status"].toString();

    QJsonArray jsarr = jsob_1["cost"].toArray();
    foreach (const QJsonValue &value, jsarr) {
    QJsonObject jsob_2 = value.toObject();
    qDebug() << jsob_2["credits"].toInt();
    qDebug() << jsob_2["money"].toDouble();

    }
    reply->deleteLater();
}

void MainWindow::replyStatus(QNetworkReply *reply){
    qDebug() << "Статус:";
    QJsonDocument jsdoc;
    jsdoc = QJsonDocument::fromJson(reply->readAll());
    QJsonObject jsob_1 = jsdoc.object();
    qDebug() << jsob_1["id"].toInt();
    qDebug() << jsob_1["status"].toString();
    reply->deleteLater();
}


// проверка статуса смс
//    QUrlQuery querystr;
//    querystr.addQueryItem("username","691816661");
//    querystr.addQueryItem("password","5C3pzNWG");
//    querystr.addQueryItem("id","106570307");

//    QUrl myurl;
//    myurl.setScheme("http"); //https also applicable
//    myurl.setHost("api.rocketsms.by");
//    myurl.setPath("/json/status");
//    myurl.setQuery(querystr);

//    QNetworkRequest request;
//    request.setUrl(myurl);
//    restclient->get(request);
//    QObject::connect(restclient, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyStatus(QNetworkReply*)));

// проверка баланса
//    QUrlQuery querystr;
//    querystr.addQueryItem("username","691816661");
//    querystr.addQueryItem("password","5C3pzNWG");
//    querystr.addQueryItem("id","106570307");

//    QUrl myurl;
//    myurl.setScheme("http"); //https also applicable
//    myurl.setHost("api.rocketsms.by");
//    myurl.setPath("/json/balance");
//    myurl.setQuery(querystr);

//    QNetworkRequest request;
//    request.setUrl(myurl);
//    restclient->get(request);
//    QObject::connect(restclient, SIGNAL(finished(QNetworkReply*)),
//                     this, SLOT(replyBalance(QNetworkReply*)));


void MainWindow::replyBalance(QNetworkReply *reply){
    qDebug() << "<Баланс:";
    QJsonDocument jsdoc;
    jsdoc = QJsonDocument::fromJson(reply->readAll());
    QJsonObject jsob_1 = jsdoc.object();
    qDebug() << jsob_1["credits"].toInt();
    qDebug() << jsob_1["balance"].toDouble();
    reply->deleteLater();
}

void MainWindow::SetNetworkConnection(){

    QNetworkConfigurationManager mgr;
    QList<QNetworkConfiguration> activeConfigs = mgr.allConfigurations(QNetworkConfiguration::Active);
    if (activeConfigs.count() > 0){
        if (mgr.isOnline()) {
            networkConnection = true;
           // ui->statusBar->showMessage("Соединение с интернетом установлено!");
        } else {
            networkConnection = false;
            //ui->statusBar->showMessage("Ошибка соединения с интернетом!");
        }

    } else{
        if (mgr.isOnline()) {
             networkConnection = true;
           //  ui->statusBar->showMessage("Соединение с интернетом установлено!");
        } else {
            networkConnection = false;
           // ui->statusBar->showMessage("Ошибка соединения с интернетом!");
        }
    }

    if (networkConnection == true && statusSMS == false) {
        sensNoSendSMS();
        statusSMS = true;
        qDebug() << "SMS!!";
    }

    DeviseConnect(_vendor_id, _product_id);
}

void MainWindow::discontInsertSlot(int id, int cost){
    if (politicDiscont->GetStatusDiscont()){
        QSqlQuery q;
        double resaltSumma = 0;
        QString phone;
        q.prepare("SELECT summa_many, client_phone FROM client WHERE id=?");
        q.addBindValue(id);
        if (q.exec()){
            q.next();
            resaltSumma = q.value(0).toDouble() + cost;
            phone = q.value(1).toString();
            qDebug() << phone;

            if (resaltSumma >= politicDiscont->GetSummaDiscont()){
                qDebug() << "SMS!!!!";
                resaltSumma -= politicDiscont->GetSummaDiscont();
                if(networkConnection == true) {
                    sendSMS(phone, politicDiscont->GetTextSMS() + " Код:" + politicDiscont->GetLastDiscondCode());
                    writeCode(id,"OK");
                } else{
                    writeCode(id,"NO_SEND");
                    statusSMS = false;
                }

            } else {
                qDebug() << " NO  SMS!!!!";
            }
            q.prepare("UPDATE  client SET summa_many=? WHERE id=?");
            q.addBindValue(resaltSumma);
            q.addBindValue(id);
            q.exec();

        } else {
            qDebug() << "Error!!!!";
        }
    }
}
void MainWindow::sendSMS(const QString& phone, const QString& textSMS){
    QString new_phone = phone;
    if (phone.contains("8(029)")){
        new_phone = new_phone.replace(0,6,"+37529");
    }
    if (phone.contains("8(033)")){
        new_phone = new_phone.replace(0,6,"+37533");
    }
    if (phone.contains("8(044)")){
        new_phone = new_phone.replace(0,6,"+37544");
    }
    if (phone.contains("8(025)")){
        new_phone = new_phone.replace(0,6,"+37525");
    }
    QUrlQuery querystr;
    querystr.addQueryItem("username","691816661");
    querystr.addQueryItem("password","5C3pzNWG");
    querystr.addQueryItem("sender","likator");
    querystr.addQueryItem("priority","true");
    querystr.addQueryItem("phone",QVariant(new_phone).toString());
    querystr.addQueryItem("text",QVariant(textSMS).toString());

    QUrl myurl;
    myurl.setScheme("http"); //https also applicable
    myurl.setHost("api.rocketsms.by");
    myurl.setPath("/json/send");
    myurl.setQuery(querystr);

    QNetworkRequest request;
    request.setUrl(myurl);
    restclient->get(request);

    QObject::connect(restclient, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));
}


void MainWindow::writeCode(int id, const QString& status_sms){
    QSqlQuery q;


        q.prepare("insert into discont(id_client, date_set_code, discont_code, "
                  "status_sms ) values(?, ?, ?, ?)");
        q.addBindValue(id);
        QDate currDate = QDate::currentDate();

        q.addBindValue(currDate);
        q.addBindValue(politicDiscont->GetLastDiscondCode());
        politicDiscont->IncrementDiscondCode();
        q.addBindValue(status_sms);
        q.exec();


}

void MainWindow::sensNoSendSMS(){
    QSqlQuery q;
    QSqlQuery q2;
    q.prepare("SELECT client.client_phone, discont.id, discont.discont_code   "
                              "FROM client INNER JOIN "
                              "discont ON client.id = discont.id_tablename1 AND "
              "discont.status_sms =?");
    q.addBindValue("NO_SEND");
    //q.addBindValue("OK");
    if(q.exec()) {
        while (q.next()) {
            qDebug() << q.value(0) <<  q.value(1) << endl;
            QString phone = q.value(0).toString();
            sendSMS(phone, politicDiscont->GetTextSMS() + "Код:" + q.value(2).toString());
            q2.prepare("UPDATE  discont SET status_sms=? WHERE id=?");
            q2.addBindValue("OK");
            q2.addBindValue(q.value(1).toInt());
            q2.exec();

        }
    }

}


void MainWindow::updateFindLine(){
    QSqlQuery q;
    q.prepare("SELECT uid, client_phone, name1, number_card FROM client");
    if (q.exec()){
        QString phone, name, number_card, uid;
        QStringList phoneList, nameList, cardList;
        while(q.next()){
            uid = q.value(0).toString();
            phone = q.value(1).toString();
            name = q.value(2).toString();
            number_card = q.value(3).toString();
            phoneList.push_back(phone);
            nameList.push_back(name);
            cardList.push_back(number_card);
            telUid[phone]= uid;
            telUid[name]= uid;
            telUid[number_card] = uid;

        }
        QCompleter* cPhone = new QCompleter(phoneList, this );
        QCompleter* cName = new QCompleter(nameList, this );
        QCompleter* cNumCard = new QCompleter(cardList, this );
        cPhone->setCaseSensitivity( Qt::CaseInsensitive );
        cName->setCaseSensitivity( Qt::CaseInsensitive );
        cNumCard->setCaseSensitivity( Qt::CaseInsensitive );

        ui->phoneLine->setCompleter(cPhone);
        ui->nameLine->setCompleter(cName);
        ui->kardNumLine->setCompleter(cNumCard);

        QObject::connect(cPhone, SIGNAL(activated(QString)), this, SLOT(insertCompletion(QString)));
        QObject::connect(cName, SIGNAL(activated(QString)), this, SLOT(insertCompletion(QString)));
        QObject::connect(cNumCard, SIGNAL(activated(QString)), this, SLOT(insertCompletion(QString)));
    }
}

void MainWindow::createActions()
{
    exitAct = new QAction(tr("В&ыход"), this);
    exitAct->setShortcuts(QKeySequence::Quit);
    exitAct->setStatusTip(tr("Выход из программы"));
    connect(exitAct, &QAction::triggered, this, &QWidget::close);

    serviceAct = new QAction(tr("&Таблица услуг"), this);
    serviceAct->setShortcuts(QKeySequence::Undo);
    serviceAct->setStatusTip(tr("Редактирование таблицы услуг"));
    connect(serviceAct, &QAction::triggered, this, &MainWindow::openService);

    catServiceAct = new QAction(tr("&Названия зала"), this);
    catServiceAct->setShortcuts(QKeySequence::Redo);
    catServiceAct->setStatusTip(tr("Редактирование таблицы категорий услуг"));
    connect(catServiceAct, &QAction::triggered, this, &MainWindow::loadCatService);

    catMasterAct = new QAction(tr("&Категории мастеров"), this);
    catMasterAct->setShortcuts(QKeySequence::Undo);
    catMasterAct->setStatusTip(tr("Редактирование таблицы категорий мастеров"));
    connect(catMasterAct, &QAction::triggered, this, &MainWindow::OpenCatMaster);

    masterAct = new QAction(tr("&Таблица мастеров"), this);
    masterAct->setShortcuts(QKeySequence::Redo);
    masterAct->setStatusTip(tr("Редактирование таблицы мастеров"));
    connect(masterAct, &QAction::triggered, this, &MainWindow::OpenMaster);


            jurnalAct = new QAction(tr("&Журнал"), this);
            jurnalAct->setEnabled(true);
            jurnalAct->setShortcuts(QKeySequence::Redo);
            jurnalAct->setStatusTip(tr("Запись клиентов к мастерам"));
            connect(jurnalAct, &QAction::triggered, this, &MainWindow::openJurnal);

    discontAct = new QAction(tr("&Политика дисконта"), this);
    //discontAct->setCheckable(true);
    discontAct->setEnabled(true);
    discontAct->setShortcut(QKeySequence::Bold);
    discontAct->setStatusTip(tr("Управление дисконтной политикой"));
    connect(discontAct, &QAction::triggered, this, &MainWindow::OpenPoliticDiscont);

    timetableAct = new QAction(tr("&Расписание"), this);
    //timetableAct->setCheckable(true);
    timetableAct->setEnabled(true);
    timetableAct->setShortcut(QKeySequence::Bold);
    timetableAct->setStatusTip(tr("Редактирование расписания работы салона"));
    connect(timetableAct, &QAction::triggered, this, &MainWindow::OpenTimetable);

    statistickAct = new QAction(tr("&Отчет за период"), this);
    //statistickAct->setCheckable(true);
    statistickAct->setEnabled(true);
    statistickAct->setShortcut(QKeySequence::FindNext);
    statistickAct->setStatusTip(tr("Статистика отчетности"));
    connect(statistickAct, &QAction::triggered, this, &MainWindow::OpenStatistick);

    settingAct = new QAction(tr("&Настройки"), this);
    settingAct->setShortcuts(QKeySequence::ZoomIn);
    settingAct->setStatusTip(tr("Настроки программы"));
    connect(settingAct, &QAction::triggered, this, &MainWindow::openSetting);

    aboutAct = new QAction(tr("&About"), this);
    aboutAct->setStatusTip(tr("Показать справку о программе"));
    // connect(aboutAct, &QAction::triggered, this, &MainWindow::about);

    aboutQtAct = new QAction(tr("About &Qt"), this);
    aboutQtAct->setStatusTip(tr("Show the Qt library's About box"));
    connect(aboutQtAct, &QAction::triggered, qApp, &QApplication::aboutQt);
    //connect(aboutQtAct, &QAction::triggered, this, &MainWindow::aboutQt);

}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&Файл"));
    fileMenu->addAction(exitAct);
    editMenu = menuBar()->addMenu(tr("&Параметры"));
    editMenu->addAction(discontAct);
    editMenu->addAction(timetableAct);
    editMenu->addAction(jurnalAct);


   // helpMenu = menuBar()->addMenu(tr("&Справка"));
   // helpMenu->addAction(aboutAct);
   // helpMenu->addAction(aboutQtAct);

    serviceMenu = editMenu->addMenu(tr("&Услуги")); 
    serviceMenu->addAction(serviceAct);
    serviceMenu->addAction(catServiceAct);

    masterMenu = editMenu->addMenu(tr("&Мастера"));
    masterMenu->addAction(catMasterAct);
    masterMenu->addAction(masterAct);


    editMenu->addAction(statistickAct);
    editMenu->addSeparator();
    editMenu->addAction(settingAct);

}

void MainWindow::OpenPoliticDiscont(){
    //politicDiscont = new PoliticDiscont();
    politicDiscont->setModal(true);
    politicDiscont->exec();
}

void MainWindow::closeDevice(){
    deviceConnection = false;
    qDebug() << "close _port!!";
}

void MainWindow::DeviseConnect(quint16 vendor_id, quint16 product_id){
    if(deviceConnection == false) {
        device = new Device(); // обект для работы с железкой
        if (device->FindDevise(vendor_id, product_id)) {
            ui->statusBar->showMessage("Считывающее устройство подключено!");
            deviceConnection = true;
            connect(device->GetPort(), &QSerialPort::readyRead, this, &MainWindow::readData);
            connect(device->GetPort(), &QSerialPort::errorOccurred, this, &MainWindow::closeDevice);
        } else {
            ui->statusBar->showMessage("Ошибка подключения считывающего устройства!");
        }
    }
}

void MainWindow::openSetting(){
    setting = new Setting();
    setting->setModal(true);
    connect(setting, &Setting::changAdressLine, info, &HumanInfo::changeLineAdress);
    setting->exec();
}

void MainWindow::openJurnal()
{
    jurnal = new Jurnal();
    jurnal->setModal(true);
    jurnal->exec();
}

void MainWindow::OpenStatistick(){
    QMap<int, int> myMap;
    QDate currDate = QDate::currentDate();
    QDate lastYearDate;
    lastYearDate.setDate(currDate.year() - 1, currDate.month(), currDate.day());
    lastYearDate = lastYearDate.addMonths(1);

    QSqlQuery q;
    q.prepare("SELECT date_work  FROM workefftable WHERE uid =? AND   date_work BETWEEN ? AND ? ");
    q.addBindValue("2BC4C947");
    q.addBindValue(lastYearDate);
    q.addBindValue(currDate);

    q.exec();
    while( q.next()) {
        qDebug() << q.value(0).toDate().toString("yyyy-MMMM");
        myMap[q.value(0).toDate().month()]++;
    }

    QString fullName;
    q.prepare("SELECT name1, name2, name3 FROM tablename1 where uid = ?");
    q.addBindValue("2BC4C947");
    if (q.exec()) {
        q.next();
        fullName = q.value(0).toString() + ' ' + q.value(1).toString() + ' ' + q.value(2).toString();
    }

       QStringList categories;
       QBarSet *set0 = new QBarSet(fullName);

       for (QDate d = lastYearDate; d <= currDate; d= d.addMonths(1) ) {
         categories << d.toString("MM-yy");
         *set0 << myMap[d.month()];
       }

      qDebug() << set0->sum(); // сумма всех посещений

        QBarSeries *series = new QBarSeries();
        series->append(set0);

        QChart *chart = new QChart();
        chart->addSeries(series);
        chart->setTitle("Статистика посещения салона за год");
        chart->setAnimationOptions(QChart::SeriesAnimations);
        chart->setTheme(QChart::ChartThemeLight);
        //chart->setTitleFont(QFont::);



        QBarCategoryAxis *axisX = new QBarCategoryAxis();
        axisX->append(categories);
        chart->addAxis(axisX, Qt::AlignBottom);
        series->attachAxis(axisX);

        QValueAxis *axisY = new QValueAxis();
        axisY->setRange(0,10);
        chart->addAxis(axisY, Qt::AlignLeft);
        series->attachAxis(axisY);

        chart->legend()->setVisible(true);
        chart->legend()->setAlignment(Qt::AlignBottom);

        QChartView *chartView = new QChartView(chart);
        chartView->setRenderHint(QPainter::Antialiasing);
        //chartView->style()


        QDialog *d = new QDialog();
        QGridLayout *layout = new QGridLayout;
        layout->addWidget(chartView, 0, 0);
        setLayout(layout);
        d->setLayout(layout);
        d->resize(860, 300);
        d->windowModality();
        d->setModal(true);
        d->exec();

}

void MainWindow::OpenTimetable(){
    timetable = new Timetable();
    timetable->setModal(true);
    timetable->exec();

}

void MainWindow::OpenCatMaster() {
    catMaster = new CatMaster();
    catMaster->setModal(true);
    catMaster->exec();
}

void MainWindow::OpenMaster(){
    master = new Master();
    master->setModal(true);
    master->ShowTable();
    master->exec();
}

void  MainWindow::insertCompletion(QString str){
     emit comeUid(telUid[str]);
}
