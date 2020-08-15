#include "catdell.h"
#include "ui_catdell.h"
#include <QMessageBox>

CatDell::CatDell(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CatDell)
{
    ui->setupUi(this);
    UpdateCombo();

//   connect(ui->comboBoxWork, SIGNAL(currentIndexChanged(QString)), this, SLOT(updatePrice(QString)));
//   connect(ui->comboBoxCat, SIGNAL(currentIndexChanged(QString)), this, SLOT(updateCombo(QString)));
}

CatDell::~CatDell()
{
    delete ui;
}

void CatDell::on_dellButton_clicked()
{
    QString cat_using = ui->catComboBox->currentText();
    int id_cat_service;
    QSqlQuery q;
    q.prepare("SELECT id, cat_using FROM cat_service WHERE cat_using=?");
    q.addBindValue(cat_using);
    if(q.exec()) {
       id_cat_service = q.value(0).toInt();
    }

    q.prepare(R"(DELETE FROM cat_service WHERE cat_using=?)");
    q.addBindValue(cat_using);
    if (q.exec()) {
        q.prepare(R"(DELETE FROM service WHERE id_cat_service=?)");
        q.addBindValue(id_cat_service);
        q.exec();
        emit dell_cat();
        this->close();
    }
}

void CatDell::on_canselButton_clicked()
{
    this->close();
}

void CatDell::UpdateCombo(){
    QSqlQuery sqlQ;
    if(sqlQ.exec("SELECT id, cat_using FROM cat_service")) {
        ui->catComboBox->clear();
        while (sqlQ.next()){
            ui->catComboBox->addItem(sqlQ.value(1).toString(),sqlQ.value(0).toInt());
        }
    }
}
