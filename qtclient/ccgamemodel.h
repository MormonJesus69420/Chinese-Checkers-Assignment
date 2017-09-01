#ifndef CCGAMEMODEL_H
#define CCGAMEMODEL_H


// cclibrary
#include "../cclibrary/cclibrary.h"

// qt
#include <QAbstractListModel>
#include <QPoint>


// stl
#include <memory>



class CcGameModel : public QAbstractListModel {
  Q_OBJECT
public:
  Q_PROPERTY(int boardSize READ boardSize NOTIFY boardSizeChanged)

  enum GoEngineModelRoles { OccupiedRole = Qt::UserRole + 1, PlayerNrRole };

  CcGameModel(const MySoothingNamespace::Game& game_engine,
              QObject*                         parent = nullptr);

  int      rowCount(const QModelIndex& parent = QModelIndex()) const override;
  QVariant data(const QModelIndex& index, int role) const override;
  QHash<int, QByteArray> roleNames() const override;


public slots:
  void update();

private:
  const MySoothingNamespace::Game& m_game_engine;

  size_t boardSize() const;

signals:
  void boardSizeChanged(size_t);
};





#endif   // CCGAMEMODEL_H
