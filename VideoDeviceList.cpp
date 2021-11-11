#include "VideoDeviceList.h"
#include "helpers.h"

VideoDeviceList::VideoDeviceList() {
}
VideoDeviceList::~VideoDeviceList() {}
void VideoDeviceList::addVideoDevice(QString devpath) {
    bool device_exists = false;
    QString businfo;
    QString devname;

    std::string cmd1 = std::string("v4l2-ctl -d " + devpath.toStdString() + " --info | grep Model");
    devname = QString::fromStdString(get_str_right_of_substr(exec_cmd(cmd1),std::string(":"))).simplified();
    printf(" dev name : -%s-\n",devname.toStdString().c_str());
    std::string cmd2 = std::string("v4l2-ctl -d " + devpath.toStdString() + " --info | grep \"Bus info\" | sort -u");
    businfo = QString::fromStdString(get_str_right_of_substr(exec_cmd(cmd2),std::string(":"))).simplified();
    for (VideoDevice & dev : m_device_list)
    {
        if (dev.getVideoDeviceBusInfo().toStdString() == businfo.toStdString()) {
        //     dev.setVideoDeviceBusInfo(businfo);
        //     dev.setVideoDeviceName(devname);
            dev.setVideoDevicePath(devpath);
            device_exists = true;
            break;
        }
    }

    if (!device_exists && devpath.contains(QString::fromStdString("/dev/video"))){
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