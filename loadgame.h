#ifndef LOADGAME_H
#define LOADGAME_H

#include "customdialog.h"
#include "gamemanager.h"


class LoadGame:public CustomDialog
{
    Q_OBJECT
public:
    LoadGame();
private slots:
    void okButton_Clicked();
};

#endif // LOADGAME_H
