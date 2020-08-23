#include "masterchange.h"
#include "ui_masterchange.h"

MasterChange::MasterChange(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MasterChange)
{
    ui->setupUi(this);
    updateFindLine();
}

MasterChange::~MasterChange()
{
    delete ui;
}

void MasterChange::updateFindLine()
{
    QSqlQuery q;
    q.prepare(R"(SELECT  masters.id, masters.name_master
              || ' ' || masters.fam_master || ' ' || masters.firstname_master
              FROM masters)");
    if (q.exec()){
        QString  name;
        QStringList nameList;
        while(q.next()){

            name = q.value(1).toString();
            if (name[0] == ' ') {
                name.remove(0,1);
            }
            nameList.push_back(name);
            nameIdMaster[name] = q.value(0).toInt();
        }

        QCompleter* cName = new QCompleter(nameList, this );
        cName->setCaseSensitivity( Qt::CaseInsensitive );
        ui->FamLineEdit->setCompleter(cName);
        QObject::connect(cName, SIGNAL(activated(QString)), this, SLOT(insertCompletion(QString)));
    }
}

void MasterChange::insertCompletion(QString name)
{
    emit SendUpdateMaster(nameIdMaster[name]);
    this->close();
}


void MasterChange::on_CanselButton_clicked()
{
    this->close();
}

void MasterChange::on_AddButton_clicked()
{

}
