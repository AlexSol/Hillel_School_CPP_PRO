import QtQuick

Window {
    id: root
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    Rectangle {
        id: rect
        width: 100; height: 100
        color: "red"

        RotationAnimation on rotation {
                loops: Animation.Infinite
                from: 0
                to: 360
                duration: 1000
            }

        SequentialAnimation {
            running: true
            NumberAnimation { target: rect; property: "x"; to: 50; duration: 1000 }
            NumberAnimation { target: rect; property: "y"; to: 50; duration: 1000 }
        }

        MouseArea {
            id: myMouse
            anchors.fill: parent
        }
    }

}
