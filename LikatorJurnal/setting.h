#ifndef SETTING_H
#define SETTING_H

#include <QDialog>
#include <QSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

namespace Ui {
class Setting;
}

class Setting : public QDialog
{
    Q_OBJECT

public:
    explicit Setting(QWidget *parent = nullptr);
    ~Setting();
signals:
    void changAdressLine(int);

private slots:
    void on_adressCheckBox_stateChanged(int arg1);

private:
    Ui::Setting *ui;
    bool flagChecBox;
};

#endif // SETTING_H
