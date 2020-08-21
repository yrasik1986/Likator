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
    connect(addMaster, &AddMaster::SendUpdateTable, this, &Master::ShowTable);
    addMaster->setModal(true);
    addMaster->exec();
}

void Master::on_changeButton_clicked()
{
    masterChange = new MasterChange();
    connect(masterChange, &MasterChange::SendUpdateMaster, this, &Master::UpdateTable);
    masterChange->setModal(true);
    masterChange->exec();
}

void Master::ShowTable(){
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
    model->setHeaderData(0, Qt::Horizontal, tr("ФИО"));
    model->setHeaderData(1, Qt::Horizontal, tr("День Рождения"));
    model->setHeaderData(2, Qt::Horizontal, tr("телефон"));
    ui->tableView->resizeColumnsToContents();
}

void Master::UpdateTable(int idMaster)
{
    masterUpdate = new MasterUpdate(idMaster);
    connect(masterUpdate, &MasterUpdate::SendUpdateTable, this, &Master::ShowTable);
    masterUpdate->setModal(true);
    masterUpdate->exec();
}
