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
#include <QStringListModel>
#include <QJSValue>

class QWebcamSettings : public KQuickAddons::ConfigModule
{
    Q_OBJECT
    Q_PROPERTY(QStringListModel* device_list_model READ getDeviceList NOTIFY deviceIndexChanged)
    Q_PROPERTY(int deviceIndex READ getDeviceIndex WRITE setDeviceIndex NOTIFY deviceIndexChanged)
    Q_PROPERTY(QString device_info_name READ getSelectedDeviceName NOTIFY deviceIndexChanged)
    Q_PROPERTY(QString device_info_path READ getSelectedDevicePath NOTIFY deviceIndexChanged)
    Q_PROPERTY(QString device_info_vendorid READ getSelectedDeviceVendorId NOTIFY deviceIndexChanged)
    Q_PROPERTY(QString device_info_modelid READ getSelectedDeviceModelId NOTIFY deviceIndexChanged)
    

    Q_PROPERTY(QStringList format_list READ getFormatList NOTIFY formatIndexChanged)
    Q_PROPERTY(int formatIndex READ getFormatIndex WRITE setFormatIndex NOTIFY formatIndexChanged)

    Q_PROPERTY(qreal brightness READ getBrightness WRITE setBrightness NOTIFY brightnessChanged)
    Q_PROPERTY(int brightness_spin READ getBrightnessSpin NOTIFY brightnessChanged)
    // Q_PROPERTY(qreal brightness_min READ getBrightnessMin NOTIFY deviceIndexChanged)
    // Q_PROPERTY(qreal brightness_max READ getBrightnessMax NOTIFY deviceIndexChanged)
    // Q_PROPERTY(qreal brightness_step READ getBrightnessStep NOTIFY deviceIndexChanged)
    Q_PROPERTY(qreal brightness_visible READ getBrightnessVisible NOTIFY deviceIndexChanged)

    Q_PROPERTY(qreal contrast READ getContrast WRITE setContrast NOTIFY contrastChanged)
    Q_PROPERTY(int contrast_spin READ getContrastSpin NOTIFY contrastChanged)
    // Q_PROPERTY(qreal contrast_min READ getContrastMin NOTIFY deviceIndexChanged)
    // Q_PROPERTY(qreal contrast_max READ getContrastMax NOTIFY deviceIndexChanged)
    // Q_PROPERTY(qreal contrast_step READ getContrastStep NOTIFY deviceIndexChanged)
    Q_PROPERTY(qreal contrast_visible READ getContrastVisible NOTIFY deviceIndexChanged)

    Q_PROPERTY(qreal sharpness READ getSharpness WRITE setSharpness NOTIFY sharpnessChanged)
    Q_PROPERTY(int sharpness_spin READ getSharpnessSpin NOTIFY sharpnessChanged)
    // Q_PROPERTY(qreal sharpness_min READ getSharpnessMin NOTIFY deviceIndexChanged)
    // Q_PROPERTY(qreal sharpness_max READ getSharpnessMax NOTIFY deviceIndexChanged)
    // Q_PROPERTY(qreal sharpness_step READ getSharpnessStep NOTIFY deviceIndexChanged)
    Q_PROPERTY(qreal sharpness_visible READ getSharpnessVisible NOTIFY deviceIndexChanged)

    Q_PROPERTY(qreal saturation READ getSaturation WRITE setSaturation NOTIFY saturationChanged)
    Q_PROPERTY(int saturation_spin READ getSaturationSpin NOTIFY saturationChanged)
    // Q_PROPERTY(qreal saturation_min READ getSaturationMin NOTIFY deviceIndexChanged)
    // Q_PROPERTY(qreal saturation_max READ getSaturationMax NOTIFY deviceIndexChanged)
    // Q_PROPERTY(qreal saturation_step READ getSaturationStep NOTIFY deviceIndexChanged)
    Q_PROPERTY(qreal saturation_visible READ getSaturationVisible NOTIFY deviceIndexChanged)

    Q_PROPERTY(qreal optical_zoom READ getOpticalZoom WRITE setOpticalZoom NOTIFY opticalZoomChanged)
    Q_PROPERTY(qreal optical_zoom_max READ getOpticalZoomMax NOTIFY deviceIndexChanged)
    Q_PROPERTY(qreal optical_zoom_visible READ getOpticalZoomVisible NOTIFY deviceIndexChanged)

    Q_PROPERTY(qreal digital_zoom READ getDigitalZoom WRITE setDigitalZoom NOTIFY digitalZoomChanged)
    Q_PROPERTY(qreal digital_zoom_max READ getDigitalZoomMax NOTIFY deviceIndexChanged)
    Q_PROPERTY(qreal digital_zoom_visible READ getDigitalZoomVisible NOTIFY deviceIndexChanged)

    Q_PROPERTY(int auto_focus READ getAutoFocus WRITE setAutoFocus NOTIFY autoFocusChanged)
    Q_PROPERTY(int auto_focus_visible READ getAutoFocusVisible NOTIFY autoFocusChanged)

