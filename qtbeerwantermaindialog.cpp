#include "qtbeerwantermaindialog.h"

#include "beerwantermaindialog.h"
#include "qtbeerwanterwidget.h"

#include "ui_qtbeerwantermaindialog.h"

ribi::QtBeerWanterMainDialog::QtBeerWanterMainDialog(QWidget *parent)
  : QDialog(parent),
    ui(new Ui::QtBeerWanterMainDialog),
    m_widget(new QtBeerWanterWidget)
{
  ui->setupUi(this);
  #ifdef Q_OS_WASM
  //The page is the frame, the player can leave using Escape
  setWindowFlag(Qt::FramelessWindowHint);
  #endif
  ui->beerwanter_layout->addWidget(m_widget);
  setGeometry(
    m_widget->GetBeerWanter()->GetWindowX(),
    m_widget->GetBeerWanter()->GetWindowY(),
    m_widget->GetBeerWanter()->GetWindowWidth(),
    m_widget->GetBeerWanter()->GetWindowHeight()
  );

  connect(
    m_widget, &QtBeerWanterWidget::LevelUp,
    this, &QtBeerWanterMainDialog::ChangeTitle
  );
  connect(
    m_widget, &QtBeerWanterWidget::DoShake,
    this, &QtBeerWanterMainDialog::OnShake
  );
}

ribi::QtBeerWanterMainDialog::~QtBeerWanterMainDialog() noexcept
{
  delete ui;
}

void ribi::QtBeerWanterMainDialog::ChangeTitle(const QString& title)
{
  setWindowTitle(title);
}

void ribi::QtBeerWanterMainDialog::OnShake(const int x, const int y)
{
  setGeometry(x, y, width(), height());
}
