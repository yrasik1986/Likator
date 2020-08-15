#include "timetable.h"
#include "ui_timetable.h"
#include <QtDebug>
#include <QSqlQueryModel>
#include <QSqlTableModel>

#include <QStandardItemModel>
#include "delegate.h"

#include "mymodelsql.h"

Timetable::Timetable(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Timetable)
{
    ui->setupUi(this);

    MyModelSql *model = new  MyModelSql();
   // QSqlTableModel *model = new QSqlTableModel();
   TimeEditDelegate *delegate = new TimeEditDelegate();
    ui->tableView->setItemDelegate(delegate);

    model->setTable("timetable_salon");
    model->select();
    ui->tableView->setModel(model);
    ui->tableView->resizeColumnsToContents();
    ui->tableView->horizontalHeader()->setStretchLastSection(true);

    ui->tableView->hideColumn(0);
    ui->tableView->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    ui->tableView->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);
    model->setHeaderData(3, Qt::Horizontal, tr("день недели"));
    model->setHeaderData(1, Qt::Horizontal, tr("начало работы"));
    model->setHeaderData(2, Qt::Horizontal, tr("окончание работы"));

}

Timetable::~Timetable()
{
    delete ui;
}
