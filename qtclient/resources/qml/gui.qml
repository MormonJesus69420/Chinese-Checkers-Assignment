import QtQuick 2.0
import QtQuick.Layouts 1.0
import QtQuick.Controls 1.4

ApplicationWindow {
  id: root

  signal initNewGame(int no_players)
  signal endGameAndQuit()

  visible: true

  width: 800
  height: 600

  menuBar: MenuBar {
        Menu {
            title: "Game"
            MenuItem {
              text: "New 2P Game"
              onTriggered: initNewGame(2)
            }
            MenuItem {
              text: "New 3P Game"
              onTriggered: initNewGame(3)
            }
            MenuItem {
              text: "New 4P Game"
              onTriggered: initNewGame(4)
            }
            MenuItem {
              text: "New 6P Game"
              onTriggered: initNewGame(6)
            }
            MenuItem {
              text: "Close"
              onTriggered: endGameAndQuit()
            }

        }
    }


  GridLayout {
    anchors.fill: parent
    columns: ccgamemodel.boardSize
    rows: 1
    columnSpacing: 0
    rowSpacing: 0

    Repeater {
      model: VisualDataModel {
        model: ccgamemodel
        delegate: Rectangle {
            Layout.fillHeight: true
            Layout.fillWidth: true
            color: {
              if (occupied) {
                if(playernr == 0) return "green"
                else if(playernr == 1) return "yellow"
                else if(playernr == 2) return "orange"
                else if(playernr == 3) return "red"
                else if(playernr == 4) return "purple"
                else if(playernr == 5) return "blue"
                else return "black"
              }
              else {
                return "white"
              }
            }

            border.color: "black"
            border.width: 1
        }
      }
    }
  }
}
