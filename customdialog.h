#ifndef CUSTOMDIALOG_H
#define CUSTOMDIALOG_H

#include <QDialog>
#include <QListWidget>
#include <QPushButton>

#include "gamemanager.h"

class CustomDialog:public QDialog
{

public:
    CustomDialog();
    void setGameList(QVector<QString> saveGameList); // a játékok betöltése
    int selectedGame() const { return _listWidget->currentRow(); } // a kiválasztott játék lekérdezése
protected:
     QPushButton* _okButton;
     QPushButton* _cancelButton;
     QListWidget* _listWidget;
};

#endif // CUSTOMDIALOG_H
