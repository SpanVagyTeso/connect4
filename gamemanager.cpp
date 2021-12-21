#include "gamemanager.h"
//#include <QMessageBox>
#include <QString>
#include <iostream>

GameManager::GameManager()
{
    currentPlayer=0;
    columnN=0;
    rowN=0;

}

int GameManager::getField(int x, int y){
    return field[x].column[y];
}

void GameManager::newGame(int a,int b){
    if(a==5 && b==8){
        newGame(1);
    }
    else if(a == 6 && b==10){
        newGame(2);
    }
    else if(a==7 && b==12){
        newGame(3);
    }
}

void GameManager::newGame(int _type){
    if(_type == 1 || _type==2 || _type==3){
        type=_type;
        switch (type) {
            case 1:
                columnN=8;
                rowN=5;
                break;

            case 2:
                columnN=10;
                rowN=6;
                break;

            case 3:
                columnN=12;
                rowN=7;
                break;
        }
        field.resize(columnN);
        for(unsigned int i=0;i<columnN;i++){
            field[i].column.resize(rowN);
            field[i].db=0;
            for(int j=0;j<rowN;j++){
                field[i].column[j]=0;

            }
        }
        tableGraph(columnN,rowN);
        currentPlayer=0;
        DB=0;
    }
    else{
        return;
    }
}

void GameManager::place(int pos){
    int column=pos/(800/(columnN+2));
    //QMessageBox::information(nullptr,QString::number(column),QString::number(DB));
    if(column<1){
        return;
    }
    if(column>columnN){
        return;
    }
    if(field[column-1].db >= rowN){
        return;
    }
    column--;
    DB++;
    //QMessageBox::information(nullptr,QString::number(column),QString::number(DB));
    field[column].column[field[column].db]=currentPlayer+1;
    //QMessageBox::information(nullptr,QString::number(column),QString::number(DB));
    fieldChange(column,field[column].db++,currentPlayer+1);
    //QMessageBox::information(nullptr,QString::number(column),QString::number(DB));
    currentPlayer=!currentPlayer;
    //print();
    checkGame(column,field[column].db-1);
    if(DB>=columnN*rowN)gameOver();
}

void GameManager::print(){
    for(int j=0;j<rowN;j++){
        for(int i=0;i<columnN;i++){
            std::cout <<field[i].column[j]<<" ";
        }
        std::cout<<std::endl;
    }
    for(int i=0;i<columnN;i++){
        std::cout<<field[i].db<<" ";

    }
    std::cout<<std::endl;
}

void GameManager::checkGame(int column,int row){
    //QMessageBox::information(nullptr,QString::number(column),QString::number(row));
    int won=0;
    int player=field[column].column[row];
    int db=0;
    //Vízszint check
    //std::cout <<"Vízszint check"<<std::endl;
    for(int i=0;i<columnN;i++){
        if(field[i].column[row]==player){
            db++;
        }
        else{
            if(db>=4){
                won=player;
                gameWon(player);
                return;
            }
            else{
                db=0;
            }
        }
    }
    if(db>=4){
        won=player;
        gameWon(player);
        return;
    }
    db=0;
    //Függő check
    //std::cout <<"Függő check"<<std::endl;
    for(int i=0;i<rowN;i++){
        if(field[column].column[i]==player){
            db++;
        }
        else{
            if(db>=4){
                won=player;
                gameWon(player);
                return;
            }
            db=0;
        }
    }
    if(db>=4){
        won=player;
        gameWon(player);
        return;
    }
    db=0;
    int tempCol,tempRow;
    if(column>row){
        tempCol=column-row;
        tempRow=0;
    }
    else{
        tempRow=row-column;
        tempCol=0;
    }
    //Átló check 1
    //std::cout <<"Átlo check 1"<<std::endl;
    while(tempRow<rowN&&tempCol<columnN){
        if(field[tempCol].column[tempRow]==player){
            db++;
        }
        else{
            db=0;
        }
        if(db>=4){
            won=player;
            gameWon(player);
            return;
        }
        tempRow++;
        tempCol++;
    }
    db=0;
    if((columnN-column)<=row){
        tempCol=columnN-1;
        tempRow=row-columnN+column-1;
    }
    else{
        tempCol=column+row;
        tempRow=0;
    }
    //Átló Check 2
    //std::cout <<"Átlo check 2"<<std::endl;
    while(tempRow<rowN&&tempCol>=0){
        if(field[tempCol].column[tempRow]==player){
            db++;
        }

        if(db>=4){
            won=player;
            gameWon(player);
            return;
        }
        tempRow++;
        tempCol--;
    }
    //std::cout<<"Vege"<<std::endl;



}

bool GameManager::loadGame(int index){
    int a=currentPlayer;
    field.resize(0);
    if (!data.loadGame(index, field,currentPlayer, DB)) // az adatelérés végzi a tevékenységeket
        return false;
    rowN=field[0].column.size();
    columnN=field.size();
    tableGraph(columnN,rowN);
    print();
    return true;
}

bool GameManager::saveGame(int index){
    int a=currentPlayer;
    return data.saveGame(index, field,a, DB);
}

void GameManager::setCP(int player){
    currentPlayer=player-1;
}
