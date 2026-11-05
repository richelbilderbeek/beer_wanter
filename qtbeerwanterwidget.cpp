#include "qtbeerwanterwidget.h"

#include <algorithm>
#include <cassert>
#include <cstdlib>

#include <QCursor>
#include <QGuiApplication>
#include <QMouseEvent>
#include <QPainter>
#include <QScreen>

ribi::QtBeerWanterWidget::QtBeerWanterWidget(QWidget *parent)
  : QWidget(parent),
    m_background(
      (0xff + 0xff)/2, //Average redness in stylesheet of menu
      (0xff + 0xc5)/2, //Average greenness in stylesheet of menu
      (0x00 + 0x00)/2  //Average blueness in stylesheet of menu
    ),
    m_cursor_offset{},
    m_dialog{},
    m_sprite(BeerWanterMainDialog::GetResourceFilename().c_str()),
    m_timer{}
{
  assert(!m_sprite.isNull());

  setMouseTracking(true);

  const QSize screen = QGuiApplication::primaryScreen()->size();
  //A browser page can be smaller than the regular window size
  const int window_size = std::min({520, screen.width(), screen.height()});

  m_dialog = std::make_unique<BeerWanterMainDialog>(
    screen.width(),
    screen.height(),
    m_sprite.width(),
    m_sprite.height(),
    window_size,
    window_size
  );

  //Ensure the window does not get resized
  setFixedHeight(m_dialog->GetWindowHeight());
  setFixedWidth(m_dialog->GetWindowWidth());

  #ifdef Q_OS_WASM
  setCursor(Qt::BlankCursor);
  #endif

  connect(&m_timer, &QTimer::timeout, this, &QtBeerWanterWidget::onTimer);
  m_timer.start(20); //Framerate about (1000/20=) 50 fps
}

const ribi::BeerWanterMainDialog * ribi::QtBeerWanterWidget::GetBeerWanter() const
{
  return m_dialog.get();
}

void ribi::QtBeerWanterWidget::mouseMoveEvent(QMouseEvent * event)
{
  assert(event);
  const QPoint cursor = event->position().toPoint() + m_cursor_offset;
  m_dialog->SetCursorPos(cursor.x(), cursor.y());
  update();
}

void ribi::QtBeerWanterWidget::mousePressEvent(QMouseEvent * event)
{
  assert(event);
  Q_UNUSED(event) //Only used by the WebAssembly build, and assert
  #ifdef Q_OS_WASM
  //A touch screen has no mouse moves before a press
  const QPoint cursor = event->position().toPoint() + m_cursor_offset;
  m_dialog->SetCursorPos(cursor.x(), cursor.y());
  #endif
  if (m_dialog->Click())
  {
    //Inform user of level-up
    emit LevelUp(QString::fromStdString(m_dialog->GetWindowTitle()));
  }
  update();
}

void ribi::QtBeerWanterWidget::onTimer()
{
  #ifdef Q_OS_WASM
  const QPoint before(m_dialog->GetCursorX(), m_dialog->GetCursorY());
  #endif

  m_dialog->ShakeCursor();

  const int mouse_x = m_dialog->GetCursorX();
  const int mouse_y = m_dialog->GetCursorY();

  #ifdef Q_OS_WASM
  //Let the offset slowly fade: the real cursor stops at the edge of the page,
  //from where a drawn cursor that wandered off could never be brought back
  const int fade = 50;
  m_cursor_offset += QPoint(mouse_x, mouse_y) - before;
  const QPoint faded = m_cursor_offset - (m_cursor_offset / fade);
  m_dialog->SetCursorPos(
    mouse_x + faded.x() - m_cursor_offset.x(),
    mouse_y + faded.y() - m_cursor_offset.y()
  );
  m_cursor_offset = faded;
  #else
  const QPoint base_pos = mapToGlobal(QPoint(0,0));
  QCursor::setPos(base_pos.x() + mouse_x, base_pos.y() + mouse_y);
  #endif

  //Move window
  m_dialog->ShakeWindow();
  #ifdef Q_OS_WASM
  m_dialog->ClampWindowToScreen();
  #endif
  //QtBeerWanterWidget cannot shake itself
  emit DoShake(m_dialog->GetWindowX(),m_dialog->GetWindowY());
  update();
}

void ribi::QtBeerWanterWidget::paintEvent(QPaintEvent *)
{
  QPainter painter(this);

  m_background.setRgb(
    Modify(m_background.red()),
    Modify(m_background.green()),
    Modify(m_background.blue())
  );
  painter.fillRect(rect(), m_background);

  painter.drawPixmap(
    m_dialog->GetSpriteX(),
    m_dialog->GetSpriteY(),
    m_sprite
  );

  #ifdef Q_OS_WASM
  //There is no title bar to show the score in
  painter.setPen(Qt::black);
  painter.drawText(
    rect().adjusted(8, 8, -8, -8),
    Qt::AlignLeft | Qt::AlignTop,
    QString("Beer gotten: %1 (Esc to quit)").arg(m_dialog->GetLevel() - 1)
  );

  const QPoint cursor(m_dialog->GetCursorX(), m_dialog->GetCursorY());
  const int size = 8;
  for (const QColor& color: {QColor(Qt::white), QColor(Qt::black)})
  {
    painter.setPen(QPen(color, color == Qt::white ? 4 : 2));
    painter.drawLine(cursor - QPoint(size, 0), cursor + QPoint(size, 0));
    painter.drawLine(cursor - QPoint(0, size), cursor + QPoint(0, size));
  }
  #endif
}

int ribi::Modify(const int color) noexcept
{
  const int new_color = color + ((std::rand() >> 4) % 3) - 1;
  if (new_color > 255)
  {
    return 255;
  }
  else if (new_color < 0)
  {
    return 0;
  }
  return new_color;
}
