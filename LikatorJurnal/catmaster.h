#ifndef CATMASTER_H
#define CATMASTER_H

#include <QDialog>
#include <QSqlQueryModel>
#include "addcatmaster.h"
#include "dellcatmaster.h"

namespace Ui {
class CatMaster;
}

class CatMaster : public QDialog
{
    Q_OBJECT

public:
    explicit CatMaster(QWidget *parent = nullptr);
    ~CatMaster();

private slots:
    void on_addButton_clicked();
    void LoadCatMasters();

    void on_delButton_clicked();

private:
    Ui::CatMaster *ui;
    AddCatMaster *addCatMaster;
    DellCatMaster *dellCatMaster;
};

#endif // CATMASTER_H
