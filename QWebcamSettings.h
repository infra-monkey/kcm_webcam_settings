/**
 * SPDX-FileCopyrightText: Year Author <author@domanin.com>
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#pragma once

#include "VideoDevice.h"
#include <KQuickAddons/ConfigModule>
//#include <libv4l2.h>
//#include <linux/videodev2.h>
#include <dirent.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/media.h>
#include <string>
#include <QString>
#include <QStringList>
#include <fstream>
#include <iostream>
#include <sstream>

class QWebcamSettings : public KQuickAddons::ConfigModule
{
    Q_OBJECT
    Q_PROPERTY(QStringList device_list READ getDeviceList)
    Q_PROPERTY(int deviceIndex READ getDeviceIndex WRITE setDeviceIndex NOTIFY deviceIndexChanged)

public:
    QWebcamSettings(QObject *parent, const QVariantList &args);
    virtual ~QWebcamSettings() override = default;
    Q_INVOKABLE QStringList getDeviceList();
    Q_INVOKABLE void populateDeviceList(VideoDeviceList);
    Q_INVOKABLE int getDeviceIndex();
    Q_INVOKABLE void setDeviceIndex(int);
    Q_SIGNAL void deviceIndexChanged(int);

private:
    //cv4l_fd *m_fd;
    VideoDeviceList m_device_list;
    VideoDevice m_current_device;
    QStringList m_devname_list;
    int m_device_index;
};
