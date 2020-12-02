#include <QApplication>
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "QGraphicsPixmapItem"
#include <QTimer>
#include <algorithm>
#include "random"
#include "QMediaPlayer"
#include "Reversi.h"
#include "scrollingbg.h"
#include "virus.h"
#include "reversiPlayer.h"
#include "welcomepage.h"
#include "gameover.h"
#include "QSound"
#include "QMediaPlaylist"



#include "QDebug"

//To add more pressure to the game, players can start with a preset time limit for their total number of moves

Reversi::Reversi(user *activeUser, QWidget *parent)
{
    this->parent = parent;
    this->activeUser = activeUser;

    //Set game state
    this->state = "mainMenu";

    //Players must always make a move that captures at least one tile.
    //The game ends when a player either cannot make a move, or the board is completely full.
    //The player with the most tiles of their color wins.
    //The black always moves first.

    //Start music
    this->song = new QSound("qrc:/static_images/reversi/gameTwoMusic.wav");
    song->setLoops(-1);
    song->play();

    //set player score board
    playerBoard = new QGridLayout;
    playerOneBox = new QVBoxLayout;
    playerTwoBox = new QVBoxLayout;

    playerOneLabel = new QLabel("Player 1");
    playerTwoLabel = new QLabel("Player 2");

    playerOneBox->addWidget(playerOneLabel);
    playerTwoBox->addWidget(playerTwoLabel);

    playerBoard->addItem(playerOneBox,0,0);
    playerBoard->addItem(playerTwoBox,1,0);

    //set up game board
    int row = 0;
    int column = 0;
    for (int i = 0; i < 64; i++){
        if (i%8 == 0) { row++; column = 0;}
        QGraphicsPixmapItem* tile = new QGraphicsPixmapItem();
        tile->setAcceptHoverEvents(true);
        tile->setPixmap((QPixmap(":/static_images/reversi/tile.png")));
        tile->setPos(68*row,68*column);
        gridTiles.push_back(tile);
        column ++;
        this->addItem(tile);
    }

    this->gridState[3][3] = 1;
    this->gridState[3][4] = 2;
    this->gridState[4][4] = 1;
    this->gridState[4][3] = 2;

    this->redrawGrid();

//    //score display
//    this->score = 0;
//    this->scoreStr = new QGraphicsTextItem();
//    this->scoreStr->setPos(5,40);
//    this->scoreStr->setPlainText(QString("Score: %1").arg(this->score));
//    this->scoreStr->hide();
//    this->addItem(scoreStr);

//    //Create a scrolling background
//    scrollingBg* bg =  new scrollingBg();
//    scrollingBg* bg1 =  new scrollingBg(NULL, -3);

//    this->addItem(bg);
//    this->addItem(bg1);
//    this->setSceneRect(0,0,390,620);

    //Add play button
    playButton = new QGraphicsPixmapItem();
    playButton->setPixmap((QPixmap(":/static_images/killCovid/play-circle-solid.svg")).scaled(100,100));
    playButton->setPos(this->QGraphicsScene::width()/2 + 20,this->QGraphicsScene::height()/2 - 50);
    playButton->setFlag(QGraphicsItem::ItemIsSelectable,true);
    this->addItem(playButton);

//    QCheckBox * checkBox = new QCheckBox();
//    QGridLayout * layout = new QGridLayout(this);
//    layout->addWidget(checkBox,0,0,0,0,Qt::AlignBottom | Qt::AlignLeft);
//    //add how-to panel
//    howTo = new QGraphicsPixmapItem();
//    howTo->setPixmap((QPixmap(":/static_images/killCovid/howTo.png")));
//    howTo->setPos(this->width()/2 - 125,this->height()/2 + 50);
//    this->addItem(howTo);

//    //When game starts add these
//    QTimer *timer = new QTimer(this);
//    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(createVirus()));
//    timer->start(3000);


}
//void Reversi::endGame(){

//    song->stop();

//    int score = this->score;

