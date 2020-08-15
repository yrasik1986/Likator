#ifndef MYMODELSQL_H
#define MYMODELSQL_H

#include <QSqlTableModel>

class MyModelSql : public QSqlTableModel
{
    Q_OBJECT
public:
    explicit MyModelSql(QSqlTableModel *parent = nullptr);
    QVariant data(const QModelIndex& item, int role = Qt::DisplayRole) const;

signals:

public slots:
};

#endif // MYMODELSQL_H
