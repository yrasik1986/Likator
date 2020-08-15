#include "addmaster.h"
#include "ui_addmaster.h"

AddMaster::AddMaster(QString type,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddMaster)
{
    ui->setupUi(this);
    if(type == "add") {
        ui->UpdateButton->close();
        ui->AddButton->show();

    } else if (type == "update") {
        ui->UpdateButton->show();
        ui->AddButton->close();

    }
    QSqlQuery sqlQ;
    if(sqlQ.exec("SELECT id, name FROM cat_masters")) {
        ui->CatMastersComboBox->clear();
        while (sqlQ.next()){
            ui->CatMastersComboBox->addItem(sqlQ.value(1).toString(),sqlQ.value(0).toInt());
        }
    }
}

AddMaster::~AddMaster()
{
    delete ui;
}

void AddMaster::on_CanselButton_clicked()
{
    this->close();
}

void AddMaster::on_AddButton_clicked()
{

    QSqlQuery q;
    q.prepare(R"(INSERT INTO masters (id_cat_master, name_master, fam_master,
              firstname_master, birth_master, phone_master) values(?, ?, ?, ?, ?, ?))");
    q.addBindValue(ui->CatMastersComboBox->currentIndex());
    q.addBindValue(ui->nameLineEdit->text());
    q.addBindValue(ui->FamLineEdit->text());
    q.addBindValue(ui->FatheNameLineEdit->text());
    q.addBindValue(ui->BirthdayDateEdit->date());
    q.addBindValue(ui->PhoneLineEdit->text());

    if (q.exec()) {
        emit SendUpdateTable();
        QMessageBox msbox;
        msbox.setWindowTitle("Успех!");
        msbox.setText("Мастер успешно записан в базу данных!");
        msbox.exec();
        this->close();
    } else {
        QMessageBox msbox;
        msbox.setWindowTitle("ОШИБКА!");
        msbox.setText("Ошибка добаления мастера!");
        msbox.exec();
    }

}
