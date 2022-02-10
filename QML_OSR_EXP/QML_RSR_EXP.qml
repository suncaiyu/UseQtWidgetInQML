import QtQuick 2.3
import QtQuick.Window 2.2

import Diy.WidgetOSRItem 1.0

Item
{
    id: osrRoot
    anchors.fill: parent
    property alias osrItem_OSRWidget : osrItem.osrWidget

    Text
    {
        id: expName
        text: "WidgetOSRExp"
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.right: parent.right
        height: 18
        font.pointSize: 14
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
    }

    Rectangle
    {
        id: qmlTitle
        Text
        {
            text: "Qml TextEdit"
            anchors.fill: parent
            font.pointSize: 14
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
        }

        anchors.left: parent.left
        anchors.top: expName.bottom
        width: parent.width/2
        height: 18
        color: "lightblue"
    }


    Rectangle
    {
        id: qtlTitle
        Text
        {
            text: "Qt Widgets"
            anchors.fill: parent
            font.pointSize: 14
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
        }

        anchors.left: qmlTitle.right
        anchors.top: expName.bottom
        width: parent.width/2
        height: 18
        color: "darkred"
    }


    WidgetOSRItem //OSR ITEM
    {
        id: osrItem
        anchors.top: qtlTitle.bottom
        anchors.left: qtlTitle.left
        anchors.right: qtlTitle.right
        anchors.bottom: parent.bottom

        //MouseArea//控制osrItem的焦点
        //{
        //    anchors.fill: parent;
        //    propagateComposedEvents: true
        //
        //    onPressed:
        //    {
        //        mouse.accepted = false
        //        parent.focus = true
        //    }
        //    onReleased: mouse.accepted = false
        //    onMouseXChanged: mouse.accepted = false
        //    onMouseYChanged: mouse.accepted = false
        //}
    }

    TextEdit
    {
        id: qmlTextEdit
        anchors.top: qmlTitle.bottom
        anchors.left: qmlTitle.left
        anchors.right: qmlTitle.right
        anchors.bottom: parent.bottom
        text:"hello I'm Qml Text Editor !"
    }

}
