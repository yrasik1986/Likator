#include "firstdevice.h"
#include "ui_firstdevice.h"

FirstDevice::FirstDevice(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FirstDevice)
{
    ui->setupUi(this);
}

FirstDevice::~FirstDevice()
{
    delete ui;
}

void FirstDevice::SetVidPid(quint16 vendor_id,quint16 product_id){
    ui->vendor->setText(QString::number(vendor_id));
    ui->product->setText(QString::number(product_id));
    _vendor_id = vendor_id;
    _product_id = product_id;

}

void FirstDevice::on_next_clicked()
{
    QSqlQuery q;
    q.prepare(R"(INSERT INTO setting(name, val) values(?, ?))");
    q.addBindValue("vendor_id");
    q.addBindValue(_vendor_id);
    q.exec();
    q.prepare(R"(INSERT INTO setting(name, val) values(?, ?))");
    q.addBindValue("product_id");
    q.addBindValue(_product_id);
    q.exec();
    this->close();
}
