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

void MasterChange::updateFindLine(){
    QSqlQuery q;
    q.prepare(R"(SELECT cat_masters.name, masters.name_master
              || ' ' || masters.fam_master || ' ' || masters.firstname_master,
              masters.birth_master, masters.phone_master
              FROM masters
              LEFT JOIN cat_masters
              ON cat_masters.id = masters.id_cat_master)");
    //q.exec();


   // QSqlQuery q;
    //q.prepare("SELECT uid, client_phone, name1, number_card FROM client");
    if (q.exec()){
        QString phone, name, number_card, uid;
        QStringList phoneList, nameList, cardList;
        while(q.next()){
          //  uid = q.value(0).toString();
           // phone = q.value(1).toString();
            name = q.value(1).toString();
           // number_card = q.value(3).toString();
           // phoneList.push_back(phone);
            nameList.push_back(name);
           // cardList.push_back(number_card);
          //  telUid[phone]= uid;
          //  telUid[name]= uid;
           // telUid[number_card] = uid;

        }
       // QCompleter* cPhone = new QCompleter(phoneList, this );
        QCompleter* cName = new QCompleter(nameList, this );
       // QCompleter* cNumCard = new QCompleter(cardList, this );
       // cPhone->setCaseSensitivity( Qt::CaseInsensitive );
        cName->setCaseSensitivity( Qt::CaseInsensitive );
      //  cNumCard->setCaseSensitivity( Qt::CaseInsensitive );

        //ui->phoneLine->setCompleter(cPhone);
        ui->FamLineEdit->setCompleter(cName);
       // ui->kardNumLine->setCompleter(cNumCard);

       // QObject::connect(cPhone, SIGNAL(activated(QString)), this, SLOT(insertCompletion(QString)));
        QObject::connect(cName, SIGNAL(activated(QString)), this, SLOT(insertCompletion(QString)));
       // QObject::connect(cNumCard, SIGNAL(activated(QString)), this, SLOT(insertCompletion(QString)));
    }
}

