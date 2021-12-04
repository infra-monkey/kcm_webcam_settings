/**
 * SPDX-FileCopyrightText: Year Author <author@domanin.com>
 * SPDX-License-Identifier: GPL-2.0-or-later
 */
#ifndef QWEBCAMSETTINGS_H
#define QWEBCAMSETTINGS_H

#include "VideoDevice.h"
#include "VideoDeviceList.h"
#include <KQuickAddons/ConfigModule>
#include <dirent.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/media.h>
#include <QString>
#include <QStringList>

class QWebcamSettings : public KQuickAddons::ConfigModule
{
    Q_OBJECT
    Q_PROPERTY(QStringList device_list READ getDeviceList NOTIFY deviceIndexChanged)
    Q_PROPERTY(int deviceIndex READ getDeviceIndex WRITE setDeviceIndex NOTIFY deviceIndexChanged)

    Q_PROPERTY(QStringList format_list READ getFormatList NOTIFY formatIndexChanged)
    Q_PROPERTY(int formatIndex READ getFormatIndex WRITE setFormatIndex NOTIFY formatIndexChanged)

    Q_PROPERTY(QStringList resolution_list READ getResolutionList NOTIFY resolutionIndexChanged)
    Q_PROPERTY(int resolutionIndex READ getResolutionIndex WRITE setResolutionIndex NOTIFY resolutionIndexChanged)

    Q_PROPERTY(qreal brightness READ getBrightness WRITE setBrightness NOTIFY brightnessChanged)
    Q_PROPERTY(qreal brightness_min READ getBrightnessMin NOTIFY deviceIndexChanged)
    Q_PROPERTY(qreal brightness_max READ getBrightnessMax NOTIFY deviceIndexChanged)
    Q_PROPERTY(qreal brightness_step READ getBrightnessStep NOTIFY deviceIndexChanged)
    Q_PROPERTY(qreal brightness_visible READ getBrightnessVisible NOTIFY deviceIndexChanged)

    Q_PROPERTY(qreal contrast READ getContrast WRITE setContrast NOTIFY contrastChanged)
    Q_PROPERTY(qreal contrast_min READ getContrastMin NOTIFY deviceIndexChanged)
    Q_PROPERTY(qreal contrast_max READ getContrastMax NOTIFY deviceIndexChanged)
    Q_PROPERTY(qreal contrast_step READ getContrastStep NOTIFY deviceIndexChanged)
    Q_PROPERTY(qreal contrast_visible READ getContrastVisible NOTIFY deviceIndexChanged)

    Q_PROPERTY(qreal sharpness READ getSharpness WRITE setSharpness NOTIFY sharpnessChanged)
    Q_PROPERTY(qreal sharpness_min READ getSharpnessMin NOTIFY deviceIndexChanged)
    Q_PROPERTY(qreal sharpness_max READ getSharpnessMax NOTIFY deviceIndexChanged)
    Q_PROPERTY(qreal sharpness_step READ getSharpnessStep NOTIFY deviceIndexChanged)
    Q_PROPERTY(qreal sharpness_visible READ getSharpnessVisible NOTIFY deviceIndexChanged)

    Q_PROPERTY(qreal saturation READ getSaturation WRITE setSaturation NOTIFY saturationChanged)
    Q_PROPERTY(qreal saturation_min READ getSaturationMin NOTIFY deviceIndexChanged)
    Q_PROPERTY(qreal saturation_max READ getSaturationMax NOTIFY deviceIndexChanged)
    Q_PROPERTY(qreal saturation_step READ getSaturationStep NOTIFY deviceIndexChanged)
    Q_PROPERTY(qreal saturation_visible READ getSaturationVisible NOTIFY deviceIndexChanged)

