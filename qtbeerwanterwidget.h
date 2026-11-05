//---------------------------------------------------------------------------
/*
BeerWanter. A simple game.
Copyright (C) 2005-2016 Richel Bilderbeek

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/GameBeerWanter.htm
//---------------------------------------------------------------------------
#ifndef QTBEERWANTERWIDGET_H
#define QTBEERWANTERWIDGET_H

#include <memory>

#include <QColor>
#include <QPixmap>
#include <QPoint>
#include <QTimer>
#include <QWidget>

#include "beerwantermaindialog.h"

class QMouseEvent;
class QPaintEvent;

namespace ribi {

class QtBeerWanterWidget : public QWidget
{
  Q_OBJECT //!OCLINT

public:
  explicit QtBeerWanterWidget(QWidget *parent = nullptr);
  const BeerWanterMainDialog * GetBeerWanter() const;

protected:
  void mouseMoveEvent(QMouseEvent * event) override;
  void mousePressEvent(QMouseEvent * event) override;
  void paintEvent(QPaintEvent * event) override;

private:
  QColor m_background;

  ///A browser does not allow moving the real cursor, so there the
  ///game hides it and draws its own cursor at the shaken position.
  ///This is the distance from the real cursor to the one drawn.
  ///Always zero on desktop, where the real cursor is moved
  QPoint m_cursor_offset;

  std::unique_ptr<BeerWanterMainDialog> m_dialog;

  QPixmap m_sprite;
  QTimer m_timer;

  void onTimer();

signals:
  void DoShake(const int x, const int y);
  void LevelUp(const QString& title);
};

///Modify the color value by [-1,1], keep it in [0, 255] range
int Modify(const int color) noexcept;

} //~namespace ribi

#endif // QTBEERWANTERWIDGET_H
