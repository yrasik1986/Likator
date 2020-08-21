#ifndef FIRSTDEVICE_H
#define FIRSTDEVICE_H

#include <QDialog>
#include <QSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

namespace Ui {
class FirstDevice;
}

class FirstDevice : public QDialog
{
    Q_OBJECT

public:
    explicit FirstDevice(QWidget *parent = nullptr);
    void SetVidPid(quint16 vendor_id,quint16 product_id);
    ~FirstDevice();

private slots:
    void on_next_clicked();

private:
    Ui::FirstDevice *ui;
    quint16 _vendor_id;
    quint16 _product_id;

};

#endif // FIRSTDEVICE_H
