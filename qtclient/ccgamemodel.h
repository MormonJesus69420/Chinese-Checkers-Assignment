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

  enum GoEngineModelRoles {
    OccupiedRole = Qt::UserRole + 1,
    PlayerNrRole,
    CenterPositionRole,
    PositonRole
  };

  CcGameModel(const GaymSpace::Game& game_engine, QObject* parent = nullptr);

  int rowCount(const QModelIndex& parent = QModelIndex()) const override;
  QVariant data(const QModelIndex& index, int role) const override;
  QHash<int, QByteArray> roleNames() const override;

public slots:
  void update();

private:
  size_t                 boardSize() const;
  const GaymSpace::Game& m_game_engine;
  QPointF getPosition(const size_t& index) const;

signals:
  void boardSizeChanged(size_t);
};





#endif   // CCGAMEMODEL_H
