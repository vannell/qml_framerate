import QtQuick 2.7
import be.mindgoo.tools 0.1

Item {
    visible: true
    width: 640
    height: 480

    FrequencyMonitor {
        id: monitor
        refreshFrequency: 500
    }

    Text {
        text: monitor.fps
    }

    Rectangle {
        anchors.centerIn: parent
        width: 200
        height: 200

        ColorAnimation on color {
            from: "red"
            to: "purple"
            duration: 3000
            loops: Animation.Infinite
        }
    }
}
