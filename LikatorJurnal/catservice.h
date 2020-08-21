#ifndef CATSERVICE_H
#define CATSERVICE_H

#include <QDialog>
#include <QSqlQueryModel>
#include "catadd.h"
#include "catdell.h"
#include "catchange.h"

namespace Ui {
class CatService;
}

class CatService : public QDialog
{
    Q_OBJECT

public:
    explicit CatService(QWidget *parent = nullptr);
    ~CatService();

public slots:
    void LoadCatService();
    void del_LoadCatService();

private slots:
    void on_addButton_clicked();
    void on_delButton_clicked();

    void on_changeButton_clicked();

private:
    Ui::CatService *ui;
    CatAdd *catAdd;
    CatDell *catDell;
    CatChange *catChange;
};

#endif // CATSERVICE_H
