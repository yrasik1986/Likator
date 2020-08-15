#ifndef MASTER_H
#define MASTER_H

#include <QDialog>
#include <QSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QFileDialog>
#include <QSqlQueryModel>
#include <QSqlTableModel>
#include "addmaster.h"

namespace Ui {
class Master;
}

class Master : public QDialog
{
    Q_OBJECT

public:
    explicit Master(QWidget *parent = nullptr);
    ~Master();
public slots:
    void UpdateTable();

private slots:
    void on_addButton_clicked();
    void on_changeButton_clicked();

private:
    Ui::Master *ui;
    AddMaster *addMaster;
};

#endif // MASTER_H
