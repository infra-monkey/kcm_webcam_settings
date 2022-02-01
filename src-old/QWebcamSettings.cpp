/**
 * SPDX-FileCopyrightText: Year Author <author@domain.com>
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#include "QWebcamSettings.h"
#include "helpers.h"
#include <KPluginFactory>
#include <KLocalizedString>
#include <KAboutData>
#include <KSharedConfig>
#include <KConfigGroup>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <sys/ioctl.h>
#include <QCamera>
#include <QCameraInfo>
#include <QList>
#include <KAuth>

using namespace KAuth;

K_PLUGIN_CLASS_WITH_JSON(QWebcamSettings, "metadata.json")

QWebcamSettings::QWebcamSettings(QObject *parent, const QVariantList &args)
    : KQuickAddons::ConfigModule(parent, args)
{
	qCDebug(webcam_settings_kcm) << "QWebcamSettings::QWebcamSettings";
    KAboutData *aboutData = new KAboutData(QStringLiteral("kcm_webcam_settings"),
        i18nc("@title", "Webcam"),
        QStringLiteral("0.1"),
        QStringLiteral(""),
        KAboutLicense::LicenseKey::GPL_V3,
        i18nc("@info:credit", "Copyright 2021 Antoine Gatineau"));

    aboutData->addAuthor(i18nc("@info:credit", "Antoine Gatineau"),
                        i18nc("@info:credit", "Antoine Gatineau"),
                        QStringLiteral("antoine.gatineau@infra-monkey.com"));

	m_device_list = VideoDeviceList();
	m_devname_list = QStringList();
	m_device_index = 0;
    setAboutData(aboutData);
    setButtons(Apply | Default);
}

void QWebcamSettings::save() {
	qCDebug(webcam_settings_kcm) << "QWebcamSettings::save save current settings";
	//build udev rule file
	QVariantMap args;
	QStringList udevrules = m_device_list.getUdevRules();
    args["filename"] = QLatin1String("/etc/udev/rules.d/99-persistent-webcam.rules");
	args["contents"] = udevrules;
    Action saveAction("kcm.webcam.settings.udevhelper.applyudevrules");
    saveAction.setHelperId("kcm.webcam.settings.udevhelper");
    saveAction.setArguments(args);
    ExecuteJob *job = saveAction.execute();
    if (!job->exec()) {
        qCDebug(webcam_settings_kcm) << "KAuth returned an error code:" << job->error();
		qCDebug(webcam_settings_kcm) << job->errorString();
    } else {
		qCDebug(webcam_settings_kcm) << job->data()["contents"].toString();
    }

}

void QWebcamSettings::load() {
	qCDebug(webcam_settings_kcm) << "QWebcamSettings::load load settings from config";
    populateDeviceList();
}

void QWebcamSettings::defaults() {
	qCDebug(webcam_settings_kcm) << "QWebcamSettings::defaults reset to default settings";
	bool save_needed = m_current_device.resetToDefault();
	m_absolute_zoom = m_current_device.getAbsoluteZoom();
	m_brightness = m_current_device.getBrightness();
	m_contrast = m_current_device.getContrast();
	m_saturation = m_current_device.getSaturation();
	m_sharpness = m_current_device.getSharpness();
	Q_EMIT absoluteZoomChanged();
	Q_EMIT brightnessChanged();
	Q_EMIT contrastChanged();
	Q_EMIT saturationChanged();
	Q_EMIT sharpnessChanged();
	if (save_needed){setNeedsSave(true);}
}

void QWebcamSettings::populateDeviceList() {
	qCDebug(webcam_settings_kcm) << "QWebcamSettings::populateDeviceList Starting to populate the video devices";
	const QList<QCameraInfo> cameras = QCameraInfo::availableCameras();
	for (const QCameraInfo &cameraInfo : cameras) {
		qCDebug(webcam_settings_kcm) << "Detected QCamera : " << cameraInfo.description() << cameraInfo.deviceName();
		m_device_list.addVideoDevice(cameraInfo.deviceName(),cameraInfo.description());
	}
	m_devname_list = m_device_list.getDeviceNameList();
	setDeviceIndex(0);
}

QStringList QWebcamSettings::getDeviceList(){
	QStringList devname_list = m_device_list.getDeviceNameList();
	return m_devname_list;
}

QStringList QWebcamSettings::getFormatList(){
	m_current_format_list = m_current_device.getFormatList();
	return m_current_format_list;
}

QStringList QWebcamSettings::getResolutionList(){
	m_current_resolution_list = m_current_device.getResolutionList();
	return m_current_resolution_list;
}

void QWebcamSettings::setDeviceIndex(int devindex) {
	qCDebug(webcam_settings_kcm) << "QWebcamSettings::setDeviceIndex";
	m_device_index = devindex;
	m_current_device = m_device_list.getDeviceFromIndex(devindex);
	qCInfo(webcam_settings_kcm) << "Selected device " << m_current_device.getVideoDeviceName();
	m_absolute_zoom = m_current_device.getAbsoluteZoom();
	m_absolute_zoom_min = m_current_device.getAbsoluteZoomMin();
	m_absolute_zoom_max = m_current_device.getAbsoluteZoomMax();
	m_absolute_zoom_step = m_current_device.getAbsoluteZoomStep();
	m_absolute_zoom_visible = m_current_device.getAbsoluteZoomVisible();
	m_brightness = m_current_device.getBrightness();
	m_brightness_min = m_current_device.getBrightnessMin();
	m_brightness_max = m_current_device.getBrightnessMax();
	m_brightness_step = m_current_device.getBrightnessStep();
	m_brightness_visible = m_current_device.getBrightnessVisible();
	m_contrast = m_current_device.getContrast();
	m_contrast_min = m_current_device.getContrastMin();
	m_contrast_max = m_current_device.getContrastMax();
	m_contrast_step = m_current_device.getContrastStep();
	m_contrast_visible = m_current_device.getContrastVisible();
	m_sharpness = m_current_device.getSharpness();
	m_sharpness_min = m_current_device.getSharpnessMin();
	m_sharpness_max = m_current_device.getSharpnessMax();
	m_sharpness_step = m_current_device.getSharpnessStep();
	m_sharpness_visible = m_current_device.getSharpnessVisible();
	m_saturation = m_current_device.getSaturation();
	m_saturation_min = m_current_device.getSaturationMin();
	m_saturation_max = m_current_device.getSaturationMax();
	m_saturation_step = m_current_device.getSaturationStep();
	m_saturation_visible = m_current_device.getSaturationVisible();
	Q_EMIT deviceIndexChanged();
	Q_EMIT formatIndexChanged();
	Q_EMIT resolutionIndexChanged();
	Q_EMIT absoluteZoomChanged();
	Q_EMIT brightnessChanged();
	Q_EMIT contrastChanged();
	Q_EMIT saturationChanged();
	Q_EMIT sharpnessChanged();


}

void QWebcamSettings::setFormatIndex(int fmtindex) {
	qCDebug(webcam_settings_kcm) << "QWebcamSettings::setFormatIndex";
	m_current_device.setFormatIndex(fmtindex);
	Q_EMIT formatIndexChanged();
	Q_EMIT resolutionIndexChanged();
}

void QWebcamSettings::setResolutionIndex(int resindex) {
	qCDebug(webcam_settings_kcm) << "QWebcamSettings::setResolutionIndex";
	m_current_device.setResolutionIndex(resindex);
	Q_EMIT resolutionIndexChanged();
}

void QWebcamSettings::setAbsoluteZoom(double zoom) {
	qCDebug(webcam_settings_kcm) << "QWebcamSettings::setAbsoluteZoom";
	m_absolute_zoom = zoom;
	bool save_needed = m_current_device.setAbsoluteZoom(zoom);
	Q_EMIT absoluteZoomChanged();
	if (save_needed){setNeedsSave(true);}
}

void QWebcamSettings::setBrightness(double brightness) {
	qCDebug(webcam_settings_kcm) << "QWebcamSettings::setBrightness";
	m_brightness = brightness;
	bool save_needed = m_current_device.setBrightness(brightness);
	Q_EMIT brightnessChanged();
	if (save_needed){setNeedsSave(true);}
}

void QWebcamSettings::setContrast(double contrast) {
	qCDebug(webcam_settings_kcm) << "QWebcamSettings::setContrast";
	m_contrast = contrast;
	bool save_needed = m_current_device.setContrast(contrast);
	Q_EMIT contrastChanged();
	if (save_needed){setNeedsSave(true);}
}

void QWebcamSettings::setSharpness(double sharpness) {
	qCDebug(webcam_settings_kcm) << "QWebcamSettings::setSharpness";
	m_sharpness = sharpness;
	bool save_needed = m_current_device.setSharpness(sharpness);
	Q_EMIT sharpnessChanged();
	if (save_needed){setNeedsSave(true);}
}

void QWebcamSettings::setSaturation(double saturation) {
	qCDebug(webcam_settings_kcm) << "QWebcamSettings::setSaturation";
	m_saturation = saturation;
	bool save_needed = m_current_device.setSaturation(saturation);
	Q_EMIT saturationChanged();
	if (save_needed){setNeedsSave(true);}
}

void QWebcamSettings::resetCrtlToDefault(QString ctrl_name) {
	qCDebug(webcam_settings_kcm) << "QWebcamSettings::resetCrtlToDefault";
	double default_value = m_current_device.getCtrlDefaultValue(ctrl_name);
	m_absolute_zoom = m_current_device.getCtrlDefaultValue(ctrl_name);

	if (ctrl_name.toStdString() == "brightness") {
		m_brightness = default_value;
		m_current_device.setBrightness(m_brightness);
		Q_EMIT brightnessChanged();
    }
    if (ctrl_name.toStdString() == "contrast") {
		m_contrast = default_value;
		m_current_device.setContrast(m_contrast);
		Q_EMIT contrastChanged();
    }
    if (ctrl_name.toStdString() == "sharpness") {
		m_sharpness = default_value;
		m_current_device.setSharpness(m_sharpness);
		Q_EMIT sharpnessChanged();
    }
    if (ctrl_name.toStdString() == "saturation") {
		m_saturation = default_value;
		m_current_device.setSaturation(m_saturation);
		Q_EMIT saturationChanged();
    }
    if (ctrl_name.toStdString() == "zoom_absolute") {
		m_absolute_zoom = default_value;
		m_current_device.setAbsoluteZoom(m_absolute_zoom);
		Q_EMIT absoluteZoomChanged();
    }
}

void QWebcamSettings::applyResolution(){
	qCDebug(webcam_settings_kcm) << "QWebcamSettings::applyResolution";
	m_current_device.applyResolution();
	setNeedsSave(true);
}

#include "QWebcamSettings.moc"
