#ifndef COREGUI_H
#define COREGUI_H

#include <QObject>

class CoreGui : public QObject
{
    Q_OBJECT
public:
    explicit CoreGui(QObject *parent = nullptr);

signals:

public slots:
};

#endif // COREGUI_H
