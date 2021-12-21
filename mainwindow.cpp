#include "mainwindow.h"
#include <QMessageBox>
#include <QMouseEvent>
#include <QPainter>
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    setMinimumSize(800,600);
    setBaseSize(800,600);
    setMaximumSize(800,600);
    setWindowTitle("Connect4");

    //load/saveWindow

    list = new QListWidget(this);
    list->addItem("8x5");
    list->addItem("10x6");
    list->addItem("12x7");

    btn= new QPushButton(this);

    float x=list->geometry().right();
    float y=(list->geometry().bottom()-geometry().top())/2;

    btn->setGeometry(x*2.7+10,y*2.7,100,30);
    btn->setText("Indítás");

    load= new QPushButton(this);
    load->setGeometry(x*2.7,y*2.7+40,120,30);
    load->setText("Mentés betöltése");

    save= new QPushButton(this);
    save->setGeometry(350,30,100,30);
    save->setText("Mentés");
    save->setHidden(true);

    lbl_curr_player=new QLabel("1",this);
    lbl_curr_player->setHidden(true);
    lbl_curr_player->setGeometry(350,100,50,25);

    connect(&gm,SIGNAL(gameWon(int)),this,SLOT(gm_gameWon(int)));
    connect(&gm,SIGNAL(fieldChange(int,int,int)),this,SLOT(gm_fieldChanged(int,int,int)));
    connect(&gm,SIGNAL(gameOver()),this,SLOT(gm_gameOver()));
    connect(&gm,SIGNAL(tableGraph(int,int)),SLOT(gm_tableGraph(int,int)));
    connect(btn,SIGNAL(released()),this,SLOT(newGame()));
    connect(load,SIGNAL(clicked()),this,SLOT(btn_loadGame()));
    connect(save,SIGNAL(clicked()),this,SLOT(btn_saveGame()));

    _tableGraphics.clear();

    ld= new LoadGame();
    sd= new SaveGame();
    connect(sd, SIGNAL(accepted()), this, SLOT(saveGame()));
    connect(ld, SIGNAL(accepted()), this, SLOT(loadGame()));

}

MainWindow::~MainWindow(){

}

void MainWindow::btn_loadGame(){
    if (ld == nullptr) // ha még egyszer sem nyitották meg az ablakot
           {
               ld = new LoadGame();
               connect(ld, SIGNAL(accepted()), this, SLOT(loadGame()));
           }

           // beállítjuk a listát, és megnyitjuk az ablakot
           ld->setGameList(gm.saveGameList());
           ld->open();
}

void MainWindow::btn_saveGame(){
    if (sd == nullptr) // ha még egyszer sem nyitották meg az ablakot
    {
        sd = new SaveGame();
        connect(sd, SIGNAL(accepted()), this, SLOT(saveGame()));
    }

    // beállítjuk a listát, és megnyitjuk az ablakot
    sd->setGameList(gm.saveGameList());
    sd->open();
}

void MainWindow::saveGame(){
    // elmentjük a kiválasztott játékot
    std::cout << sd->selectedGame();
    if (gm.saveGame(sd->selectedGame()))
    {
        update();
        QMessageBox::information(this, trUtf8("Tic-Tac-Toe"), trUtf8("Játék sikeresen mentve!"));
    }
    else
    {
        QMessageBox::warning(this, trUtf8("Tic-Tac-Toe"), trUtf8("A játék mentése sikertelen!"));
    }
}

void MainWindow::loadGame(){
    // betöltjük a kiválasztott játékot
    if (gm.loadGame(ld->selectedGame()))
    {
        update();
        QMessageBox::information(this, trUtf8("JTic-Tac-Toe"), trUtf8("Játék betöltve"));
    }
    else
    {
        QMessageBox::warning(this, trUtf8("Tic-Tac-Toe"), trUtf8("A játék betöltése sikertelen!"));
    }
}

void MainWindow::gm_tableGraph(int n, int m){
    cellWidth=200.0f/(n+2);
    _tableGraphics.clear();
    _player1.clear();
    _player1.append(QLineF(0,0,cellWidth,cellWidth));
    _player1.append(QLineF(cellWidth,0,0,cellWidth));
    _player2=QRect(0,0,cellWidth,cellWidth);
    for(int i=1;i<=n+1;i++){
        _tableGraphics.append(QLineF(cellWidth*i, 200-(cellWidth*m), cellWidth*i, 200));
    }

    for(int i=0;i<m;i++){
        _tableGraphics.append(QLineF(cellWidth,200-(cellWidth*m)+(cellWidth*i),200-cellWidth,200-(cellWidth*m)+(cellWidth*i)));
    }
    changeState(1);
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if(state){
        int x = event->pos().x();
        gm.place(x); // játék léptetése
    }
}

void MainWindow::gm_gameWon(int player){
    QMessageBox::information(this,tr("Győzelem"),QString::number(player)+"-es játékos nyert");
    changeState(0);
}

void MainWindow::gm_gameOver(){
    QMessageBox::information(this,tr("title"),tr("Tie"));
    changeState(0);
}

void MainWindow::changeState(int _state){
    switch (_state) {
        case 0:
            list->setHidden(false);
            btn->setHidden(false);
            lbl_curr_player->setHidden(true);
            load->setHidden(false);
            save->setHidden(true);
            _tableGraphics.clear();
            update();
            state=0;
            break;
        case 1:
            list->setHidden(true);
            btn->setHidden(true);
            lbl_curr_player->setHidden(false);
            load->setHidden(true);
            save->setHidden(false);
            update();
            state=1;
            break;
    }
}

void MainWindow::gm_fieldChanged(int x,int y,int player){
    if(player==1)
        lbl_curr_player->setText("2");
    else
        lbl_curr_player->setText("1");
    update();
}

void MainWindow::newGame(){
    if(list->selectedItems().length()>1){

    }
    else{
        _tableGraphics.clear();
        gm.newGame(list->currentRow()+1);
        changeState(1);
        lbl_curr_player->setText(QString::number(gm.getCP()));
    }
}

void MainWindow::paintEvent(QPaintEvent *)
{
    if(state){
        QPainter painter(this); // rajzoló objektum
        painter.setRenderHint(QPainter::Antialiasing); // élsimítás használata
        painter.scale(width() / 200.0, height() / 200.0); // skálázás

        painter.setPen(QPen(Qt::black, 2)); // toll beállítása
        painter.setBrush(Qt::red); // ecset beállítása
        painter.drawLines(_tableGraphics); // tábla kirajzolása

        for(int i=0;i<gm.getColumn();i++){
            for(int j=0;j<gm.getRow();j++){
                painter.save(); // elmentjük a rajztulajdonságokat
                painter.translate(i * cellWidth + cellWidth , 200-((gm.getRow()*cellWidth)-(gm.getRow()-1-j) * cellWidth)); // elmozdítjuk a rajzpontot a megfelelő mezőre
                switch(gm.getField(i,j)){
                    case 1:
                        painter.drawLines(_player1);
                        break;
                    case 2:
                        painter.drawRect(_player2);
                        break;
                }
                painter.restore();
            }
        }
    }

}