    Q_PROPERTY(qreal absolute_zoom READ getAbsoluteZoom WRITE setAbsoluteZoom NOTIFY absoluteZoomChanged)
    Q_PROPERTY(qreal absolute_zoom_min READ getAbsoluteZoomMin NOTIFY deviceIndexChanged)
    Q_PROPERTY(qreal absolute_zoom_max READ getAbsoluteZoomMax NOTIFY deviceIndexChanged)
    Q_PROPERTY(qreal absolute_zoom_step READ getAbsoluteZoomStep NOTIFY deviceIndexChanged)
    Q_PROPERTY(qreal absolute_zoom_visible READ getAbsoluteZoomVisible NOTIFY deviceIndexChanged)

public:
    QWebcamSettings(QObject *parent, const QVariantList &args);
    virtual ~QWebcamSettings() override = default;
    QStringList getDeviceList();
    QStringList getFormatList();
    QStringList getResolutionList();
    void populateDeviceList();
    int getDeviceIndex(){return m_device_index;};
    int getFormatIndex(){return m_current_device.getFormatIndex();};
    int getResolutionIndex(){return m_current_device.getResolutionIndex();};
    qreal getBrightness() const {return m_brightness;};
    qreal getBrightnessMin() const {return m_brightness_min;};
    qreal getBrightnessMax() const {return m_brightness_max;};
    qreal getBrightnessStep() const {return m_brightness_step;};
    bool getBrightnessVisible() const {return m_brightness_visible;};
    qreal getContrast() const {return m_contrast;};
    qreal getContrastMin() const {return m_contrast_min;};
    qreal getContrastMax() const {return m_contrast_max;};
    qreal getContrastStep() const {return m_contrast_step;};
    bool getContrastVisible() const {return m_contrast_visible;};
    qreal getSharpness() const {return m_sharpness;};
    qreal getSharpnessMin() const {return m_sharpness_min;};
    qreal getSharpnessMax() const {return m_sharpness_max;};
    qreal getSharpnessStep() const {return m_sharpness_step;};
    bool getSharpnessVisible() const {return m_sharpness_visible;};
    qreal getSaturation() const {return m_saturation;};
    qreal getSaturationMin() const {return m_saturation_min;};
    qreal getSaturationMax() const {return m_saturation_max;};
    qreal getSaturationStep() const {return m_saturation_step;};
    bool getSaturationVisible() const {return m_saturation_visible;};
    qreal getAbsoluteZoom() const {return m_absolute_zoom;};
    qreal getAbsoluteZoomMin() const {return m_absolute_zoom_min;};
    qreal getAbsoluteZoomMax() const {return m_absolute_zoom_max;};
    qreal getAbsoluteZoomStep() const {return m_absolute_zoom_step;};
    bool getAbsoluteZoomVisible() const {return m_absolute_zoom_visible;};

    void load() override;
    void save() override;
    void defaults() override;

    Q_INVOKABLE void setDeviceIndex(int);
    Q_INVOKABLE void setFormatIndex(int);
    Q_INVOKABLE void setResolutionIndex(int);
    Q_INVOKABLE void setAbsoluteZoom(double);
    Q_INVOKABLE void setBrightness(double);
    Q_INVOKABLE void setContrast(double);
    Q_INVOKABLE void setSaturation(double);
    Q_INVOKABLE void setSharpness(double);
    Q_INVOKABLE void resetCrtlToDefault(QString);
    Q_INVOKABLE void applyResolution();
Q_SIGNALS:
    void deviceIndexChanged();
    void formatIndexChanged();
    void resolutionIndexChanged();
    void absoluteZoomChanged();
    void brightnessChanged();
    void contrastChanged();
    void saturationChanged();
    void sharpnessChanged();

// public Q_SLOTS:
//     void load() Q_DECL_OVERRIDE;
//     void save() Q_DECL_OVERRIDE;
//     void defaults() Q_DECL_OVERRIDE;

private:
    VideoDeviceList m_device_list;
    VideoDevice m_current_device;
    QStringList m_devname_list;
    QStringList m_current_format_list;
    QStringList m_current_resolution_list;
    int m_device_index;
    int m_format_index;
    int m_resolution_index;
    double m_absolute_zoom;
    double m_absolute_zoom_min;
    double m_absolute_zoom_max;
    double m_absolute_zoom_step;
    bool m_absolute_zoom_visible;

    double m_brightness;
    double m_brightness_min;
    double m_brightness_max;
    double m_brightness_step;
    bool m_brightness_visible;

    double m_contrast;
    double m_contrast_min;
    double m_contrast_max;
    double m_contrast_step;
    bool m_contrast_visible;

    double m_saturation;
    double m_saturation_min;
    double m_saturation_max;
    double m_saturation_step;
    bool m_saturation_visible;

    double m_sharpness;
    double m_sharpness_min;
    double m_sharpness_max;
    double m_sharpness_step;
    bool m_sharpness_visible;
};

#endif
