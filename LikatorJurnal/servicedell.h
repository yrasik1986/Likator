#ifndef SERVICEDELL_H
#define SERVICEDELL_H

#include <QDialog>
#include <QSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

namespace Ui {
class ServiceDell;
}

class ServiceDell : public QDialog
{
    Q_OBJECT

public:
    explicit ServiceDell(QWidget *parent = nullptr);
    ~ServiceDell();
signals:
    void dell_service();

private slots:
    void on_canselButton_2_clicked();
    void on_dellButton_clicked();

private:
    Ui::ServiceDell *ui;
};

#endif // SERVICEDELL_H
