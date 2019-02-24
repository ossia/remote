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

            Layout.preferredWidth: 240;
            Layout.maximumWidth: 240;

            Layout.alignment: Qt.AlignTop | Qt.AlignHCenter

            WidgetList {
                Layout.alignment: Qt.AlignHCenter
                Layout.fillWidth: true
                implicitHeight: 250

            }

            NodeTree {
                Layout.alignment: Qt.AlignHCenter
                Layout.fillHeight: true
                Layout.fillWidth: true
            }

        }

        CentralArea { Layout.preferredWidth: 200; implicitHeight: 200}


    }

}
