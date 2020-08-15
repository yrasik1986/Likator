#ifndef JURNAL_H
#define JURNAL_H

#include <QDialog>
#include <QSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QTimeEdit>
#include <QLineEdit>

namespace Ui {
class Jurnal;
}

class Jurnal : public QDialog
{
    Q_OBJECT

public:
    explicit Jurnal(QDialog *parent = nullptr);
    ~Jurnal();

private slots:
       void selectedDateChanged();

private:
    Ui::Jurnal *ui;

};

#endif // JURNAL_H
