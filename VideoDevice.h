#ifndef VIDEODEVICE_H
#define VIDEODEVICE_H

#include <QString>
#include <QStringList>
#include <KConfigGroup>
#include "helpers.h"
#include <unistd.h>
#include <QCamera>
#include <QCameraInfo>
#include <QCameraImageProcessing>

class VideoDevice : public QObject {
public:
    VideoDevice();
    VideoDevice(const QCameraInfo,QString,QString,QString);
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
    bool setBrightness(qreal);
    qreal getBrightness(){return m_ctrl_brightness["value"];};
    // double getBrightnessMin(){return m_ctrl_brightness["min"];};
    // double getBrightnessMax(){return m_ctrl_brightness["max"];};
    // double getBrightnessStep(){return m_ctrl_brightness["step"];};
    // double getBrightnessDefault(){return m_ctrl_brightness["default"];};
    bool getBrightnessVisible(){return m_ctrl_brightness_visible;};
    bool setContrast(qreal);
    qreal getContrast(){return m_ctrl_contrast["value"];};
    // double getContrastMin(){return m_ctrl_contrast["min"];};
    // double getContrastMax(){return m_ctrl_contrast["max"];};
    // double getContrastStep(){return m_ctrl_contrast["step"];};
    // double getContrastDefault(){return m_ctrl_contrast["default"];};
    bool getContrastVisible(){return m_ctrl_contrast_visible;};
    bool setSharpness(qreal);
    qreal getSharpness(){return m_ctrl_sharpness["value"];};
    // double getSharpnessMin(){return m_ctrl_sharpness["min"];};
    // double getSharpnessMax(){return m_ctrl_sharpness["max"];};
    // double getSharpnessStep(){return m_ctrl_sharpness["step"];};
    // double getSharpnessDefault(){return m_ctrl_sharpness["default"];};
    bool getSharpnessVisible(){return m_ctrl_sharpness_visible;};
    bool setSaturation(qreal);
    qreal getSaturation(){return m_ctrl_saturation["value"];};
    // double getSaturationMin(){return m_ctrl_saturation["min"];};
    // double getSaturationMax(){return m_ctrl_saturation["max"];};
    // double getSaturationStep(){return m_ctrl_saturation["step"];};
    // double getSaturationDefault(){return m_ctrl_saturation["default"];};
    bool getSaturationVisible(){return m_ctrl_saturation_visible;};
    bool setOpticalZoom(qreal);
    qreal getOpticalZoom(){return m_ctrl_zoom_optical["value"];};
    double getOpticalZoomMax(){return m_ctrl_zoom_optical["max"];};
    bool getOpticalZoomVisible(){return m_ctrl_zoom_optical_visible;};
    bool setDigitalZoom(qreal);
    qreal getDigitalZoom(){return m_ctrl_zoom_digital["value"];};
    double getDigitalZoomMax(){qCDebug(webcam_settings_kcm) << "VideoDevice::getDigitalZoomMax" << m_ctrl_zoom_digital["max"];return m_ctrl_zoom_digital["max"];};
    bool getDigitalZoomVisible(){return m_ctrl_zoom_digital_visible;};
    bool setAutoFocus(int);
    int getAutoFocus(){return m_ctrl_auto_focus["value"];};
    int getAutoFocusDefault(){return m_ctrl_auto_focus["default"];};
    bool getAutoFocusVisible(){return m_ctrl_auto_focus_visible;};
    bool setFocus(double);
    double getFocus(){return m_ctrl_focus["value"];};
    double getFocusMin(){return m_ctrl_focus["min"];};
    double getFocusMax(){return m_ctrl_focus["max"];};
    double getFocusStep(){return m_ctrl_focus["step"];};
    double getFocusDefault(){return m_ctrl_focus["default"];};
    bool getFocusVisible(){return (!getAutoFocus() && m_ctrl_focus_visible);};
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
    void setZoom(qreal,qreal);
    void applyControlValue(QString,QString);
    void applyControlValue(bool,QString,qreal,qreal,qreal);
    int getControlValueV4L(bool,qreal,qreal,qreal);
    QCamera *m_current_camera;
    QString m_device_serial;
    QString m_device_name;
    QString m_device_vendor_id;
    QString m_device_model_id;
    QString m_device_path;
    QStringList m_ctrl_list = {"brightness","contrast","sharpness","saturation","zoom_optical", "zoom_digital","focus_automatic_continuous","focus_absolute"};
    QMap<QString, qreal> m_ctrl_brightness;
    bool m_ctrl_brightness_visible;
    QMap<QString, double> m_ctrl_contrast;
    bool m_ctrl_contrast_visible;
    QMap<QString, double> m_ctrl_sharpness;
    bool m_ctrl_sharpness_visible;
    QMap<QString, double> m_ctrl_saturation;
    bool m_ctrl_saturation_visible;
    QMap<QString, double> m_ctrl_zoom_optical;
    bool m_ctrl_zoom_optical_visible;
    QMap<QString, double> m_ctrl_zoom_digital;
    bool m_ctrl_zoom_digital_visible;
    QMap<QString, int> m_ctrl_auto_focus;
    bool m_ctrl_auto_focus_visible;
    QMap<QString, double> m_ctrl_focus;
    bool m_ctrl_focus_visible;
    QString m_current_fmt;
    int m_current_width;
    int m_current_height;
    QList<QStringList> m_device_formats;
    QStringList m_format_list;
    int m_current_format_index;
    bool m_is_dummy_device = false;
};

#endif
