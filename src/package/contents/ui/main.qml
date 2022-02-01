/**
 * SPDX-FileCopyrightText: Year Author <author@domanin.com>
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

import QtQuick 2.15
import QtQuick.Controls 2.15 as Controls
import QtMultimedia 5.8
import QtQuick.Layouts 1.15

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
            Kirigami.FormData.label: "Device list:"
            model: kcm.device_list
            currentIndex: kcm.deviceIndex
            onActivated: {
                kcm.setDeviceIndex(currentIndex)
                currentIndex=index
            }
            onCurrentIndexChanged: kcm.deviceIndex
        }
        RowLayout {
            Controls.ComboBox {
                id: formatList
                editable: false
                Kirigami.FormData.label: "Format list:"
                model: kcm.format_list
                currentIndex: kcm.formatIndex
                onActivated: {
                    kcm.setFormatIndex(currentIndex)
                    currentIndex=index
                }
                onCurrentIndexChanged: kcm.formatIndex
            }
            Controls.ComboBox {
                id: resolutionList
                editable: false
                Kirigami.FormData.label: "Resolution list:"
                model: kcm.resolution_list
                currentIndex: kcm.resolutionIndex
                onActivated: {
                    kcm.setResolutionIndex(currentIndex)
                    currentIndex=index
                }
                onCurrentIndexChanged: kcm.resolutionIndex
            }
            Controls.Button {
                id: resolutionApply
                text: i18n("Apply")
                onClicked: kcm.applyResolution()
            }
        }
        RowLayout {
            id: brightnessCtrl
            visible: kcm.brightness_visible
            Layout.fillWidth: true
            Layout.maximumWidth: Kirigami.Units.gridUnit * 16
            Kirigami.FormData.label: i18n("Brightness:")
            Controls.Slider {
                id: brightnessSlide
                from: kcm.brightness_min
                to: kcm.brightness_max
                stepSize: kcm.brightness_step
                value: kcm.brightness
                onMoved: kcm.brightness = value
                live: true
            }
            Controls.SpinBox {
                implicitWidth: 100
                implicitHeight: 45
                id: brightnessSpinbox
                from: kcm.brightness_min
                to: kcm.brightness_max
                stepSize: kcm.brightness_step
                value: kcm.brightness
                onValueModified: kcm.brightness = value
            }
            Controls.Button {
                id: brightnessResetCtrl
                text: i18n("Reset To Default")
                onClicked: kcm.resetCrtlToDefault("brightness")
            }
        }
        RowLayout {
            id: contrastCtrl
            visible: kcm.contrast_visible
            Layout.fillWidth: true
            Layout.maximumWidth: Kirigami.Units.gridUnit * 16
            Kirigami.FormData.label: i18n("Contrast:")
            Controls.Slider {
                id: contrastSlide
                from: kcm.contrast_min
                to: kcm.contrast_max
                stepSize: kcm.contrast_step
                value: kcm.contrast
                onMoved: kcm.contrast = value
                live: true
            }
            Controls.SpinBox {
                implicitWidth: 100
                implicitHeight: 45
                id: contrastSpinbox
                from: kcm.contrast_min
                to: kcm.contrast_max
                stepSize: kcm.contrast_step
                value: kcm.contrast
                onValueModified: kcm.contrast = value
            }
            Controls.Button {
                id: contrastResetCtrl
                text: i18n("Reset To Default")
                onClicked: kcm.resetCrtlToDefault("contrast")
            }
        }
        RowLayout {
            id: sharpnessCtrl
            visible: kcm.sharpness_visible
            Layout.fillWidth: true
            Layout.maximumWidth: Kirigami.Units.gridUnit * 16
            Kirigami.FormData.label: i18n("Sharpness:")
            Controls.Slider {
                id: sharpnessSlide
                from: kcm.sharpness_min
                to: kcm.sharpness_max
                stepSize: kcm.sharpness_step
                value: kcm.sharpness
                onMoved: kcm.sharpness = value
                live: true
            }
            Controls.SpinBox {
                implicitWidth: 100
                implicitHeight: 45
                id: sharpnessSpinbox
                from: kcm.sharpness_min
                to: kcm.sharpness_max
                stepSize: kcm.sharpness_step
                value: kcm.sharpness
                onValueModified: kcm.sharpness = value
            }
            Controls.Button {
                id: sharpnessResetCtrl
                text: i18n("Reset To Default")
                onClicked: kcm.resetCrtlToDefault("sharpness")
            }
        }
        RowLayout {
            id: saturationCtrl
            visible: kcm.saturation_visible
            Layout.fillWidth: true
            Layout.maximumWidth: Kirigami.Units.gridUnit * 16
            Kirigami.FormData.label: i18n("Saturation:")
            Controls.Slider {
                id: saturationSlide
                from: kcm.saturation_min
                to: kcm.saturation_max
                stepSize: kcm.saturation_step
                value: kcm.saturation
                onMoved: kcm.saturation = value
                live: true
            }
            Controls.SpinBox {
                implicitWidth: 100
                implicitHeight: 45
                id: saturationSpinbox
                from: kcm.saturation_min
                to: kcm.saturation_max
                stepSize: kcm.saturation_step
                value: kcm.saturation
                onValueModified: kcm.saturation = value
            }
            Controls.Button {
                id: saturationResetCtrl
                text: i18n("Reset To Default")
                onClicked: kcm.resetCrtlToDefault("saturation")
            }
        }
        RowLayout {
            id: zoomCtrl
            visible: kcm.absolute_zoom_visible
            Layout.fillWidth: true
            Layout.maximumWidth: Kirigami.Units.gridUnit * 16
            Kirigami.FormData.label: i18n("Absolute Zoom:")
            Controls.Slider {
                id: absoluteZoomSlide
                from: kcm.absolute_zoom_min
                to: kcm.absolute_zoom_max
                stepSize: kcm.absolute_zoom_step
                value: kcm.absolute_zoom
                onMoved: kcm.absolute_zoom = value
                live: true
            }
            Controls.SpinBox {
                implicitWidth: 100
                implicitHeight: 45
                id: absoluteZoomSpinbox
                from: kcm.absolute_zoom_min
                to: kcm.absolute_zoom_max
                stepSize: kcm.absolute_zoom_step
                value: kcm.absolute_zoom
                onValueModified: kcm.absolute_zoom = value
            }
            Controls.Button {
                id: absoluteZoomResetCtrl
                text: i18n("Reset To Default")
                onClicked: kcm.resetCrtlToDefault("zoom_absolute")
            }
        }
    }
}

