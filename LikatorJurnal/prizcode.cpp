#include "prizcode.h"
#include "ui_prizcode.h"

PrizCode::PrizCode(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PrizCode)
{
    ui->setupUi(this);

}

PrizCode::~PrizCode()
{
    delete ui;
}

void PrizCode::ViewInform(int id){
    QString s = QString::number(id);
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT date_set_code,  discont_code FROM discont WHERE id_client =" + s);
    ui->tableView->setModel(model);
    model->setHeaderData(0, Qt::Horizontal, tr("Дата"));
    model->setHeaderData(1, Qt::Horizontal, tr("Код"));

    ui->tableView->resizeColumnsToContents();
    ui->tableView->horizontalHeader()->setStretchLastSection(true);
}
