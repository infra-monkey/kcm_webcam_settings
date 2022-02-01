#ifndef VIDEODEVICECAPFORMAT_H
#define VIDEODEVICECAPFORMAT_H

#include <list>
#include <string>
#include <QString>
#include <QStringList>
#include "VideoDeviceResolution.h"

class VideoDeviceCapFormat {
public:
    VideoDeviceCapFormat();
    VideoDeviceCapFormat(QString,QString);
    virtual ~VideoDeviceCapFormat();
    QString getFormatName(){return m_format_name;};
    QStringList getResList(){return m_resolution_list;};
    std::list<VideoDeviceResolution>  getResolutionObjectList(){return m_resolutions;};
    void setResolutionIndex(int);
    int getResolutionIndex(){return m_current_resolution_index;};
    void initializeResolutions();
    void addResolution(QString,bool);
    void applyResolution();
    VideoDeviceResolution getCurrentResolution(){return m_current_resolution;};
    int getCurrentFormatWidth(){ return m_current_resolution.getWidth();};
    int getCurrentFormatHeight(){ return m_current_resolution.getHeight();};
private:
    int m_current_resolution_index = 0;
    QString m_format_name;
    QString m_device_path;
    QStringList m_resolution_list;
    std::list<VideoDeviceResolution> m_resolutions;
    VideoDeviceResolution m_current_resolution;
};

#endif