    Q_PROPERTY(qreal absolute_focus READ getFocus WRITE setFocus NOTIFY focusChanged)
    Q_PROPERTY(qreal absolute_focus_min READ getFocusMin NOTIFY deviceIndexChanged)
    Q_PROPERTY(qreal absolute_focus_max READ getFocusMax NOTIFY deviceIndexChanged)
    Q_PROPERTY(qreal absolute_focus_step READ getFocusStep NOTIFY deviceIndexChanged)
    Q_PROPERTY(qreal absolute_focus_visible READ getFocusVisible NOTIFY autoFocusChanged)

public:
    QWebcamSettings(QObject *parent, const QVariantList &args);
    virtual ~QWebcamSettings() override = default;
    QStringListModel* getDeviceList();
    QStringList getFormatList(){return this->m_current_device->getFormatList();};
    void populateDeviceList();
    int getDeviceIndex(){return m_device_index;};
    QString getSelectedDeviceName();
    QString getSelectedDevicePath();
    QString getSelectedDeviceVendorId();
    QString getSelectedDeviceModelId();
    int getFormatIndex(){return this->m_current_device->getFormatIndex();};
    qreal getBrightness() {return this->m_current_device->getBrightness();};
    int getBrightnessSpin() {return (int)(this->m_current_device->getBrightness() * 100);};
    // qreal getBrightnessMin() {return this->m_current_device->getBrightnessMin();};
    // qreal getBrightnessMax() {return this->m_current_device->getBrightnessMax();};
    // qreal getBrightnessStep() {return this->m_current_device->getBrightnessStep();};
    bool getBrightnessVisible() {return this->m_current_device->getBrightnessVisible();};
    qreal getContrast() {return this->m_current_device->getContrast();};
    qreal getContrastSpin() {return (int)(this->m_current_device->getContrast() * 100);};
    // qreal getContrastMin() {return this->m_current_device->getContrastMin();};
    // qreal getContrastMax() {return this->m_current_device->getContrastMax();};
    // qreal getContrastStep() {return this->m_current_device->getContrastStep();};
    bool getContrastVisible() {return this->m_current_device->getContrastVisible();};
    qreal getSharpness() {return this->m_current_device->getSharpness();};
    int getSharpnessSpin() {return (int)(this->m_current_device->getSharpness() * 100);};
    // qreal getSharpnessMin() {return this->m_current_device->getSharpnessMin();};
    // qreal getSharpnessMax() {return this->m_current_device->getSharpnessMax();};
    // qreal getSharpnessStep() {return this->m_current_device->getSharpnessStep();};
    bool getSharpnessVisible() {return this->m_current_device->getSharpnessVisible();};
    qreal getSaturation() {return this->m_current_device->getSaturation();};
    int getSaturationSpin() {return (int)(this->m_current_device->getSaturation() * 100);};
    // qreal getSaturationMin() {return this->m_current_device->getSaturationMin();};
    // qreal getSaturationMax() {return this->m_current_device->getSaturationMax();};
    // qreal getSaturationStep() {return this->m_current_device->getSaturationStep();};
    bool getSaturationVisible() {return this->m_current_device->getSaturationVisible();};
    qreal getOpticalZoom() {return this->m_current_device->getOpticalZoom();};
    qreal getOpticalZoomMax() {return this->m_current_device->getOpticalZoomMax();};
    bool getOpticalZoomVisible() {return this->m_current_device->getOpticalZoomVisible();};
    qreal getDigitalZoom() {return this->m_current_device->getDigitalZoom();};
    qreal getDigitalZoomMax() {return this->m_current_device->getDigitalZoomMax();};
    bool getDigitalZoomVisible() {return this->m_current_device->getDigitalZoomVisible();};
    int getAutoFocus(){return this->m_current_device->getAutoFocus();};
    bool getAutoFocusVisible() {return this->m_current_device->getAutoFocusVisible();};
    qreal getFocus() {return this->m_current_device->getFocus();};
    qreal getFocusMin() {return this->m_current_device->getFocusMin();};
    qreal getFocusMax() {return this->m_current_device->getFocusMax();};
    qreal getFocusStep() {return this->m_current_device->getFocusStep();};
    bool getFocusVisible() {qCDebug(webcam_settings_kcm) << "QWebcamSettings::getFocusVisible" << this->m_current_device->getFocusVisible();return this->m_current_device->getFocusVisible();};
    void load() override;
    void save() override;
    void defaults() override;

    Q_INVOKABLE void setDeviceIndex(int);
    Q_INVOKABLE void setFormatIndex(int);
    Q_INVOKABLE void setOpticalZoom(qreal);
    Q_INVOKABLE void setDigitalZoom(qreal);
    Q_INVOKABLE void setBrightness(double);
    Q_INVOKABLE void setContrast(double);
    Q_INVOKABLE void setSaturation(double);
    Q_INVOKABLE void setSharpness(double);
    Q_INVOKABLE void resetCrtlToDefault(QString);
    Q_INVOKABLE void setAutoFocus(int);
    Q_INVOKABLE void setFocus(double);
    // Q_INVOKABLE void applyResolution();
Q_SIGNALS:
    void deviceIndexChanged();
    void formatIndexChanged();
    void opticalZoomChanged();
    void digitalZoomChanged();
    void brightnessChanged();
    void contrastChanged();
    void saturationChanged();
    void sharpnessChanged();
    void autoFocusChanged();
    void focusChanged();

private:
    VideoDevice* getDeviceFromIndex(int);
    QStringList m_devicename_list;
    QStringListModel *m_devicename_list_model;
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
