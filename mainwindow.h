#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QMediaPlayer>
#include <QAudioOutput>
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

private:
  void setBackground(const QString &filename);
  void setButtonStyle(QPushButton *button, const QString &filename);
  void initButtons();

private:
  Ui::MainWindow *ui;
  QMediaPlayer *m_player;
};
#endif // MAINWINDOW_H
