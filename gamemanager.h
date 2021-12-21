#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H
#include <vector>
#include <QObject>

#include "dataaccess.h"
#include "a.h"

class GameManager:public QObject
{
    Q_OBJECT
private:

    std::vector<Column> field;

    unsigned int columnN,rowN;
    int DB;
    int type;
    bool currentPlayer;
    void checkGame(int, int);
    void print();
    DataAccess data;

public:
    GameManager();
    void place(int pos);
    void newGame(int type);
    void newGame(int,int);
    bool loadGame(int gameIndex);
    bool saveGame(int gameIndex);
    void setCP(int player);
    int getField(int, int);
    int getColumn(){return columnN;}
    int getRow(){return rowN;}
    int getCP(){return currentPlayer+1;}
    QVector<QString> saveGameList(){return data.saveGameList();}
signals:
    void gameWon(int player);         //Win
    void gameOver();        //Draw
    void fieldChange(int x,int y,int player);
    void tableGraph(int,int);



};

#endif // GAMEMANAGER_H
