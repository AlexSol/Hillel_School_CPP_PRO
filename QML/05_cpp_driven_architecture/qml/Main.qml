import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

ApplicationWindow {
    width: 920
    height: 640
    visible: true
    title: "05 C++ Driven QML Architecture"

    Rectangle {
        anchors.fill: parent
        color: "#f3f6f9"

        ColumnLayout {
            anchors.fill: parent
            anchors.margins: 20
            spacing: 12

            Label {
                text: "QML renders, C++ owns logic"
                font.pixelSize: 24
                font.bold: true
            }

            Label {
                text: appController.summary
                color: "#1b5e20"
                font.pixelSize: 16
            }

            RowLayout {
                Layout.fillWidth: true
                spacing: 10

                TextField {
                    id: taskInput
                    Layout.fillWidth: true
                    placeholderText: "New task title"
                }

                ComboBox {
                    id: priorityBox
                    model: ["Low", "Medium", "High"]
                    currentIndex: 1
                }

                Button {
                    text: "Add"
                    onClicked: {
                        const ok = appController.addTask(taskInput.text, priorityBox.currentIndex + 1)
                        if (ok) {
                            taskInput.text = ""
                        }
                    }
                }

                Button {
                    text: "Remove Completed"
                    onClicked: appController.removeCompleted()
                }
            }

            ListView {
                Layout.fillWidth: true
                Layout.fillHeight: true
                model: appController.taskModel
                clip: true
                spacing: 6

                delegate: Frame {
                    required property int index
                    required property string title
                    required property bool done
                    required property int priority

                    width: ListView.view.width
                    padding: 10

                    background: Rectangle {
                        radius: 8
                        color: done ? "#e8f5e9" : "#ffffff"
                        border.color: "#d9e2ec"
                    }

                    RowLayout {
                        anchors.fill: parent
                        spacing: 10

                        CheckBox {
                            checked: done
                            onToggled: appController.toggleTask(index)
                        }

                        Label {
                            Layout.fillWidth: true
                            text: title
                            font.strikeout: done
                        }

                        Label {
                            text: priority === 3 ? "High" : (priority === 2 ? "Medium" : "Low")
                            color: priority === 3 ? "#b71c1c" : (priority === 2 ? "#ef6c00" : "#1b5e20")
                        }
                    }
                }
            }
        }
    }
}
