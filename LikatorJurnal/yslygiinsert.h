#ifndef YSLYGIINSERT_H
#define YSLYGIINSERT_H

#include <QDialog>
#include <QSqlQuery>
#include <QMessageBox>
#include <QMap>

namespace Ui {
class YslygiInsert;
}

class YslygiInsert : public QDialog
{
    Q_OBJECT

public:
    explicit YslygiInsert(QWidget *parent = nullptr);
    ~YslygiInsert();

    void setClearInfo();
    void AddItemCombo();

signals:
    void insertServise();

private slots:
    void on_pushButtonInsert_clicked();
    void on_pushButton_clicked();

private:
    Ui::YslygiInsert *ui;
};

#endif // YSLYGIINSERT_H
