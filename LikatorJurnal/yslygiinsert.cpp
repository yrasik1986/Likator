#include "yslygiinsert.h"
#include "ui_yslygiinsert.h"
#include <QtDebug>

YslygiInsert::YslygiInsert(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::YslygiInsert)
{
    ui->setupUi(this);
}

YslygiInsert::~YslygiInsert(){
    delete ui;
}


void YslygiInsert :: setClearInfo(){
    ui ->lineEditcellname       -> clear();
    ui ->lineEditbcoastyslygi   -> clear();
}

void YslygiInsert::on_pushButtonInsert_clicked(){
    QSqlQuery q;

    q.exec("SELECT id FROM cat_service where cat_using = '" + ui ->comboBox->currentText() + "'");
    q.next();
    int id_cat_service = q.value(0).toInt();

    q.prepare(R"(INSERT INTO service(id_cat_service, name_service, cost) values(?, ?, ?))");
    q.addBindValue(id_cat_service);
    q.addBindValue(ui ->lineEditcellname->text());
    q.addBindValue(ui ->lineEditbcoastyslygi->text().toDouble());

    if (q.exec()) {
        setClearInfo();
        emit insertServise();
        this -> close();
    } else {
        QMessageBox msbox;
        msbox.setWindowTitle("ОШИБКА!");
        msbox.setText("Ошибка  добавления услуги!");
        msbox.exec();
    }
}

void YslygiInsert::on_pushButton_clicked()
{
    setClearInfo();
    this -> close();
}

void YslygiInsert::AddItemCombo(){
    QSqlQuery sqlQ;
    if(sqlQ.exec("SELECT id, cat_using FROM cat_service")) {
        ui->comboBox->clear();
        while (sqlQ.next()){
            ui->comboBox->addItem(sqlQ.value(1).toString(),sqlQ.value(0).toInt());
        }
    }

}
