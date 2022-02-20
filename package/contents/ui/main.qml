/**
 * SPDX-FileCopyrightText: Year Author <author@domanin.com>
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

import QtQuick 2.15 as Basic
import QtQuick.Controls 2.15 as Controls
import QtMultimedia 5.8
import QtQuick.Layouts 1.15
import QtQml.Models 2.15

import org.kde.kirigami 2.10 as Kirigami
import org.kde.kcm 1.2 as KCM


KCM.SimpleKCM {
    id: root
    title: i18n("Configure Webcam")
    implicitWidth: Kirigami.Units.gridUnit * 38
    implicitHeight: Kirigami.Units.gridUnit * 35
    Kirigami.Theme.colorSet: Kirigami.Theme.Window
    
    ColumnLayout {
        id: mainItem
        Layout.fillWidth: true
        RowLayout {
            ColumnLayout {
                Layout.margins: 20
                Layout.alignment: Qt.AlignTop
                Kirigami.Heading {
                    Layout.fillWidth: true
                    level: 2
                    text: "Device Selection"
                    color: Kirigami.Theme.textColor
                }

                Kirigami.Separator {
                    Layout.fillWidth: true
                    visible: true
                }
                Basic.ListView {
                    visible: true
                    property var customHighlightedTextColor
                    property var customHighlightColor
                    id: cameraList
                    height: Kirigami.Units.gridUnit * 4
                    model: kcm.device_list_model
                    customHighlightedTextColor: (cameraList.count > 1) ? Kirigami.Theme.highlightedTextColor : Kirigami.Theme.textColor
                    customHighlightColor: (cameraList.count > 1) ? Kirigami.Theme.highlightColor : Kirigami.Theme.backgroundColor
                    highlight: Basic.Rectangle { color: cameraList.customHighlightColor; }
                    highlightFollowsCurrentItem: true
                    delegate: Basic.Text {
                        Kirigami.Theme.inherit: true
                        text: display
                        color: Basic.ListView.isCurrentItem ? cameraList.customHighlightedTextColor : Kirigami.Theme.textColor
                        Basic.MouseArea {
                            anchors.fill: parent
                            onClicked: {
                                cameraList.currentIndex = index
                                //camera.stop()
                                kcm.setDeviceIndex(cameraList.currentIndex)
                                camera.deviceId = kcm.device_info_path
                                formatList.currentIndex = kcm.formatIndex
                                //camera.start()
                            }
                        }
                    }
                }
            }
            ColumnLayout {
                Layout.margins: 20
                Layout.alignment: Qt.AlignTop
                Kirigami.Heading {
                    Layout.fillWidth: true
                    level: 2
                    text: "Device Information"
                    color: Kirigami.Theme.textColor
                }
                Kirigami.Separator {
                    Layout.fillWidth: true
                    visible: true
                }

                RowLayout {
                    Kirigami.Heading {
                        Layout.fillWidth: true
                        level: 3
                        text: "Device Name"
                        color: Kirigami.Theme.textColor
                    }

                    Controls.Label {
                        Layout.fillWidth: true
                        horizontalAlignment: Basic.Text.AlignRight
                        wrapMode: Basic.Text.WordWrap
                        id: deviceInfoName
                        text: kcm.device_info_name
                        color: Kirigami.Theme.textColor
                    }
                }
                RowLayout {
                    Kirigami.Heading {
                        Layout.fillWidth: true
                        Layout.alignment: Qt.AlignLeft
                        level: 3
                        text: "Device Path"
                        color: Kirigami.Theme.textColor
                    }
                    Controls.Label {
                        Layout.fillWidth: true
                        horizontalAlignment: Basic.Text.AlignRight
                        wrapMode: Basic.Text.WordWrap
                        id: deviceInfoPath
                        text: kcm.device_info_path
                        color: Kirigami.Theme.textColor
                    }
                }
                RowLayout {
                    Kirigami.Heading {
                        Layout.fillWidth: true
                        Layout.alignment: Qt.AlignLeft
                        level: 3
                        text: "Device Vendor Id"
                        color: Kirigami.Theme.textColor
                    }
                    Controls.Label {
                        Layout.fillWidth: true
                        horizontalAlignment: Basic.Text.AlignRight
                        wrapMode: Basic.Text.WordWrap
                        id: deviceInfoVendorId
                        text: kcm.device_info_vendorid
                        color: Kirigami.Theme.textColor
                    }
                }
                RowLayout {
                    Kirigami.Heading {
                        Layout.fillWidth: true
                        Layout.alignment: Qt.AlignLeft
                        level: 3
                        text: "Device Model Id"
                        color: Kirigami.Theme.textColor
                    }
                    Controls.Label {
                        Layout.fillWidth: true
                        horizontalAlignment: Basic.Text.AlignRight
                        wrapMode: Basic.Text.WordWrap
                        id: deviceInfoModelId
                        text: kcm.device_info_modelid
                        color: Kirigami.Theme.textColor
                    }
                }
            }
        }
        Kirigami.FormLayout {
            id: formId
            Controls.CheckBox {
                visible: true
                implicitWidth: 217
                implicitHeight: 45
                id: previewCheckbox
                checked: false
                text: i18n("Preview webcam")
                onToggled: {
                    if (checked) {
                        camera.start();
                    } else {
                        camera.stop();
                    }
                }
            }
            Basic.Item {
                id: previewSpace
                visible: previewCheckbox.checked
                implicitWidth: 320
                implicitHeight: 180
                VideoOutput {
                    id: previewOutput
                    visible: previewSpace.visible
                    source: camera
                    anchors.fill: parent
                    Camera {
                        id: camera
                        deviceId: kcm.device_info_path
                        digitalZoom: kcm.digital_zoom_prev
                        Basic.Component.onCompleted: {
                            camera.stop();
                        }
                    }
                }
            }

            Controls.ComboBox {
                id: formatList
                Layout.fillWidth: true
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
            RowLayout {
                id: brightnessCtrl
                visible: kcm.brightness_visible
                Layout.fillWidth: true
                Kirigami.FormData.label: i18n("Brightness:")
                Controls.Slider {
                    id: brightnessSlide
                    from: -1.0
                    to: 1.0
                    value: kcm.brightness
                    onMoved: kcm.brightness = value
                    live: true
                }
                Controls.SpinBox {
                    //implicitWidth: 100
                    //implicitHeight: 33
                    id: brightnessSpinbox
                    from: -100
                    value: kcm.brightness_spin
                    to: 100
                    stepSize: 5
                    property int decimals: 2
                    property real realValue: value / 100
                    validator: Basic.DoubleValidator {
                        bottom: Math.min(brightnessSpinbox.from, brightnessSpinbox.to)
                        top:  Math.max(brightnessSpinbox.from, brightnessSpinbox.to)
                    }
                    textFromValue: function(value, locale) {
                        return Number(value / 100).toLocaleString(locale, 'f', brightnessSpinbox.decimals)
                    }
                    valueFromText: function(text, locale) {
                        return Number.fromLocaleString(locale, text) * 100
                    }
                    onValueModified: kcm.brightness = realValue
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
                Kirigami.FormData.label: i18n("Contrast:")
                Controls.Slider {
                    id: contrastSlide
                    from: -1.0
                    to: 1.0
                    value: kcm.contrast
                    onMoved: kcm.contrast = value
                    live: true
                }
                Controls.SpinBox {
                    //implicitWidth: 100
                    //implicitHeight: 33
                    id: contrastSpinbox
                    from: -100
                    value: kcm.contrast_spin
                    to: 100
                    stepSize: 5
                    property int decimals: 2
                    property real realValue: value / 100
                    validator: Basic.DoubleValidator {
                        bottom: Math.min(contrastSpinbox.from, contrastSpinbox.to)
                        top:  Math.max(contrastSpinbox.from, contrastSpinbox.to)
                    }
                    textFromValue: function(value, locale) {
                        return Number(value / 100).toLocaleString(locale, 'f', contrastSpinbox.decimals)
                    }
                    valueFromText: function(text, locale) {
                        return Number.fromLocaleString(locale, text) * 100
                    }
                    onValueModified: kcm.contrast = realValue
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
                //Layout.fillWidth: true
                //Layout.maximumWidth: Kirigami.Units.gridUnit * 16
                Kirigami.FormData.label: i18n("Sharpness:")
                Controls.Slider {
                    id: sharpnessSlide
                    from: -1.0
                    to: 1.0
                    value: kcm.sharpness
                    onMoved: kcm.sharpness = value
                    live: true
                }
                Controls.SpinBox {
                    //implicitWidth: 100
                    //implicitHeight: 33
                    id: sharpnessSpinbox
                    from: -100
                    value: kcm.sharpness_spin
                    to: 100
                    stepSize: 5
                    property int decimals: 2
                    property real realValue: value / 100
                    validator: Basic.DoubleValidator {
                        bottom: Math.min(sharpnessSpinbox.from, sharpnessSpinbox.to)
                        top:  Math.max(sharpnessSpinbox.from, sharpnessSpinbox.to)
                    }
                    textFromValue: function(value, locale) {
                        return Number(value / 100).toLocaleString(locale, 'f', sharpnessSpinbox.decimals)
                    }
                    valueFromText: function(text, locale) {
                        return Number.fromLocaleString(locale, text) * 100
                    }
                    onValueModified: kcm.sharpness = realValue
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
                //Layout.fillWidth: true
                //Layout.maximumWidth: Kirigami.Units.gridUnit * 16
                Kirigami.FormData.label: i18n("Saturation:")
                Controls.Slider {
                    id: saturationSlide
                    from: -1.0
                    to: 1.0
                    value: kcm.saturation
                    onMoved: kcm.saturation = value
                    live: true
                }
                Controls.SpinBox {
                    //implicitWidth: 100
                    //implicitHeight: 33
                    id: saturationSpinbox
                    from: -100
                    value: kcm.saturation_spin
                    to: 100
                    stepSize: 5
                    property int decimals: 2
                    property real realValue: value / 100
                    validator: Basic.DoubleValidator {
                        bottom: Math.min(saturationSpinbox.from, saturationSpinbox.to)
                        top:  Math.max(saturationSpinbox.from, saturationSpinbox.to)
                    }
                    textFromValue: function(value, locale) {
                        return Number(value / 100).toLocaleString(locale, 'f', saturationSpinbox.decimals)
                    }
                    valueFromText: function(text, locale) {
                        return Number.fromLocaleString(locale, text) * 100
                    }
                    onValueModified: kcm.saturation = realValue
                }
                Controls.Button {
                    id: saturationResetCtrl
                    text: i18n("Reset To Default")
                    onClicked: kcm.resetCrtlToDefault("saturation")
                }
            }
            RowLayout {
                id: opticalZoomCtrl
                visible: kcm.optical_zoom_visible
                //Layout.fillWidth: true
                //Layout.maximumWidth: Kirigami.Units.gridUnit * 16
                Kirigami.FormData.label: i18n("Optical Zoom:")
                Controls.Slider {
                    id: opticalZoomSlide
                    from: 0
                    to: kcm.optical_zoom_max
                    stepSize: 1
                    value: kcm.optical_zoom
                    onMoved: kcm.optical_zoom = value
                    live: true
                }
                Controls.SpinBox {
                    //implicitWidth: 100
                    //implicitHeight: 33
                    id: opticalZoomSpinbox
                    from: 0
                    value: kcm.optical_zoom
                    to: kcm.optical_zoom_max
                    //stepSize: 5
                    property int decimals: 2
                    validator: Basic.DoubleValidator {
                        bottom: Math.min(opticalZoomSpinbox.from, opticalZoomSpinbox.to)
                        top:  Math.max(opticalZoomSpinbox.from, opticalZoomSpinbox.to)
                    }
                    textFromValue: function(value, locale) {
                        return Number(value).toLocaleString(locale, 'f', opticalZoomSpinbox.decimals)
                    }
                    valueFromText: function(text, locale) {
                        return Number.fromLocaleString(locale, text)
                    }
                    onValueModified: kcm.optical_zoom = value
                }
                Controls.Button {
                    id: opticalZoomResetCtrl
                    text: i18n("Reset To Default")
                    onClicked: kcm.resetCrtlToDefault("optical_absolute")
                }
            }
            RowLayout {
                id: digitalZoomCtrl
                visible: kcm.digital_zoom_visible
                //Layout.fillWidth: true
                //Layout.maximumWidth: Kirigami.Units.gridUnit * 16
                Kirigami.FormData.label: i18n("Digital Zoom:")
                Controls.Slider {
                    id: digitalZoomSlide
                    from: 0
                    to: kcm.digital_zoom_max
                    //stepSize: 1
                    value: kcm.digital_zoom
                    onMoved: kcm.digital_zoom = value
                    live: true
                }
                Controls.SpinBox {
                    //implicitWidth: 100
                    //implicitHeight: 33
                    id: digitalZoomSpinbox
                    from: 0
                    value: kcm.digital_zoom
                    to: kcm.digital_zoom_max
                    //stepSize: 5
                    property int decimals: 2
                    validator: Basic.DoubleValidator {
                        bottom: Math.min(digitalZoomSpinbox.from, digitalZoomSpinbox.to)
                        top:  Math.max(digitalZoomSpinbox.from, digitalZoomSpinbox.to)
                    }
                    textFromValue: function(value, locale) {
                        return Number(value).toLocaleString(locale, 'f', digitalZoomSpinbox.decimals)
                    }
                    valueFromText: function(text, locale) {
                        return Number.fromLocaleString(locale, text)
                    }
                    onValueModified: kcm.digital_zoom = value
                }
                Controls.Button {
                    id: digitalZoomResetCtrl
                    text: i18n("Reset To Default")
                    onClicked: kcm.resetCrtlToDefault("digital_absolute")
                }
            }
            RowLayout {
                id: focusCtrl
                visible: kcm.auto_focus_visible
                //Layout.fillWidth: true
                //Layout.maximumWidth: Kirigami.Units.gridUnit * 16
                Kirigami.FormData.label: i18n("Auto Focus:")
                Controls.CheckBox {
                    implicitWidth: 217
                    implicitHeight: 45
                    id: autoFocusCheckbox
                    checked: kcm.auto_focus
                    onClicked: kcm.setAutoFocus(checked)
                }
                Basic.Rectangle {
                    implicitWidth: 100
                    implicitHeight: 33
                    id: focusSpinboxFiller
                    visible: true
                    color: Kirigami.Theme.backgroundColor
                }
                Controls.Button {
                    id: autoFocusResetCtrl
                    text: i18n("Reset To Default")
                    onClicked: kcm.resetCrtlToDefault("focus_automatic_continuous")
                }
            }
            RowLayout {
                id: absoluteFocusCtrl
                visible: kcm.absolute_focus_visible
                //Layout.fillWidth: true
                //Layout.maximumWidth: Kirigami.Units.gridUnit * 16
                Kirigami.FormData.label: i18n("Absolute Focus:")
                Controls.Slider {
                    id: absoluteFocusSlide
                    from: kcm.absolute_focus_min
                    to: kcm.absolute_focus_max
                    stepSize: kcm.absolute_focus_step
                    value: kcm.absolute_focus
                    onMoved: kcm.absolute_focus = value
                    live: true
                }
                Controls.SpinBox {
                    implicitWidth: 100
                    implicitHeight: 33
                    id: absoluteFocusSpinbox
                    from: kcm.absolute_focus_min
                    to: kcm.absolute_focus_max
                    stepSize: kcm.absolute_focus_step
                    value: kcm.absolute_focus
                    onValueModified: kcm.absolute_focus = value
                }
                Controls.Button {
                    id: absoluteFocusResetCtrl
                    text: i18n("Reset To Default")
                    onClicked: kcm.resetCrtlToDefault("focus_absolute")
                }
            }
        }
    }
}

