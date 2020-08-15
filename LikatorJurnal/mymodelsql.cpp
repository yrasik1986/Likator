#include "mymodelsql.h"
#include <QTimeEdit>

MyModelSql::MyModelSql(QSqlTableModel *parent) : QSqlTableModel(parent)
{

}

QVariant MyModelSql::data(const QModelIndex& item, int role) const{

    if (role == Qt::DisplayRole){
        if(item.column()  == 1 || item.column()  == 2)
         return QVariant(QString(QSqlTableModel::data(item, role).toString()));
    }
    return QSqlTableModel::data(item, role);
}
