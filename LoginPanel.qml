import QtQuick 2.0
import QtQuick.Controls 2.1


Rectangle
{
    id: rootRect
    visible: true

    signal loginClicked (string user, string pass)

    Image {
        id: background
        source: "png/login-bg.png"
        anchors.fill: parent
    }

    TextField
    {
        id: userName
        width: 300; height: 40

        placeholderText: "请输入用户名"
        selectByMouse: true

        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
    }

    Label
    {
        id: labelUserName
        text: "用户名"

        anchors.right: userName.left
        anchors.rightMargin: 4

        anchors.verticalCenter: userName.verticalCenter
    }

    TextField
    {
        id: password
        width: 300; height: 40

        anchors.top: userName.bottom
        anchors.topMargin: 4
        anchors.horizontalCenter: parent.horizontalCenter

        placeholderText: "请输入密码"

        echoMode: TextInput.Password
    }

    Label
    {
        id: labelPassword
        text: "密码"
        anchors.right: password.left
        anchors.rightMargin: 4
        anchors.verticalCenter: password.verticalCenter
    }

    Button
    {
        id: loginButton
        text: "登录"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: password.bottom
        anchors.topMargin: 10
        width: password.width
        height: password.height

        onClicked: rootRect.loginClicked (userName.text, password.text)

        background: Rectangle
        {
            id: loginButtonBg
            anchors.fill: parent
            property color bg: "#A0A0A0"
            color: loginButton.pressed ? Qt.darker(bg) : loginButton.hovered ? Qt.lighter(bg) : bg
            radius: 4
        }
        Text
        {
            text: parent.text
            color: parent.pressed ? "#FFFFFF" : parent.hovered ? "#666666" : "#FFFFFF"

            anchors.centerIn: parent
        }
    }
}
