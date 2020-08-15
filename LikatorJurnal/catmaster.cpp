#include "catmaster.h"
#include "ui_catmaster.h"

CatMaster::CatMaster(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CatMaster)
{
    ui->setupUi(this);
    LoadCatMasters();

}

CatMaster::~CatMaster()
{
    delete ui;
}

void CatMaster::on_addButton_clicked()
{
    addCatMaster = new AddCatMaster();
    connect(addCatMaster, &AddCatMaster::UpdateCatMasters, this, &CatMaster::LoadCatMasters);
    addCatMaster->setModal(true);
    addCatMaster->exec();

}

void CatMaster::LoadCatMasters(){
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT name  FROM cat_masters");
    ui->listView->setModel(model);
    model->setHeaderData(0, Qt::Horizontal, tr("Название"));
    //model->setHeaderData(1, Qt::Horizontal, tr("Номер категории"));
   // ui->listView->showGrid();
   // ui->listView->resizeColumnsToContents();
   // ui->listView->horizontalHeader()->setStretchLastSection(true);
   // this->setModal(true);
   // this->exec();
}

void CatMaster::on_delButton_clicked()
{
    dellCatMaster = new DellCatMaster();
    connect(dellCatMaster, &DellCatMaster::sendDellCatMasters, this, &CatMaster::LoadCatMasters);
    dellCatMaster->setModal(true);
    dellCatMaster->exec();
}
