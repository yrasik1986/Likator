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
#include <QDate>

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
       void click(const QDate& date);

private:
    Ui::Jurnal *ui;

};

#endif // JURNAL_H
