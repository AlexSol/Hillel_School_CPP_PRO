import QtQuick

Window {
    width: 640
    height: 480
    visible: true
    title: "Parallel Animation Example"

    Rectangle {
            id: rect
            width: 100
            height: 100
            color: "red"

            MouseArea {
                        anchors.fill: parent
                        onClicked:
                            SequentialAnimation {
                            ParallelAnimation{
                                NumberAnimation { target: rect; property: "x"; to: 50; duration: 1000 }
                                NumberAnimation { target: rect; property: "y"; to: 50; duration: 1000 }
                                }
                            }

            }
    }
}
