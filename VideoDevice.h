#ifndef VIDEODEVICE_H
#define VIDEODEVICE_H

#include <QString>
#include <QStringList>
#include "VideoDeviceCtrl.h"
#include "VideoDeviceCapFormat.h"

class VideoDevice {
public:
    VideoDevice();
    virtual ~VideoDevice();
    void setVideoDeviceName(QString);
    QString getVideoDeviceName(){return m_device_name;};
    void setVideoDeviceSerialId(QString);
    QString getVideoDeviceSerialId(){return m_device_serial_id;};
    void setVideoDeviceVendorId(QString);
    QString getVideoDeviceVendorId(){return m_device_vendor_id;};
    void setVideoDeviceModelId(QString);
    QString getVideoDeviceModelId(){return m_device_model_id;};
    void setVideoDevicePath(QString);
    QStringList getVideoDevicePaths(){return m_device_paths;};
    QString getVideoDevicePath(){return m_device_path;};
    void initializeCtrls();
    void initializeFormats();
    QStringList getFormatList(){return m_format_list;};
    QStringList getResolutionList();
    void setFormatIndex(int);
    int getFormatIndex(){return m_current_format_index;};
    void setResolutionIndex(int resindex){m_current_fmt.setResolutionIndex(resindex);};
    int getResolutionIndex(){return m_current_fmt.getResolutionIndex();};
    void setAbsoluteZoom(double);
    void setBrightness(double);
    double getBrightness();
    double getBrightnessMin();
    double getBrightnessMax();
    double getBrightnessStep();
    bool getBrightnessVisible();
    void setContrast(double);
    double getContrast();
    double getContrastMin();
    double getContrastMax();
    double getContrastStep();
    bool getContrastVisible();
    void setSharpness(double);
    double getSharpness();
    double getSharpnessMin();
    double getSharpnessMax();
    double getSharpnessStep();
    bool getSharpnessVisible();
    void setSaturation(double);
    double getSaturation();
    double getSaturationMin();
    double getSaturationMax();
    double getSaturationStep();
    bool getSaturationVisible();
    double getAbsoluteZoom();
    double getAbsoluteZoomMin();
    double getAbsoluteZoomMax();
    double getAbsoluteZoomStep();
    bool getAbsoluteZoomVisible();
    double getCtrlDefaultValue(QString);
private:
    QString m_device_name;
    QString m_device_vendor_id;
    QString m_device_model_id;
    QString m_device_serial_id;
    QStringList m_device_paths;
    std::list<VideoDeviceCapFormat> m_device_formats;
    VideoDeviceCapFormat m_current_fmt;
    QString m_current_resolution;
    QStringList m_format_list;
    int m_current_format_index = 0;
    int m_current_resolution_index = 0;
    QString m_device_path;
    VideoDeviceCtrl m_ctrl_brightness;
    VideoDeviceCtrl m_ctrl_contrast;
    VideoDeviceCtrl m_ctrl_sharpness;
    VideoDeviceCtrl m_ctrl_saturation;
    VideoDeviceCtrl m_ctrl_zoom_absolute;
    double m_brightness;
    double m_brightness_min;
    double m_brightness_max;
    double m_brightness_step;
    bool m_brightness_visible;
    double m_zoom_absolute;
    double m_zoom_absolute_min;
    double m_zoom_absolute_max;
    double m_zoom_absolute_step;
    bool m_absolute_zoom_visible;
    double m_contrast;
    double m_contrast_min;
    double m_contrast_max;
    double m_contrast_step;
    bool m_contrast_visible;
    double m_sharpness;
    double m_sharpness_min;
    double m_sharpness_max;
    double m_sharpness_step;
    bool m_sharpness_visible;
    double m_saturation;
    double m_saturation_min;
    double m_saturation_max;
    double m_saturation_step;
    bool m_saturation_visible;
};

#endif
