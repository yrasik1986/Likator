#include "addmaster.h"
#include "ui_addmaster.h"

AddMaster::AddMaster(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddMaster)
{
   ui->setupUi(this);

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
    q.prepare(R"(INSERT INTO masters (name_master, fam_master,
              firstname_master, birth_master, phone_master) values(?, ?, ?, ?, ?))");
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
