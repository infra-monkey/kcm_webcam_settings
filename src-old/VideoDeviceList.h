#ifndef VIDEODEVICELIST_H
#define VIDEODEVICELIST_H

#include <QString>
#include <QStringList>
#include <list>
#include "VideoDevice.h"

class VideoDeviceList {
public:
    VideoDeviceList();
    virtual ~VideoDeviceList();
    void addVideoDevice(QString,QString);
    QStringList getDeviceNameList() {return m_devname_list;};
    VideoDevice getDeviceFromIndex(int);
    QStringList getUdevRules();
private:
    std::list<VideoDevice> m_device_list;
    QStringList m_devname_list;
    VideoDevice m_device;
};

#endif
