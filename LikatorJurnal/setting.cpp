#include "setting.h"
#include "ui_setting.h"



Setting::Setting(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Setting)
{
    ui->setupUi(this);
    QSqlQuery q;
    q.prepare("SELECT val FROM setting where name = ? ");
    q.addBindValue("setting_adress");
    if (q.exec()) {
        q.next();

        if (q.value(0).toInt() == 2){
            ui->adressCheckBox->setChecked(true);
        }else {
           ui->adressCheckBox->setChecked(false);
        }
    }

}

Setting::~Setting()
{
    delete ui;
}

void Setting::on_adressCheckBox_stateChanged(int arg1)
{
   emit changAdressLine(arg1);
}

