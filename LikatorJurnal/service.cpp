#include "service.h"
#include "ui_service.h"

Service::Service(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Service)
{
    ui->setupUi(this);
    insertWindow = new YslygiInsert();
   // catService = new CatService();
   // serviceDell = new ServiceDell();
    connect(insertWindow, &YslygiInsert::insertServise, this, &Service::openService);
   // connect(this, &Service::loadCatService, catService, &CatService::LoadCatService);
   // connect(catService, &CatService::del_cat, this, &Service::openService);
    //connect(serviceDell, &ServiceDell::dell_service, this, &Service::openService);

}

Service::~Service()
{
    delete ui;
}

void Service::openService(){
    //    ui->tableView->hideColumn(0);
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT service.id,  cat_service.cat_using, name_service, cost  "
                    "FROM service INNER JOIN "
                    "cat_service ON cat_service.id = service.id_cat_service");
    ui->tableView->setModel(model);
    model->setHeaderData(0, Qt::Horizontal, tr("Номер"));
    model->setHeaderData(1, Qt::Horizontal, tr("Категория"));
    model->setHeaderData(2, Qt::Horizontal, tr("Название"));
    model->setHeaderData(3, Qt::Horizontal, tr("Стоимость"));
    ui->tableView->resizeColumnsToContents();
    ui->tableView->horizontalHeader()->setStretchLastSection(true);
    this->setModal(true);
    this->exec();

}


void Service::on_addServiceButton_clicked(){    
    insertWindow->AddItemCombo();
    insertWindow->setModal(true);
    insertWindow->exec();
}




void Service::on_delButton_clicked()
{
    serviceDell = new ServiceDell();
    connect(serviceDell, &ServiceDell::dell_service, this, &Service::openService);
    serviceDell->setModal(true);
    serviceDell->exec();
}
