#include "masterupdate.h"
#include "ui_masterupdate.h"

MasterUpdate::MasterUpdate(int idMaster,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MasterUpdate),
    _idMaster(idMaster)
{
    ui->setupUi(this);
    QSqlQuery q;

//    q.prepare("SELECT name, id FROM cat_masters");
//    if (q.exec()) {
//        int i = 1;
//                while (q.next()){
//                    qDebug() << q.value(0).toString();
//                    ui->CatMastersComboBox->addItem(q.value(0).toString(),i++);
//                    idCatAndComboIndex[q.value(1).toInt()] = q.value(0).toString();
//                }

//    }

    q.prepare(R"(SELECT name_master,fam_master,
              firstname_master,birth_master, phone_master
              FROM masters
              WHERE id = ?)");
    q.addBindValue(_idMaster);
    if (q.exec()) {
        q.next();
        ui->nameLineEdit->setText(q.value(0).toString());
        ui->FamLineEdit->setText(q.value(1).toString());
        ui->FatheNameLineEdit->setText(q.value(2).toString());
        ui->BirthdayDateEdit->setDate(q.value(3).toDate());
        ui->PhoneLineEdit->setText(q.value(4).toString());

    }

}

MasterUpdate::~MasterUpdate()
{
    delete ui;
}

void MasterUpdate::on_AddButton_clicked()
{
    QSqlQuery q;
    q.prepare(R"(UPDATE masters SET name_master = ?, fam_master = ?,
              firstname_master = ?, birth_master = ?, phone_master = ? WHERE id = ?)");

    q.addBindValue(ui->nameLineEdit->text());
    q.addBindValue(ui->FamLineEdit->text());
    q.addBindValue(ui->FatheNameLineEdit->text());
    q.addBindValue(ui->BirthdayDateEdit->date());
    q.addBindValue(ui->PhoneLineEdit->text());
    q.addBindValue(_idMaster);

    if (q.exec()) {
        emit SendUpdateTable();
        QMessageBox msbox;
        msbox.setWindowTitle("Успех!");
        msbox.setText("Данные мастера успешно обновлены!");
        msbox.exec();
        this->close();
    } else {
        QMessageBox msbox;
        msbox.setWindowTitle("ОШИБКА!");
        msbox.setText("Ошибка обновления данных мастера!");
        msbox.exec();
    }
}
