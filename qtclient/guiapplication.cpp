#include "guiapplication.h"


// qt
#include <QQmlContext>
#include <QQuickItem>
#include <QQuickWindow>
#include <QTimer>
#include <QDebug>


GuiApplication::GuiApplication(int& argc, char** argv)
  : QGuiApplication(argc, argv),
    m_game_engine{}, m_model{m_game_engine}, m_app{}
{


  m_app.rootContext()->setContextProperty("ccgamemodel", &m_model);

  m_app.load(QUrl("qrc:/qml/gui.qml"));

  auto* root_window = qobject_cast<QQuickWindow*>(m_app.rootObjects().first());
  if (root_window) {

    connect(root_window, SIGNAL(endGameAndQuit()), this,
            SLOT(endGameAndQuit()));

    connect(root_window, SIGNAL(initNewGame(int)), this,
            SLOT(initNewGame(int)));
  }
}

void GuiApplication::initNewGame(int no_players)
{

  const std::unordered_set<int> legal_np{2, 3, 4, 6};
  if (!legal_np.count(no_players)) return;

  m_game_engine.clearGame();
  for (auto i = 0; i < no_players; ++i)
    m_game_engine.addPlayer<CC::HumanPlayer>();
  m_game_engine.initNewGame();

  m_model.update();
}

void GuiApplication::endGameAndQuit() { QGuiApplication::quit(); }
