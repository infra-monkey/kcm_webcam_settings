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
                                kcm.setDeviceIndex(cameraList.currentIndex)
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
                        wrapMode: Text.WordWrap
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
                        wrapMode: Text.WordWrap
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
                        wrapMode: Text.WordWrap
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
                        wrapMode: Text.WordWrap
                        id: deviceInfoModelId
                        text: kcm.device_info_modelid
                        color: Kirigami.Theme.textColor
                    }
                }
            }
        }
        Kirigami.FormLayout {
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
                //Layout.fillWidth: true
                //Layout.maximumWidth: Kirigami.Units.gridUnit * 16
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
                    implicitHeight: 33
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
                //Layout.fillWidth: true
                //Layout.maximumWidth: Kirigami.Units.gridUnit * 16
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
                    implicitHeight: 33
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
                //Layout.fillWidth: true
                //Layout.maximumWidth: Kirigami.Units.gridUnit * 16
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
                    implicitHeight: 33
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
                //Layout.fillWidth: true
                //Layout.maximumWidth: Kirigami.Units.gridUnit * 16
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
                    implicitHeight: 33
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
                //Layout.fillWidth: true
                //Layout.maximumWidth: Kirigami.Units.gridUnit * 16
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
                    implicitHeight: 33
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

