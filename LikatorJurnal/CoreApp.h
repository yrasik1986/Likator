#ifndef COREAPP_H
#define COREAPP_H

#include <QObject>
#include "MenuController.h"
#include "CoreGui.h"

class CoreApp : public QObject
{
    Q_OBJECT
public:
    explicit CoreApp(QObject *parent = nullptr);

signals:

public slots:

private:
    MenuController* _menuController;
    CoreGui* _coreGui;


};

#endif // COREAPP_H
