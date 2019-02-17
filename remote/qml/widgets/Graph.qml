import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3
import com.github.jcelerier.CreativeControls 1.0 as CC

Rectangle {
    id: widg

    property alias graph: graph
    property alias label: label
    property alias dropper: dropper

    signal valueChange(point val)
    signal addressChanged(string addr)

    // Use this function to add a value to the graph.
    function pushValue(v) {
        graph.pushValue(v);
    }
    width: 162
    height: 150
    color: "#00000000"
    Drag.dragType: Drag.Internal

    ColumnLayout {
        AddressLabel {
            id: label
            Layout.preferredHeight: 18
            Layout.preferredWidth: 162
        }

        CC.Graph {
            id: graph
            width: 162
            height: 126
        }
    }

    AddressDrop {
        id: dropper
        item: widg
    }
}