//    if (score>this->activeUser->highScore)
//    {
//        this->activeUser->highScore = score;
//        if (this->activeUser->username != "guest"){ //if not a guest we need to update the database

//            //update the user score in the database
//            QString val;
//            QFile file;
//            file.setFileName("../gameOne/users.json");
//            file.open(QIODevice::ReadWrite | QIODevice::Text);
//            val = file.readAll();

//            QJsonDocument doc;
//            doc = QJsonDocument::fromJson(val.toUtf8());

//            QJsonObject RootObject = doc.object();
//            QJsonObject usersObject = RootObject["users"].toObject();
//            QJsonObject userObject = usersObject[this->activeUser->username].toObject();
//            userObject["high_score"] = score;

//            //update JSON
//            userObject.insert("high_score",score);
//            usersObject[this->activeUser->username] = userObject;
//            RootObject["users"] = usersObject;
//            doc.setObject(RootObject);

//            file.resize(0);
//            file.write(doc.toJson());
//            file.close();
//        }
//    }

//    this->activeUser->currentScore = score;

//    gameOver *gameover = new gameOver(this->activeUser);
//    gameover->show();
//    delete views().first();
////    delete this;
//}

//void Reversi::updateScore(int score){

//    this->score += score;
//    this->scoreStr->setPlainText(QString("Score: %1").arg(this->score));

//    if(this->score > 50){
//        this->speed = 6;
//    }

//    if(this->score > 100){
//        this->speed = 3;
//    }

//    if (this->score == 150)
//    {
//        this->state = "gameOver";
//        this->endGame();
//    }
//}

void Reversi::mousePressEvent(QGraphicsSceneMouseEvent *event){
    if (playButton->isSelected())
    {
    //play button pressed
    playButton->hide();//hide button
    this->activePlayer = 1; //player one (black) is active

    //start timers if applicable

    this->state = "playing";
    }
    else {
        //clicked on tile
        int index = -1;
        QGraphicsItem *item = itemAt(event->scenePos(), QTransform());
        std::vector<QGraphicsPixmapItem*>::iterator it = std::find(gridTiles.begin(), gridTiles.end(), item);
        if (it != gridTiles.end()){
            index = std::distance(gridTiles.begin(), it);
            qDebug() << "Element Found " << index;
        }
        else{
            qDebug() << "Element Not Found";
        }

        if (index > -1){
         //check if valid move
         if (checkMoveIsValid(index)){ //if valid place a token there
             placeNewToken(index);
             redrawGrid();
             togglePlayers();
            }
         }

    }
}

void Reversi::redrawGrid()
{
    for(int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++){
            if (gridState[i][j] == 1){
                int tileIndex = j * 8 + i;
                qDebug() << i << " " << j;
                gridTiles[tileIndex]->setPixmap((QPixmap(":/static_images/reversi/black_token.png")).scaled(67,67));
            }
            else if (gridState[i][j] == 2){
                int tileIndex = j * 8 + i;
                gridTiles[tileIndex]->setPixmap((QPixmap(":/static_images/reversi/white_token.png")).scaled(67,67));
            }
        }
    }
};

void Reversi::togglePlayers(){
    if (this->activePlayer == 1){
        this->activePlayer = 2;
        }
    else{
        this->activePlayer = 1;
    }
};

