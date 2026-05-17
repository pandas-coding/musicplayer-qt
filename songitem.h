#ifndef SONGITEM_H
#define SONGITEM_H

#include <QPixmap>
#include <QWidget>
#include <qobject.h>

namespace Ui {
class SongItem;
}

class SongItem : public QWidget {
  Q_OBJECT

public:
  explicit SongItem(QWidget *parent = nullptr);
  ~SongItem();

public slots:
  void handleFavoriteSlot();

public:
  void setAlboumPixPic(const QPixmap &pixmap);
  void setMusicName(const QString &name);
  void setArtist(const QString &artist);
  void setDuration(const QString &duration);

private:
  Ui::SongItem *ui;
  // is marked as favorite
  bool m_isFavorite;
  // music name
  QString m_musicName;
  // music artist
  QString m_artist;
  // music duration
  QString m_duration;
};

#endif // SONGITEM_H
