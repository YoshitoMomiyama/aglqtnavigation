/*
 * Copyright (C) 2016 The Qt Company Ltd.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *	  http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

import QtQuick 2.6
import QtQuick.Layouts 1.1
import QtQuick.Controls 2.0
import QtWebSockets 1.0
import QtLocation 5.9
import QtPositioning 5.6

ApplicationWindow {
	id: root
	visible: true
	width: 1080
	height: 1488
	title: qsTr("TestQt")

    property real car_position_lat: 42.2980     // Toyota Motor North America
    property real car_position_lon: -83.6773
    property real car_direction: 135    //SouthEast
    property bool st_heading_up: false
    property real default_zoom_level : 18


	Map{
		id: map
        property int pathcounter : 0
        property int segmentcounter : 0
        property int waypoint_count: -1
		property int lastX : -1
		property int lastY : -1
		property int pressX : -1
		property int pressY : -1
		property int jitterThreshold : 30
        property variant currentpostion : QtPositioning.coordinate(car_position_lat, car_position_lon)	// Toyota Motor North America
        property variant demoguidance_position : currentpostion

        width: 1080
		height: 1488
		plugin: Plugin {
			name: "mapbox"
			PluginParameter { name: "mapbox.access_token";
			value: "pk.eyJ1IjoiYWlzaW53ZWkiLCJhIjoiY2pqNWg2cG81MGJoazNxcWhldGZzaDEwYyJ9.imkG45PQUKpgJdhO2OeADQ" }
		}
        center: currentpostion	// Toyota Motor North America
        zoomLevel: default_zoom_level
        bearing: 0  //north up

		GeocodeModel {
			id: geocodeModel
			plugin: map.plugin
			onStatusChanged: {
				if ((status == GeocodeModel.Ready) || (status == GeocodeModel.Error))
					map.geocodeFinished()
			}
			onLocationsChanged:
			{
				if (count == 1) {
					map.center.latitude = get(0).coordinate.latitude
					map.center.longitude = get(0).coordinate.longitude
				}
			}
            //coordinate: poiTheQtComapny.coordinate
            //anchorPoint: Qt.point(-poiTheQtComapny.sourceItem.width * 0.5,poiTheQtComapny.sourceItem.height * 1.5)
		}
		MapItemView {
			model: geocodeModel
			delegate: pointDelegate
		}
		Component {
			id: pointDelegate

			MapCircle {
				id: point
				radius: 1000
				color: "#46a2da"
				border.color: "#190a33"
				border.width: 2
				smooth: true
				opacity: 0.25
				center: locationData.coordinate
			}
		}
		function geocode(fromAddress)
		{
			// send the geocode request
			geocodeModel.query = fromAddress
			geocodeModel.update()
		}
		
        MapQuickItem {
            id: car_position_mapitem
            sourceItem: Image {
                id: car_position_mapitem_image
                width: 16
                height: 16
                source: "images/240px-Red_Arrow_Up.svg.png"

                transform: Rotation {
                    id: car_position_mapitem_image_rotate
                    origin.x: car_position_mapitem_image.width/2
                    origin.y: car_position_mapitem_image.height/2
                    angle: car_direction
                }
            }
            anchorPoint: Qt.point(car_position_mapitem_image.width/2, car_position_mapitem_image.height/2)
            coordinate: map.demoguidance_position


            states: [
                State {
                    name: "HeadingUp"
                    PropertyChanges { target: car_position_mapitem_image_rotate; angle: 0 }
                },
                State {
                    name: "NorthUp"
                    PropertyChanges { target: car_position_mapitem_image_rotate; angle: root.car_direction }
                }
            ]
            transitions: Transition {
                NumberAnimation { properties: "angle"; easing.type: Easing.InOutQuad }
            }
        }

		RouteModel {
			id: routeModel
			plugin : map.plugin
			query:  RouteQuery {
				id: routeQuery
			}
			onStatusChanged: {
				if (status == RouteModel.Ready) {
					switch (count) {
					case 0:
						// technically not an error
					//	map.routeError()
						break
					case 1:
						map.pathcounter = 0
						map.segmentcounter = 0
						console.log("1 route found")
						console.log("path: ", get(0).path.length, "segment: ", get(0).segments.length)
						for(var i = 0; i < get(0).path.length; i++){
							console.log("", get(0).path[i])
						}
						console.log("1st instruction: ", get(0).segments[map.segmentcounter].maneuver.instructionText)
						break
					}
				} else if (status == RouteModel.Error) {
				//	map.routeError()
				}
			}
		}
		
		Component {
			id: routeDelegate

			MapRoute {
				id: route
				route: routeData
				line.color: "#4658da"
				line.width: 10
				smooth: true
				opacity: 0.8
			}
		}
		
		MapItemView {
			model: routeModel
			delegate: routeDelegate
		}

        function addDestination(coord){
            if( waypoint_count < 0 ){
                initDestination()
            }

            if(waypoint_count < 9){
                routeQuery.addWaypoint(coord)
                waypoint_count += 1

                btn_guidance.sts_guide = 1
                btn_guidance.state = "Routing"

                routeModel.update()
            }
        }

        function initDestination(){
            routeModel.reset();
            console.log("initWaypoint")
            routeQuery.clearWaypoints();
            routeQuery.addWaypoint(currentpostion)
            routeQuery.travelModes = RouteQuery.CarTravel
            routeQuery.routeOptimizations = RouteQuery.FastestRoute
            for (var i=0; i<9; i++) {
                routeQuery.setFeatureWeight(i, 0)
            }
            waypoint_count = 0
            pathcounter = 0
            segmentcounter = 0
            routeModel.update();

            // update car_position_mapitem
            car_position_mapitem.coordinate = currentpostion

            // TODO:update car_position_mapitem angle


            // update map.center
            map.center = currentpostion
        }

		function calculateMarkerRoute()
		{
            var startCoordinate = QtPositioning.coordinate(car_position_lat, car_position_lon)

			console.log("calculateMarkerRoute")
			routeQuery.clearWaypoints();
            routeQuery.addWaypoint(startCoordinate)
            routeQuery.addWaypoint(mouseArea.lastCoordinate)
			routeQuery.travelModes = RouteQuery.CarTravel
			routeQuery.routeOptimizations = RouteQuery.FastestRoute
			for (var i=0; i<9; i++) {
				routeQuery.setFeatureWeight(i, 0)
			}
			routeModel.update();
		}

        function calculateNextCoordinate(currentCoordinate,degree,distance)
        {
            console.log("calculateDemoRouteCoordinate")

            var radian = degree * Math.PI / 180;
            var toSN = Math.sin(radian) * distance
            var toEW = Math.cos(radian) * distance
            var lat
            var lon
        }

		MouseArea {
			id: mouseArea
			property variant lastCoordinate
			anchors.fill: parent
			acceptedButtons: Qt.LeftButton | Qt.RightButton
			
			onPressed : {
				map.lastX = mouse.x
				map.lastY = mouse.y
				map.pressX = mouse.x
				map.pressY = mouse.y
				lastCoordinate = map.toCoordinate(Qt.point(mouse.x, mouse.y))
			}
			
			onPositionChanged: {
                if (mouse.button === Qt.LeftButton) {
					map.lastX = mouse.x
					map.lastY = mouse.y
				}
			}
			
			onPressAndHold:{
				if (Math.abs(map.pressX - mouse.x ) < map.jitterThreshold
						&& Math.abs(map.pressY - mouse.y ) < map.jitterThreshold) {
                    map.addDestination(lastCoordinate)
				}
			}
		}
		
		function updatePositon()
		{
			console.log("updatePositon")
            if(pathcounter < routeModel.get(0).path.length){
                console.log("path: ", pathcounter, "/", routeModel.get(0).path.length, "", routeModel.get(0).path[pathcounter])
                map.demoguidance_position = routeModel.get(0).path[pathcounter]

                // report a new instruction if current position matches with the head position of the segment
                if(segmentcounter < routeModel.get(0).segments.length){
                    if(routeModel.get(0).path[pathcounter] === routeModel.get(0).segments[segmentcounter].path[0]){
                        console.log("new segment: ", segmentcounter, "/", routeModel.get(0).segments.length)
                        console.log("instruction: ", routeModel.get(0).segments[segmentcounter].maneuver.instructionText)
                        segmentcounter++
                    }
                }

                // update car_position_mapitem
                car_position_mapitem.coordinate = map.demoguidance_position

                // TODO:update car_position_mapitem angle

                // update progress_next_cross
                progress_next_cross.setProgress(Math.random() * 150)

                // update map.center
                map.center = map.demoguidance_position

                pathcounter++
            }
            else
            {
                btn_guidance.sts_guide = 0
            }
		}
	}
		
	Item {
		id: btn_present_position
		x: 942
//		y: 1328
        y: 530      // for debug
		
		Button {
            id: btn_present_position_
			width: 100
			height: 100
			
			function present_position_clicked() {
                map.center = currentpostion
                map.zoomLevel = default_zoom_level
            }
			onClicked: { present_position_clicked() }
			
			Image {
				id: image_present_position
                width: 48
				height: 92
				anchors.verticalCenter: parent.verticalCenter
				anchors.horizontalCenter: parent.horizontalCenter
                source: "images/207px-Car_icon_top.svg.png"
			}
		}
	}
	
	BtnMapDirection {
        id: btn_map_direction
		x: 15
		y: 20
	}

    BtnGuidance {
        id: btn_guidance
		x: 940
		y: 20
	}

	BtnShrink {
        id: btn_shrink
		x: 23
//		y:1200
        y:400   // for debug
	}

	BtnEnlarge {
        id: btn_enlarge
		x: 23
//		y: 1330
        y:530   // for debug
	}

	ImgDestinationDirection {
        id: img_destination_direction
		x: 120
		y: 20
	}

    ProgressNextCross {
        id: progress_next_cross
		x: 225
		y: 20
	}
}
