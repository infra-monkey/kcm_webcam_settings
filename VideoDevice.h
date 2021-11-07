#include <QString>
#include <QStringList>
#include <list>

class VideoDevice {
public:
    VideoDevice();
    virtual ~VideoDevice();
    void setVideoDeviceName(QString);
    QString getVideoDeviceName();
    void setVideoDeviceBusInfo(QString);
    QString getVideoDeviceBusInfo();
    void setVideoDevicePath(QString);
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
    void addVideoDevice(QString,QString,QString);
    void removeVideoDevice(QString);
    void printVideoDeviceInfo();
    QStringList getDeviceNameList();
    VideoDevice getDeviceFromIndex(int);
private:
    std::list<VideoDevice> m_device_list;
    QStringList m_devname_list;
};
