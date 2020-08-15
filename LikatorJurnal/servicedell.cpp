#include "servicedell.h"
#include "ui_servicedell.h"
#include <QMessageBox>

ServiceDell::ServiceDell(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ServiceDell)
{
    ui->setupUi(this);
}

ServiceDell::~ServiceDell()
{
    delete ui;
}

void ServiceDell::on_canselButton_2_clicked()
{
    this->close();
}

void ServiceDell::on_dellButton_clicked()
{
    QSqlQuery q;
    q.prepare(R"(DELETE FROM service WHERE id=?)");
    q.addBindValue(ui->lineEdit->text().toInt());
    if (q.exec()) {
        emit dell_service();
        ui->lineEdit->setText("");
        this->close();
    } else {
        QMessageBox msbox;
        msbox.setWindowTitle("ОШИБКА!");
        msbox.setText("Ошибка удаления  услуги!");
        msbox.exec();
    }
}
