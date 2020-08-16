#include "addmaster.h"
#include "ui_addmaster.h"

AddMaster::AddMaster(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddMaster)
{
   ui->setupUi(this);
//    if(type == "add") {
//        ui->UpdateButton->close();
//        ui->AddButton->show();

//    } else if (type == "update") {
//        ui->UpdateButton->show();
//        ui->AddButton->close();

//    }
    QSqlQuery q;
    q.prepare("SELECT name, id FROM cat_masters");
    if (q.exec()) {
        int i = 1;
                while (q.next()){
                    qDebug() << q.value(0).toString();
                    ui->CatMastersComboBox->addItem(q.value(0).toString(),i++);
                    idCatAndComboIndex[q.value(0).toString()] = q.value(1).toInt();
                }

    }
//    if(q.exec()) {
//        ui->CatMastersComboBox->clear();
//        int i = 0;
//        while (q.next()){
//            ui->CatMastersComboBox->addItem(q.value(0).toString(),i++);
//            idCatAndComboIndex[q.value(0).toString()] = q.value(1).toInt();
//        }
//    }
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
    q.addBindValue(idCatAndComboIndex[ui->CatMastersComboBox->currentText()]);
    q.addBindValue(ui->nameLineEdit->text());
    q.addBindValue(ui->FamLineEdit->text());
    q.addBindValue(ui->FatheNameLineEdit->text());
    q.addBindValue(ui->BirthdayDateEdit->date());
    q.addBindValue(ui->PhoneLineEdit->text());

    if (q.exec()) {
        emit SendUpdateTable();
//        QMessageBox msbox;
//        msbox.setWindowTitle("Успех!");
//        msbox.setText("Мастер успешно записан в базу данных!");
//        msbox.exec();
        this->close();
    } else {
        QMessageBox msbox;
        msbox.setWindowTitle("ОШИБКА!");
        msbox.setText("Ошибка добаления мастера!");
        msbox.exec();
    }

}
