#include "catchange.h"
#include "ui_catchange.h"

CatChange::CatChange(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CatChange)
{
    ui->setupUi(this);
    UpdateCombo();
    ui-> backButton->close();
    ui-> saveButton->close();
    ui->lineEdit->close();

}

CatChange::~CatChange()
{
    delete ui;
}

void CatChange::on_saveButton_clicked()
{
    QSqlQuery q;

    q.prepare(R"(UPDATE cat_service SET cat_using=? WHERE cat_using=?)");
    q.addBindValue(ui->lineEdit->text());
    q.addBindValue(ui->catComboBox->currentText());
    if (q.exec()) {
        QMessageBox msbox;
        //msbox.setWindowTitle("ОШИБКА!");
        msbox.setText("Категория успешно обновлена!");
        msbox.exec();
        emit change_cat();
        this->close();
    }

}

void CatChange::UpdateCombo(){
    QSqlQuery sqlQ;
    if(sqlQ.exec("SELECT id, cat_using FROM cat_service")) {
        ui->catComboBox->clear();
        while (sqlQ.next()){
            ui->catComboBox->addItem(sqlQ.value(1).toString(),sqlQ.value(0).toInt());
        }
    }
}

void CatChange::on_nextButton_clicked()
{
    ui->label->setText("Внесите изменения:");
    ui-> backButton->show();
    ui-> saveButton->show();
    ui-> lineEdit->show();
    ui->lineEdit->setText(ui->catComboBox->currentText());

    ui-> nextButton->close();
    ui-> canselButton->close();
    ui-> catComboBox->close();
}

void CatChange::on_backButton_clicked()
{
    ui->label->setText("Выберите категория для изменения:");
    ui-> backButton->close();
    ui-> saveButton->close();
    ui->lineEdit->close();

    ui-> nextButton->show();
    ui-> canselButton->show();
    ui-> catComboBox->show();


}

void CatChange::on_canselButton_clicked()
{
     this->close();
}
