#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <vector>
#include <QVector>
#include <QListWidget>
#include <QPushButton>
#include <QLabel>
#include "gamemanager.h"
#include "loadgame.h"
#include "savegame.h"

using std::vector;

class MainWindow : public QWidget
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void gm_gameWon(int player);
    void gm_gameOver();
    void gm_fieldChanged(int,int,int);
    void gm_tableGraph(int,int);
    void newGame();
    void loadGame();
    void saveGame();
    void btn_loadGame();
    void btn_saveGame();

private:
    bool state;
    float cellWidth;
    GameManager gm;
    QVector<QLineF> _tableGraphics;
    QVector<QLineF> _player1;
    QRect _player2;

    QListWidget* list;
    QPushButton* btn;
    QPushButton* load;
    QPushButton* save;
    QLabel* lbl_curr_player;

    LoadGame* ld;
    SaveGame* sd;

    void changeState(int);
    void paintEvent(QPaintEvent *event);
    //void keyPressEvent(QKeyEvent *event);
    void mousePressEvent(QMouseEvent *event);
};
#endif // MAINWINDOW_H
