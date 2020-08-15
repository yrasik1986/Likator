#ifndef TIMETABLE_H
#define TIMETABLE_H

#include <QDialog>
#include <QSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

namespace Ui {
class Timetable;
}

class Timetable : public QDialog
{
    Q_OBJECT

public:
    explicit Timetable(QWidget *parent = nullptr);
    ~Timetable();

private:
    Ui::Timetable *ui;
};

#endif // TIMETABLE_H
