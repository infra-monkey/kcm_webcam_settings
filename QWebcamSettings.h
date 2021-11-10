/**
 * SPDX-FileCopyrightText: Year Author <author@domanin.com>
 * SPDX-License-Identifier: GPL-2.0-or-later
 */
#ifndef QWEBCAMSETTINGS_H
#define QWEBCAMSETTINGS_H

#include "VideoDevice.h"
#include "VideoDeviceList.h"
#include <KQuickAddons/ConfigModule>
#include <dirent.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/media.h>
#include <QString>
#include <QStringList>


class QWebcamSettings : public KQuickAddons::ConfigModule
{
    Q_OBJECT
    Q_PROPERTY(QStringList device_list READ getDeviceList NOTIFY deviceIndexChanged)
    Q_PROPERTY(int deviceIndex READ getDeviceIndex WRITE setDeviceIndex NOTIFY deviceIndexChanged)
    Q_PROPERTY(qreal absolute_zoom READ getAbsoluteZoom WRITE setAbsoluteZoom NOTIFY absoluteZoomChanged)
    Q_PROPERTY(qreal absolute_zoom_min READ getAbsoluteZoomMin NOTIFY deviceIndexChanged)
    Q_PROPERTY(qreal absolute_zoom_max READ getAbsoluteZoomMax NOTIFY deviceIndexChanged)
    Q_PROPERTY(qreal absolute_zoom_step READ getAbsoluteZoomStep NOTIFY deviceIndexChanged)

public:
    QWebcamSettings(QObject *parent, const QVariantList &args);
    virtual ~QWebcamSettings() override = default;
    QStringList getDeviceList();
    void populateDeviceList(VideoDeviceList);
    int getDeviceIndex(){return m_device_index;};
    qreal getAbsoluteZoom() const {return m_absolute_zoom;};
    qreal getAbsoluteZoomMin() const {return m_absolute_zoom_min;};
    qreal getAbsoluteZoomMax() const {return m_absolute_zoom_max;};
    qreal getAbsoluteZoomStep() const {return m_absolute_zoom_step;};
    Q_INVOKABLE void setDeviceIndex(int);
    void setAbsoluteZoom(double);
Q_SIGNALS:
    void deviceIndexChanged();
    void absoluteZoomChanged();
private:
    VideoDeviceList m_device_list;
    VideoDevice m_current_device;
    QStringList m_devname_list;
    int m_device_index;
    double m_absolute_zoom;
    double m_absolute_zoom_min;
    double m_absolute_zoom_max;
    double m_absolute_zoom_step;
};

#endif
