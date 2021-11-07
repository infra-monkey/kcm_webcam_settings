/**
 * SPDX-FileCopyrightText: Year Author <author@domanin.com>
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

import QtQuick 2.12
import QtQuick.Controls 2.12 as Controls
import QtMultimedia 5.8

import org.kde.kirigami 2.10 as Kirigami
import org.kde.kcm 1.2


SimpleKCM {
    title: i18n("Configure Webcam")

    Kirigami.Theme.colorSet: Kirigami.Theme.Window
    Kirigami.FormLayout {
        id: mainItem
        Controls.ComboBox {
            id: deviceList
            Kirigami.FormData.label: "Webcam List"
            editable: false
            model: kcm.getDeviceList()
        }
    }
}
