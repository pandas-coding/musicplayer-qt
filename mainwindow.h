#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QAudioOutput>
#include <QMainWindow>
#include <QMediaPlayer>
#include <QPushButton>
#include <QUrl>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow() override;

public slots:
  void handlePlaySlot();

private:
  void setBackground(const QString &filename);
  void setButtonStyle(QPushButton *button, const QString &filename);
  void initButtons();

private:
  Ui::MainWindow *ui;
  QMediaPlayer *m_player;
};
#endif // MAINWINDOW_H
