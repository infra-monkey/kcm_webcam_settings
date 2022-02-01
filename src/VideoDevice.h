#ifndef VIDEODEVICE_H
#define VIDEODEVICE_H

#include <QString>
#include <QStringList>
#include "helpers.h"
#include <unistd.h>

class VideoDevice {
public:
    VideoDevice();
    VideoDevice(QString,QString,QString,QString);
    virtual ~VideoDevice();
    void setVideoDeviceName(QString);
    QString getVideoDeviceName(){return m_device_name;};
    void setVideoDeviceVendorId(QString);
    QString getVideoDeviceVendorId(){return m_device_vendor_id;};
    void setVideoDeviceModelId(QString);
    QString getVideoDeviceModelId(){return m_device_model_id;};
    void setVideoDevicePath(QString);
    QString getVideoDevicePath(){return m_device_path;};
    void initializeCtrls();
    void initializeCtrl(const QString);
    void initializeFormats();
    QStringList getFormatList(){return m_format_list;};
    void setFormatIndex(int);
    int getFormatIndex(){return m_current_format_index;};
    bool setBrightness(double);
    double getBrightness(){return m_ctrl_brightness["value"];};
    double getBrightnessMin(){return m_ctrl_brightness["min"];};
    double getBrightnessMax(){return m_ctrl_brightness["max"];};
    double getBrightnessStep(){return m_ctrl_brightness["step"];};
    bool getBrightnessVisible(){return m_ctrl_brightness_visible;};
    bool setContrast(double);
    double getContrast(){return m_ctrl_contrast["value"];};
    double getContrastMin(){return m_ctrl_contrast["min"];};
    double getContrastMax(){return m_ctrl_contrast["max"];};
    double getContrastStep(){return m_ctrl_contrast["step"];};
    bool getContrastVisible(){return m_ctrl_contrast_visible;};
    bool setSharpness(double);
    double getSharpness(){return m_ctrl_sharpness["value"];};
    double getSharpnessMin(){return m_ctrl_sharpness["min"];};
    double getSharpnessMax(){return m_ctrl_sharpness["max"];};
    double getSharpnessStep(){return m_ctrl_sharpness["step"];};
    bool getSharpnessVisible(){return m_ctrl_sharpness_visible;};
    bool setSaturation(double);
    double getSaturation(){return m_ctrl_saturation["value"];};
    double getSaturationMin(){return m_ctrl_saturation["min"];};
    double getSaturationMax(){return m_ctrl_saturation["max"];};
    double getSaturationStep(){return m_ctrl_saturation["step"];};
    bool getSaturationVisible(){return m_ctrl_saturation_visible;};
    bool setAbsoluteZoom(double);
    double getAbsoluteZoom(){return m_ctrl_zoom_absolute["value"];};
    double getAbsoluteZoomMin(){return m_ctrl_zoom_absolute["min"];};
    double getAbsoluteZoomMax(){return m_ctrl_zoom_absolute["max"];};
    double getAbsoluteZoomStep(){return m_ctrl_zoom_absolute["step"];};
    bool getAbsoluteZoomVisible(){return m_ctrl_zoom_absolute_visible;};
    double getCtrlDefaultValue(QString);
    bool resetCrtlToDefault(QString);
    // void applyResolution();
    bool resetToDefault();
    int getCurrentFormatWidth(){return QString(m_current_fmt.at(1)).toInt();};
    int getCurrentFormatHeight(){return QString(m_current_fmt.at(2)).toInt();};
    QString getCurrentFormatName(){return m_current_fmt.at(0);};
    // QString getUdevRule();
private:
    QString m_device_name;
    QString m_device_vendor_id;
    QString m_device_model_id;
    QString m_device_path;
    QStringList m_ctrl_list = {"brightness","contrast","sharpness","saturation","zoom_absolute"};
    QMap<QString, double> m_ctrl_brightness;
    bool m_ctrl_brightness_visible;
    QMap<QString, double> m_ctrl_contrast;
    bool m_ctrl_contrast_visible;
    QMap<QString, double> m_ctrl_sharpness;
    bool m_ctrl_sharpness_visible;
    QMap<QString, double> m_ctrl_saturation;
    bool m_ctrl_saturation_visible;
    QMap<QString, double> m_ctrl_zoom_absolute;
    bool m_ctrl_zoom_absolute_visible;

    QList<QStringList> m_device_formats;
    QString m_current_fmt;
    QStringList m_format_list;
    int m_current_format_index = 0;
};

#endif
