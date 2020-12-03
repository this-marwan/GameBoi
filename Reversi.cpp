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
#include "welcomepage.h"
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
    QMediaPlaylist *playlist = new QMediaPlaylist();
    playlist->addMedia(QUrl("qrc:/static_images/reversi/gameTwoMusic.wav"));
    playlist->setPlaybackMode(QMediaPlaylist::Loop);

    this->music = new QMediaPlayer();
    this->music->setVolume(25);
    this->music->setPlaylist(playlist);
    this->music->play();

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

    //score display
        //for player one

    this->playerOneBox = new QGraphicsPixmapItem();
    this->playerOneBox->setPixmap((QPixmap(":/static_images/reversi/playerOneActiveBoard.png")));
    this->playerOneBox->setPos(-20,30);
    this->addItem(playerOneBox);

    this->playerOneLabel = new QGraphicsTextItem();
    this->playerOneLabel->setDefaultTextColor("white");
    this->playerOneLabel->setPos(-20,40);
    this->playerOneLabel->setPlainText(QString("Player One"));
    this->addItem(playerOneLabel);

    this->playerOneDiscsLabel = new QGraphicsTextItem();
    this->playerOneDiscsLabel->setDefaultTextColor("white");
    this->playerOneDiscsLabel->setPos(-20,60);
    this->playerOneDiscsLabel->setPlainText(QString("Discs Left: %1").arg(this->playerOneDiscsLeft));
    this->addItem(playerOneDiscsLabel);

    this->playerOneScoreLabel = new QGraphicsTextItem();
    this->playerOneScoreLabel->setDefaultTextColor("white");
    this->playerOneScoreLabel->setPos(-20,80);
    this->playerOneScoreLabel->setPlainText(QString("Score: %1").arg(this->playerOneScore));
    this->addItem(playerOneScoreLabel);

        //for player two
    this->playerTwoBox = new QGraphicsPixmapItem();
    this->playerTwoBox->setPixmap((QPixmap(":/static_images/reversi/playerTwoActiveBoard.png")));
    this->playerTwoBox->setPos(-20,130);
    this->addItem(playerTwoBox);

    this->playerTwoLabel = new QGraphicsTextItem();
    this->playerTwoLabel->setPos(-20,140);
    this->playerTwoLabel->setPlainText(QString("Player Two"));
    this->addItem(playerTwoLabel);

    this->playerTwoDiscsLabel = new QGraphicsTextItem();
    this->playerTwoDiscsLabel->setPos(-20,160);
    this->playerTwoDiscsLabel->setPlainText(QString("Discs Left: %1").arg(this->playerTwoDiscsLeft));
    this->addItem(playerTwoDiscsLabel);

    this->playerTwoScoreLabel = new QGraphicsTextItem();
    this->playerTwoScoreLabel->setPos(-20,180);
    this->playerTwoScoreLabel->setPlainText(QString("Score: %1").arg(this->playerTwoScore));
    this->addItem(playerTwoScoreLabel);

    //Add play button
    playButton = new QGraphicsPixmapItem();
    playButton->setPixmap((QPixmap(":/static_images/killCovid/play-circle-solid.svg")).scaled(100,100));
    playButton->setPos(this->QGraphicsScene::width()/2 - 25,this->QGraphicsScene::height()/2 - 50);
    playButton->setFlag(QGraphicsItem::ItemIsSelectable,true);
    this->addItem(playButton);

    //Add try again button
    playAgainButton = new QGraphicsPixmapItem();
    playAgainButton->setPixmap((QPixmap(":/static_images/reversi/playAgainButton.png")));
    playAgainButton->setPos(this->QGraphicsScene::width()/2 + 65,this->QGraphicsScene::height()/2 - 50);
    playAgainButton->setFlag(QGraphicsItem::ItemIsSelectable,true);
    playAgainButton->hide();
    this->addItem(playAgainButton);

    //Add return to main menu button
    returnToMenuButton = new QGraphicsPixmapItem();
    returnToMenuButton->setPixmap((QPixmap(":/static_images/reversi/returnToMenuButton.png")));
    returnToMenuButton->setPos(this->QGraphicsScene::width()/2 - 65,this->QGraphicsScene::height()/2 - 50);
    returnToMenuButton->setFlag(QGraphicsItem::ItemIsSelectable,true);
    returnToMenuButton->hide();
    this->addItem(returnToMenuButton);

    // add background color
    QGraphicsRectItem *rect_item1 = this->addRect(-20,-20,this->width() + 5, this->height() + 20);
    rect_item1->setZValue(-10);
    rect_item1->setBrush(QColor(129, 91, 64));

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

