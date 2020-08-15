#ifndef INSERTWORK_H
#define INSERTWORK_H

#include <QDialog>
#include <QSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QFileDialog>

namespace Ui {
class InsertWork;
}

class InsertWork : public QDialog
{
    Q_OBJECT

public:
    explicit InsertWork(QWidget *parent = nullptr);
    ~InsertWork();
    void SetId(int id);
signals:
    void discontInsert(int, int);

private slots:
    void on_pushButton_clicked();
    void updatePrice(const QString& name_service);
    void updateCombo(const QString& comboBoxCatText);
    void on_canselButton_clicked();

private:
    Ui::InsertWork *ui;
    int _id;

};

#endif // INSERTWORK_H
