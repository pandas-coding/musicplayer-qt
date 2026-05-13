#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QAudioOutput>
#include <QMainWindow>
#include <QMediaPlayer>
#include <QPushButton>
#include <QUrl>
#include <qobject.h>
#include <qwidget.h>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

enum PLAY_MODE {
  ORDER_MODE,
  RANDOM_MODE,
  CIRCLE_MODE,
};

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow() override;

public slots:
  void handlePlaySlot();
  void handleModeSlot();
  void handleNextSlot();
  void handlePrevSlot();
  void handleMusicListSlot();

private:
  void setBackground(const QString &filename);
  void setButtonStyle(QPushButton *button, const QString &filename);
  void initButtons();
  // load mucic list folder
  void loadAppointMusicFolder(const QString &filepath);
  // play music
  void startPlayMusic();
  // music list widget show transparent
  void showMusicListAnimation(QWidget *window);
  // music list widget hide transparent
  void hideMusicListAnimation(QWidget *window);

private:
  Ui::MainWindow *ui;
  QMediaPlayer *m_player;
  // current play mode
  PLAY_MODE m_playMode;
  // music absolute path
  QString m_musicPath;
  // music list  visibility
  bool m_musicListVisible;
};
#endif // MAINWINDOW_H
