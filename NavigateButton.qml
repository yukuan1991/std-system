import QtQuick 2.0
import QtQuick.Controls 2.1


Button
{
    width: 150
    height: 50
    checkable: true
    checked: false

    background: Rectangle
    {
        anchors.fill: parent
        property color bg: "#4472C5"
        color: pressed || checked ? Qt.darker(bg) : hovered ? Qt.lighter(bg) : bg

        border.width: 1
        border.color: "lightblue"
        radius: 4
    }
    contentItem: Rectangle
    {
        color: "transparent"
    }

    Text
    {
        text: parent.text
        color: parent.pressed ? "#FFFFFF" : parent.hovered ? "#666666" : "#FFFFFF"
        font.pixelSize: 20
        font.bold: true
        anchors.centerIn: parent
    }


}
