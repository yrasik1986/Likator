#include "CoreApp.h"

CoreApp::CoreApp(QObject *parent)
    : QObject(parent)
    , _menuController(new MenuController(this))
    , _coreGui(new CoreGui(this))
{

}
