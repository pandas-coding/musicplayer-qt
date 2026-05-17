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

SongItem::~SongItem() { delete ui; }
