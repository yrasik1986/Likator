#ifndef HUMANINFO_H
#define HUMANINFO_H
#pragma once
#include <QDialog>
#include <QLineEdit>
#include <QSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>
#include "woreff.h"
#include "insertwork.h"
#include "prizcode.h"

namespace Ui {
class HumanInfo;
}

class HumanInfo : public QDialog
{
    Q_OBJECT
public:
    explicit HumanInfo(QWidget *parent = nullptr);
    ~HumanInfo();
    void readOnlyAll();
    void writeAllOn();
    InsertWork * GetInsertWork();

signals:
    void discontInsert(int, int);
    void addClient();

private slots:
    void on_insertbutton_clicked();
    void on_viewButton_clicked();
    void on_writeButton_clicked();
    void on_applayButton_clicked();
    void on_changButton_clicked();
    void discontInsertSlot(int _id, int cost);
    void on_prizButton_clicked();

public slots:
    void comeUid(const QString& uid);
    void changeLineAdress(int arg);

private:
    Ui::HumanInfo *ui;
    WorEff *workinfo;
    InsertWork *insertwork;
    PrizCode *prizCode;
    QString _uid;
    int id;
    bool offAdressLine;

};

#endif // HUMANINFO_H
