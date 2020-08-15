#include "humaninfo.h"
#include "ui_humaninfo.h"
#include "mainwindow.h"


HumanInfo::HumanInfo(QWidget *parent) : QDialog(parent), ui(new Ui::HumanInfo){
    ui->setupUi(this);
    ui->ostatokByn->setReadOnly(true);
    QSqlQuery q;
    q.prepare("SELECT val FROM setting where name = ? ");
    q.addBindValue("setting_adress");
    if (q.exec()) {
        q.next();
        qDebug() << q.value(0).toInt();
        if (q.value(0).toInt() == 2){
            //offAdressLine = false;
            ui->adress->close();
            ui->label_4->close();
        }else {
            ui->adress->show();
            ui->label_4->show();
        }

    }

}

HumanInfo::~HumanInfo(){
    delete ui;
}

void HumanInfo::on_insertbutton_clicked(){
    insertwork = new InsertWork();
    connect(insertwork, &InsertWork::discontInsert, this, &HumanInfo::discontInsertSlot);
    insertwork->SetId(id);
    insertwork->setModal(true);
    insertwork->exec();

}

void HumanInfo::on_viewButton_clicked(){
    workinfo = new WorEff();
    workinfo->setId(id);
    workinfo->setTextTable();
    workinfo->setModal(true);
    workinfo->exec();

}

void HumanInfo::on_writeButton_clicked() {
    QSqlQuery q;
    q.prepare("insert into client(client_phone, uid, name1, "
              "name2, name3, adress, birthdate, number_card, summa_many ) values(?, ?, ?, ?, ?, ?, ?, ?, 0)");
    q.addBindValue(ui->phone->text());
    q.addBindValue(_uid);
    q.addBindValue(ui->name1->text());
    q.addBindValue(ui->name2->text());
    q.addBindValue(ui->name3->text());
    q.addBindValue(ui->adress->text());
    q.addBindValue(ui->dateEdit->date());
    q.addBindValue(ui->cardname->text());
    if (q.exec()) {
        QMessageBox msbox;
        msbox.setWindowTitle("УСПЕШНО!");
        msbox.setText("Новый клиент добавлен в базу данных!");
        msbox.exec();
        comeUid(_uid);
        emit addClient();
    }

}

void HumanInfo::on_applayButton_clicked() {
    QSqlQuery q;
    q.prepare("UPDATE  client SET client_phone=?, name1=?, "
              "name2=?, name3=?, adress=?, birthdate=?, number_card=?  WHERE uid=?");
    q.addBindValue(ui->phone->text());
    q.addBindValue(ui->name1->text());
    q.addBindValue(ui->name2->text());
    q.addBindValue(ui->name3->text());
    q.addBindValue(ui->adress->text());
    q.addBindValue(ui->dateEdit->date());
    q.addBindValue(ui->cardname->text());
    q.addBindValue(_uid);
    q.exec();
    comeUid(_uid);
    emit addClient();

}

void HumanInfo::on_changButton_clicked() {
    writeAllOn();
    ui->prizButton->close();
    ui->viewButton->close();
    ui->insertbutton->close();
    ui->applayButton->show();
    ui->changButton->close();
    ui->writeButton->close();

}

void HumanInfo::readOnlyAll(){
    ui->ostatokByn->show();
    ui->label_7->show();
    ui->viewButton->show();
    ui->insertbutton->show();
    ui->applayButton->close();
    ui->changButton->show();
    ui->writeButton->close();
    ui->FIO->show();
    ui->label_8->show();
    ui->name1->close();
    ui->name2->close();
    ui->name3->close();
    ui->label_1->close();
    ui->label_2->close();
    ui->label_3->close();
    ui->phone->setReadOnly(true);
    ui->name1->setReadOnly(true);
    ui->name2->setReadOnly(true);
    ui->name3->setReadOnly(true);
    ui->adress->setReadOnly(true);
    ui->dateEdit->setReadOnly(true);
    ui->cardname->setReadOnly(true);
    ui->FIO->setReadOnly(true);
}

void HumanInfo::writeAllOn(){

    ui->ostatokByn->close();
    ui->label_7->close();
    ui->FIO->close();
    ui->label_8->close();
    ui->name1->show();
    ui->name2->show();
    ui->name3->show();
    ui->label_1->show();
    ui->label_2->show();
    ui->label_3->show();
    ui->phone->setReadOnly(false);
    ui->name1->setReadOnly(false);
    ui->name2->setReadOnly(false);
    ui->name3->setReadOnly(false);
    ui->adress->setReadOnly(false);
    ui->dateEdit->setReadOnly(false);
    ui->cardname->setReadOnly(false);
    ui->FIO->setReadOnly(false);
}

void HumanInfo::comeUid(const QString& uid){
    qDebug() << "hello, uid = " << uid;
    QSqlQuery q;
    const QString Select = "SELECT * FROM client where uid ='" + uid +"'";
    if (q.exec(Select)) {
        if(q.next()) {
            readOnlyAll();
            ui->prizButton->show();
            id = q.value(0).toInt();
            ui->phone->setText(q.value(1).toString());
            _uid = q.value(2).toString();
            ui->name1->setText(q.value(3).toString());
            ui->name2->setText(q.value(4).toString());
            ui->name3->setText(q.value(5).toString());
            ui->FIO->setText(q.value(3).toString() + " " + q.value(4).toString() + " " +
                             q.value(5).toString());
            ui->adress->setText(q.value(6).toString());
            ui->dateEdit->setDate(q.value(7).toDate());
            ui->cardname->setText(q.value(8).toString());
            ui->ostatokByn->setText(q.value(9).toString());

        } else {

            writeAllOn();
            ui->prizButton->close();
            ui->viewButton->close();
            ui->insertbutton->close();
            ui->applayButton->close();
            ui->changButton->close();
            ui->writeButton->show();
            ui->FIO->close();
            ui->name1->show();
            ui->name2->show();
            ui->name3->show();
            ui->label_1->show();
            ui->label_2->show();
            ui->label_3->show();

            ui->phone->setText("8()");
            _uid = uid;
            ui->name1->setText("");
            ui->name2->setText("");
            ui->name3->setText("");
            ui->adress->setText("Адрес");
            ui->dateEdit->setDate(QDate());
            ui->cardname->setText("");
            qDebug() << "Nocard!";

        }
        this->setModal(true);
        this->exec();
    }
}

InsertWork* HumanInfo:: GetInsertWork(){
    return insertwork;
}

void HumanInfo::discontInsertSlot(int _id, int cost){
    emit discontInsert(_id, cost);
    comeUid(_uid);//для обновления поля остатка
}


void HumanInfo::changeLineAdress(int arg){
   qDebug() << arg;
    QSqlQuery q;
    q.prepare("UPDATE  setting SET val=?  WHERE name=?");
    ui->adress->close();
    ui->label_4->close();
    q.addBindValue(arg);
    q.addBindValue("setting_adress");
    q.exec();
    if (arg == 2){
        ui->adress->close();
        ui->label_4->close();
    }else {
        ui->adress->show();
        ui->label_4->show();
    }

}

void HumanInfo::on_prizButton_clicked()
{
    prizCode = new PrizCode();
    prizCode->setModal(true);
    prizCode->ViewInform(id);
    prizCode->exec();

}
