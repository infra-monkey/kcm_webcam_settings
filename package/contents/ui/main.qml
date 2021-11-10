/**
 * SPDX-FileCopyrightText: Year Author <author@domanin.com>
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

import QtQuick 2.12
import QtQuick.Controls 2.12 as Controls
import QtMultimedia 5.8

import org.kde.kirigami 2.10 as Kirigami
import org.kde.kcm 1.2 as KCM


KCM.SimpleKCM {
    title: i18n("Configure Webcam")
    implicitWidth: Kirigami.Units.gridUnit * 32
    implicitHeight: Kirigami.Units.gridUnit * 38
    Kirigami.Theme.colorSet: Kirigami.Theme.Window
    Kirigami.FormLayout {
        id: mainItem
        Controls.ComboBox {
            id: deviceList
            editable: false
            Kirigami.FormData.label: "Webcam List :"
            model: kcm.device_list
            currentIndex: kcm.deviceIndex
            onActivated: {
                kcm.setDeviceIndex(currentIndex)
                currentIndex=index
            }
            onCurrentIndexChanged: kcm.deviceIndex
        }
        Controls.Slider {
            id: absoluteZoomSlide
            from: kcm.absolute_zoom_min
            to: kcm.absolute_zoom_max
            stepSize: kcm.absolute_zoom_step
            value: kcm.absolute_zoom
            onValueChanged: kcm.absolute_zoom = value
            live: true
        }
    }
}

