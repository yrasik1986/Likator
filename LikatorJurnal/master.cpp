#include "master.h"
#include "ui_master.h"

Master::Master(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Master)
{
    ui->setupUi(this);

}

Master::~Master()
{
    delete ui;
}

void Master::on_addButton_clicked()
{
    addMaster = new AddMaster();
    connect(addMaster, &AddMaster::SendUpdateTable, this, &Master::UpdateTable);
    addMaster->setModal(true);
    addMaster->exec();
}

void Master::on_changeButton_clicked()
{
    masterChange = new MasterChange();
    //connect(masterChange, &AddMaster::SendUpdateTable, this, &Master::UpdateTable);
    masterChange->setModal(true);
    masterChange->exec();
}

void Master::UpdateTable(){
    ui->tableView->setEditTriggers(QAbstractItemView::EditTrigger::AnyKeyPressed);
    ui->tableView->horizontalHeader()->setStretchLastSection(true);

    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery q;
    q.prepare(R"(SELECT cat_masters.name, masters.name_master
              || ' ' || masters.fam_master || ' ' || masters.firstname_master,
              masters.birth_master, masters.phone_master
              FROM masters
              LEFT JOIN cat_masters
              ON cat_masters.id = masters.id_cat_master)");
    q.exec();
    model->setQuery(q);
    ui->tableView->setModel(model);
    model->setHeaderData(0, Qt::Horizontal, tr("Категория мастера"));
    model->setHeaderData(1, Qt::Horizontal, tr("ФИО"));
    model->setHeaderData(2, Qt::Horizontal, tr("День Рождения"));
    model->setHeaderData(3, Qt::Horizontal, tr("телефон"));
    ui->tableView->resizeColumnsToContents();
}
