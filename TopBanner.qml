import QtQuick 2.0

Rectangle {
    color: "#4472C5"
    objectName: "mainWindowTop"
    signal mouseDragged (int x, int y)
    Text
    {
        id: title
        text: "标准工时系统"
        color: "white"

        font.pixelSize: 25
        font.bold: true

        anchors.left: parent.left
        anchors.verticalCenter: parent.verticalCenter
    }

    MouseArea
    {
        property point clickPos: "1,1"
        id: headerMouseArea
        anchors.fill: parent
        onPressed:
        {
            clickPos = Qt.point(mouse.x, mouse.y)
        }

        onPositionChanged:
        {
            mouseDragged(mouse.x - clickPos.x, mouse.y - clickPos.y)
        }
    }
}
