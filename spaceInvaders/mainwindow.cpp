#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_close_clicked()
{
    close();
}


void MainWindow::on_start_clicked()
{
    ui->start->hide();
    ui->controls->hide();
    ui->close->hide();
    ui->title->hide();
    ui->description->hide();
    gameOver = false;
    score = 0;
    music->play();
}
