#ifndef DELLCATMASTER_H
#define DELLCATMASTER_H

#include <QDialog>
#include <QSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

namespace Ui {
class DellCatMaster;
}

class DellCatMaster : public QDialog
{
    Q_OBJECT

public:
    explicit DellCatMaster(QWidget *parent = nullptr);
    ~DellCatMaster();
signals:
    void sendDellCatMasters();
public slots:
    void UpdateCombo();

private slots:
    void on_dellButton_clicked();

    void on_canselButton_clicked();

private:
    Ui::DellCatMaster *ui;
};

#endif // DELLCATMASTER_H
