#include "ccgamemodel.h"

CcGameModel::CcGameModel(const GaymSpace::Game& game_engine, QObject* parent)
  : QAbstractListModel(parent), m_game_engine{game_engine} {}

int CcGameModel::rowCount(const QModelIndex& parent) const {

  if (parent.isValid()) return 0;

  return boardSize();
}

QVariant CcGameModel::data(const QModelIndex& index, int role) const {

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
  } else if (role == CenterPositionRole) {
    auto point = getPosition(bp_row.value());
    return QVariant(point);
  } else if (role == PositonRole) {
    return QVariant(int(bp_row.value()));
  }

  return QVariant();
}

size_t CcGameModel::boardSize() const { return CC::computeBoardSize(); }

QHash<int, QByteArray> CcGameModel::roleNames() const {

  QHash<int, QByteArray> role_names;
  role_names[OccupiedRole]       = "occupied";
  role_names[PlayerNrRole]       = "playernr";
  role_names[CenterPositionRole] = "centerpos";
  role_names[PositonRole]        = "position";

  return role_names;
}

void CcGameModel::update() {

  beginResetModel();
  endResetModel();
  emit boardSizeChanged(CC::computeBoardSize());
}


// BEWARE DON'T SCROLL DOWN PAST THIS POINT










// I WARNED YOU










