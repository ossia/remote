import QtQuick 2.7
import QtQuick.Layouts 1.3
import com.github.jcelerier.CreativeControls 1.0

MainPageForm {

    Rectangle{
        anchors.fill: parent
        color: "#302d2e"
    }

    RowLayout
    {
        id: lay
        anchors.fill: parent

        ColumnLayout{

            WidgetList {
                Layout.alignment: Qt.AlignHCenter
                Layout.preferredWidth: 186; implicitHeight: 156}

            NodeTree {
                Layout.alignment: Qt.AlignHCenter
                Layout.preferredWidth: 200;
                implicitHeight: lay.height
                implicitWidth: 200
                width: 200
            }

        }

        CentralArea { Layout.preferredWidth: 200; implicitHeight: 200}


    }

}
