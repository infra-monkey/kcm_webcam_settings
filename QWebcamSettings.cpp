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


K_PLUGIN_CLASS_WITH_JSON(QWebcamSettings, "metadata.json")

QWebcamSettings::QWebcamSettings(QObject *parent, const QVariantList &args)
    : KQuickAddons::ConfigModule(parent, args)
{
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
    populateDeviceList(m_device_list);
	m_device_index = 0;
    setAboutData(aboutData);
    setButtons(Apply | Default);
}

void QWebcamSettings::populateDeviceList(VideoDeviceList devlist) {
	std::string devices = exec_cmd("v4l2-ctl --list-devices");
	std::istringstream f(devices);
    std::string line;    
	QString name;
	QString bus_info;
    while (std::getline(f, line)) {
		QString qline = QString::fromStdString(line).trimmed();
		if (qline.startsWith(QString::fromStdString("/"))){
			QString file = qline.trimmed();
			devlist.addVideoDevice(file);
		}
    }
	m_device_list = devlist;
	m_device_list.printVideoDeviceInfo();
	m_devname_list = m_device_list.getDeviceNameList();
	setDeviceIndex(0);
}

QStringList QWebcamSettings::getDeviceList(){
	printf("Invoked getDeviceList\n");
	QStringList devname_list = m_device_list.getDeviceNameList();
	for (QString & devname : devname_list)
    {
        printf("%s\n",devname.toStdString().c_str());
    }
	return m_devname_list;
}

QStringList QWebcamSettings::getFormatList(){
	printf("Invoked getFormatList\n");
	m_current_format_list = m_current_device.getFormatList();
	return m_current_format_list;
}

QStringList QWebcamSettings::getResolutionList(){
	printf("Invoked getResolutionList\n");
	m_current_resolution_list = m_current_device.getResolutionList();
	return m_current_resolution_list;
}

void QWebcamSettings::setDeviceIndex(int devindex) {
	printf("Device index is changed to %i\n",devindex);
	m_device_index = devindex;
	m_current_device = m_device_list.getDeviceFromIndex(devindex);
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
	m_contrast = m_current_device.getSaturation();
	m_contrast_min = m_current_device.getSaturationMin();
	m_contrast_max = m_current_device.getSaturationMax();
	m_contrast_step = m_current_device.getSaturationStep();
	m_contrast_visible = m_current_device.getSaturationVisible();
	Q_EMIT deviceIndexChanged();
	Q_EMIT formatIndexChanged();
	Q_EMIT resolutionIndexChanged();
	Q_EMIT absoluteZoomChanged();
	Q_EMIT brightnessChanged();
	Q_EMIT contrastChanged();
	Q_EMIT contrastChanged();
	Q_EMIT sharpnessChanged();


}

void QWebcamSettings::setFormatIndex(int fmtindex) {
	printf("Format index is changed to %i\n",fmtindex);
	m_current_device.setFormatIndex(fmtindex);
	Q_EMIT formatIndexChanged();
	Q_EMIT resolutionIndexChanged();
}

void QWebcamSettings::setResolutionIndex(int resindex) {
	printf("Resolution index is changed to %i\n",resindex);
	m_current_device.setResolutionIndex(resindex);
	Q_EMIT resolutionIndexChanged();
}

void QWebcamSettings::setAbsoluteZoom(double zoom) {
	printf("Absolute zoom index is changed to %f\n",zoom);
	m_absolute_zoom = zoom;
	m_current_device.setAbsoluteZoom(zoom);
	Q_EMIT absoluteZoomChanged();
}

void QWebcamSettings::setBrightness(double brightness) {
	printf("Brightness index is changed to %f\n",brightness);
	m_brightness = brightness;
	m_current_device.setBrightness(brightness);
	Q_EMIT brightnessChanged();
}

void QWebcamSettings::setContrast(double contrast) {
	printf("Contrast index is changed to %f\n",contrast);
	m_contrast = contrast;
	m_current_device.setContrast(contrast);
	Q_EMIT contrastChanged();
}

void QWebcamSettings::setSharpness(double sharpness) {
	printf("Sharpness index is changed to %f\n",sharpness);
	m_sharpness = sharpness;
	m_current_device.setSharpness(sharpness);
	Q_EMIT sharpnessChanged();
}

void QWebcamSettings::setSaturation(double saturation) {
	printf("Saturation index is changed to %f\n",saturation);
	m_saturation = saturation;
	m_current_device.setSaturation(saturation);
	Q_EMIT saturationChanged();
}

void QWebcamSettings::resetCrtlToDefault(QString ctrl_name) {
	printf("Reset control %s to value %f\n",ctrl_name.toStdString().c_str(),m_current_device.getCtrlDefaultValue(ctrl_name));
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
		m_current_device.setBrightness(m_absolute_zoom);
		Q_EMIT absoluteZoomChanged();
    }
}


#include "QWebcamSettings.moc"
