#include <QString>
#include <QStringList>
#include <list>

class VideoDevice {
public:
    VideoDevice();
    virtual ~VideoDevice();
    void setVideoDeviceName(QString devname);
    QString getVideoDeviceName();
    void setVideoDeviceBusInfo(QString businfo);
    QString getVideoDeviceBusInfo();
    void setVideoDevicePath(QString path);
    QStringList getVideoDevicePath();
    void printVideoDeviceInfo();
private:
    QString m_device_name;
    QString m_device_bus_info;
    QStringList m_device_paths;
};

class VideoDeviceList {
public:
    VideoDeviceList();
    virtual ~VideoDeviceList();
    void addVideoDevice(QString devname,QString businfo,QString devpath);
    void removeVideoDevice(QString businfo);
    void printVideoDeviceInfo();
    QStringList getDeviceNameList();
private:
    std::list<VideoDevice> m_device_list;
    QStringList m_devname_list;
};