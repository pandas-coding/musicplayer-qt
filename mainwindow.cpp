#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qsize.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("MusicPlayer");
    
    initButtons();
}

void MainWindow::setButtonStyle(QPushButton *button, const QString &filename)
{
    button->setFixedSize(50, 50);
    button->setIcon(QIcon(filename));
    button->setIconSize(QSize(button->width(), button->height()));
    button->setStyleSheet("background-color: transparent");
}

void MainWindow::initButtons()
{
    setButtonStyle(ui->prevButton, ":/Icon/prev.png");
    setButtonStyle(ui->playButton, ":/Icon/play.png");
    setButtonStyle(ui->nextButton, ":/Icon/next.png");
    setButtonStyle(ui->modeButton, ":/Icon/order.png");
}

MainWindow::~MainWindow()
{
    delete ui;
}
