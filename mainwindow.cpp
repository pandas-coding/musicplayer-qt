#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QIcon>
#include <QMediaPlayer>
#include <QMessageBox>
#include <QPalette>
#include <QPixmap>
#include <QPropertyAnimation>
#include <QPushButton>
#include <QSize>
#include <QUrl>
#include <cstddef>
#include <cstdlib>
#include <qdebug.h>
#include <qdir.h>
#include <qeventloop.h>
#include <qicon.h>
#include <qlogging.h>
#include <qmessagebox.h>
#include <qobject.h>
#include <qpoint.h>
#include <qpropertyanimation.h>
#include <qpushbutton.h>
#include <qurl.h>
#include <qwidget.h>
#include <time.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), m_playMode(PLAY_MODE::ORDER_MODE),
      m_musicListVisible(false), ui(new Ui::MainWindow) {
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

  m_musicPath = "./asserts/";
  loadAppointMusicFolder(m_musicPath);

  // setup random number seed.
  srand(time(NULL));
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

  ui->musicList->setStyleSheet(
      "QListWidget { border: none; border-radius: 4px; background-color: "
      "rgba(255, 255, 255, 0.8); }");

  /// init music list visibility as hidden.
  ui->musicList->hide();

  /* bingding buttons signals with slots */
  connect(ui->playButton, &QPushButton::clicked, this,
          &MainWindow::handlePlaySlot);
  connect(ui->modeButton, &QPushButton::clicked, this,
          &MainWindow::handleModeSlot);
  connect(ui->nextButton, &QPushButton::clicked, this,
          &MainWindow::handleNextSlot);
  connect(ui->prevButton, &QPushButton::clicked, this,
          &MainWindow::handlePrevSlot);
  connect(ui->listButton, &QPushButton::clicked, this,
          &MainWindow::handleMusicListSlot);
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

void MainWindow::handleModeSlot() {
  switch (m_playMode) {
  case PLAY_MODE::ORDER_MODE: {
    m_playMode = PLAY_MODE::RANDOM_MODE;
    ui->modeButton->setIcon(QIcon(":/Icon/random.png"));
    break;
  }
  case PLAY_MODE::RANDOM_MODE: {
    m_playMode = PLAY_MODE::CIRCLE_MODE;
    ui->modeButton->setIcon(QIcon(":/Icon/list.png"));
    break;
  }
  case PLAY_MODE::CIRCLE_MODE: {
    m_playMode = PLAY_MODE::ORDER_MODE;
    ui->modeButton->setIcon(QIcon(":/Icon/order.png"));
    break;
  }
  }
}

void MainWindow::handleNextSlot() {
  int currentIndex = ui->musicList->currentRow();
  int nextIndex = 0;

  switch (m_playMode) {
  case PLAY_MODE::ORDER_MODE: {
    nextIndex = (currentIndex + 1) % ui->musicList->count();
    break;
  }
  case PLAY_MODE::RANDOM_MODE: {
    // using do-while to avoid the case where the next index is the same as the
    // current index.
    int cnt = 0;
    do {
      nextIndex = rand() % ui->musicList->count();
      cnt++;
    } while ((currentIndex == nextIndex) && (cnt <= 3));
    break;
  }
  case PLAY_MODE::CIRCLE_MODE: {
    nextIndex = currentIndex;
    break;
  }
  }

  ui->musicList->setCurrentRow(nextIndex);

  startPlayMusic();
}

void MainWindow::handlePrevSlot() {
  int currentIndex = ui->musicList->currentRow();
  int prevIndex = 0;

  switch (m_playMode) {
  case PLAY_MODE::ORDER_MODE: {
    prevIndex =
        (currentIndex - 1 + ui->musicList->count()) % ui->musicList->count();
    break;
  }
  case PLAY_MODE::RANDOM_MODE: {
    int cnt = 0;
    do {
      prevIndex = rand() % ui->musicList->count();
    } while (currentIndex == prevIndex && cnt <= 3);
    break;
  }
  case PLAY_MODE::CIRCLE_MODE: {
    prevIndex = currentIndex;
    break;
  }
  }

  ui->musicList->setCurrentRow(prevIndex);

  startPlayMusic();
}

void MainWindow::startPlayMusic() {
  auto musicName = ui->musicList->currentItem()->text();
  qDebug() << musicName << Qt::endl;
  QString musicAbsolutePath = m_musicPath + musicName + ".mp3";

  m_player->setSource(QUrl::fromLocalFile(musicAbsolutePath));
  handlePlaySlot();
}

void MainWindow::handleMusicListSlot() {
  if (false == m_musicListVisible) {
    ui->musicList->show();
    showMusicListAnimation(ui->musicList);
    m_musicListVisible = true;
  } else {
    hideMusicListAnimation(ui->musicList);
    ui->musicList->hide();
    m_musicListVisible = false;
  }
}

void MainWindow::showMusicListAnimation(QWidget *widget) {
  QPropertyAnimation animation(widget, "pos");
  animation.setDuration(100);
  animation.setStartValue(QPoint(this->width(), 0));
  animation.setEndValue(QPoint(this->width() - ui->musicList->width(), 0));
  animation.start();

  // waiting for animation finished
  QEventLoop loop;
  connect(&animation, &QPropertyAnimation::finished, &loop, &QEventLoop::quit);
  loop.exec();
}

void MainWindow::hideMusicListAnimation(QWidget *window) {
  QPropertyAnimation animation(window, "pos");
  animation.setDuration(100);
  animation.setStartValue(QPoint(this->width() - ui->musicList->width(), 0));
  animation.setEndValue(QPoint(this->width(), 0));
  animation.start();

  // waiting for animation finished
  QEventLoop loop;
  connect(&animation, &QPropertyAnimation::finished, &loop, &QEventLoop::quit);
  loop.exec();
}

void MainWindow::loadAppointMusicFolder(const QString &filepath) {
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

  // default load the first music
  ui->musicList->setCurrentRow(0);
}

MainWindow::~MainWindow() { delete ui; }
