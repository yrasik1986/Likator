#include "dellcatmaster.h"
#include "ui_dellcatmaster.h"

DellCatMaster::DellCatMaster(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DellCatMaster)
{
    ui->setupUi(this);
    UpdateCombo();
}

DellCatMaster::~DellCatMaster()
{
    delete ui;
}

void DellCatMaster::UpdateCombo(){
    QSqlQuery sqlQ;
    if(sqlQ.exec("SELECT id, name FROM cat_masters")) {
        ui->comboBox->clear();
        while (sqlQ.next()){
            ui->comboBox->addItem(sqlQ.value(1).toString(),sqlQ.value(0).toInt());
        }
    }
}

void DellCatMaster::on_dellButton_clicked()
{
    QString cat_using = ui->comboBox->currentText();
    int id_cat_service;
    QSqlQuery q;
    q.prepare("SELECT id, name FROM cat_masters WHERE name=?");
    q.addBindValue(cat_using);
    if(q.exec()) {
       id_cat_service = q.value(0).toInt();
    }

    q.prepare(R"(DELETE FROM cat_masters WHERE name=?)");
    q.addBindValue(cat_using);
    if (q.exec()) {
       // q.prepare(R"(DELETE FROM service WHERE id=?)");
       // q.addBindValue(id_cat_service);
       // q.exec();
        emit sendDellCatMasters();
        this->close();
    }
}

void DellCatMaster::on_canselButton_clicked()
{
    this->close();
}
