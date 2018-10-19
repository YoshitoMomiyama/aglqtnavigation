import QtQuick 2.0
import QtQuick.Controls 1.5

Item {
	Button {
		id: btn_map_direction
		width: 100
		height: 100

//        property bool heading_up: false

		function settleState() {
            if(root.st_heading_up){
                btn_map_direction.state = "NorthUp"
                car_position_mapitem.state = "NorthUp"
                root.st_heading_up = false
			} else {
                btn_map_direction.state = "HeadingUp"
                car_position_mapitem.state = "HeadingUp"
                root.st_heading_up = true
			}
        }

		onClicked: { settleState() }

		Image {
			id: image
			width: 92
			height: 92
			anchors.verticalCenter: parent.verticalCenter
			anchors.horizontalCenter: parent.horizontalCenter
            source: "images/202px-Compass-icon_bb_N.svg.png"
		}

		states: [
			State {
				name: "HeadingUp"
                PropertyChanges { target: image; source: "images/240px-Compass_icon_NE.svg.png" }
                PropertyChanges { target: map; bearing: 360 - car_direction }
			},
			State {
				name: "NorthUp"
                PropertyChanges { target: image; source: "images/202px-Compass-icon_bb_N.svg.png" }
                PropertyChanges { target: map; bearing: 0 }
			}
		]

        transitions: Transition {
            NumberAnimation { properties: "bearing"; easing.type: Easing.InOutQuad }
        }
	}
}
