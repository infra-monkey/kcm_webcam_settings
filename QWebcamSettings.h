/**
 * SPDX-FileCopyrightText: Year Author <author@domanin.com>
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#pragma once

#include "VideoDevice.h"
#include <KQuickAddons/ConfigModule>
#include <libv4l2.h>
#include <linux/videodev2.h>
#include <dirent.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/media.h>
#include <string>
#include <QStringList>

using dev_vec = std::vector<std::string>;
using dev_map = std::map<std::string, std::string>;

class QWebcamSettings : public KQuickAddons::ConfigModule
{
    Q_OBJECT
    

public:
    QWebcamSettings(QObject *parent, const QVariantList &args);
    virtual ~QWebcamSettings() override = default;
    Q_INVOKABLE QStringList getDeviceList();
    Q_INVOKABLE void populateDeviceList(VideoDeviceList);

private:
    VideoDeviceList m_device_list;
    QStringList m_devname_list;
};
