#ifndef CATDELL_H
#define CATDELL_H

#include <QDialog>
#include <QSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

namespace Ui {
class CatDell;
}

class CatDell : public QDialog
{
    Q_OBJECT

public:
    explicit CatDell(QWidget *parent = nullptr);
    ~CatDell();
signals:
    void dell_cat();

private slots:
    void on_dellButton_clicked();
    void on_canselButton_clicked();

private:
    void UpdateCombo();
    Ui::CatDell *ui;
};

#endif // CATDELL_H
