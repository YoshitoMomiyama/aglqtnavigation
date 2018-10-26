import QtQuick 2.0

Item {
	id: img_destination_direction

	width: childrenRect.width
	height: childrenRect.height

    visible: false

//    function settleState() {
//        if(img_destination_direction.state == "0"){
//            img_destination_direction.state = "1";
//        } else if(img_destination_direction.state == "1"){
//            img_destination_direction.state = "2";
//        } else if(img_destination_direction.state == "2"){
//            img_destination_direction.state = "3";
//        } else if(img_destination_direction.state == "3"){
//            img_destination_direction.state = "4";
//        } else if(img_destination_direction.state == "4"){
//            img_destination_direction.state = "5";
//        } else if(img_destination_direction.state == "5"){
//            img_destination_direction.state = "6";
//        } else if(img_destination_direction.state == "6"){
//            img_destination_direction.state = "7";
//        } else if(img_destination_direction.state == "7"){
//            img_destination_direction.state = "8";
//        } else if(img_destination_direction.state == "8"){
//            img_destination_direction.state = "9";
//        } else if(img_destination_direction.state == "9"){
//            img_destination_direction.state = "10";
//        } else if(img_destination_direction.state == "10"){
//            img_destination_direction.state = "11";
//        } else {
//            img_destination_direction.state = "0";
//        }
//    }

	Image {
		id: direction
		x: 0
		y: 0
		width: 100
		height: 100
        source: "images/SW_Patern_3.bmp"

		MouseArea {
			anchors.fill: parent
//            onClicked: { settleState() }
		}
	}

	states: [
        State {
            name: "0" // NoDirection
            PropertyChanges { target: img_destination_direction; visible: true }
            PropertyChanges { target: direction; source: "images/SW_Patern_3.bmp" }
        },
        State {
            name: "1" // DirectionForward
            PropertyChanges { target: img_destination_direction; visible: true }
            PropertyChanges { target: direction; source: "images/5_straight.png" }
		},
		State {
            name: "2" // DirectionBearRight
            PropertyChanges { target: img_destination_direction; visible: true }
            PropertyChanges { target: direction; source: "images/11_2_bear_right_112px-Signal_C117a.svg.png" }
		},
		State {
            name: "3" // DirectionLightRight
            PropertyChanges { target: img_destination_direction; visible: true }
            PropertyChanges { target: direction; source: "images/4_slight_right.png" }
		},
		State {
            name: "4" // DirectionRight
            PropertyChanges { target: img_destination_direction; visible: true }
            PropertyChanges { target: direction; source: "images/3_right.png" }
		},
		State {
            name: "5" // DirectionHardRight
            PropertyChanges { target: img_destination_direction; visible: true }
            PropertyChanges { target: direction; source: "images/2_sharp_right.png" }
		},
		State {
            name: "6" // DirectionUTurnRight
            PropertyChanges { target: img_destination_direction; visible: true }
            PropertyChanges { target: direction; source: "images/1_uturn.png" }
		},
		State {
            name: "7" // DirectionUTurnLeft
            PropertyChanges { target: img_destination_direction; visible: true }
            PropertyChanges { target: direction; source: "images/9_7_uturn_left.png" }
		},
		State {
            name: "8" // DirectionHardLeft
            PropertyChanges { target: img_destination_direction; visible: true }
            PropertyChanges { target: direction; source: "images/8_sharp_left.png" }
		},
		State {
            name: "9" // DirectionLeft
            PropertyChanges { target: img_destination_direction; visible: true }
            PropertyChanges { target: direction; source: "images/7_left.png" }
        },
        State {
            name: "10" // DirectionLightLeft
            PropertyChanges { target: img_destination_direction; visible: true }
            PropertyChanges { target: direction; source: "images/6_slight_left.png" }
        },
        State {
            name: "11" // DirectionBearLeft
            PropertyChanges { target: img_destination_direction; visible: true }
            PropertyChanges { target: direction; source: "images/10_11_bear_left_112px-Signal_C117a.svg.png" }
        },
        State {
            name: "12" // arrived at your destination
            PropertyChanges { target: img_destination_direction; visible: true }
            PropertyChanges { target: direction; source: "images/Dest_Flag.jpg" }
        },
        State {
            name: "invisible"
            PropertyChanges { target: img_destination_direction; visible: false }
        }

	]
}
