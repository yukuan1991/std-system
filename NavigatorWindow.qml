import QtQuick 2.0
import QtQuick.Controls 2.2

Rectangle
{
    id : navigator

    width: 155
    color: "#DDDDDD"
    property int heightLimit: 10 * 50 + 6 * 4 + 20 + 200
    signal stackChanged (string id)

    Rectangle
    {
        color: parent.color
        width: 150; height: 50 * 2 + 4 * 2

        id: videoAnalysis


        anchors.top: parent.top
        anchors.topMargin: 30
        anchors.horizontalCenter: parent.horizontalCenter
        NavigateButton
        {
            id:videoMassProduction
            objectName: "videoMassProduction"
            text: "视频分析(量产)"
        }

        NavigateButton
        {
            id: videoTestProduction
            objectName: "videoTestProduction"
            text: "视频分析(试产)"
            anchors.top: videoMassProduction.bottom
            anchors.topMargin: 4
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 4
        }
    }

    Rectangle
    {
        color: parent.color
        width: 150; height: 50 * 3 + 4 * 4
        id: ptsAnalysis
        anchors.top: videoAnalysis.bottom
        anchors.topMargin: 30
        anchors.horizontalCenter: parent.horizontalCenter

        NavigateButton
        {
            id:mtm
            text: "MTM-UAS"
            objectName: "mtm"
            anchors.top: parent.top
            anchors.topMargin: 4
        }

        NavigateButton
        {
            id: mod
            text: "MOD"
            objectName: "mod"
            anchors.top: mtm.bottom
            anchors.topMargin: 4
        }

        NavigateButton
        {
            id: most
            text: "MOST"
            objectName: "most"
            anchors.top: mod.bottom
            anchors.topMargin: 4
        }
    }

    Rectangle
    {
        color: parent.color
        width: 150; height: 50 * 3 + 4 * 4
        id: management
        anchors.top: ptsAnalysis.bottom
        anchors.topMargin: 30
        anchors.horizontalCenter: parent.horizontalCenter

        NavigateButton
        {
            id: productionClassManagement
            text: "产品族管理"
            anchors.top: parent.top
            anchors.topMargin: 4
        }

        NavigateButton
        {
            id: productionFixedAmount
            text: "产品工时定额"
            anchors.top: productionClassManagement.bottom
            anchors.topMargin: 4
        }

        NavigateButton
        {
            id: productionTimeChart
            text: "产品工时报表"
            anchors.top: productionFixedAmount.bottom
            anchors.topMargin: 4
        }
    }

    Rectangle
    {
        color: parent.color
        width: 150
        height: 50 * 2 + 4 * 4
        id: dataStorage
        anchors.top: management.bottom
        anchors.topMargin: 30
        anchors.horizontalCenter: parent.horizontalCenter

        NavigateButton
        {
            id: stdStorage
            text: "标准资料库"
            anchors.top: parent.top
            anchors.topMargin: 4
        }

        NavigateButton
        {
            id: approving
            text: "审批"
            anchors.top: stdStorage.bottom
            anchors.topMargin: 4
        }
    }

    ButtonGroup
    {
        id: bgroup
        onCheckedButtonChanged:  stackChanged(checkedButton.objectName)
    }

    Component.onCompleted:
    {
        bgroup.addButton (videoMassProduction)
        bgroup.addButton (videoTestProduction)
        bgroup.addButton (mtm)
        bgroup.addButton (mod)
        bgroup.addButton (most)
        bgroup.addButton (productionClassManagement)
        bgroup.addButton (productionFixedAmount)
        bgroup.addButton (productionTimeChart)
        bgroup.addButton (stdStorage)
        bgroup.addButton (approving)
    }
}
