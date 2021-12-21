#include "loadgame.h"
#include <QMessageBox>


LoadGame::LoadGame():CustomDialog(){
    setWindowTitle("Tic-Tac-Toe - Játék betöltése");

    // ellenőrzést is végzünnk az OK gomb lenyomására
    disconnect(_okButton, SIGNAL(clicked()), this, SLOT(accept()));
    connect(_okButton, SIGNAL(clicked()), this, SLOT(okButton_Clicked()));
}

void LoadGame::okButton_Clicked()
{
    if (_listWidget->currentItem()->text() == "üres")
    {
        // ha üres mezőt választott, akkor nem engedjük tovább
        QMessageBox::warning(this, trUtf8("Tic-Tac-Toe"), trUtf8("Nincs játék kiválasztva!"));
        return;
    }

    accept(); // különben elfogadjuk a dialógust
}
