import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

ApplicationWindow {
    width: 900
    height: 620
    visible: true
    title: "02 Basic QtQuick UI Components"

    property string selectedOption: combo.currentText

    Rectangle {
        anchors.fill: parent
        color: "#f7f9fc"

        ScrollView {
            anchors.fill: parent
            contentWidth: availableWidth

            ColumnLayout {
                width: parent.width
                spacing: 14
                //padding: 20

                Label {
                    text: "Base Qt Quick Controls demo"
                    font.pixelSize: 26
                    font.bold: true
                }

                TextField {
                    id: nameField
                    Layout.fillWidth: true
                    placeholderText: "Type your name"
                }

                RowLayout {
                    spacing: 12

                    Button {
                        text: "Say Hello"
                        onClicked: output.text = "Hello, " + (nameField.text.length ? nameField.text : "student")
                    }

                    CheckBox {
                        id: check
                        text: "Advanced mode"
                    }

                    Switch {
                        id: sw
                        text: checked ? "On" : "Off"
                    }
                }

                Slider {
                    id: slider
                    from: 0
                    to: 100
                    value: 30
                    Layout.fillWidth: true
                }

                ProgressBar {
                    value: slider.value / 100.0
                    Layout.fillWidth: true
                }

                RowLayout {
                    spacing: 12

                    ComboBox {
                        id: combo
                        model: ["C++", "Qt Quick", "QML"]
                    }

                    SpinBox {
                        id: spin
                        from: 1
                        to: 10
                        value: 3
                    }

                    Dial {
                        id: dial
                        from: 0
                        to: 360
                        value: 90
                    }
                }

                TextArea {
                    id: notes
                    Layout.fillWidth: true
                    Layout.preferredHeight: 120
                    placeholderText: "Write some notes"
                }

                Label {
                    id: output
                    text: "Selected: " + selectedOption + ", level: " + spin.value + ", angle: " + Math.round(dial.value)
                    wrapMode: Text.Wrap
                    Layout.fillWidth: true
                }

                Frame {
                    Layout.fillWidth: true
                    contentItem: Column {
                        spacing: 6
                        Label { text: "Live state" }
                        Label { text: "Checkbox: " + (check.checked ? "true" : "false") }
                        Label { text: "Switch: " + (sw.checked ? "true" : "false") }
                        Label { text: "Slider: " + Math.round(slider.value) }
                        Label { text: "Text size: " + notes.text.length }
                    }
                }
            }
        }
    }
}