// Awfully long switch case used to calculate relativistic positions for each
// piece on board. Courtesy of Clemence Picard.
QPointF CcGameModel::getPosition(const size_t& index) const {
  float l = 1 / 8.5;
  switch (index) {
    case 0:
      return QPointF(0, -8 * l);
    case 1:
      return QPointF(-l / 2, -7 * l);
    case 2:
      return QPointF(l / 2, -7 * l);
    case 3:
      return QPointF(-l, -6 * l);
    case 4:
      return QPointF(0, -6 * l);
    case 5:
      return QPointF(l, -6 * l);
    case 6:
      return QPointF(-l / 2 - l, -5 * l);
    case 7:
      return QPointF(-l / 2, -5 * l);
    case 8:
      return QPointF(l / 2, -5 * l);
    case 9:
      return QPointF(l / 2 + l, -5 * l);
    case 10:
      return QPointF(-6 * l, -4 * l);
    case 11:
      return QPointF(-5 * l, -4 * l);
    case 12:
      return QPointF(-4 * l, -4 * l);
    case 13:
      return QPointF(-3 * l, -4 * l);
    case 14:
      return QPointF(-2 * l, -4 * l);
    case 15:
      return QPointF(-l, -4 * l);
    case 16:
      return QPointF(0, -4 * l);
    case 17:
      return QPointF(l, -4 * l);
    case 18:
      return QPointF(2 * l, -4 * l);
    case 19:
      return QPointF(3 * l, -4 * l);
    case 20:
      return QPointF(4 * l, -4 * l);
    case 21:
      return QPointF(5 * l, -4 * l);
    case 22:
      return QPointF(6 * l, -4 * l);
    case 23:
      return QPointF(-l / 2 - 5 * l, -3 * l);
    case 24:
      return QPointF(-l / 2 - 4 * l, -3 * l);
    case 25:
      return QPointF(-l / 2 - 3 * l, -3 * l);
    case 26:
      return QPointF(-l / 2 - 2 * l, -3 * l);
    case 27:
      return QPointF(-l / 2 - l, -3 * l);
    case 28:
      return QPointF(-l / 2, -3 * l);
    case 29:
      return QPointF(l / 2, -3 * l);
    case 30:
      return QPointF(l / 2 + l, -3 * l);
    case 31:
      return QPointF(l / 2 + 2 * l, -3 * l);
    case 32:
      return QPointF(l / 2 + 3 * l, -3 * l);
    case 33:
      return QPointF(l / 2 + 4 * l, -3 * l);
    case 34:
      return QPointF(l / 2 + 5 * l, -3 * l);
    case 35:
      return QPointF(-5 * l, -2 * l);
    case 36:
      return QPointF(-4 * l, -2 * l);
    case 37:
      return QPointF(-3 * l, -2 * l);
    case 38:
      return QPointF(-2 * l, -2 * l);
    case 39:
      return QPointF(-l, -2 * l);
    case 40:
      return QPointF(0, -2 * l);
    case 41:
      return QPointF(l, -2 * l);
    case 42:
      return QPointF(2 * l, -2 * l);
    case 43:
      return QPointF(3 * l, -2 * l);
    case 44:
      return QPointF(4 * l, -2 * l);
    case 45:
      return QPointF(5 * l, -2 * l);
    case 46:
      return QPointF(-l / 2 - 4 * l, -l);
    case 47:
      return QPointF(-l / 2 - 3 * l, -l);
    case 48:
      return QPointF(-l / 2 - 2 * l, -l);
    case 49:
      return QPointF(-l / 2 - l, -l);
    case 50:
      return QPointF(-l / 2, -l);
    case 51:
      return QPointF(l / 2, -l);
    case 52:
      return QPointF(l / 2 + l, -l);
    case 53:
      return QPointF(l / 2 + 2 * l, -l);
    case 54:
      return QPointF(l / 2 + 3 * l, -l);
    case 55:
      return QPointF(l / 2 + 4 * l, -l);
    case 56:
      return QPointF(-4 * l, 0);
    case 57:
      return QPointF(-3 * l, 0);
    case 58:
      return QPointF(-2 * l, 0);
    case 59:
      return QPointF(-l, 0);
    case 60:
      return QPointF(0, 0);
    case 61:
      return QPointF(l, 0);
    case 62:
      return QPointF(2 * l, 0);
    case 63:
      return QPointF(3 * l, 0);
    case 64:
      return QPointF(4 * l, 0);
    case 65:
      return QPointF(-l / 2 - 4 * l, l);
    case 66:
      return QPointF(-l / 2 - 3 * l, l);
    case 67:
      return QPointF(-l / 2 - 2 * l, l);
    case 68:
      return QPointF(-l / 2 - l, l);
    case 69:
      return QPointF(-l / 2, l);
    case 70:
      return QPointF(l / 2, l);
    case 71:
      return QPointF(l / 2 + l, l);
    case 72:
      return QPointF(l / 2 + 2 * l, l);
    case 73:
      return QPointF(l / 2 + 3 * l, l);
    case 74:
      return QPointF(l / 2 + 4 * l, l);
    case 75:
      return QPointF(-5 * l, 2 * l);
    case 76:
      return QPointF(-4 * l, 2 * l);
    case 77:
      return QPointF(-3 * l, 2 * l);
    case 78:
      return QPointF(-2 * l, 2 * l);
    case 79:
      return QPointF(-l, 2 * l);
    case 80:
      return QPointF(0, 2 * l);
    case 81:
      return QPointF(l, 2 * l);
    case 82:
      return QPointF(2 * l, 2 * l);
    case 83:
      return QPointF(3 * l, 2 * l);
    case 84:
      return QPointF(4 * l, 2 * l);
    case 85:
      return QPointF(5 * l, 2 * l);
    case 86:
      return QPointF(-l / 2 - 5 * l, 3 * l);
    case 87:
      return QPointF(-l / 2 - 4 * l, 3 * l);
    case 88:
      return QPointF(-l / 2 - 3 * l, 3 * l);
    case 89:
      return QPointF(-l / 2 - 2 * l, 3 * l);
    case 90:
      return QPointF(-l / 2 - l, 3 * l);
    case 91:
      return QPointF(-l / 2, 3 * l);
    case 92:
      return QPointF(l / 2, 3 * l);
    case 93:
      return QPointF(l / 2 + l, 3 * l);
    case 94:
      return QPointF(l / 2 + 2 * l, 3 * l);
    case 95:
      return QPointF(l / 2 + 3 * l, 3 * l);
    case 96:
      return QPointF(l / 2 + 4 * l, 3 * l);
    case 97:
      return QPointF(l / 2 + 5 * l, 3 * l);
    case 98:
      return QPointF(-6 * l, 4 * l);
    case 99:
      return QPointF(-5 * l, 4 * l);
    case 100:
      return QPointF(-4 * l, 4 * l);
    case 101:
      return QPointF(-3 * l, 4 * l);
    case 102:
      return QPointF(-2 * l, 4 * l);
    case 103:
      return QPointF(-l, 4 * l);
    case 104:
      return QPointF(0, 4 * l);
    case 105:
      return QPointF(l, 4 * l);
    case 106:
      return QPointF(2 * l, 4 * l);
    case 107:
      return QPointF(3 * l, 4 * l);
    case 108:
      return QPointF(4 * l, 4 * l);
    case 109:
      return QPointF(5 * l, 4 * l);
    case 110:
      return QPointF(6 * l, 4 * l);
    case 111:
      return QPointF(-l / 2 - l, 5 * l);
    case 112:
      return QPointF(-l / 2, 5 * l);
    case 113:
      return QPointF(l / 2, 5 * l);
    case 114:
      return QPointF(l / 2 + l, 5 * l);
    case 115:
      return QPointF(-l, 6 * l);
    case 116:
      return QPointF(0, 6 * l);
    case 117:
      return QPointF(l, 6 * l);
    case 118:
      return QPointF(-l / 2, 7 * l);
    case 119:
      return QPointF(l / 2, 7 * l);
    case 120:
      return QPointF(0, 8 * l);
    default:
      return QPointF(0, 0);
  }
}
