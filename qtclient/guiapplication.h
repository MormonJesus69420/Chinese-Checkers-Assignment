#ifndef GUIAPPLICATION_H
#define GUIAPPLICATION_H


// local
#include "ccgamemodel.h"

// cclibrary
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
  MySoothingNamespace::Game m_game_engine;
  CcGameModel               m_model;
  QQmlApplicationEngine     m_app;
  int                       m_timer_id;

private slots:
  void initNewGame(int no_players);
  void endGameAndQuit();


};   // END class GuiApplication





#endif   // GUIAPPLICATION_H
