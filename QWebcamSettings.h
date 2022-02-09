/**
 * SPDX-FileCopyrightText: Year Author <author@domanin.com>
 * SPDX-License-Identifier: GPL-2.0-or-later
 */
#ifndef QWEBCAMSETTINGS_H
#define QWEBCAMSETTINGS_H

#include "VideoDevice.h"
#include <KQuickAddons/ConfigModule>
#include <dirent.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/media.h>
#include <QString>
#include <QStringList>
#include <KConfig>
#include <KConfigGroup>

class QWebcamSettings : public KQuickAddons::ConfigModule
{
    Q_OBJECT
    Q_PROPERTY(QStringList device_list READ getDeviceList NOTIFY deviceIndexChanged)
    Q_PROPERTY(int deviceIndex READ getDeviceIndex WRITE setDeviceIndex NOTIFY deviceIndexChanged)

    Q_PROPERTY(QStringList format_list READ getFormatList NOTIFY formatIndexChanged)
    Q_PROPERTY(int formatIndex READ getFormatIndex WRITE setFormatIndex NOTIFY formatIndexChanged)

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

    Q_PROPERTY(int auto_focus READ getAutoFocus WRITE setAutoFocus NOTIFY autoFocusChanged)
    Q_PROPERTY(int auto_focus_visible READ getAutoFocusVisible NOTIFY autoFocusChanged)

public:
    QWebcamSettings(QObject *parent, const QVariantList &args);
    virtual ~QWebcamSettings() override = default;
    QStringList getDeviceList(){return m_devicename_list;};
    QStringList getFormatList(){return this->m_current_device->getFormatList();};
    void populateDeviceList();
    int getDeviceIndex(){return m_device_index;};
    int getFormatIndex(){return this->m_current_device->getFormatIndex();};
    qreal getBrightness() {return this->m_current_device->getBrightness();};
    qreal getBrightnessMin() {return this->m_current_device->getBrightnessMin();};
    qreal getBrightnessMax() {return this->m_current_device->getBrightnessMax();};
    qreal getBrightnessStep() {return this->m_current_device->getBrightnessStep();};
    bool getBrightnessVisible() {return this->m_current_device->getBrightnessVisible();};
    qreal getContrast() {return this->m_current_device->getContrast();};
    qreal getContrastMin() {return this->m_current_device->getContrastMin();};
    qreal getContrastMax() {return this->m_current_device->getContrastMax();};
    qreal getContrastStep() {return this->m_current_device->getContrastStep();};
    bool getContrastVisible() {return this->m_current_device->getContrastVisible();};
    qreal getSharpness() {return this->m_current_device->getSharpness();};
    qreal getSharpnessMin() {return this->m_current_device->getSharpnessMin();};
    qreal getSharpnessMax() {return this->m_current_device->getSharpnessMax();};
    qreal getSharpnessStep() {return this->m_current_device->getSharpnessStep();};
    bool getSharpnessVisible() {return this->m_current_device->getSharpnessVisible();};
    qreal getSaturation() {return this->m_current_device->getSaturation();};
    qreal getSaturationMin() {return this->m_current_device->getSaturationMin();};
    qreal getSaturationMax() {return this->m_current_device->getSaturationMax();};
    qreal getSaturationStep() {return this->m_current_device->getSaturationStep();};
    bool getSaturationVisible() {return this->m_current_device->getSaturationVisible();};
    qreal getAbsoluteZoom() {return this->m_current_device->getAbsoluteZoom();};
    qreal getAbsoluteZoomMin() {return this->m_current_device->getAbsoluteZoomMin();};
    qreal getAbsoluteZoomMax() {return this->m_current_device->getAbsoluteZoomMax();};
    qreal getAbsoluteZoomStep() {return this->m_current_device->getAbsoluteZoomStep();};
    bool getAbsoluteZoomVisible() {return this->m_current_device->getAbsoluteZoomVisible();};
    int getAutoFocus(){return this->m_current_device->getAutoFocus();};
    bool getAutoFocusVisible() {return this->m_current_device->getAutoFocusVisible();};
    void load() override;
    void save() override;
    void defaults() override;

    Q_INVOKABLE void setDeviceIndex(int);
    Q_INVOKABLE void setFormatIndex(int);
    Q_INVOKABLE void setAbsoluteZoom(double);
    Q_INVOKABLE void setBrightness(double);
    Q_INVOKABLE void setContrast(double);
    Q_INVOKABLE void setSaturation(double);
    Q_INVOKABLE void setSharpness(double);
    Q_INVOKABLE void resetCrtlToDefault(QString);
    Q_INVOKABLE void setAutoFocus(int);
    // Q_INVOKABLE void applyResolution();
Q_SIGNALS:
    void deviceIndexChanged();
    void formatIndexChanged();
    void absoluteZoomChanged();
    void brightnessChanged();
    void contrastChanged();
    void saturationChanged();
    void sharpnessChanged();
    void autoFocusChanged();

private:
    VideoDevice* getDeviceFromIndex(int);
    QStringList m_devicename_list;
    QList<VideoDevice*> m_device_list;
    VideoDevice *m_current_device;
    QStringList m_current_format_list;
    int m_device_index;
    int m_format_index;
	//KConfig m_config;
    KConfigGroup m_webcam_config;
	QStringList m_config_grouplist;
    bool m_devices_available;
};

#endif
