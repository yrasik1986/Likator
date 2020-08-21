
#include "delegate.h"
#include <QSpinBox>
#include <QTimeEdit>
#include <QLineEdit>

//! [0]
TimeEditDelegate::TimeEditDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{

}

QWidget *TimeEditDelegate::createEditor(QWidget *parent,
    const QStyleOptionViewItem &option,
    const QModelIndex &index) const
{

    switch(index.column()){

    case 1:
    case 2:
    {
        QTimeEdit *editor = new QTimeEdit(parent);
        editor->setDisplayFormat("hh:mm");
        editor->setCalendarPopup(true);
        return editor;
        break;
    }
    default:
       QLineEdit *linee = new QLineEdit(parent);
       return linee;
       break;
    }
}


void TimeEditDelegate::setEditorData(QWidget *editor,
                                    const QModelIndex &index) const
{
    switch(index.column()){

    case 1:
    case 2:
    {
          QTimeEdit *timeEditor = qobject_cast<QTimeEdit *>(editor);
          if (timeEditor) {
             timeEditor->setTime(QTime::fromString(index.model()->data(index, Qt::EditRole).toString(),"hh:mm"));
             timeEditor->setCurrentSectionIndex(2);
          }
          break;
    }
    default:
       QLineEdit *lineeEditor = qobject_cast<QLineEdit *>(editor);
       if (lineeEditor) {
          lineeEditor->setText((index.model()->data(index, Qt::EditRole).toString()));
          lineeEditor->setReadOnly(true);
       }
       break;
    }



}


void TimeEditDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
                                   const QModelIndex &index) const
{

    switch(index.column()){
       case 1:
    case 2:
    {
           QTimeEdit *timeEditor = qobject_cast<QTimeEdit *>(editor);
           if (timeEditor) {
               model->setData(index, timeEditor->time().toString("hh:mm")); // время приводим к формату ЧЧ.ММ
           }
           break;
    }
    default:
       QLineEdit *lineeEditor = qobject_cast<QLineEdit *>(editor);
       if (lineeEditor) {
          lineeEditor->setText((index.model()->data(index, Qt::EditRole).toString()));
           lineeEditor->setReadOnly(true);
       }
       break;
       }

}

void TimeEditDelegate::updateEditorGeometry(QWidget *editor,
    const QStyleOptionViewItem &option, const QModelIndex &/* index */) const
{
    editor->setGeometry(option.rect);
}
//! [4]
QString TimeEditDelegate::displayText(const QVariant& value, const QLocale& locale) const
{
  switch (value.type()) {
    case QVariant::Time:
      //return locale.toString(value.toTime(), "hh:mm");
    default:
      return QStyledItemDelegate::displayText(value, locale);
  }
}