void Reversi::mousePressEvent(QGraphicsSceneMouseEvent *event){
    if (playButton->isSelected())
    {
    //play button pressed
    playButton->hide();//hide button
    this->activePlayer = 1; //player one (black) is active

    //start timers if applicable

    this->state = "playing";
    showHints(); //changes game state
    redrawGrid(true); //show hints

    togglePlayers(); //changes players
    togglePlayers(); //changes players
    }
    else if (this->state == "playing"){
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
             placeNewToken(index); //changes game state
             redrawGrid(); //changes scene
             updateScore(); //updates score board
             togglePlayers(); //changes players
             showHints(); //changes game state
             redrawGrid(true);
             endGame(); //checks if the game has ended
            }
         }

    }
    else if (this->state == "gameOver"){
        if (playAgainButton->isSelected())
        {
            //play again
            //reset all variables
            for(int i = 0; i < 8; i++){
                for (int j = 0; j < 8; j++){
                    gridState[i][j] = 0;
                }
            }

            this->playerOneScore = 0;
            this->playerTwoScore = 0;
            this->playerOneDiscsLeft = 30;
            this->playerTwoDiscsLeft = 30;

            playAgainButton->hide();
            returnToMenuButton->hide();

            this->gridState[3][3] = 1;
            this->gridState[3][4] = 2;
            this->gridState[4][4] = 1;
            this->gridState[4][3] = 2;

            this->activePlayer = 1;

            showHints(); //changes game state
            redrawGrid(true); //show hints

            togglePlayers(); //changes players
            togglePlayers(); //changes players

            this->redrawGrid(true);

            this->state = "playing";
        }
        if (returnToMenuButton->isSelected()){
            //return us to the main menu
            this->music->stop();
            welcomePage *window1 = new welcomePage(activeUser);
            window1->show();
            delete views().first();
        }
    }
}

void Reversi::endGame(){
    //the game ends when
    //both players run out of discs - this implies no valid moves
    //both player no longr have valid moves
    int temp = this->activePlayer;

    this->activePlayer = 1;
    //check if player one has valid moves
    bool hasValidMoves = false;
    for(int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++){
                int tileIndex = j * 8 + i;
                if (checkMoveIsValid(tileIndex)){
                    hasValidMoves = true;
            }
        }
    }
   if (hasValidMoves && this->playerOneDiscsLeft > 0)
   {
        this->activePlayer = temp;
        return;
   }


   this->activePlayer = 2;
   //check if player two has valid moves
   hasValidMoves = false;
   for(int i = 0; i < 8; i++){
       for (int j = 0; j < 8; j++){
               int tileIndex = j * 8 + i;
               if (checkMoveIsValid(tileIndex)){
                   hasValidMoves = true;
           }
       }
   }
  if (hasValidMoves && this->playerTwoDiscsLeft > 0)
  {
       this->activePlayer = temp;
       return;
  }


  //if we are here the game has ended

   this->activePlayer = temp;
   this->state = "gameOver";

  qDebug() << "Game ended";


  int score = 0;
  if (playerOneScore>playerTwoScore)
  {
    score = playerOneScore;
  }
  else {
    score = playerTwoScore;
  }

  //update the database if this is a new highscore
  if (score>this->activeUser->highScoreReversi)
  {
      this->activeUser->highScoreReversi = score;
      if (this->activeUser->username != "guest"){ //if not a guest we need to update the database

          //update the user score in the database
          QString val;
          QFile file;
          file.setFileName("../gameOne/users.json");
          file.open(QIODevice::ReadWrite | QIODevice::Text);
          val = file.readAll();

          QJsonDocument doc;
          doc = QJsonDocument::fromJson(val.toUtf8());

          QJsonObject RootObject = doc.object();
          QJsonObject usersObject = RootObject["users"].toObject();
          QJsonObject userObject = usersObject[this->activeUser->username].toObject();
          userObject["high_score_reversi"] = score;

          //update JSON
          userObject.insert("high_score_reversi",score);
          usersObject[this->activeUser->username] = userObject;
          RootObject["users"] = usersObject;
          doc.setObject(RootObject);

          file.resize(0);
          file.write(doc.toJson());
          file.close();
      }
  }


  //show game over banner and the winner

  //show buttons to repeat game or leave
   playAgainButton -> show();
   returnToMenuButton -> show();
}

void Reversi::updateScore(){
    int playerOne = 0;
    int playerTwo = 0;
    for(int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++){
             if (gridState[i][j] == 1){
               playerOne++;
             }
             else if (gridState[i][j] == 2){
                 playerTwo++;
             }
        }
    }
    this->playerOneScore = playerOne;
    this->playerTwoScore = playerTwo;

    this->playerOneScoreLabel->setPlainText(QString("Score: %1").arg(this->playerOneScore));
    this->playerTwoScoreLabel->setPlainText(QString("Score: %1").arg(this->playerTwoScore));

};

void Reversi::showHints(){
    for(int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++){
                int tileIndex = j * 8 + i;
                if (gridState[i][j] == -1){ //remove previous hints if they exist
                    gridState[i][j] = 0;
                }
                if (checkMoveIsValid(tileIndex)){
                    gridState[i][j] = -1;
            }
        }
    }
};

