import QtQuick
import QtQuick.Controls

ApplicationWindow {
    width: 640
    height: 360
    visible: true
    title: "01 Minimal QML"

    Rectangle {
        anchors.fill: parent
        color: "#f4f7fb"

        Text {
            anchors.centerIn: parent
            text: "Hello from minimal Qt Quick app"
            font.pixelSize: 24
            color: "#203040"
        }
    }
}
