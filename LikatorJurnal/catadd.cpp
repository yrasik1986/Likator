#include "catadd.h"
#include "ui_catadd.h"
#include <QMessageBox>

CatAdd::CatAdd(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CatAdd)
{
    ui->setupUi(this);
}

CatAdd::~CatAdd()
{
    delete ui;
}

void CatAdd::on_saveButton_clicked()
{
    QSqlQuery q;
    q.prepare(R"(INSERT INTO cat_service (cat_using) values(?))");
    q.addBindValue(ui->catName->text());
    if (q.exec()) {
        emit UpdateCatService();
        this->close();
    } else {
        QMessageBox msbox;
        msbox.setWindowTitle("ОШИБКА!");
        msbox.setText("Ошибка добаления услуги!");
        msbox.exec();
    }


}

void CatAdd::on_canselButton_clicked()
{
    this->close();
}