void Reversi::redrawGrid(bool hint)
{
    for(int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++){
            if (gridState[i][j] == 1){
                int tileIndex = j * 8 + i;
                gridTiles[tileIndex]->setPixmap((QPixmap(":/static_images/reversi/black_token.png")));
            }
            else if (gridState[i][j] == 2){
                int tileIndex = j * 8 + i;
                gridTiles[tileIndex]->setPixmap((QPixmap(":/static_images/reversi/white_token.png")));
            }
            else if (gridState[i][j] == -1 && hint){
                int tileIndex = j * 8 + i;
                gridTiles[tileIndex]->setPixmap((QPixmap(":/static_images/reversi/hint.png")));
            }
            else{
                int tileIndex = j * 8 + i;
                gridTiles[tileIndex]->setPixmap((QPixmap(":/static_images/reversi/tile.png")));
            }
        }
    }
};

void Reversi::togglePlayers(){
    //to switch players we need to make sure the next player:
    //1. has enough discs
    //2. has valid moves

    if (this->activePlayer == 1){
        if (this->playerTwoDiscsLeft > 0){
            this->activePlayer = 2;
            bool valid = false;
            for(int i = 0; i < 8; i++){
                for (int j = 0; j < 8; j++){
                        int tileIndex = j * 8 + i;
                        if (checkMoveIsValid(tileIndex)){ //check if any of the moves are valid
                            valid = true;
                            break;
                        }
                }
            }
            if (!valid){ //if no valid moves exist revert to player one
                this->activePlayer = 1;
            }
        };
        }
    else{
        if (this->playerOneDiscsLeft > 0){
            this->activePlayer = 1;
            bool valid = false;
            for(int i = 0; i < 8; i++){
                for (int j = 0; j < 8; j++){
                        int tileIndex = j * 8 + i;
                        if (checkMoveIsValid(tileIndex)){ //check if any of the moves are valid
                            valid = true;
                            break;
                        }
                }
            }
            if (!valid){ //if no valid moves exist revert to player two
                this->activePlayer = 2;
            }
        };
    }

   //now set the player board to refelct the changes above
    if (activePlayer == 1){
        this->playerOneBox->setPixmap((QPixmap(":/static_images/reversi/playerOneActiveBoard.png")));
        this->playerTwoBox->setPixmap((QPixmap(":/static_images/reversi/playerTwoPassiveBoard.png")));
    }
    else
    {
        this->playerOneBox->setPixmap((QPixmap(":/static_images/reversi/playerOnePassiveBoard.png")));
        this->playerTwoBox->setPixmap((QPixmap(":/static_images/reversi/playerTwoActiveBoard.png")));
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
        if (gridState[row][i] <= 0){
            break;
        }
        i--;
    }
    //change tiles now
        i = column - 1;
        while (i>-1 && valid){
        //check if there is a similar token of the active player

            if (gridState[row][i] == this->activePlayer  || gridState[row][i] <= 0){
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
        if (gridState[row][i] <= 0){
            break;
        }
        i++;
    }
    //change tiles now
        i = column + 1;
        while (i<8 && valid){
        //check if there is a similar token of the active player
            if (gridState[row][i] == this->activePlayer  || gridState[row][i] <= 0){
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
        if (gridState[i][column] <= 0){
            break;
        }
        i--;
    }
        //change tiles now
        i = row - 1;
        while (i>-1 && valid){
    //check if there is a similar token of the active player
        if (gridState[i][column] == this->activePlayer  || gridState[i][column] <= 0){
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
        if (gridState[i][column] <= 0){
            break;
        }
        i++;
    }
        //change the tiles now
        i = row + 1;
        while (i<8 && valid){
    //check if there is a similar token of the active player
        if (gridState[i][column] == this->activePlayer  || gridState[i][column] <= 0){
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
        if (gridState[i][j] <= 0){
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
        if (gridState[i][j] == this->activePlayer  || gridState[i][j] <= 0){
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
        if (gridState[i][j] <= 0){
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
        if (gridState[i][j] == this->activePlayer  || gridState[i][j] <= 0){
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
        if (gridState[i][j] <= 0){
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
            if (gridState[i][j] == this->activePlayer  || gridState[i][j] <= 0){
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

        if (gridState[i][j] <= 0){
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
        if (gridState[i][j] == this->activePlayer || gridState[i][j] <= 0){
             break;
        }
        gridState[i][j] = this->activePlayer;
        i++;
        j--;
    }


    if (this->activePlayer == 1){
        this->playerOneDiscsLeft--;
       }
    else{
        this->playerTwoDiscsLeft--;
       }

    this->playerOneDiscsLabel->setPlainText(QString("Discs Left: %1").arg(this->playerOneDiscsLeft));
    this->playerTwoDiscsLabel->setPlainText(QString("Discs Left: %1").arg(this->playerTwoDiscsLeft));

    return;
}

bool Reversi::checkMoveIsValid(int position){
    int row = position%8;
    int column = position/8;
    qDebug() << "Clicked: " << row << "," << column;

    if(this->gridState[row][column] > 0){ //place taken
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
        if (gridState[row][i] <= 0){
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
        if (gridState[row][i] <= 0){
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
        if (gridState[i][column] <= 0){
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
        if (gridState[i][column] <= 0){
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
        if (gridState[i][j] <= 0){
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
        if (gridState[i][j] <= 0){
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
        if (gridState[i][j] <= 0){
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

        if (gridState[i][j] <= 0){
            break;
        }
        i++;
        j--;
    }

    return false;
}

