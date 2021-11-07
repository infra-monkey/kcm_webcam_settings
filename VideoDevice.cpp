#include "VideoDevice.h"

VideoDevice::VideoDevice() {}
VideoDevice::~VideoDevice() {}
void VideoDevice::setVideoDeviceName(QString devname) {
    m_device_name = QString(devname);
}
QString VideoDevice::getVideoDeviceName() {
    return m_device_name;
}

void VideoDevice::setVideoDeviceBusInfo(QString businfo) {
    m_device_bus_info = QString(businfo);
}
QString VideoDevice::getVideoDeviceBusInfo() {
    return m_device_bus_info;
}

void VideoDevice::setVideoDevicePath(QString path) {
    bool path_exists = false;
    for (QString & devpath : m_device_paths)
    {
        if ( devpath == path ) {
            path_exists = true;
        }
    }
    if (!path_exists){
        QString devpath = QString(path);
        m_device_paths.append(devpath);
    }
}

QStringList VideoDevice::getVideoDevicePath() {
    return m_device_paths;
}

void VideoDevice::printVideoDeviceInfo() {
    printf("Name : %s\n", m_device_name.toStdString().c_str());
    printf("Bus info : %s\n", m_device_bus_info.toStdString().c_str());
    printf("Paths :\n");
    for (QString & devpath : m_device_paths)
    {
        printf("\t%s\n",devpath.toStdString().c_str());
    }
}

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
        m_device_list.push_back(device);
        m_devname_list.append(devname);
    }
}

void VideoDeviceList::removeVideoDevice(QString businfo) {
    
}

void VideoDeviceList::printVideoDeviceInfo() {
    for (VideoDevice & dev : m_device_list)
    {
        dev.printVideoDeviceInfo();
    }
}

QStringList VideoDeviceList::getDeviceNameList(){
	return m_devname_list;
}
