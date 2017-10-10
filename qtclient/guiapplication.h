#ifndef GUIAPPLICATION_H
#define GUIAPPLICATION_H

// local
#include "ccgamemodel.h"

// cclibrary
#include "../cclibrary/aiplayer.h"
#include "../cclibrary/cclibrary.h"

// qt
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QSizeF>

// stl
#include <memory>

class GuiApplication : public QGuiApplication {
  Q_OBJECT
public:
  GuiApplication(int& argc, char** argv);

private:
  GaymSpace::Game       m_game_engine;
  CcGameModel           m_model;
  QQmlApplicationEngine m_app;
  int                   m_timer_id;

private slots:
  void endGame();
  void clearGame();
  void initNewGame();
  void executeMove();
  void addPlayer(int type);
  size_t checkWinGame(CC::PlayerId player_id);


};   // END class GuiApplication
#endif   // GUIAPPLICATION_H
