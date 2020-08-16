#ifndef MASTERCHANGE_H
#define MASTERCHANGE_H

#include <QDialog>
#include <QSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QCompleter>

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
    void updateFindLine();

private:
    Ui::MasterChange *ui;
};

#endif // MASTERCHANGE_H
