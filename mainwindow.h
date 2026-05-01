#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QAudioOutput>
#include <QMainWindow>
#include <QMediaPlayer>
#include <QPushButton>
#include <QUrl>
#include <qobject.h>

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

private:
  void setBackground(const QString &filename);
  void setButtonStyle(QPushButton *button, const QString &filename);
  void initButtons();
  // load mucic list folder
  void loadAppointMusicFoler(const QString &filepath);

private:
  Ui::MainWindow *ui;
  QMediaPlayer *m_player;
  // current play mode
  PLAY_MODE m_playMode;
};
#endif // MAINWINDOW_H
