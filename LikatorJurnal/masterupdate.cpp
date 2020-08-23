#include "masterupdate.h"
#include "ui_masterupdate.h"

MasterUpdate::MasterUpdate(int idMaster,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MasterUpdate),
    _idMaster(idMaster)
{
    ui->setupUi(this);
    QSqlQuery q;

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
    q.clear();

   q.prepare(R"(SELECT master_cat_id.id, master_cat_id.status, cat_masters.name
             FROM master_cat_id INNER JOIN  cat_masters
             on cat_masters.id = master_cat_id.id_cat_master
             WHERE master_cat_id.id_master = ?)");
   q.addBindValue(_idMaster);
   if(!q.exec()){
       qDebug() << "Error exec";
       return;
   }

   ui->tableWidget->setColumnCount(2);
   QStringList labels;
   labels << "Выбрать " << "Название категории";
   ui->tableWidget->setHorizontalHeaderLabels(labels);

   int rowCountCatMaset = 0;
   while (q.next())
   {
       ui->tableWidget->insertRow(rowCountCatMaset);
       QTableWidgetItem *select = new QTableWidgetItem;
       QTableWidgetItem *name = new QTableWidgetItem;

       if (q.value(1).toInt()!= 2)
       {
           select->setCheckState(Qt::Unchecked);
       }
       else
       {
           select->setCheckState(Qt::Checked);
       }

       name->setText(q.value(2).toString());

       ui->tableWidget->setItem(rowCountCatMaset, 0, select);
       ui->tableWidget->setItem(rowCountCatMaset, 1, name);
       idMasterCats.push_back(q.value(0).toInt());

       rowCountCatMaset++;
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
        int row = 0;
        for(const auto& idMasterCat: idMasterCats)
        {
            q.prepare(R"(UPDATE master_cat_id SET status = ? WHERE id = ?)");
            q.addBindValue(static_cast<int>(ui->tableWidget->item(row,0)->checkState()));
            q.addBindValue(idMasterCat);
            q.exec();
            row++;
        }
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
