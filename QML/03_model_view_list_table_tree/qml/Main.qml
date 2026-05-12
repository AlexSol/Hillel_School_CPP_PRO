import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

ApplicationWindow {
    width: 1100
    height: 720
    visible: true
    title: "03 List, Table and Tree"

    Rectangle {
        anchors.fill: parent
        color: "#eef3f8"

        ColumnLayout {
            anchors.fill: parent
            anchors.margins: 16
            spacing: 12

            Label {
                text: "Qt Model/View in QML"
                font.pixelSize: 24
                font.bold: true
            }

            SplitView {
                Layout.fillWidth: true
                Layout.fillHeight: true

                Frame {
                    SplitView.preferredWidth: parent.width * 0.26
                    ColumnLayout {
                        anchors.fill: parent
                        Label {
                            text: "ListView"
                            font.bold: true
                        }
                        ListView {
                            Layout.fillWidth: true
                            Layout.fillHeight: true
                            model: modelProvider.listModel
                            clip: true
                            delegate: Rectangle {
                                width: ListView.view.width
                                height: 36
                                color: index % 2 ? "#ffffff" : "#f5f8fc"
                                Text {
                                    anchors.centerIn: parent
                                    text: display
                                }
                            }
                        }
                    }
                }

                Frame {
                    SplitView.preferredWidth: parent.width * 0.37
                    ColumnLayout {
                        anchors.fill: parent
                        Label {
                            text: "TableView"
                            font.bold: true
                        }

                        HorizontalHeaderView {
                            Layout.fillWidth: true
                            syncView: tableView
                        }

                        TableView {
                            id: tableView
                            Layout.fillWidth: true
                            Layout.fillHeight: true
                            clip: true
                            model: modelProvider.tableModel
                            columnSpacing: 1
                            rowSpacing: 1

                            delegate: Rectangle {
                                implicitWidth: 120
                                implicitHeight: 36
                                color: row % 2 ? "#ffffff" : "#f5f8fc"
                                border.color: "#d9e2ec"
                                Text {
                                    anchors.centerIn: parent
                                    text: display
                                }
                            }
                        }
                    }
                }

                Frame {
                    SplitView.preferredWidth: parent.width * 0.37
                    ColumnLayout {
                        anchors.fill: parent
                        Label {
                            text: "TreeView"
                            font.bold: true
                        }

                        TreeView {
                            Layout.fillWidth: true
                            Layout.fillHeight: true
                            model: modelProvider.treeModel
                            clip: true
                            delegate: TreeViewDelegate {
                                implicitHeight: 34
                            }
                        }
                    }
                }
            }
        }
    }
}
