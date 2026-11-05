#include <boost/test/unit_test.hpp>
#include "beerwantermaindialog.h"
#include <QFile>

BOOST_AUTO_TEST_CASE(BeerWanterMainDialog_test)
{
  const int screen_width = 640;
  const int screen_height = 400;
  const int sprite_width = 32;
  const int sprite_height = 48;
  const int window_width = 320;
  const int window_height = 200;

  ribi::BeerWanterMainDialog d(
    screen_width,
    screen_height,
    sprite_width,
    sprite_height,
    window_width,
    window_height
  );
  BOOST_CHECK(d.GetWindowWidth() == window_width);
  BOOST_CHECK(d.GetWindowHeight() == window_height);
  BOOST_CHECK(d.GetSpriteWidth() == sprite_width);
  BOOST_CHECK(d.GetSpriteHeight() == sprite_height);
}

BOOST_AUTO_TEST_CASE(BeerWanterMainDialog_check_resources)
{
  BOOST_CHECK(
    QFile::exists(ribi::BeerWanterMainDialog::GetResourceFilename().c_str())
  );
}

BOOST_AUTO_TEST_CASE(BeerWanterMainDialog_click_on_sprite_goes_to_next_level)
{
  ribi::BeerWanterMainDialog d(640, 400, 32, 48, 320, 200);
  BOOST_CHECK(d.GetWindowTitle().find("Beer gotten: 0") != std::string::npos);
  BOOST_CHECK(d.ClickWilBeSuccess()); //Starts with cursor on the sprite
  BOOST_CHECK(d.Click());
  BOOST_CHECK(d.GetLevel() == 2);
  BOOST_CHECK(d.GetWindowTitle().find("Beer gotten: 1") != std::string::npos);
}

BOOST_AUTO_TEST_CASE(BeerWanterMainDialog_click_next_to_sprite_does_nothing)
{
  ribi::BeerWanterMainDialog d(640, 400, 32, 48, 320, 200);
  d.SetCursorPos(0, 0);
  BOOST_CHECK(!d.Click());
  BOOST_CHECK(d.GetLevel() == 1);
}

BOOST_AUTO_TEST_CASE(BeerWanterMainDialog_window_stays_on_screen_when_clamped)
{
  ribi::BeerWanterMainDialog d(340, 220, 8, 8, 320, 200);
  d.SetCursorPos(160, 100);
  for (int level = 0; level != 100; ++level)
  {
    d.SetCursorPos(d.GetSpriteX(), d.GetSpriteY());
    BOOST_REQUIRE(d.Click());
  }
  for (int i = 0; i != 1000; ++i)
  {
    d.ShakeWindow();
    d.ClampWindowToScreen();
    BOOST_REQUIRE(d.GetWindowX() >= 0);
    BOOST_REQUIRE(d.GetWindowY() >= 0);
    BOOST_REQUIRE(d.GetWindowX() <= 20);
    BOOST_REQUIRE(d.GetWindowY() <= 20);
  }
}
