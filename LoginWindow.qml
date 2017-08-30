import QtQuick 2.0
import QtQuick.Window 2.0
import QtQuick.Controls 2.2

ApplicationWindow
{
    width: 600; height: 450
    id: rootWindow
    visible: true
    flags: Qt.FramelessWindowHint
    Rectangle
    {
        anchors.fill: parent
        LoginHeader
        {
            id: header
            headerHeight: 30
            color: "lightgray"
            rootWindow: rootWindow
        }
        LoginPanel
        {
            anchors.top: header.bottom
            anchors.bottom: parent.bottom
            anchors.left: header.left
            anchors.right: header.right
        }
    }

}
