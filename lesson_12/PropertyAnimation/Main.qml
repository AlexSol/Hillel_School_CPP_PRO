import QtQuick
import QtQuick.Controls

Window {
    id: root
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    Rectangle {
        width: 300
        height: 300
        color: "lightgreen"

        Rectangle {
            id: animatedRect
            width: 100
            height: 100
            color: "blue"
            anchors.centerIn: parent

            // Автоматическая анимация изменения ширины
            Behavior on width {
                NumberAnimation { duration: 500; easing.type: Easing.InOutQuad }
            }

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    animatedRect.width = animatedRect.width === 100 ? 200 : 100;
                }
            }
        }
    }
}

