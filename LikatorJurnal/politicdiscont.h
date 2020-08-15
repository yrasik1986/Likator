#ifndef POLITICDISCONT_H
#define POLITICDISCONT_H

#include <QDialog>
#include <QSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>


namespace Ui {
class PoliticDiscont;
}

class PoliticDiscont : public QDialog
{
    Q_OBJECT

public:
    explicit PoliticDiscont(QWidget *parent = nullptr);
    ~PoliticDiscont();
    bool GetStatusDiscont() const;
    int GetSummaDiscont() const;
    QString GetTextSMS() const;
    QString GetLastDiscondCode() const;
    void IncrementDiscondCode();

private slots:
    void on_checkBox_stateChanged(int arg1);
    void on_changeButton_clicked();
    void on_cancelButton_2_clicked();
    void on_saveButton_3_clicked();

private:
    Ui::PoliticDiscont *ui;
    bool status_diskont;
    QString last_discont_code;
};

#endif // POLITICDISCONT_H
