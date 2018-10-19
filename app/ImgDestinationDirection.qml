import QtQuick 2.0

Item {
	id: img_destination_direction

	width: childrenRect.width
	height: childrenRect.height

    visible: false

	function settleState() {
		if(img_destination_direction.state == "1"){
			img_destination_direction.state = "2";
		} else if(img_destination_direction.state == "2"){
			img_destination_direction.state = "3";
		} else if(img_destination_direction.state == "3"){
			img_destination_direction.state = "4";
		} else if(img_destination_direction.state == "4"){
			img_destination_direction.state = "5";
		} else if(img_destination_direction.state == "5"){
			img_destination_direction.state = "6";
		} else if(img_destination_direction.state == "6"){
			img_destination_direction.state = "7";
		} else if(img_destination_direction.state == "7"){
			img_destination_direction.state = "8";
		} else if(img_destination_direction.state == "8"){
			img_destination_direction.state = "9";
		} else {
			img_destination_direction.state = "1";
		}
	}

	Image {
		id: direction
		x: 0
		y: 0
		width: 100
		height: 100
        source: "images/181px-u-turn.svg.png"

		MouseArea {
			anchors.fill: parent
			onClicked: { settleState() }
		}
	}

	states: [
		State {
			name: "1"
            PropertyChanges { target: img_destination_direction; visible: true }
            PropertyChanges { target: direction; source: "images/181px-u-turn.svg.png" }
		},
		State {
			name: "2"
            PropertyChanges { target: img_destination_direction; visible: true }
            PropertyChanges { target: direction; source: "images/91px-MUTCD_M6-2aR.svg.png" }
		},
		State {
			name: "3"
            PropertyChanges { target: img_destination_direction; visible: true }
            PropertyChanges { target: direction; source: "images/91px-MUTCD_M6-1R.svg.png" }
		},
		State {
			name: "4"
            PropertyChanges { target: img_destination_direction; visible: true }
            PropertyChanges { target: direction; source: "images/91px-MUTCD_M6-2R.svg.png" }
		},
		State {
			name: "5"
            PropertyChanges { target: img_destination_direction; visible: true }
            PropertyChanges { target: direction; source: "images/91px-MUTCD_M6-3.svg.png" }
		},
		State {
			name: "6"
            PropertyChanges { target: img_destination_direction; visible: true }
            PropertyChanges { target: direction; source: "images/91px-MUTCD_M6-2L.svg.png" }
		},
		State {
			name: "7"
            PropertyChanges { target: img_destination_direction; visible: true }
            PropertyChanges { target: direction; source: "images/91px-MUTCD_M6-1L.svg.png" }
		},
		State {
			name: "8"
            PropertyChanges { target: img_destination_direction; visible: true }
            PropertyChanges { target: direction; source: "images/91px-MUTCD_M6-2aL.svg.png" }
		},
		State {
			name: "9"
            PropertyChanges { target: img_destination_direction; visible: true }
            PropertyChanges { target: direction; source: "images/240px-HEB_project_flow_icon_04_checkered_flag.svg.png" }
        },
        State {
            name: "invisible"
            PropertyChanges { target: img_destination_direction; visible: false }
        }

	]
}
