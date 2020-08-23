#include "jurnal.h"
#include "ui_jurnal.h"
#include <QDebug>
#include<QSqlQueryModel>

Jurnal::Jurnal(QDialog *parent) :
    QDialog(parent),
    ui(new Ui::Jurnal)
{
    ui->setupUi(this);
   // connect(ui->calendarWidget, &QCalendarWidget::selectionChanged,this, &Jurnal::selectedDateChanged);
    //void clicked(const QDate &date);
    connect(ui->calendarWidget, &QCalendarWidget::clicked,this, &Jurnal::click);
    ui->calendarWidget->setVerticalHeaderFormat(QCalendarWidget::VerticalHeaderFormat(QCalendarWidget::NoVerticalHeader));

    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery q;
    q.prepare(R"(SELECT  masters.name_master
              || ' ' || masters.fam_master || ' ' || masters.firstname_master,
              masters.birth_master, masters.phone_master
              FROM masters)");
    q.exec();
    model->setQuery(q);
    ui->tableView->setModel(model);
    model->setHeaderData(0, Qt::Horizontal, tr("Категория мастера"));
    model->setHeaderData(1, Qt::Horizontal, tr("ФИО"));
    model->setHeaderData(2, Qt::Horizontal, tr("День Рождения"));
    model->setHeaderData(3, Qt::Horizontal, tr("телефон"));
    ui->tableView->resizeColumnsToContents();




//    ui->tableWidgeWorkday->setColumnCount(2);
//    QStringList labels;
//    labels << "Время " << "Статус";
//    ui->tableWidgeWorkday->setHorizontalHeaderLabels(labels);

//    int rowCountCatMaset = 0;
//    while (q.next())
//    {
//        ui->tableWidgeWorkday->insertRow(rowCountCatMaset);
//        QTableWidgetItem *select = new QTableWidgetItem;
//        QTableWidgetItem *name = new QTableWidgetItem;

//        select->setCheckState(Qt::Unchecked);
//        name->setText(q.value(1).toString());

//        ui->tableWidgeWorkday->setItem(rowCountCatMaset, 0, select);
//        ui->tableWidgeWorkday->setItem(rowCountCatMaset, 1, name);
//       // idCatMasters.push_back(q.value(0).toInt());

//        rowCountCatMaset++;
//    }




}

Jurnal::~Jurnal()
{
    delete ui;
}

void Jurnal::selectedDateChanged(){

}

void Jurnal::click(const QDate &date)
{
     ui->dateEdit->setDate(date);

     qDebug() <<  date.dayOfWeek();

     QSqlQuery q;
     q.prepare(R"(SELECT time_start, time_finish
               FROM timetable_salon
               WHERE day_in_week = ?)");
     q.addBindValue(date.dayOfWeek());
     if (!q.exec()){
         qDebug() << "Error!";
         return;
     }

     q.next();

     QTime startTime = q.value(0).toTime();
     QTime finTime = q.value(1).toTime();
     QTime deltaTime = QTime(00,30,00,00);

     ui->tableWidgeWorkday->setColumnCount(2);
     QStringList labels;
     labels << "Время " << "Статус";
     ui->tableWidgeWorkday->setHorizontalHeaderLabels(labels);
     int rowCountCatMaset = 0;
     while (startTime != finTime)
     {
         ui->tableWidgeWorkday->insertRow(rowCountCatMaset);
         QTableWidgetItem *select = new QTableWidgetItem;
         QTableWidgetItem *name = new QTableWidgetItem;

         select->setCheckState(Qt::Unchecked);
         name->setText(startTime.toString());

         ui->tableWidgeWorkday->setItem(rowCountCatMaset, 1, select);
         ui->tableWidgeWorkday->setItem(rowCountCatMaset, 0, name);
         startTime = startTime.addSecs(deltaTime.minute()*60);

         rowCountCatMaset++;
     }



//         ui->tableWidgeWorkday->setColumnCount(2);
//         QStringList labels;
//         labels << "Время " << "Статус";
//         ui->tableWidgeWorkday->setHorizontalHeaderLabels(labels);

//         int rowCountCatMaset = 0;
//         while (q.next())
//         {
//             ui->tableWidgeWorkday->insertRow(rowCountCatMaset);
//             QTableWidgetItem *select = new QTableWidgetItem;
//             QTableWidgetItem *name = new QTableWidgetItem;

//             select->setCheckState(Qt::Unchecked);
//             name->setText(q.value(1).toString());

//             ui->tableWidgeWorkday->setItem(rowCountCatMaset, 0, select);
//             ui->tableWidgeWorkday->setItem(rowCountCatMaset, 1, name);
//            // idCatMasters.push_back(q.value(0).toInt());

//             rowCountCatMaset++;
//         }

}