void Reversi::placeNewToken(int position){
    int row = position%8;
    int column = position/8;
    this->gridState[row][column] = this->activePlayer;

    int i = 0;
    int j = 0;
    //check the left of the tile
    bool valid = false;
    i = column - 1;
    while (i>-1 && gridState[row][column - 1] != this->activePlayer){  //add an exception that the immediate slot be different
    //check if there is a similar token of the active player
        if (gridState[row][i] == this->activePlayer){
            valid = true;
        }
        if (gridState[row][i] == 0){
            break;
        }
        i--;
    }
    //change tiles now
        i = column - 1;
        while (i>-1 && valid){
        //check if there is a similar token of the active player

            if (gridState[row][i] == this->activePlayer  || gridState[row][i] == 0){
                break;
            }
            gridState[row][i] = this->activePlayer;
            i--;
        }

    //check the right
    valid = false;
    i = column + 1;
    while (i<8 && gridState[row][column + 1] != this->activePlayer){
    //check if there is a similar token of the active player
        if (gridState[row][i] == this->activePlayer){
            valid = true;
        }
        if (gridState[row][i] == 0){
            break;
        }
        i++;
    }
    //change tiles now
        i = column + 1;
        while (i<8 && valid){
        //check if there is a similar token of the active player
            if (gridState[row][i] == this->activePlayer  || gridState[row][i] == 0){
                break;
            }
            gridState[row][i] = this->activePlayer;
            i++;
        }

    //check the top
    valid = false;
    i = row - 1;
    while (i>-1 && gridState[row - 1][column] != this->activePlayer){
    //check if there is a similar token of the active player
        if (gridState[i][column] == this->activePlayer){
            valid = true;
        }
        if (gridState[i][column] == 0){
            break;
        }
        i--;
    }
        //change tiles now
        i = row - 1;
        while (i>-1 && valid){
    //check if there is a similar token of the active player
        if (gridState[i][column] == this->activePlayer  || gridState[i][column] == 0){
            break;
        }
        gridState[i][column] = this->activePlayer;
        i--;
    }

    //check the bottom
    valid = false;
    i = row + 1;
    while (i<8 && gridState[row + 1][column] != this->activePlayer){
    //check if there is a similar token of the active player
        if (gridState[i][column] == this->activePlayer){
            valid = true;
        }
        if (gridState[i][column] == 0){
            break;
        }
        i++;
    }
        //change the tiles now
        i = row + 1;
        while (i<8 && valid){
    //check if there is a similar token of the active player
        if (gridState[i][column] == this->activePlayer  || gridState[i][column] == 0){
            break;
        }
        gridState[i][column] = this->activePlayer;
        i++;
    }

    //check upper left
    valid = false;
    i = row - 1;
    j = column - 1;
    while (i>-1 && j>-1 && gridState[row - 1][column - 1] != this->activePlayer){
    //check if there is a similar token of the active player
        if (gridState[i][j] == this->activePlayer){
            valid = true;
        }
        if (gridState[i][j] == 0){
            break;
        }
        i--;
        j--;
    }
       //change tiles now
        i = row - 1;
        j = column - 1;
        while (i>-1 && j>-1 && valid){
    //check if there is a similar token of the active player
        if (gridState[i][j] == this->activePlayer  || gridState[i][j] == 0){
            break;
        }
        gridState[i][j] = this->activePlayer;
        i--;
        j--;
    }

    //check upper right
    valid = false;
    i = row - 1;
    j = column + 1;
    while (i>-1 && j<8 && gridState[row - 1][column + 1] != this->activePlayer){
    //check if there is a similar token of the active player
        if (gridState[i][j] == this->activePlayer){
            valid = true;
        }
        if (gridState[i][j] == 0){
            break;
        }
        i--;
        j++;
    }
        //change tiles now
        i = row - 1;
        j = column + 1;
        while (i>-1 && j<8 && valid){
    //check if there is a similar token of the active player
        if (gridState[i][j] == this->activePlayer  || gridState[i][j] == 0){
            break;
        }
        gridState[i][j] = this->activePlayer;
        i--;
        j++;
    }

   //check lower right
    valid = false;
    i = row + 1;
    j = column + 1;
    while (i<8 && j<8 && gridState[row + 1][column + 1] != this->activePlayer){
    //check if there is a similar token of the active player
        if (gridState[i][j] == this->activePlayer){
            valid = true;
        }
        if (gridState[i][j] == 0){
            break;
        }
        i++;
        j++;
    }
        //change tiles now
        i = row + 1;
        j = column + 1;
        while (i<8 && j<8 && valid){
        //check if there is a similar token of the active player
            if (gridState[i][j] == this->activePlayer  || gridState[i][j] == 0){
                break;
            }
            gridState[i][j] = this->activePlayer;
            i++;
            j++;
        }

    //check lower left
    valid = false;
    i = row + 1;
    j = column - 1;
    while (i<8 && j>-1 && gridState[row + 1][column - 1] != this->activePlayer){
    //check if there is a similar token of the active player
        if (gridState[i][j] == this->activePlayer){
            valid = true;
        }

        if (gridState[i][j] == 0){
            break;
        }
        i++;
        j--;
    }
        //change tiles now
        i = row + 1;
        j = column - 1;
        while (i<8 && j>-1 && valid){
    //check if there is a similar token of the active player
        if (gridState[i][j] == this->activePlayer || gridState[i][j] == 0){
             break;
        }
        gridState[i][j] = this->activePlayer;
        i++;
        j--;
    }
}

