#ifndef VIDEODEVICERESOLUTION_H
#define VIDEODEVICERESOLUTION_H

#include <QString>

class VideoDeviceResolution {
public:
    VideoDeviceResolution();
    VideoDeviceResolution(QString, QString, QString);
    virtual ~VideoDeviceResolution();
    QString getLabel(){return m_res_label;};
    QString getRes(){return m_res;};
    QString getFormat(){return m_format;};
    int getHeight(){return m_height;};
    int getWidth(){return m_width;};
private:
    QString m_res_label;
    QString m_res;
    QString m_format;
    int m_height;
    int m_width;
};

#endif
