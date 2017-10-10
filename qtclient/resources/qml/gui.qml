import QtQuick 2.0
import QtQuick.Layouts 1.0
import QtQuick.Controls 1.4

ApplicationWindow {
  id: root

  signal endGame()
  signal clearGame()
  signal initNewGame()
  signal addPlayer(int type)

  visible: true

  width: 800
  height: 820

  menuBar: MenuBar {

    Menu {
      title: "Game"
        MenuItem {
          text: "Add Human Player"
          onTriggered: addPlayer(0)
        }
        MenuItem {
          text: "Add AI Player"
          onTriggered: addPlayer(1)
        }
        MenuItem {
          text: "Initialize Game"
          onTriggered: initNewGame()
        }
        MenuItem {
          text: "Clear Game"
          onTriggered: clearGame()
        }
        MenuItem {
          text: "Close"
          onTriggered: endGame()
        }
    }
  }

// COPY IN CASE I FUCK IT ALL UP
//  GridLayout {
//    anchors.fill: parent
//    columns: ccgamemodel.boardSize
//    rows: 1
//    columnSpacing: 0
//    rowSpacing: 0
//    Repeater {
//      model: VisualDataModel {
//        model: ccgamemodel
//        delegate: Rectangle {
//          Layout.fillHeight: true
//          Layout.fillWidth: true
//          color: {
//            if (occupied) {
//              if(playernr == 0) return "green"
//              else if(playernr == 1) return "yellow"
//              else if(playernr == 2) return "orange"
//              else if(playernr == 3) return "red"
//              else if(playernr == 4) return "purple"
//              else if(playernr == 5) return "blue"
//              else return "black"
//            }
//            else {
//              return "white"
//            }
//          }

//          border.color: "black"
//          border.width: 1
//        }
//      }
//    }
//  }

  Repeater {
    model: VisualDataModel {
      model: ccgamemodel
      delegate: Item {
        visible: true
        width: parent.width / 17
        height: parent.height / 17
        x: (centerpos.x+1) * parent.width  / 2 - parent.width  / 34
        y: (centerpos.y+1) * parent.height / 2 - parent.height / 34
        Canvas {
          id: canvas
          anchors.fill: parent
          onPaint: {
            var ctx = canvas.getContext("2d");
            ctx.scale(canvas.width,canvas.height);
            ctx.clearRect(0,0,1, 1);

            ctx.lineWidth = 0.03
            ctx.strokeStyle="black";

            ctx.beginPath()
            ctx.arc(0.5,0.5,0.5-0.03,0,2*Math.PI)

            ctx.closePath()
            var fillColor = ""

            if (occupied) {
              if(playernr == 0){
                fillColor="dark green"
              } else if(playernr == 1) {
                fillColor="yellow"
              } else if(playernr == 2) {
                fillColor="orange"
              } else if(playernr == 3) {
                fillColor="red"
              } else if(playernr == 4) {
                fillColor="purple"
              } else if(playernr == 5) {
                fillColor="blue"
              } else fillColor="black"
            } else {
              fillColor="white"
            }

            ctx.fillStyle =fillColor
            ctx.fill()
            ctx.stroke()
          }
        }
      }
    }
  }
}
