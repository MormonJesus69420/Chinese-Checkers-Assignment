#include "guiapplication.h"
#include "../cclibrary/aiplayer.h"

// qt
#include <QDebug>
#include <QQmlContext>
#include <QQuickItem>
#include <QQuickWindow>
#include <QTimer>


GuiApplication::GuiApplication(int& argc, char** argv)
  : QGuiApplication(argc, argv),
    m_game_engine{}, m_model{m_game_engine}, m_app{} {


  m_app.rootContext()->setContextProperty("ccgamemodel", &m_model);

  m_app.load(QUrl("qrc:/qml/gui.qml"));

  auto* root_window = qobject_cast<QQuickWindow*>(m_app.rootObjects().first());
  if (root_window) {
    connect(root_window, SIGNAL(endGame()), this, SLOT(endGame()));

    connect(root_window, SIGNAL(clearGame()), this, SLOT(clearGame()));

    connect(root_window, SIGNAL(initNewGame()), this, SLOT(initNewGame()));

    connect(root_window, SIGNAL(addPlayer(int)), this, SLOT(addPlayer(int)));
  }
  m_model.update();
}

void GuiApplication::addPlayer(int type) {
  if (type == 0)
    m_game_engine.addPlayer<CC::HumanPlayer>();
  else if (type == 1)
    m_game_engine.addPlayer<GaymSpace::AiPlayer>();
  else
    return;
  m_model.update();
}

void GuiApplication::initNewGame() {
  const std::unordered_set<int> legal_np{2, 3, 4, 6};
  if (!legal_np.count(m_game_engine.players().size())) return;

  m_game_engine.initNewGame();

  executeMove();

  m_model.update();
}

void GuiApplication::clearGame() {
  m_game_engine.clearGame();
  m_model.update();
}

void GuiApplication::executeMove() {
  auto id = m_game_engine.currentPlayerId();
  m_game_engine.think(std::chrono::seconds(2));
  m_model.update();

  if (checkWinGame(id) != 42) return;

  // TODO CHANGE TIME TO 3000 millis
  QTimer::singleShot(200, this, SLOT(executeMove()));
}

size_t GuiApplication::checkWinGame(CC::PlayerId player_id) {
  if (m_game_engine.pieces(player_id) == m_game_engine.goal(player_id))
    return size_t(player_id);

  return 42;
}

void GuiApplication::endGame() { QGuiApplication::quit(); }
