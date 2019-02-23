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
            id: columnLayout

            property real colWidth: 240;
            Layout.preferredWidth: colWidth;
            Layout.alignment: Qt.AlignTop | Qt.AlignHCenter

            WidgetList {
                Layout.alignment: Qt.AlignHCenter
                implicitHeight: 250
                width: columnLayout.colWidth
            }

            NodeTree {
                Layout.alignment: Qt.AlignHCenter
                implicitHeight: 200
                width: columnLayout.colWidth
            }

        }

        CentralArea { Layout.preferredWidth: 200; implicitHeight: 200}


    }

}
