import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

ApplicationWindow {
    width: 860
    height: 560
    visible: true
    title: "04 Two-way C++ <-> QML"

    function qmlCallbackFromCpp(message) {
        const result = "QML processed: " + message
        qmlLog.text = result
        return result
    }

    Rectangle {
        anchors.fill: parent
        color: "#f5f7fa"

        ColumnLayout {
            anchors.fill: parent
            anchors.margins: 20
            spacing: 12

            Label {
                text: "Two-way bridge demo"
                font.pixelSize: 24
                font.bold: true
            }

            TextField {
                id: inputName
                Layout.fillWidth: true
                placeholderText: "Name for C++ greet()"
            }

            RowLayout {
                spacing: 10

                Button {
                    text: "QML calls C++ greet"
                    onClicked: cppResult.text = bridgeBackend.greet(inputName.text)
                }

                Button {
                    text: "QML increments C++ counter"
                    onClicked: bridgeBackend.incrementCounter()
                }

                Button {
                    text: "QML sends text to C++"
                    onClicked: bridgeBackend.sendToCpp("Button click from QML")
                }

                Button {
                    text: "C++ calls QML function"
                    onClicked: bridgeBackend.askQmlToRespond()
                }
            }

            Frame {
                Layout.fillWidth: true
                Column {
                    spacing: 6
                    Label { text: "Counter (from C++ property): " + bridgeBackend.counter }
                    Label { id: cppResult; text: "Result will be here" }
                    Label { id: qmlLog; text: "QML callback state" }
                    Label { id: backendLog; text: "Backend log" }
                }
            }
        }
    }

    Connections {
        target: bridgeBackend
        function onCppMessage(message) {
            backendLog.text = message
        }
    }
}
