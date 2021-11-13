#ifndef VIDEODEVICERESOLUTION_H
#define VIDEODEVICERESOLUTION_H

#include <QString>

class VideoDeviceResolution {
public:
    VideoDeviceResolution();
    VideoDeviceResolution(QString, QString, QString);
    virtual ~VideoDeviceResolution();
    QString getLabel(){return m_res_label;};
    int getHeight(){return m_height;};
    int getWidth(){return m_width;};
private:
    QString m_res_label;
    QString m_format;
    int m_height;
    int m_width;
};

#endif
