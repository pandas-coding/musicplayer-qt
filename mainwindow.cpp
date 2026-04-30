#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QIcon>
#include <QMediaPlayer>
#include <QMessageBox>
#include <QPalette>
#include <QPixmap>
#include <QPushButton>
#include <QSize>
#include <QUrl>
#include <qdir.h>
#include <qmessagebox.h>
#include <qobject.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  m_player = new QMediaPlayer(this);
  auto *audioOutput = new QAudioOutput(this);
  m_player->setAudioOutput(audioOutput);
  m_player->setSource(QUrl::fromLocalFile("./asserts/飞行艇.mp3"));
  audioOutput->setVolume(0.3);

  setWindowTitle("MusicPlayer");

  setFixedSize(860, 640);
  setBackground(":/Image/background1.jpg");

  initButtons();

  m_player->play();

  QString musicPath = "./asserts";
  loadAppointMusicFoler(musicPath);
}

void MainWindow::setBackground(const QString &filename) {
  QPixmap pixmap(filename);
  QSize windowSize = this->size();

  QPixmap scalePixmap = pixmap.scaled(windowSize, Qt::IgnoreAspectRatio,
                                      Qt::SmoothTransformation);

  QPalette palette = this->palette();
  palette.setBrush(QPalette::Window, QBrush(scalePixmap));

  this->setPalette(palette);
}

void MainWindow::setButtonStyle(QPushButton *button, const QString &filename) {
  button->setFixedSize(50, 50);
  button->setIcon(QIcon(filename));
  button->setIconSize(QSize(button->width(), button->height()));
  button->setStyleSheet("background-color: transparent");
}

void MainWindow::initButtons() {
  setButtonStyle(ui->prevButton, ":/Icon/prev.png");
  setButtonStyle(ui->playButton, ":/Icon/play.png");
  setButtonStyle(ui->nextButton, ":/Icon/next.png");
  setButtonStyle(ui->modeButton, ":/Icon/order.png");
  setButtonStyle(ui->listButton, ":/Icon/music.png");

  connect(ui->playButton, &QPushButton::clicked, this,
          &MainWindow::handlePlaySlot);
}

void MainWindow::handlePlaySlot() {
  if (m_player->playbackState() == QMediaPlayer::PlayingState) {
    m_player->pause();
    ui->playButton->setIcon(QIcon(":/Icon/play.png"));
  } else {
    m_player->play();
    ui->playButton->setIcon(QIcon(":/Icon/pause.png"));
  }
}

void MainWindow::loadAppointMusicFoler(const QString &filepath) {
  QDir dir(filepath);
  if (dir.exists() == false) {
    QMessageBox::warning(this, "文件夹", "文件夹打开失败");
    return;
  }

  auto fileList = dir.entryInfoList(QDir::Files);
  for (auto file : fileList) {
    if (file.suffix() == "mp3") {
        ui->musicList->addItem(file.baseName());
    }
  }
}

MainWindow::~MainWindow() { delete ui; }
