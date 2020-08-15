#ifndef CATADD_H
#define CATADD_H

#include <QDialog>
#include <QSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

namespace Ui {
class CatAdd;
}

class CatAdd : public QDialog
{
    Q_OBJECT

public:
    explicit CatAdd(QWidget *parent = nullptr);
    ~CatAdd();

signals:
    void UpdateCatService();

private slots:
    void on_saveButton_clicked();
    void on_canselButton_clicked();

private:
    Ui::CatAdd *ui;
};

#endif // CATADD_H
