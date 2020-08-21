#ifndef CATCHANGE_H
#define CATCHANGE_H

#include <QDialog>
#include <QSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>

namespace Ui {
class CatChange;
}

class CatChange : public QDialog
{
    Q_OBJECT

public:
    explicit CatChange(QWidget *parent = nullptr);
    ~CatChange();
signals:
    void change_cat();

private slots:
    void on_saveButton_clicked();

    void on_nextButton_clicked();

    void on_backButton_clicked();

    void on_canselButton_clicked();

private:
    void UpdateCombo();
    Ui::CatChange *ui;
};

#endif // CATCHANGE_H
