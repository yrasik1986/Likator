#ifndef MASTERCHANGE_H
#define MASTERCHANGE_H

#include <QDialog>
#include <QSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QCompleter>
#include <QDebug>

namespace Ui {
class MasterChange;
}

class MasterChange : public QDialog
{
    Q_OBJECT

public:
    explicit MasterChange(QWidget *parent = nullptr);
    ~MasterChange();

private slots:
    void updateFindLine(QString currentCat);
    void insertCompletion(QString);
    void on_CanselButton_clicked();

    void on_AddButton_clicked();

signals:
    void SendUpdateMaster(int idMaster);


private:
    Ui::MasterChange *ui;
    QMap<QString,int> idCatAndComboIndex;
    QMap<QString,int> nameIdMaster;
};

#endif // MASTERCHANGE_H
