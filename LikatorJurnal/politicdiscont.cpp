#include "politicdiscont.h"
#include "ui_politicdiscont.h"
#include <QtDebug>

PoliticDiscont::PoliticDiscont(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PoliticDiscont)
{
    ui->setupUi(this);


    QSqlQuery q;
    q.exec("SELECT status, last_discont_code FROM policity_discont");
    q.next();
    last_discont_code = q.value(1).toString();

    if(q.value(0).toInt() == 1) {
        ui->checkBox->setChecked(true);
        q.exec("SELECT summa, text_sms, status FROM policity_discont");
        q.next();

        ui->summaDiscont->show();
        ui->textSMS->show();
        ui->label->show();
        ui->label_2->show();
        ui->saveButton_3->close();
        ui->changeButton->show();
        ui->cancelButton_2->close();

        ui->summaDiscont->setReadOnly(true);
        ui->textSMS->setReadOnly(true);

        ui->summaDiscont->setText(q.value(0).toString());
        ui->textSMS->setText(q.value(1).toString());
        status_diskont = true;
        ui->saveButton_3->close();
    } else {
        ui->checkBox->setChecked(false);
        ui->summaDiscont->close();
        ui->textSMS->close();
        ui->label->close();
        ui->label_2->close();
        ui->saveButton_3->close();
        ui->changeButton->close();
        ui->cancelButton_2->close();
        status_diskont = false;
    }


}

PoliticDiscont::~PoliticDiscont()
{
    delete ui;
}

void PoliticDiscont::on_checkBox_stateChanged(int arg1)
{

    if(arg1 == 0) {

        QMessageBox msgBox;
        msgBox.setText("Вы отключили программу дисконта!");
        msgBox.setInformativeText("Вы действительно хотите сохранить ваше действие?");
        msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::No| QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Save);
        int ret = msgBox.exec();
        QSqlQuery q;
        switch (ret) {
          case QMessageBox::Save:

            q.prepare("UPDATE policity_discont set status=?");
            q.addBindValue(0);
            q.exec();
            status_diskont = false;
            ui->summaDiscont->close();
            ui->textSMS->close();
            ui->label->close();
            ui->label_2->close();
            ui->saveButton_3->close();
            ui->changeButton->close();
            ui->cancelButton_2->close();

              break;
          case QMessageBox::No:

              this->close();
              break;
          case QMessageBox::Cancel:
              this->close();
              break;
          default:
              // should never be reached
              break;
        }





    } else {
        QSqlQuery q;

        q.exec("SELECT summa, text_sms, status FROM policity_discont");
        q.next();

        ui->summaDiscont->show();
        ui->textSMS->show();
        ui->label->show();
        ui->label_2->show();
        ui->saveButton_3->close();
        ui->changeButton->show();
        ui->cancelButton_2->close();

        ui->summaDiscont->setReadOnly(true);
        ui->textSMS->setReadOnly(true);

        ui->summaDiscont->setText(q.value(0).toString());
        ui->textSMS->setText(q.value(1).toString());

        q.prepare("UPDATE policity_discont set status=?");
        q.addBindValue(1);
        q.exec();
        status_diskont = true;
    }

}

void PoliticDiscont::on_changeButton_clicked()
{
    ui->checkBox->close();
    ui->summaDiscont->show();
    ui->textSMS->show();
    ui->label->show();
    ui->label_2->show();
    ui->saveButton_3->show();
    ui->changeButton->close();
    ui->cancelButton_2->show();

    ui->summaDiscont->setReadOnly(false);
    ui->textSMS->setReadOnly(false);

}

void PoliticDiscont::on_cancelButton_2_clicked()
{
    ui->checkBox->show();
    ui->summaDiscont->show();
    ui->textSMS->show();
    ui->label->show();
    ui->label_2->show();
    ui->saveButton_3->close();
    ui->changeButton->show();
    ui->cancelButton_2->close();

    ui->summaDiscont->setReadOnly(true);
    ui->textSMS->setReadOnly(true);

}


void PoliticDiscont::on_saveButton_3_clicked()
{
    QSqlQuery q;
    q.prepare("UPDATE policity_discont set summa=?, text_sms=?");
    q.addBindValue(ui->summaDiscont->text());
    q.addBindValue(ui->textSMS->toPlainText());
    q.exec();
    on_cancelButton_2_clicked();

}

bool PoliticDiscont::GetStatusDiscont() const{
    return status_diskont;
}

int PoliticDiscont::GetSummaDiscont() const{
    QSqlQuery q;
    q.exec("SELECT summa FROM policity_discont");
    q.next();
    return  q.value(0).toInt();
}

QString PoliticDiscont::GetTextSMS() const{
    QSqlQuery q;
    q.exec("SELECT text_sms FROM policity_discont");
    q.next();
    return  q.value(0).toString();
}

QString PoliticDiscont::GetLastDiscondCode() const{
    return last_discont_code;
}

void PoliticDiscont::IncrementDiscondCode(){
    uint64_t temp = last_discont_code.toUInt();
    ++temp;
    last_discont_code = QString::number(temp);
    QSqlQuery q;
    q.prepare("UPDATE policity_discont set last_discont_code=?");
    q.addBindValue(last_discont_code);
    q.exec();
}
