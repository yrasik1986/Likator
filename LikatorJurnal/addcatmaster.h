#ifndef ADDCATMASTER_H
#define ADDCATMASTER_H

#include <QDialog>
#include <QSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>

namespace Ui {
class AddCatMaster;
}

class AddCatMaster : public QDialog
{
    Q_OBJECT

public:
    explicit AddCatMaster(QWidget *parent = nullptr);
    ~AddCatMaster();

signals:
    void UpdateCatMasters();

private slots:
    void on_canselButton_clicked();

    void on_saveButton_clicked();

private:
    Ui::AddCatMaster *ui;
};

#endif // ADDCATMASTER_H
