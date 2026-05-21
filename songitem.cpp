#include "songitem.h"
#include "ui_songitem.h"

#include <QIcon>
#include <QPushButton>
#include <QSize>
#include <qsize.h>

SongItem::SongItem(QWidget *parent) : QWidget(parent), ui(new Ui::SongItem) {
  ui->setupUi(this);

  ui->favoriteButton->setIcon(QIcon(":/Icon/unfavorite.png"));
  ui->favoriteButton->setIconSize(
      QSize(ui->favoriteButton->width(), ui->favoriteButton->height()));
  ui->favoriteButton->setStyleSheet("background-color: transparent");

  connect(ui->favoriteButton, &QPushButton::clicked, this,
          &SongItem::handleFavoriteSlot);
}

void SongItem::handleFavoriteSlot() {
  if (m_isFavorite) {
    ui->favoriteButton->setIcon(QIcon(":/Icon/unfavorite.png"));
    m_isFavorite = false;
  } else {
    ui->favoriteButton->setIcon(QIcon(":/Icon/favorite.png"));
    m_isFavorite = true;
  }
}

void SongItem::setAlboumPixPic(const QPixmap &pixmap) {
  ui->albumLabel->setPixmap(pixmap.scaled(60, 60, Qt::KeepAspectRatio, Qt::SmoothTransformation));
}
void SongItem::setMusicName(const QString &name) {
  ui->musicNameLabel->setText(name);
 
  m_musicName = name;
}
void SongItem::setArtist(const QString &artist) { m_artist = artist; }
void SongItem::setDuration(const QString &duration) {
  ui->durationLabel->setText(duration);
  m_duration = duration;
}

QSize SongItem::sizeHint() const { return QSize(300, 70); }

SongItem::~SongItem() { delete ui; }
