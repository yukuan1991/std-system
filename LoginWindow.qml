import QtQuick 2.0
import QtQuick.Window 2.0
import QtQuick.Controls 2.2

Rectangle
{
    width: 600; height: 450
    id: rootWindow
    //visible: true
    //flags: Qt.FramelessWindowHint
    signal loginClicked (string name, string pass)
    Rectangle
    {
        anchors.fill: parent
        LoginHeader
        {
            id: header
            headerHeight: 30
            color: "red"
        }
        LoginPanel
        {
            id: pannel
            anchors.top: header.bottom
            anchors.bottom: parent.bottom
            anchors.left: header.left
            anchors.right: header.right
            onLoginClicked: rootWindow.loginClicked (name, pass)
        }
    }

}
