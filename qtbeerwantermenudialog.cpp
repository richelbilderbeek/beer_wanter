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
#include "qtbeerwantermenudialog.h"

#include <QGuiApplication>
#include <QScreen>

#include "qtbeerwanteraboutdialog.h"
#include "qtbeerwantermaindialog.h"
#include "ui_qtbeerwantermenudialog.h"

ribi::QtBeerWanterMenuDialog::QtBeerWanterMenuDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::QtBeerWanterMenuDialog)
{
  ui->setupUi(this);
  #ifdef Q_OS_WASM
  //A web page cannot be quit, and the page is the frame
  ui->button_quit->hide();
  setWindowFlag(Qt::FramelessWindowHint);
  adjustSize();
  move(QGuiApplication::primaryScreen()->geometry().center() - rect().center());
  #endif
}

ribi::QtBeerWanterMenuDialog::~QtBeerWanterMenuDialog() noexcept
{
  delete ui;
}

void ribi::QtBeerWanterMenuDialog::on_button_start_clicked()
{
  ShowChild(new QtBeerWanterMainDialog);
}

void ribi::QtBeerWanterMenuDialog::on_button_about_clicked()
{
  auto * const d = new QtBeerWanterAboutDialog;
  d->setStyleSheet(styleSheet());
  d->setWindowIcon(windowIcon());
  const QSize screen = QGuiApplication::primaryScreen()->size();
  d->resize(qMin(800, screen.width()), qMin(500, screen.height()));
  ShowChild(d);
}

void ribi::QtBeerWanterMenuDialog::on_button_quit_clicked()
{
  close();
}

void ribi::QtBeerWanterMenuDialog::reject()
{
  #ifndef Q_OS_WASM
  QDialog::reject();
  #endif
  //In a browser, closing the menu would leave an empty page
}

void ribi::QtBeerWanterMenuDialog::ShowChild(QDialog * const dialog)
{
  dialog->setAttribute(Qt::WA_DeleteOnClose);
  connect(dialog, &QDialog::finished, this, &QtBeerWanterMenuDialog::show);
  hide();
  dialog->show();
}
