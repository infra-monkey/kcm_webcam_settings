#include "VideoDeviceList.h"
#include "helpers.h"

VideoDeviceList::VideoDeviceList() {
}
VideoDeviceList::~VideoDeviceList() {}
void VideoDeviceList::addVideoDevice(QString devname,QString businfo,QString devpath) {
    bool device_exists = false;
    for (VideoDevice & dev : m_device_list)
    {
        if (dev.getVideoDeviceBusInfo().toStdString() == businfo.toStdString()) {
            dev.setVideoDeviceBusInfo(businfo);
            dev.setVideoDeviceName(devname);
            dev.setVideoDevicePath(devpath);
            device_exists = true;
            break;
        }
    }

    if (!device_exists) {
        VideoDevice device = VideoDevice();
        device.setVideoDeviceBusInfo(businfo);
        device.setVideoDeviceName(devname);
        device.setVideoDevicePath(devpath);
        device.initializeCtrls();
        m_device_list.push_back(device);
        m_devname_list.append(devname);
    }
}

void VideoDeviceList::printVideoDeviceInfo() {
    for (VideoDevice & dev : m_device_list)
    {
        dev.printVideoDeviceInfo();
    }
}

VideoDevice VideoDeviceList::getDeviceFromIndex(int index) {
    int i = 0;
    for (VideoDevice & dev : m_device_list)
    {
        if (i == index) {
            m_device = dev;
            break;
        }
        i++;
    }
    printf("Return device %s\n",m_device.getVideoDeviceName().toStdString().c_str());
    return m_device;
}   