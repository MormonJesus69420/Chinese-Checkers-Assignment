#include "ccgamemodel.h"

CcGameModel::CcGameModel(const GaymSpace::Game& game_engine,
                         QObject*                         parent)
  : QAbstractListModel(parent), m_game_engine{game_engine}
{
}

int CcGameModel::rowCount(const QModelIndex& parent) const
{

  if (parent.isValid()) return 0;

  return boardSize();
}

QVariant CcGameModel::data(const QModelIndex& index, int role) const
{

  if (!index.isValid()) return QVariant();

  const size_t st_row = size_t(boardSize() - index.row() - 1);
  const auto   bp_row = CC::BitPos(st_row);

  const auto occupied = CC::alg::occupied(m_game_engine.board(), bp_row);

  if (role == OccupiedRole)
    return occupied;
  else if (role == PlayerNrRole) {

    if (!occupied) return QVariant(-1);

    const auto player_ids = m_game_engine.playerIds();
    for (const auto& id : player_ids)
      if (CC::alg::occupied(m_game_engine.pieces(id), bp_row))
        return QVariant(uint(id));
  }

  return QVariant();
}

size_t CcGameModel::boardSize() const { return CC::computeBoardSize(); }

QHash<int, QByteArray> CcGameModel::roleNames() const
{

  QHash<int, QByteArray> role_names;
  role_names[OccupiedRole] = "occupied";
  role_names[PlayerNrRole] = "playernr";

  return role_names;
}

void CcGameModel::update()
{

  beginResetModel();
  endResetModel();
  emit boardSizeChanged(CC::computeBoardSize());
}
