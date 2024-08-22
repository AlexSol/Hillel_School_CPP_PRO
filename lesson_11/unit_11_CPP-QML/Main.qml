import QtQuick 2.15
import QtQuick.Controls 2.15

ApplicationWindow {
    visible: true
    width: 400
    height: 200
    title: "app version:" + appBackend.version

    property int app_fontSize: 20

    Column{
        anchors.fill: parent
        spacing: 10

        Row {
            spacing: 10
            Text {
                text: "User Name:"
                verticalAlignment: Text.AlignVCenter
                font.pointSize: app_fontSize
            }

            Rectangle {
                width: user_name.width
                height: user_name.height
                color: "lightblue"

                TextInput {
                    id: user_name
                    text: "user_name"
                    // width: 100
                    focus: true
                    font.pointSize: app_fontSize
                     maximumLength: 30  // Максимальна кількість символів
                }
            }
        }

        Button{
            id: bbt_login
            text: "Login"
            onClicked: {
                appBackend.userLogin(user_name.text);
            }
        }

        Text {
            id: text_wellcom
            text: ""
            visible: false
            font.pointSize: app_fontSize
        }
    }

    function onUserLogin(resCode, aDescriptions){
        console.log("resCode:" + resCode + "| " + aDescriptions)

        text_wellcom.visible = true

        if(resCode === 0){
            text_wellcom.text = "Wellcom:" + user_name.text
            text_wellcom.color = 'blue'
        }else
        {
            text_wellcom.text = aDescriptions
            text_wellcom.color = 'red'
        }
    }

    Connections{
        target: appBackend
        function onLoginResult (resCode, aDescriptions){
            onUserLogin(resCode, aDescriptions)
        }
    }

    Component.onCompleted: {
        // appBackend.loginResult.connect(onUserLogin)
    }

}
