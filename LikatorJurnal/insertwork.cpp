#include "insertwork.h"
#include "ui_insertwork.h"
#include "humaninfo.h"
#include <QDateEdit>

InsertWork::InsertWork(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InsertWork)
{
    ui->setupUi(this);
    QSqlQuery sqlQ;

    if(sqlQ.exec("SELECT id, cat_using FROM cat_service")) {
        ui->comboBoxCat->clear();
        while (sqlQ.next()){
            ui->comboBoxCat->addItem(sqlQ.value(1).toString(),sqlQ.value(0).toInt());
        }
       updateCombo(ui->comboBoxCat->currentText());
    }

   connect(ui->comboBoxWork, SIGNAL(currentIndexChanged(QString)), this, SLOT(updatePrice(QString)));
   connect(ui->comboBoxCat, SIGNAL(currentIndexChanged(QString)), this, SLOT(updateCombo(QString)));
}

InsertWork::~InsertWork()
{
    delete ui;
}
void InsertWork::SetId(int id){
    _id = id;
}

void InsertWork::on_pushButton_clicked(){
    QSqlQuery q;
    q.prepare(R"(INSERT INTO workefftable(work,
                            date_work, time_work, price, id_client) values(?, ?, ?, ?, ?))");
    q.addBindValue(ui->comboBoxWork->currentText());
    QDate currDate = QDate::currentDate();
    QTime currTime = QTime::currentTime();
    q.addBindValue(currDate);
    q.addBindValue(currTime);
    q.addBindValue(ui->lineEditMoney->text().toDouble());
    q.addBindValue(_id);
    if(q.exec()){
        QMessageBox msbox;
        msbox.setWindowTitle("УСПЕШНО!");
        msbox.setText("Новая услуга добавлена в базу данных!!!");
        msbox.exec();
    }

    emit discontInsert(_id, ui->lineEditMoney->text().toInt());
    this->close();

}
void InsertWork::updatePrice(const QString& name_service){
    QSqlQuery sqlQ;
    if(sqlQ.exec("SELECT cost FROM service where name_service ='" + name_service +"'")){
        sqlQ.next();
        ui->lineEditMoney->setText(sqlQ.value(0).toString());
    }
}

void InsertWork::updateCombo(const QString& comboBoxCatText){
    QSqlQuery sqlQ;
    if(sqlQ.exec("SELECT id FROM cat_service WHERE cat_using ='" + comboBoxCatText +"'")){
        sqlQ.next();
        QString id_cat_service = sqlQ.value(0).toString();
        if(sqlQ.exec("SELECT  name_service FROM service WHERE id_cat_service =" + id_cat_service +"")) {
           ui->comboBoxWork->clear();
           int i = 0;
           while (sqlQ.next()){
                ui->comboBoxWork->addItem(sqlQ.value(0).toString(),sqlQ.value(i).toInt());
                i++;
            }
           updatePrice(ui->comboBoxWork->currentText());
         }
    }

}

void InsertWork::on_canselButton_clicked()
{
    this->close();
}
