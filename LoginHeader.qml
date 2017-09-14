import QtQuick 2.0
import QtQuick.Controls 2.1

Rectangle
{
    id: headerArea
    property int headerHeight

    height: headerHeight
    width: parent.width

    anchors.top: parent.top
    anchors.left: parent.left
    anchors.right: parent.right

    Button
    {
        id: closeButton
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        width: height

        background: Rectangle
        {
            color: closeButton.pressed ? "#666666" : closeButton.hovered ? "#333333" : "transparent"
        }

        Text
        {
            text: "X"
            font.pointSize: 10
            font.family: "consolas"
            color: closeButton.hovered ? "white" : "black"
            anchors.centerIn: parent
        }
        onClicked: rootWindow.close()

        ToolTip
        {
            id: closeButtonToolTip
            text: "关闭"
            visible: parent.hovered
        }
    }
}
