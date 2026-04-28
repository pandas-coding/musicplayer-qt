#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qnamespace.h>
#include <qobject.h>
#include <qpalette.h>
#include <qpixmap.h>
#include <qsize.h>
#include <QIcon>
#include <QPixmap>
#include <QPalette>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("MusicPlayer");
    
    setFixedSize(860, 640);
    setBackground(":/Image/background1.jpg");
    
    initButtons();
}

void MainWindow::setBackground(const QString &filename)
{
    QPixmap pixmap(filename);
    QSize windowSize = this->size();
    
    QPixmap scalePixmap = pixmap.scaled(windowSize, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    
    QPalette palette = this->palette();
    palette.setBrush(QPalette::Window, QBrush(scalePixmap));

    this->setPalette(palette);
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
    setButtonStyle(ui->listButton, ":/Icon/music.png");
}

MainWindow::~MainWindow()
{
    delete ui;
}
