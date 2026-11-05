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
#include "beerwantermenudialog.h"

#include <iostream>

int ribi::BeerWanterMenuDialog::Execute() const
{
  std::cout << "\nBeerWanter cannot be run in console mode\n" << std::endl;
  return 0;
}

std::string ribi::BeerWanterMenuDialog::GetAboutText() const
{
  std::string text
    = "BeerWanter, version " + GetVersion() + "\n"
      "A simple game\n"
      "\n"
      "Copyright (C) 2005-2026 Richel Bilderbeek\n"
      "Licensed under the GNU General Public License, version 3 or later\n"
      "\n"
      "https://github.com/richelbilderbeek/beer_wanter\n"
      "\n"
      "Version history:\n";
  for (const std::string& version: GetVersionHistory())
  {
    text += " - " + version + "\n";
  }
  return text;
}

std::string ribi::BeerWanterMenuDialog::GetVersion() const noexcept
{
  return "9.0";
}

std::vector<std::string>
ribi::BeerWanterMenuDialog::GetVersionHistory() const
{
  return {
    "2005-11-16: version 1.0: (at that time called) 'Beerwanter 1' was "
      "programmed in C++ using the C++ Builder IDE during a "
      "'Spass programmieren' session, which made BeerWanter "
      "a game for Windows users only",
    "2005-11-18: version 2.0: (at that time called) 'Beerwanter 2' was "
      "programmed after the success of BeerWanter 1.0. "
      "The game was made tougher",
    "2005-11-22: version 3.0: (at that time called) 'Beerwanter 3' was "
      "programmed after the success of BeerWanter 2.0. "
      "The game was made even tougher",
    "2010-06-23: version 4.0: port code to Qt Creator, BeerWanter is now "
      "cross-platform. The game its name is changed back to 'BeerWanter'",
    "2010-06-24: version 5.0: improved the GUI, changed the beer sprite to "
      "an adaptation of my favorite beer",
    "2010-10-10: version 5.1: (temporary NDS-only fork) start of port to NDS",
    "2010-10-11: version 5.2: BeerWanter is one project again and build for "
      "NDS, Ubuntu and Windows",
    "2010-12-19: version 6.0: seperated project files for NDS, Ubuntu and "
      "Windows development. Preparation for seperating game logic from GUI",
    "2010-12-23: version 6.1: added ClickWilBeSuccess method, fixed bug in "
      "BeerWanterMainDialog::ShakeWindow",
    "2012-03-06: version 7.0: added menu, conformized project architecture "
      "for ProjectRichelBilderbeek",
    "2013-07-13: version 7.1: added libcvautomation script to beat the game, "
      "improved desktop menu and about screen",
    "2014-01-16: version 7.2: added command line command 'show'",
    "2015-10-02: version 7.3: move to own repository, removed command line "
      "command 'show'",
    "2015-12-17: version 7.4: cleaning up",
    "2016-03-19: version 8.0: use of Boost.Test",
    "2016-08-26: version 8.2: removed NDS support, use of OCLint",
    "2026-11-05: version 9.0: port to Qt6 and CMake, removed dependencies on "
      "RibiClasses and Boost for the game itself, added WebAssembly build "
      "that can be played in a browser",
  };
}
