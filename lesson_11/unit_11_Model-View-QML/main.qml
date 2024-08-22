import QtQuick 2.15
import QtQuick.Controls 2.15

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: "Model-View Example"

    ListView {
        width: 200
        height: 400
        anchors.centerIn: parent

        // Model: JavaScript array
        model: ["apple", "banana", "Orange", "Grapes"]

        // Delegate: How each item in the model is displayed
        delegate: Item {
            width: 200
            height: 40

            Rectangle {
                anchors.fill: parent
                color: index % 2 === 0 ? "lightblue" : "lightgreen"

                Row{
                    spacing: 10
                    Image {
                        // anchors.fill: parent
                        height: 40
                        width:  40
                        source: "images/" + modelData + ".png"
                    }
                    Text {
                        text: modelData
                        // anchors.centerIn: parent
                        font.pointSize: 18
                    }
                }
            }
        }
    }
}
