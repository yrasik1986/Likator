#include "addcatmaster.h"
#include "ui_addcatmaster.h"

AddCatMaster::AddCatMaster(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddCatMaster)
{
    ui->setupUi(this);
}

AddCatMaster::~AddCatMaster()
{
    delete ui;
}

void AddCatMaster::on_canselButton_clicked()
{
    this->close();
}

void AddCatMaster::on_saveButton_clicked()
{
    QSqlQuery q;
    q.prepare(R"(INSERT INTO cat_masters (name) values(?))");
    q.addBindValue(ui->lineEdit->text());
    if (q.exec()) {
        emit UpdateCatMasters();
        this->close();
    } else {
        QMessageBox msbox;
        msbox.setWindowTitle("ОШИБКА!");
        msbox.setText("Ошибка добаления услуги!");
        msbox.exec();
    }
}
