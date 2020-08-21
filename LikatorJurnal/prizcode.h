#ifndef PRIZCODE_H
#define PRIZCODE_H

#include <QDialog>
#include <QSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QFileDialog>
#include <QSqlQueryModel>
#include <QSqlTableModel>

namespace Ui {
class PrizCode;
}

class PrizCode : public QDialog
{
    Q_OBJECT

public:
    explicit PrizCode(QWidget *parent = nullptr);
    ~PrizCode();
     void ViewInform(int id);

private:
    Ui::PrizCode *ui;
};

#endif // PRIZCODE_H
