//---------------------------------------------------------------------------
/*
BeerWanter. A simple game.
Copyright (C) 2005-2026 Richel Bilderbeek

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
#include "qtbeerwanteraboutdialog.h"

#include <QDialogButtonBox>
#include <QPlainTextEdit>
#include <QVBoxLayout>

#include "beerwantermenudialog.h"

ribi::QtBeerWanterAboutDialog::QtBeerWanterAboutDialog(QWidget *parent)
  : QDialog(parent)
{
  setWindowTitle("About BeerWanter");

  auto * const text = new QPlainTextEdit(
    QString::fromStdString(BeerWanterMenuDialog().GetAboutText())
  );
  text->setReadOnly(true);

  auto * const buttons = new QDialogButtonBox(QDialogButtonBox::Close);
  connect(buttons, &QDialogButtonBox::rejected, this, &QDialog::reject);

  auto * const layout = new QVBoxLayout(this);
  layout->addWidget(text);
  layout->addWidget(buttons);
}
