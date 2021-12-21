#include "dataaccess.h"

#include <QFile>
#include <QFileInfo>
#include <QDateTime>
#include <QTextStream>



QVector<QString> DataAccess::saveGameList() const{
    QVector<QString> result(5);

        // végigmegyünk az 5 helyen
        for (int i = 0; i < 5; i++)
        {
            if (QFile::exists("game" + QString::number(i) + ".sav")) // ha az adott mentés létezik
            {
                QFileInfo info("game"+ QString::number(i) + ".sav");
                result[i] = "[" + QString::number(i + 1) + "] " + info.lastModified().toString("yyyy.MM.dd HH:mm:ss");
                // akkor betöltjük a fájl módosítás időpontját
            }
        }

        return result;
}

bool DataAccess::loadGame(int gameIndex,std::vector<Column> &field,bool &currentplayer, int &step)
{
    QFile file("game" + QString::number(gameIndex) + ".sav");
    if (!file.open(QFile::ReadOnly))
        return false;

    QTextStream stream(&file);
    int row,column;
    QString line;
    line=stream.readLine();
    currentplayer=line.split(" ")[0].toInt();
    step=line.split(" ")[1].toInt();
    line=stream.readLine();
    row=line.split(" ")[0].toInt();
    column=line.split(" ")[1].toInt();

    field.resize(column);
    for(int i=0;i<column;i++){
        field[i].column.resize(row);
    }
    line=stream.readLine();
    for (int i = 0; i < row; i++){
        for(int j=0;j<column;j++){
            field[j].column[i]=line.split(" ")[j].toInt();
             if(field[j].column[i]!=0)field[j].db++;
        }

        line=stream.readLine();
    }

    file.close();

    return true;
}

bool DataAccess::saveGame(int index, std::vector<Column> &field, int currentplayer,int step){
    QFile file("game" + QString::number(index) + ".sav");
        if (!file.open(QFile::WriteOnly))
            return false;

    QTextStream stream(&file);
    int row, column;
    row= field[0].column.size();
    column=field.size();
    stream<< currentplayer << " " << step << endl;
    stream << row <<" "<<column<<endl;
    for(int i=0;i<row;i++){
        for(int j=0;j<column;j++){
            stream<< field[j].column[i]<<" ";
        }
        stream<<endl;
    }
    file.close();


    return true;
}

