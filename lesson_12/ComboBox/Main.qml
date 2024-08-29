import QtQuick
import QtQuick.Controls

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    Rectangle {
        width: 200
        height: 200
        color: "lightgray"

        ComboBox {
            id: comboBox
            width: 100
            height: 30
            anchors.centerIn: parent
            model: ["Option blue", "Option green"]

            contentItem: Text {
                text: comboBox.currentIndex === 0 ? "blue" : "green"
                color: comboBox.currentIndex === 0 ? "blue" : "green"
            }
        }
    }


}
