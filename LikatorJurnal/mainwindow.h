#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMenuBar>
#include <QMenu>
//#include <qmainwindow.h>
#include <QAction>
#include <QCompleter>
#include <QMainWindow>
#include <QSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QFileDialog>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include "humaninfo.h"
#include "device.h"
#include "mydb.h"
#include "service.h"
#include "politicdiscont.h"
#include "setting.h"
#include "jurnal.h"
#include "timetable.h"
#include "catmaster.h"
#include "master.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void showError(const QSqlError &err);
    void sendSMS(const QString& phone, const QString& textSMS);
    void writeCode(int id, const QString& status_sms);
    void sensNoSendSMS();

signals:
    void comeUid(const QString& uid);
    void openService();
    void loadCatService();

private slots:
    void on_pushButton_clicked();
    void readData();
    void replyFinished(QNetworkReply *);
    void replyStatus(QNetworkReply *);
    void replyBalance(QNetworkReply *);
    void SetNetworkConnection();
    void discontInsertSlot(int id, int cost);
    void updateFindLine();
    void OpenPoliticDiscont();
    void OpenTimetable();
    void OpenCatMaster();
    void OpenMaster();
    void OpenStatistick();
    void closeDevice();
    void openSetting();
    void openJurnal();
    void insertCompletion(QString str);

private:
     void DeviseConnect(quint16 vendor_id,quint16 product_id);
     void createMenus();
     void createActions();
     Ui::MainWindow *ui;
     CatMaster *catMaster;
     Device *device;
     HumanInfo *info;
     MyDb *myDb;
     Service *service;
     CatService *catService;
     Master *master;
     Setting *setting;
     QString openDB;
     QString selectedUID;
     QString bufUid;
     QNetworkAccessManager *restclient; //in class
     bool networkConnection;
     bool deviceConnection;
     PoliticDiscont *politicDiscont;
     Timetable *timetable;
     QMap<QString, QString> telUid;
     bool statusSMS;

     Jurnal *jurnal;

     QMenu *fileMenu;
     QMenu *editMenu;
     QMenu *serviceMenu;
     QMenu *masterMenu;
     QMenu *helpMenu;
     QAction *exitAct;
     QAction *serviceAct;
     QAction *catServiceAct;
     QAction *discontAct;
     QAction *aboutAct;
     QAction *aboutQtAct;
     QAction *settingAct;
     QAction *statistickAct;
     QAction *timetableAct;
     QAction *catMasterAct;
     QAction *masterAct;
     QAction *jurnalAct;

     quint16 _vendor_id;
     quint16 _product_id;
};
#endif // MAINWINDOW_H
