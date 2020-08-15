#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>
#include <QPair>
#include <QtDebug>

#include "woreff.h"
#include "ui_woreff.h"
#include "mainwindow.h"

QT_CHARTS_USE_NAMESPACE

WorEff::WorEff(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WorEff)
{
    ui->setupUi(this);
}

WorEff::~WorEff()
{
    delete ui;
}

void WorEff :: setTextTable(){
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->horizontalHeader()->setStretchLastSection(true);

    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery q;
    q.prepare("SELECT date_work, time_work, work, price FROM workefftable where id_client=?");
    q.addBindValue(_id);
    q.exec();
    model->setQuery(q);
    ui->tableView->setModel(model);
    model->setHeaderData(0, Qt::Horizontal, tr("Дата выполнения работы"));
    model->setHeaderData(1, Qt::Horizontal, tr("Время"));
    model->setHeaderData(2, Qt::Horizontal, tr("Название работы"));
    model->setHeaderData(3, Qt::Horizontal, tr("Стоимость работы"));
    ui->tableView->resizeColumnsToContents();


    q.prepare("SELECT SUM(price)  FROM workefftable where id_client = ?");
    q.addBindValue(_id);
    if (q.exec()) {
        q.next();
        ui->lineEditMoney->setText(q.value(0).toString());
    }

}

void WorEff ::setId(int id){
    _id = id;
}

void WorEff::on_historyButton_clicked()
{
    QMap<int, int> myMap;
    QDate currDate = QDate::currentDate();
    QDate lastYearDate;
    lastYearDate.setDate(currDate.year() - 1, currDate.month(), currDate.day());
    lastYearDate = lastYearDate.addMonths(1);

    QSqlQuery q;
    q.prepare("SELECT date_work  FROM workefftable WHERE id_client =? AND   date_work BETWEEN ? AND ? ");
    q.addBindValue(_id);
    q.addBindValue(lastYearDate);
    q.addBindValue(currDate);

    q.exec();
    while( q.next()) {
        qDebug() << q.value(0).toDate().toString("yyyy-MMMM");
        myMap[q.value(0).toDate().month()]++;
    }

    QString fullName;
    q.prepare("SELECT name1, name2, name3 FROM client where id = ?");
    q.addBindValue(_id);
    if (q.exec()) {
        q.next();
        fullName = q.value(0).toString() + ' ' + q.value(1).toString() + ' ' + q.value(2).toString();
    }

       QStringList categories;
       QBarSet *set0 = new QBarSet(fullName);

       for (QDate d = lastYearDate; d <= currDate; d= d.addMonths(1) ) {
         categories << d.toString("MM-yy");
         *set0 << myMap[d.month()];
       }

      qDebug() << set0->sum(); // сумма всех посещений

        QBarSeries *series = new QBarSeries();
        series->append(set0);

        QChart *chart = new QChart();
        chart->addSeries(series);
        chart->setTitle("Статистика посещения салона за год");
        chart->setAnimationOptions(QChart::SeriesAnimations);
        chart->setTheme(QChart::ChartThemeLight);
        //chart->setTitleFont(QFont::);

        QBarCategoryAxis *axisX = new QBarCategoryAxis();
        axisX->append(categories);
        chart->addAxis(axisX, Qt::AlignBottom);
        series->attachAxis(axisX);

        QValueAxis *axisY = new QValueAxis();
        axisY->setRange(0,10);
        chart->addAxis(axisY, Qt::AlignLeft);
        series->attachAxis(axisY);

        chart->legend()->setVisible(true);
        chart->legend()->setAlignment(Qt::AlignBottom);

        QChartView *chartView = new QChartView(chart);
        chartView->setRenderHint(QPainter::Antialiasing);
        //chartView->style()


        QDialog *d = new QDialog();
        QGridLayout *layout = new QGridLayout;
        layout->addWidget(chartView, 0, 0);
        setLayout(layout);
        d->setLayout(layout);
        d->resize(860, 300);
        d->windowModality();
        d->setModal(true);
        d->exec();

}
