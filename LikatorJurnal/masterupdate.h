#ifndef MASTERUPDATE_H
#define MASTERUPDATE_H

#include <QDialog>
#include <QSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QMap>
#include <QVector>
#include <QDebug>

namespace Ui {
class MasterUpdate;
}

class MasterUpdate : public QDialog
{
    Q_OBJECT

public:
    explicit MasterUpdate(int idMaster,QWidget *parent = nullptr);
    ~MasterUpdate();

signals:
    void SendUpdateTable();

private slots:
    void on_AddButton_clicked();

private:
    Ui::MasterUpdate *ui;
    QMap<int, QString> idCatAndComboIndex;
    int _idMaster;
    QVector<int> idMasterCats;
};

#endif // MASTERUPDATE_H
