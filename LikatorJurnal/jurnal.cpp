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



    for (int i = 0 ; i < 4; ++i) {
        QTimeEdit *p = new QTimeEdit();
        //kalendar->push_back(p);
        ui->verticalLayout->addWidget(p);
        delete p;
    }


    ui->tableView->setEditTriggers(QAbstractItemView::EditTrigger::AnyKeyPressed);
    ui->tableView->horizontalHeader()->setStretchLastSection(true);

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



}

Jurnal::~Jurnal()
{
    delete ui;
}

void Jurnal::selectedDateChanged(){
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->horizontalHeader()->setStretchLastSection(true);

    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery q;
    q.prepare("SELECT day_in_week, time_start, time_finish FROM timetable_salon");
    //q.addBindValue(_id);
    q.exec();
    QVector<QPair<QString, QPair<QTime, QTime>>> timetable;


    while (q.next()) {

       // ui->timeEdit->setTime(q.value(1).toTime());
       // ui->timeEdit_2->setTime(q.value(2).toTime());

         timetable.push_back(qMakePair(QString(q.value(0).toString()),
                                       qMakePair(q.value(1).toTime(), q.value(2).toTime())));
    }

    for(const auto& item: timetable) {
        qDebug() << item.first << item.second.first.toString("hh:mm") << item.second.second.toString("hh:mm");
    }
//    model->setQuery(q);
//    ui->tableView->setModel(model);
//    model->setHeaderData(0, Qt::Horizontal, tr("день недели"));
//    model->setHeaderData(1, Qt::Horizontal, tr("время начала работы"));
//    model->setHeaderData(2, Qt::Horizontal, tr("время окончания работы"));
//    ui->tableView->resizeColumnsToContents();
    qDebug() << "Hello";
    //ui->dateEdit->setDate(ui->calendarWidget->selectedDate());
}

void Jurnal::click(const QDate &date)
{
     ui->dateEdit->setDate(date);

}
