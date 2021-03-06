#include "game.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <QPainter>
#include <QApplication>
#include <QThread>
#include <QMessageBox>

Game::Game(QWidget *parent) : QWidget(parent) {

    x = 0;
    score = 0;
    highscore = 0;
    gameOver = false;
    paused = false;
    gameStarted = false;
    food = new Food((rand()%70)*10, (rand()%50)*10);
    snake = new Snake(230, 350, 5);
    setDifficulty.exec();
    music = new QMediaPlayer();
    QMediaPlaylist *playlist = new QMediaPlaylist();
    playlist->addMedia(QUrl("qrc:/sound/bigCarTheftJasonShaw.mp3"));
    playlist->setPlaybackMode(QMediaPlaylist::Loop);
    music->setPlaylist(playlist);
    /*QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Menu", "What Level do you want",QMessageBox::Save | QMessageBox::Ok | QMessageBox::Abort);

    //QMessageBox::setButtonText(QMessageBox::Save, trUtf8("Easy"));

    if (reply == QMessageBox::Ok) {
        num = 100;
    }
    if (reply == QMessageBox::Save)
    {num = 20;}
    if(reply == QMessageBox::Abort)
    { num=4;}*/
    if (setDifficulty.clickedButton() == easy) {
        num = 100;
    }
    if (setDifficulty.clickedButton() == medium)
    {num = 30;}
    if(setDifficulty.clickedButton() == hard)
    { num=10;}
}

Game::~Game() {
    delete food;
    delete snake;
}

void Game::paintEvent(QPaintEvent *event) {
    QPainter painter(this);

    if (gameOver) {
        QFont font("Courier", 15, QFont::DemiBold);
        QFontMetrics fm(font);
        int textWidth = fm.width("Game Over");
        painter.setFont(font);
        int h = height();
        int w = width();

        painter.translate(QPoint(w/2, h/2));
        painter.drawText(-textWidth/2, 0, "Game Over");

        if (newhigh == true) {
            int textWidth2 = fm.width("New High Score: ");
            int textWidth3 = fm.width(QString::number(highscore));
            painter.drawText(-textWidth2/2, 20, "New High Score: ");
            painter.drawText(-textWidth3/2, 40, QString::number(highscore));
/*
            QMessageBox::StandardButton reply;
            reply = QMessageBox::question(this, "Menu", "What Level do you want",QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);

            //QMessageBox::setButtonText(QMessageBox::Save, trUtf8("Easy"));
            num = 40;
            if (reply == QMessageBox::Save) {
                num = 40; startGame();
            }
            if (reply == QMessageBox::Discard)
            {num = 20; startGame();}
            if(reply == QMessageBox::Cancel)
            { num=4; startGame();}
*/
        }
        else {
            int textWidth2 = fm.width("Last Score: ");
            int textWidth3 = fm.width(QString::number(score));
            painter.drawText(-textWidth2/2, 20, "Last Score: ");
            painter.drawText(-textWidth3/2, 40, QString::number(score));
            int textWidth4 = fm.width("High Score: ");
            int textWidth5 = fm.width(QString::number(highscore));
            painter.drawText(-textWidth4/2, 60, "High Score: ");
            painter.drawText(-textWidth5/2, 80, QString::number(highscore));

           /*
           QMessageBox::StandardButton reply;
            reply = QMessageBox::question(this, "Menu", "What Level do you want: \n Save = easy  Discard = medium  Cancel = hard ",QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);

            //QMessageBox::setButtonText(QMessageBox::Save, trUtf8("Easy"));
            num = 40;
            if (reply == QMessageBox::Save) {
                num = 40; startGame();
            }
            if (reply == QMessageBox::Discard)
            {num = 20; startGame();}
            if(reply == QMessageBox::Cancel)
            { num=4; startGame();}
  */
        }
    }
    else {
        QFont font("Courier", 10, QFont::DemiBold);
        int w = width();
        painter.setFont(font);
        painter.drawText(QPoint(w/2-35, 20), "Score: " + QString::number(score));
        painter.drawImage(food->getRect(), food->getImage());
        Snake::SegmentIterator iter;
        for (iter = snake->segments.begin(); iter != snake->segments.end(); ++iter) {
            painter.drawImage(iter->rect , iter->image);

        }
    }
}

void Game::timerEvent(QTimerEvent *event) {
 /*  QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Save", "What Level do you want",
                                  QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
int num;
    if (reply == QMessageBox::Save) {

        num = 40;
    }
    if (reply == QMessageBox::Discard)
    {
       // snake->move();
       // checkCollision();
       // QThread::msleep(20);
       // repaint();
       num = 20;
    }
    if(reply == QMessageBox::Cancel)
    {
        num=4;
    }
*/
    snake->move();
    checkCollision();
    QThread::msleep(num);
    repaint();
}

void Game::keyPressEvent(QKeyEvent *event) {
    switch (event->key()) {
    case Qt::Key_Left:
         snake->dir = Snake::LEFT;
       break;
    case Qt::Key_Right:
          snake->dir = Snake::RIGHT;
        break;
    case Qt::Key_Up:
          snake->dir = Snake::UP;
        break;
    case Qt::Key_Down:
          snake->dir = Snake::DOWN;
        break;
    case Qt::Key_A:
         snake->dir = Snake::LEFT;
       break;
    case Qt::Key_D:
          snake->dir = Snake::RIGHT;
        break;
    case Qt::Key_W:
          snake->dir = Snake::UP;
        break;
    case Qt::Key_S:
          snake->dir = Snake::DOWN;
        break;
    case Qt::Key_Enter:
          pauseGame();
        break;
    case Qt::Key_Space:
          startGame();
        break;
    case Qt::Key_Escape:
          qApp->exit();
        break;
    default:
        QWidget::keyPressEvent(event);
    }
    repaint();
}


void Game::startGame() {
    if (!gameStarted) {
        snake = new Snake(230, 355, 5);
        gameOver = false;
        score = 0;
        newhigh = false;
        gameStarted = true;
        timerId = startTimer(10);
        music->play();
    }
}

void Game::pauseGame() {
    if (paused) {
        timerId = startTimer(10);
        paused = false;
    } else {
        paused = true;
        killTimer(timerId);
    }
}

void Game::stopGame() {
    delete snake;
    music->stop();
    killTimer(timerId);
    gameOver = true;
    if (score > highscore) {
        highscore = score;
        newhigh = true;
    }
    gameStarted = false;
}

void Game::checkCollision() {

    if (snake->head().rect.bottom() >= this->height() || snake->head().rect.top() <= 0 || snake->head().rect.left() <= 0 || snake->head().rect.right() >= this->width())
        stopGame();

    if ((snake->head().rect).intersects(food->getRect())) {
        food->setDestroyed(true);
        int newx = (rand()%70)*10;
        int newy = (rand()%50)*10;
        /*while(snake->checkOverlap(newx, newy)){
            int newx = (rand()%70)*10;
            int newy = (rand()%50)*10;
        }*/
        if(newx == this->width() - 1 && newy == this->height() - 1){
            food = new Food(newx-20, newy-20);
        }
        else if(newx >= this->width() - 20){
            food = new Food(newx-20, newy);
        }
        else if(newy >= this->height() - 20){
            food = new Food(newx, newy-20);
        }
        else{
            food = new Food(newx, newy);
        }
        snake->growBy(1);
        score += 1;
    }

    Snake::SegmentIterator iter;
    for (iter = ++snake->segments.begin(); iter != snake->segments.end(); ++iter)
        if (iter->x == snake->head().x && iter->y == snake->head().y)
            stopGame();
}

void Game::setNum(int n){
    num = n;
}
