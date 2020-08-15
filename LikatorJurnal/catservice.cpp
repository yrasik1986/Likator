#include "catservice.h"
#include "ui_catservice.h"

CatService::CatService(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CatService)
{
    ui->setupUi(this);
    /*catAdd = new CatAdd();
    connect(catAdd, &CatAdd::UpdateCatService, this, &CatService::LoadCatService)*/;
//    catDell = new CatDell();
//    connect(catDell, &CatDell::dell_cat, this, &CatService::del_LoadCatService);

}

CatService::~CatService()
{
    delete ui;
}

void CatService::on_addButton_clicked()
{
    catAdd = new CatAdd();
    connect(catAdd, &CatAdd::UpdateCatService, this, &CatService::LoadCatService);
    catAdd->setModal(true);
    catAdd->exec();
}

void CatService::on_delButton_clicked()
{
    catDell = new CatDell();
    connect(catDell, &CatDell::dell_cat, this, &CatService::del_LoadCatService);
    catDell->setModal(true);
    catDell->exec();

}

void CatService::LoadCatService(){
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT cat_using  FROM cat_service");
    ui->tableView->setModel(model);
    model->setHeaderData(0, Qt::Horizontal, tr("Название"));
    //model->setHeaderData(1, Qt::Horizontal, tr("Номер категории"));
    ui->tableView->showGrid();
    ui->tableView->resizeColumnsToContents();
    ui->tableView->horizontalHeader()->setStretchLastSection(true);
    this->setModal(true);
    this->exec();
}

void CatService::del_LoadCatService(){
    LoadCatService();

}

void CatService::on_changeButton_clicked()
{
    catChange = new CatChange();
    connect(catChange, &CatChange::change_cat, this, &CatService::LoadCatService);
    catChange->setModal(true);
    catChange->exec();
}
