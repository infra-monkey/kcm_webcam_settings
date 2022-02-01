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

	m_device_index = 0;
    setAboutData(aboutData);
    setButtons(Apply | Default);
}

void QWebcamSettings::save() {
	qCDebug(webcam_settings_kcm) << "QWebcamSettings::save save current settings";
	//build udev rule file
	// QVariantMap args;
	// QStringList udevrules = m_device_list.getUdevRules();
    // args["filename"] = QLatin1String("/etc/udev/rules.d/99-persistent-webcam.rules");
	// args["contents"] = udevrules;
    // Action saveAction("kcm.webcam.settings.udevhelper.applyudevrules");
    // saveAction.setHelperId("kcm.webcam.settings.udevhelper");
    // saveAction.setArguments(args);
    // ExecuteJob *job = saveAction.execute();
    // if (!job->exec()) {
    //     qCDebug(webcam_settings_kcm) << "KAuth returned an error code:" << job->error();
	// 	qCDebug(webcam_settings_kcm) << job->errorString();
    // } else {
	// 	qCDebug(webcam_settings_kcm) << job->data()["contents"].toString();
    // }

}

void QWebcamSettings::load() {
	qCDebug(webcam_settings_kcm) << "QWebcamSettings::load load settings from config";
    populateDeviceList();
}

void QWebcamSettings::defaults() {
	qCDebug(webcam_settings_kcm) << "QWebcamSettings::defaults reset to default settings";
	bool save_needed = m_current_device.resetToDefault();
	Q_EMIT absoluteZoomChanged();
	Q_EMIT brightnessChanged();
	Q_EMIT contrastChanged();
	Q_EMIT saturationChanged();
	Q_EMIT sharpnessChanged();
	if (save_needed){setNeedsSave(true);}
}

void QWebcamSettings::populateDeviceList() {
    QString vendorid,modelid;
	std::string cmd;
	qCDebug(webcam_settings_kcm) << "QWebcamSettings::populateDeviceList Starting to populate the video devices";
	const QList<QCameraInfo> cameras = QCameraInfo::availableCameras();
	for (const QCameraInfo &cameraInfo : cameras) {
		qCDebug(webcam_settings_kcm) << "Detected QCamera : " << cameraInfo.description() << cameraInfo.deviceName();
		cmd = std::string("udevadm info --query=all --name=" + cameraInfo.deviceName().toStdString());
		QStringList output = QString::fromStdString(exec_cmd(cmd)).split(QLatin1Char('\n'));
		for (QString & line : output){
			if (line.length() == 0){break;}
			QString key = QString::fromStdString(get_str_right_of_substr(get_str_left_of_substr(line.toStdString(),std::string("=")),std::string("E: "))).simplified();
			if (line.contains(QString::fromStdString("ID_VENDOR_ID="))){
				vendorid = QString::fromStdString(get_str_right_of_substr(line.toStdString(),std::string("=")));
				qCDebug(webcam_settings_kcm) << "Found ID_VENDOR_ID=" << vendorid;
			}
			if (line.contains(QString::fromStdString("ID_MODEL_ID="))){
				modelid = QString::fromStdString(get_str_right_of_substr(line.toStdString(),std::string("=")));
				qCDebug(webcam_settings_kcm) << "Found ID_MODEL_ID=" << modelid;
			}
		}
		if (!m_devicename_list.contains(cameraInfo.description())){
			m_device_list << VideoDevice(cameraInfo.description(),cameraInfo.deviceName(),vendorid,modelid);
			m_devicename_list << cameraInfo.description();
		}
	}
	setDeviceIndex(0);
}


VideoDevice QWebcamSettings::getDeviceFromIndex(int index) {
    int i = 0;
	VideoDevice device;
    for (VideoDevice & dev : m_device_list)
    {
        if (i == index) {
            device = dev;
            break;
        }
        i++;
    }
	return device;
}


void QWebcamSettings::setDeviceIndex(int devindex) {
	qCDebug(webcam_settings_kcm) << "QWebcamSettings::setDeviceIndex";
	m_device_index = devindex;
	m_current_device = getDeviceFromIndex(devindex);
	qCInfo(webcam_settings_kcm) << "Selected device " << m_current_device.getVideoDeviceName();
	Q_EMIT deviceIndexChanged();
	Q_EMIT formatIndexChanged();
	// Q_EMIT resolutionIndexChanged();
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
	// Q_EMIT resolutionIndexChanged();
}

// void QWebcamSettings::setResolutionIndex(int resindex) {
// 	qCDebug(webcam_settings_kcm) << "QWebcamSettings::setResolutionIndex";
// 	m_current_device.setResolutionIndex(resindex);
// 	Q_EMIT resolutionIndexChanged();
// }

void QWebcamSettings::setAbsoluteZoom(double zoom) {
	qCDebug(webcam_settings_kcm) << "QWebcamSettings::setAbsoluteZoom";
	bool save_needed = m_current_device.setAbsoluteZoom(zoom);
	Q_EMIT absoluteZoomChanged();
	if (save_needed){setNeedsSave(true);}
}

void QWebcamSettings::setBrightness(double brightness) {
	qCDebug(webcam_settings_kcm) << "QWebcamSettings::setBrightness";
	bool save_needed = m_current_device.setBrightness(brightness);
	Q_EMIT brightnessChanged();
	if (save_needed){setNeedsSave(true);}
}

void QWebcamSettings::setContrast(double contrast) {
	qCDebug(webcam_settings_kcm) << "QWebcamSettings::setContrast";
	bool save_needed = m_current_device.setContrast(contrast);
	Q_EMIT contrastChanged();
	if (save_needed){setNeedsSave(true);}
}

void QWebcamSettings::setSharpness(double sharpness) {
	qCDebug(webcam_settings_kcm) << "QWebcamSettings::setSharpness";
	bool save_needed = m_current_device.setSharpness(sharpness);
	Q_EMIT sharpnessChanged();
	if (save_needed){setNeedsSave(true);}
}

void QWebcamSettings::setSaturation(double saturation) {
	qCDebug(webcam_settings_kcm) << "QWebcamSettings::setSaturation";
	bool save_needed = m_current_device.setSaturation(saturation);
	Q_EMIT saturationChanged();
	if (save_needed){setNeedsSave(true);}
}

// void QWebcamSettings::applyResolution(){
// 	qCDebug(webcam_settings_kcm) << "QWebcamSettings::applyResolution";
// 	m_current_device.applyResolution();
// 	setNeedsSave(true);
// }

void QWebcamSettings::resetCrtlToDefault(QString ctrl_name) {
	qCDebug(webcam_settings_kcm) << "QWebcamSettings::resetCrtlToDefault";
    bool ret = false;
	ret = m_current_device.resetCrtlToDefault(ctrl_name);
	if (ctrl_name == "brightness") {
		if (ret) {Q_EMIT brightnessChanged();}
    }
    if (ctrl_name == "contrast") {
		if (ret) {Q_EMIT contrastChanged();}
    }
    if (ctrl_name == "sharpness") {
		if (ret) {Q_EMIT sharpnessChanged();}
    }
    if (ctrl_name == "saturation") {
		if (ret) {Q_EMIT saturationChanged();}
    }
    if (ctrl_name == "zoom_absolute") {
		if (ret) {Q_EMIT absoluteZoomChanged();}
    }
}

#include "QWebcamSettings.moc"
