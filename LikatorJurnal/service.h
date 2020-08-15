#ifndef SERVICE_H
#define SERVICE_H

#include <QDialog>
#include <QSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QFileDialog>
#include <QSqlQueryModel>
#include <QSqlTableModel>
#include "yslygiinsert.h"
#include "catservice.h"
#include "servicedell.h"

namespace Ui {
class Service;
}

class Service : public QDialog
{
    Q_OBJECT

public:
    explicit Service(QWidget *parent = nullptr);
    ~Service();

signals:
    //void loadCatService();

public slots:
    void openService();

private slots:
    void on_addServiceButton_clicked();

    void on_delButton_clicked();

private:
    Ui::Service *ui;
    YslygiInsert *insertWindow;
   // CatService *catService;
    ServiceDell *serviceDell;
};

#endif // SERVICE_H
