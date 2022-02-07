#ifndef VIDEODEVICE_H
#define VIDEODEVICE_H

#include <QString>
#include <QStringList>
#include <KConfigGroup>
#include "helpers.h"
#include <unistd.h>

class VideoDevice : public QObject {
public:
    VideoDevice();
    VideoDevice(QString,QString,QString,QString,QString);
    // VideoDevice(KConfigGroup);
    virtual ~VideoDevice();
    QString getVideoDeviceName(){return m_device_name;};
    QString getVideoDeviceVendorId(){return m_device_vendor_id;};
    QString getVideoDeviceModelId(){return m_device_model_id;};
    QString getVideoDeviceSerialId(){return m_device_serial;};
    QString getVideoDevicePath(){return m_device_path;};
    void initializeCtrls();
    void initializeCtrl(const QString);
    void initializeFormats();
    QStringList getFormatList(){return m_format_list;};
    bool setFormatIndex(int);
    int getFormatIndex(){return m_current_format_index;};
    bool setBrightness(double);
    double getBrightness(){return m_ctrl_brightness["value"];};
    double getBrightnessMin(){return m_ctrl_brightness["min"];};
    double getBrightnessMax(){return m_ctrl_brightness["max"];};
    double getBrightnessStep(){return m_ctrl_brightness["step"];};
    double getBrightnessDefault(){return m_ctrl_brightness["default"];};
    bool getBrightnessVisible(){return m_ctrl_brightness_visible;};
    bool setContrast(double);
    double getContrast(){return m_ctrl_contrast["value"];};
    double getContrastMin(){return m_ctrl_contrast["min"];};
    double getContrastMax(){return m_ctrl_contrast["max"];};
    double getContrastStep(){return m_ctrl_contrast["step"];};
    double getContrastDefault(){return m_ctrl_contrast["default"];};
    bool getContrastVisible(){return m_ctrl_contrast_visible;};
    bool setSharpness(double);
    double getSharpness(){return m_ctrl_sharpness["value"];};
    double getSharpnessMin(){return m_ctrl_sharpness["min"];};
    double getSharpnessMax(){return m_ctrl_sharpness["max"];};
    double getSharpnessStep(){return m_ctrl_sharpness["step"];};
    double getSharpnessDefault(){return m_ctrl_sharpness["default"];};
    bool getSharpnessVisible(){return m_ctrl_sharpness_visible;};
    bool setSaturation(double);
    double getSaturation(){return m_ctrl_saturation["value"];};
    double getSaturationMin(){return m_ctrl_saturation["min"];};
    double getSaturationMax(){return m_ctrl_saturation["max"];};
    double getSaturationStep(){return m_ctrl_saturation["step"];};
    double getSaturationDefault(){return m_ctrl_saturation["default"];};
    bool getSaturationVisible(){return m_ctrl_saturation_visible;};
    bool setAbsoluteZoom(double);
    double getAbsoluteZoom(){return m_ctrl_zoom_absolute["value"];};
    double getAbsoluteZoomMin(){return m_ctrl_zoom_absolute["min"];};
    double getAbsoluteZoomMax(){return m_ctrl_zoom_absolute["max"];};
    double getAbsoluteZoomStep(){return m_ctrl_zoom_absolute["step"];};
    double getAbsoluteZoomDefault(){return m_ctrl_zoom_absolute["default"];};
    bool getAbsoluteZoomVisible(){return m_ctrl_zoom_absolute_visible;};
    bool setAutoFocus(int);
    int getAutoFocus(){return m_ctrl_auto_focus["value"];};
    int getAutoFocusDefault(){return m_ctrl_auto_focus["default"];};
    bool getAutoFocusVisible(){return m_ctrl_auto_focus_visible;};
    // double getCtrlDefaultValue(QString);
    bool resetCrtlToDefault(QString);
    QString getCtrlOptions();
    void applyConfiguration();
    bool resetToDefault();
    bool setCurrentFormatWidth(int);
    int getCurrentFormatWidth(){return m_current_width;};
    bool setCurrentFormatHeight(int);
    int getCurrentFormatHeight(){return m_current_height;};
    bool setCurrentFormatName(QString);
    QString getCurrentFormatName(){return m_current_fmt;};
    QString getUdevRule();

private:
    QString m_device_serial;
    QString m_device_name;
    QString m_device_vendor_id;
    QString m_device_model_id;
    QString m_device_path;
    QStringList m_ctrl_list = {"brightness","contrast","sharpness","saturation","zoom_absolute","focus_automatic_continuous"};
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
    QMap<QString, int> m_ctrl_auto_focus;
    bool m_ctrl_auto_focus_visible;
    QString m_current_fmt;
    int m_current_width;
    int m_current_height;
    QList<QStringList> m_device_formats;
    QStringList m_format_list;
    int m_current_format_index;
};

#endif
