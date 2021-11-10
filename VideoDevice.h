#ifndef VIDEODEVICE_H
#define VIDEODEVICE_H

#include <QString>
#include <QStringList>
#include "VideoDeviceCtrl.h"

class VideoDevice {
public:
    VideoDevice();
    virtual ~VideoDevice();
    void setVideoDeviceName(QString devname){m_device_name = QString(devname);};
    QString getVideoDeviceName(){return m_device_name;};
    void setVideoDeviceBusInfo(QString businfo){m_device_bus_info = QString(businfo);};
    QString getVideoDeviceBusInfo(){return m_device_bus_info;};
    void setVideoDevicePath(QString);
    QStringList getVideoDevicePaths(){return m_device_paths;};
    QString getVideoDevicePath(){return m_device_path;};
    void initializeCtrls();
    void printVideoDeviceInfo();
    void setAbsoluteZoom(double);
    double getAbsoluteZoom();
    double getAbsoluteZoomMin();
    double getAbsoluteZoomMax();
    double getAbsoluteZoomStep();
private:
    QString m_device_name;
    QString m_device_bus_info;
    QStringList m_device_paths;
    QString m_device_path;
    VideoDeviceCtrl m_ctrl_brightness;
    VideoDeviceCtrl m_ctrl_contrast;
    VideoDeviceCtrl m_ctrl_sharpness;
    VideoDeviceCtrl m_ctrl_saturation;
    VideoDeviceCtrl m_ctrl_zoom_absolute;
    double m_zoom_absolute;
    double m_zoom_absolute_min;
    double m_zoom_absolute_max;
    double m_zoom_absolute_step;
};

#endif