bool Reversi::checkMoveIsValid(int position){
    int row = position%8;
    int column = position/8;
    qDebug() << "Clicked: " << row << "," << column;

    if(this->gridState[row][column] != 0){ //place taken
    return false;
    }
    int i = 0;
    int j = 0;
    //check the left of the tile
    i = column - 1;
    while (i>-1 && gridState[row][column - 1] != this->activePlayer){ //add an exception that the immediate slot be different
    //check if there is a similar token of the active player
        if (gridState[row][i] == this->activePlayer){
            return true;
        }
        if (gridState[row][i] == 0){
            break;
        }
        i--;
    }
    //check the right
    i = column + 1;
    while (i<8 && gridState[row][column + 1] != this->activePlayer){
    //check if there is a similar token of the active player
        if (gridState[row][i] == this->activePlayer){
            return true;
        }
        if (gridState[row][i] == 0){
            break;
        }
        i++;
    }
    //check the top
    i = row - 1;
    while (i>-1 && gridState[row - 1][column] != this->activePlayer){
    //check if there is a similar token of the active player
        if (gridState[i][column] == this->activePlayer){
            return true;
        }
        if (gridState[i][column] == 0){
            break;
        }
        i--;
    }
    //check the bottom
    i = row + 1;
    while (i<8 && gridState[row + 1][column] != this->activePlayer){
    //check if there is a similar token of the active player
        if (gridState[i][column] == this->activePlayer){
            return true;
        }
        if (gridState[i][column] == 0){
            break;
        }
        i++;
    }
    //check upper left
    i = row - 1;
    j = column - 1;
    while (i>-1 && j>-1 && gridState[row - 1][column - 1] != this->activePlayer){
    //check if there is a similar token of the active player
        if (gridState[i][j] == this->activePlayer){
            return true;
        }
        if (gridState[i][j] == 0){
            break;
        }
        i--;
        j--;
    }
    //check upper right
    i = row - 1;
    j = column + 1;
    while (i>-1 && j<8 && gridState[row - 1][column + 1] != this->activePlayer){
    //check if there is a similar token of the active player
        if (gridState[i][j] == this->activePlayer){
            return true;
        }
        if (gridState[i][j] == 0){
            break;
        }
        i--;
        j++;
    }
    //check lower right
    i = row + 1;
    j = column + 1;
    while (i<8 && j<8 && gridState[row + 1][column + 1] != this->activePlayer){
    //check if there is a similar token of the active player
        if (gridState[i][j] == this->activePlayer){
            return true;
        }
        if (gridState[i][j] == 0){
            break;
        }
        i++;
        j++;
    }
    //check lower left
    i = row + 1;
    j = column - 1;
    while (i<8 && j>-1 && gridState[row + 1][column - 1] != this->activePlayer){
    //check if there is a similar token of the active player
        if (gridState[i][j] == this->activePlayer){
            return true;
        }

        if (gridState[i][j] == 0){
            break;
        }
        i++;
        j--;
    }

    return false;
}

