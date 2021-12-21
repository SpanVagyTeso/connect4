#ifndef DATAACCESS_H
#define DATAACCESS_H

#include <QVector>
#include <QString>

#include "a.h"


class DataAccess
{
public:
    explicit DataAccess(){}
    QVector<QString> saveGameList() const;

    bool loadGame(int index,std::vector<Column> &field,bool &currentplayer, int &step);
    bool saveGame(int index,std::vector<Column> &field,int currentplayer, int step);
};

#endif // DATAACCESS_H
