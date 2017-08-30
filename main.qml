import QtQuick 2.7
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3

ApplicationWindow
{
    visible: true
    id: rootWindow
    maximumWidth: navigator.width
    minimumWidth: navigator.width

    minimumHeight: navigator.heightLimit

    NavigatorWindow
    {
        id: navigator
        anchors.fill: parent
    }
}
