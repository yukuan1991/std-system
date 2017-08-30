import QtQuick 2.0
import QtQuick.Controls 2.1

Rectangle
{
    id: headerArea
    property ApplicationWindow rootWindow: null
    property int headerHeight

    height: headerHeight
    width: parent.width

    anchors.top: parent.top
    anchors.left: parent.left
    anchors.right: parent.right

    MouseArea
    {
        signal mouseDragged (real x, real y)
        property point clickPos: "1,1"
        id: headerMouseArea
        anchors.fill: parent
        onPressed:
        {
            clickPos = Qt.point(mouse.x, mouse.y)
        }

        onPositionChanged:
        {
            const delta = Qt.point (mouse.x - clickPos.x, mouse.y - clickPos.y)
            rootWindow.setX(rootWindow.x + delta.x)
            rootWindow.setY(rootWindow.y + delta.y)
        }
    }

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
