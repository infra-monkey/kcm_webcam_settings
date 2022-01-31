#include "VideoDeviceList.h"
#include "helpers.h"

VideoDeviceList::VideoDeviceList() {
}
VideoDeviceList::~VideoDeviceList() {}
void VideoDeviceList::addVideoDevice(QString devpath, QString devname) {
    std::string cmd;
    bool device_exists = false;
    QString vendorid,modelid,serial;

    cmd = std::string("udevadm info --query=all --name=" + devpath.toStdString());
    
    QStringList output = QString::fromStdString(exec_cmd(cmd)).split(QLatin1Char('\n'));
    for (QString & line : output){
        if (line.length() == 0){break;}
        QString key = QString::fromStdString(get_str_right_of_substr(get_str_left_of_substr(line.toStdString(),std::string("=")),std::string("E: "))).simplified();
        if (line.contains(QString::fromStdString("ID_SERIAL="))){
            serial = QString::fromStdString(get_str_right_of_substr(line.toStdString(),std::string("=")));
            qCDebug(webcam_settings_kcm) << "Found ID_SERIAL=" << serial;
        }
        if (line.contains(QString::fromStdString("ID_VENDOR_ID="))){
            vendorid = QString::fromStdString(get_str_right_of_substr(line.toStdString(),std::string("=")));
            qCDebug(webcam_settings_kcm) << "Found ID_VENDOR_ID=" << vendorid;
        }
        if (line.contains(QString::fromStdString("ID_MODEL_ID="))){
            modelid = QString::fromStdString(get_str_right_of_substr(line.toStdString(),std::string("=")));
            qCDebug(webcam_settings_kcm) << "Found ID_MODEL_ID=" << modelid;
        }
    }

    if (!device_exists && devpath.contains(QString::fromStdString("/dev/video"))){
        VideoDevice device = VideoDevice();
        device.setVideoDeviceName(devname);
        device.setVideoDevicePath(devpath);
        device.setVideoDeviceSerialId(serial);
        device.setVideoDeviceVendorId(vendorid);
        device.setVideoDeviceModelId(modelid);
        device.initializeFormats();
        // device.initializeResolutions();
        device.initializeCtrls();
        m_device_list.push_back(device);
        m_devname_list.append(devname);
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
    return m_device;
}

QString VideoDeviceList::getUdevRules(){
    QString udevrule = QString::fromStdString("this is a test");
    return udevrule;
}
