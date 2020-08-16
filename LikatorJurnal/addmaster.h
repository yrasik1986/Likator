#ifndef ADDMASTER_H
#define ADDMASTER_H

#include <QDialog>
#include <QSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QMap>

namespace Ui {
class AddMaster;
}

class AddMaster : public QDialog
{
    Q_OBJECT

public:
    explicit AddMaster(QWidget *parent = nullptr);
    ~AddMaster();
signals:
    void SendUpdateTable();

private slots:
    void on_CanselButton_clicked();

    void on_AddButton_clicked();

private:
    Ui::AddMaster *ui;
    QMap<QString,int> idCatAndComboIndex;
};

#endif // ADDMASTER_H
