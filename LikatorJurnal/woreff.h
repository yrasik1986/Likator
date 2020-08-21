#ifndef WOREFF_H
#define WOREFF_H

#include <QDialog>
#include <QSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QFileDialog>

namespace Ui {
class WorEff;
}

class WorEff : public QDialog
{
    Q_OBJECT

public:
    explicit WorEff(QWidget *parent = nullptr);
    ~WorEff();
    void setTextTable();
    void setId(int id);

private slots:
    void on_historyButton_clicked();

private:
    Ui::WorEff *ui;
    int _id;

};

#endif // WOREFF_H
