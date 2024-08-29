import QtQuick
import QtQuick.Controls

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")


    Rectangle {
        id:rec2
        anchors.fill: parent
        states: [
            State {
                name: "colorAnimation"
                when: id_mouseArea.pressed
                PropertyChanges { target: rec2; color: "red" }
            }
        ]
        transitions: [
            Transition {
                ParallelAnimation {
                    ColorAnimation { property: "color"; duration: 1000 }
                }
            }
        ]

        MouseArea {
            id: id_mouseArea
            anchors.fill: parent
            // onClicked:
        }
    }



    Rectangle {
        width: 300
        height: 300
        color: "white"

        Rectangle {
            id: rect
            width: 50
            height: 50
            color: "blue"

            states: [
                State {
                    name: "moved_right"
                    PropertyChanges { target: rect; x: parent.width - rect.width; color: "red" }
                },
                State {
                    name: "moved_left"
                    PropertyChanges { target: rect; x: 0; color: "blue" }
                }
            ]

            transitions: [
                Transition {
                    from: ""; to: "moved_right"
                    ParallelAnimation {
                        PropertyAnimation { property: "x"; duration: 1000 }
                        ColorAnimation { property: "color"; duration: 1000 }
                    }
                },
                Transition {
                    from: "moved_left"; to: "moved_right"
                    ParallelAnimation {
                        PropertyAnimation { property: "x"; duration: 1000 }
                        ColorAnimation { property: "color"; duration: 1000 }
                    }
                },
                Transition {
                    from: "moved_right"; to: "moved_left"
                    ParallelAnimation {
                        PropertyAnimation { property: "x"; duration: 1000 }
                        ColorAnimation { property: "color"; duration: 1000 }
                    }
                }
            ]

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    if(rect.state === ""){
                        rect.state = "moved_right"
                    }else if(rect.state === "moved_right"){
                        rect.state = "moved_left"
                    }else if(rect.state === "moved_left"){
                        rect.state = "moved_right"
                    }
                }
            }
        }
    }

}
