#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QTimer>
#include "bunker.h"
#include "enemy.h"
#include "player.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void paintEvent(QPaintEvent *event);
    void keyPressEvent(QKeyEvent *event);

    void stopGame();
    void checkCollision();

private slots:
    void on_close_clicked();

    void on_start_clicked();

private:
    Ui::MainWindow *ui;
    int score;
    player *spyro;
    enemy *ryhnoc[11][5];
    bool gameOver;
    QTimer *timer;
    QMediaPlayer *music;
};

#endif // MAINWINDOW_H
