#include "addmaster.h"
#include "ui_addmaster.h"

AddMaster::AddMaster(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddMaster)
{
   ui->setupUi(this);

   QSqlQuery q;
   q.prepare("SELECT id, name  FROM cat_masters");
   if(!q.exec()){
       qDebug() << "Error exec";
       return;
   }

   ui->tableWidget->setColumnCount(2);
   QStringList labels;
   labels << "Выбрать " << "Название категории";
   ui->tableWidget->setHorizontalHeaderLabels(labels);

   rowCountCatMaset = 0;
   while (q.next())
   {
       ui->tableWidget->insertRow(rowCountCatMaset);
       QTableWidgetItem *select = new QTableWidgetItem;
       QTableWidgetItem *name = new QTableWidgetItem;

       select->setCheckState(Qt::Unchecked);
       name->setText(q.value(1).toString());

       ui->tableWidget->setItem(rowCountCatMaset, 0, select);
       ui->tableWidget->setItem(rowCountCatMaset, 1, name);
       idCatMasters.push_back(q.value(0).toInt());

       rowCountCatMaset++;
   }

}

AddMaster::~AddMaster()
{
    delete ui;
}

void AddMaster::on_CanselButton_clicked()
{
    Qt::CheckState state = ui->tableWidget->item(0,0)->checkState();
    qDebug() << state;
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

       q.prepare("SELECT *  FROM masters WHERE   id = (SELECT MAX(id)  FROM masters);");

       if(!q.exec()){
           qDebug() << "Error exec";
           return;
       }

       q.next();
       const int idMaster = q.value(0).toInt();

       int row = 0;
       for(const auto& idCatMaster: idCatMasters)
       {
           q.prepare(R"(INSERT INTO master_cat_id (id_master, id_cat_master, status) values(?, ?, ?))");
           q.addBindValue(idMaster);
           q.addBindValue(idCatMaster);
           q.addBindValue(static_cast<int>(ui->tableWidget->item(row,0)->checkState()));
           q.exec();
           row++;

       }

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
