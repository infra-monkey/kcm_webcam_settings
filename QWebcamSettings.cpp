/**
 * SPDX-FileCopyrightText: Year Author <author@domain.com>
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#include "QWebcamSettings.h"
#include "helpers.h"
#include <KPluginFactory>
#include <KLocalizedString>
#include <KAboutData>
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
	, m_devicename_list_model(new QStringListModel(this))
{
	qCDebug(webcam_settings_kcm) << "QWebcamSettings::QWebcamSettings";
    KAboutData *aboutData = new KAboutData(QStringLiteral("kcm_webcam_settings"),
        i18nc("@title", "Webcam"),
        QStringLiteral("0.0.1"),
        QStringLiteral(""),
        KAboutLicense::LicenseKey::GPL_V3,
        i18nc("@info:credit", "Copyright 2021 Antoine Gatineau"));

    aboutData->addAuthor(i18nc("@info:credit", "Antoine Gatineau"),
                        i18nc("@info:credit", "Antoine Gatineau"),
                        QStringLiteral("antoine.gatineau@infra-monkey.com"));

    setAboutData(aboutData);
    setButtons(Apply | Default);
	setNeedsSave(false);
	populateDeviceList();
}

void QWebcamSettings::save() {
	qCDebug(webcam_settings_kcm) << "QWebcamSettings::save save current settings";
	QStringList udevrules;
	KConfig config("kcmwebcamsettingsrc");
	KConfigGroup udevconf;
	for (VideoDevice * dev : m_device_list)
    {
		qCDebug(webcam_settings_kcm) << "QWebcamSettings::save resolution "  << dev->getCurrentFormatName() << QString::number(dev->getCurrentFormatWidth()) << QString::number(dev->getCurrentFormatHeight());
		QString udevrule = dev->getUdevRule();
        KConfigGroup devconf(&config, dev->getVideoDeviceSerialId());
		qCDebug(webcam_settings_kcm) << "QWebcamSettings::save config group created for " << dev->getVideoDeviceSerialId();
		devconf.writeEntry("Name",dev->getVideoDeviceName());
		devconf.writeEntry("VendorId",dev->getVideoDeviceVendorId());
		devconf.writeEntry("ModelId",dev->getVideoDeviceModelId());
		devconf.writePathEntry("Path",dev->getVideoDevicePath());
		devconf.writeEntry("FormatIndex",dev->getFormatIndex());
		devconf.writeEntry("CtrlBrightnessValue",dev->getBrightness());
		devconf.writeEntry("CtrlBrightnessVisible",dev->getBrightnessVisible());
		devconf.writeEntry("CtrlContrastValue",dev->getContrast());
		devconf.writeEntry("CtrlContrastVisible",dev->getContrastVisible());
		devconf.writeEntry("CtrlSharpnessValue",dev->getSharpness());
		devconf.writeEntry("CtrlSharpnessVisible",dev->getSharpnessVisible());
		devconf.writeEntry("CtrlSaturationValue",dev->getSaturation());
		devconf.writeEntry("CtrlSaturationVisible",dev->getSaturationVisible());
		devconf.writeEntry("CtrlAbsoluteZoomValue",dev->getAbsoluteZoom());
		devconf.writeEntry("CtrlAbsoluteZoomVisible",dev->getAbsoluteZoomVisible());
		devconf.writeEntry("CtrlAutoFocusValue",dev->getAutoFocus());
		devconf.writeEntry("CtrlAutoFocusVisible",dev->getAutoFocusVisible());
		devconf.writeEntry("CtrlAbsoluteFocusValue",dev->getFocus());
		devconf.writeEntry("CtrlAbsoluteFocusVisible",dev->getFocusVisible());
		devconf.writeEntry("UdevRule",udevrule);
		devconf.config()->sync();
		qCDebug(webcam_settings_kcm) << "QWebcamSettings::save Saved data from camera " << devconf.readEntry("Name");
    }
	config.sync();

	QStringList config_grouplist = config.groupList();
	for (QString & devserial: config_grouplist){
		KConfigGroup udevconf(&config, devserial);
		udevrules << udevconf.readEntry("UdevRule").simplified();
	}

	//build udev rule file
	QVariantMap args;
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

	m_current_device->applyConfiguration();

}

void QWebcamSettings::load() {
	qCDebug(webcam_settings_kcm) << "QWebcamSettings::load load settings from config";
    KConfig config("kcmwebcamsettingsrc");
	for (VideoDevice * dev : m_device_list)
    {
		if (config.groupList().contains(dev->getVideoDeviceSerialId())){
			KConfigGroup devconf(&config, dev->getVideoDeviceSerialId());
			if(dev->setBrightness(devconf.readEntry("CtrlBrightnessValue").toDouble())){Q_EMIT brightnessChanged();}
			if(dev->setContrast(devconf.readEntry("CtrlContrastValue").toDouble())){Q_EMIT contrastChanged();}
			if(dev->setSharpness(devconf.readEntry("CtrlSharpnessValue").toDouble())){Q_EMIT sharpnessChanged();}
			if(dev->setSaturation(devconf.readEntry("CtrlSaturationValue").toDouble())){Q_EMIT saturationChanged();}
			if(dev->setAbsoluteZoom(devconf.readEntry("CtrlAbsoluteZoomValue").toDouble())){Q_EMIT absoluteZoomChanged();}
			if(dev->setAutoFocus(devconf.readEntry("CtrlAutoFocusValue").toInt())){Q_EMIT autoFocusChanged();}
			if(dev->setFocus(devconf.readEntry("CtrlAbsoluteFocusValue").toInt())){Q_EMIT focusChanged();}
			if(dev->setFormatIndex(devconf.readEntry("FormatIndex").toInt())){Q_EMIT formatIndexChanged();}
		}
	}
	setNeedsSave(false);
	
}

void QWebcamSettings::defaults() {
	qCDebug(webcam_settings_kcm) << "QWebcamSettings::defaults reset to default settings";
	bool save_needed = m_current_device->resetToDefault();
	Q_EMIT absoluteZoomChanged();
	Q_EMIT brightnessChanged();
	Q_EMIT contrastChanged();
	Q_EMIT saturationChanged();
	Q_EMIT sharpnessChanged();
	Q_EMIT autoFocusChanged();
	Q_EMIT focusChanged();
	if (save_needed){setNeedsSave(true);}
}

void QWebcamSettings::populateDeviceList() {
    QString vendorid,modelid,serial;
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
			if (line.contains(QString::fromStdString("ID_SERIAL="))){
				serial = QString::fromStdString(get_str_right_of_substr(line.toStdString(),std::string("=")));
				qCDebug(webcam_settings_kcm) << "Found ID_SERIAL=" << serial;
			}
		}
		if (!m_devicename_list.contains(cameraInfo.description())){
			if (!m_config_grouplist.contains(serial)){
				VideoDevice* new_device = new VideoDevice(serial,cameraInfo.description(),cameraInfo.deviceName(),vendorid,modelid);
				m_device_list.append(new_device);
				// m_device_list.append(VideoDevice(serial,cameraInfo.description(),cameraInfo.deviceName(),vendorid,modelid));
				m_devicename_list << cameraInfo.description();
			}
		}
	}
	if (cameras.size() == 0){
		m_devices_available = false;
		VideoDevice* new_device = new VideoDevice();
		m_device_list.append(new_device);
		qCDebug(webcam_settings_kcm) << "QWebcamSettings::populateDeviceList No device was found.";
		m_devicename_list << QString("No Video4Linux Device Was Found On The System");
		setDeviceIndex(0);
	} else {
		m_devices_available = true;
		setDeviceIndex(0);
		qCDebug(webcam_settings_kcm) << "QWebcamSettings::populateDeviceList current format index = " << m_current_device->getFormatIndex() << "autofocus" << m_current_device->getAutoFocus();
	}
	m_devicename_list_model->setStringList(m_devicename_list);
}

QStringListModel* QWebcamSettings::getDeviceList(){
	this->engine()->rootContext()->setContextProperty("device_list_model", m_devicename_list_model);
	return m_devicename_list_model;
}

QString QWebcamSettings::getSelectedDeviceName(){
	qCDebug(webcam_settings_kcm) << "QWebcamSettings::getSelectedDeviceName " << m_current_device->getVideoDeviceName();
	return m_current_device->getVideoDeviceName().simplified();
}

QString QWebcamSettings::getSelectedDevicePath(){
	return m_current_device->getVideoDevicePath().simplified();
}

QString QWebcamSettings::getSelectedDeviceVendorId(){
	return m_current_device->getVideoDeviceVendorId().simplified();
}

QString QWebcamSettings::getSelectedDeviceModelId(){
	return m_current_device->getVideoDeviceModelId().simplified();
}

VideoDevice* QWebcamSettings::getDeviceFromIndex(int index) {
	qCDebug(webcam_settings_kcm) << "QWebcamSettings::getDeviceFromIndex";
    int i = 0;
	VideoDevice *device;
    for (VideoDevice * dev : m_device_list)
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
	qCDebug(webcam_settings_kcm) << "QWebcamSettings::setDeviceIndex " << devindex;
	m_device_index = devindex;
	m_current_device = getDeviceFromIndex(devindex);
	m_format_index = m_current_device->getFormatIndex();
	qCDebug(webcam_settings_kcm) << "Selected device " << this->m_current_device->getVideoDeviceName();
	qCDebug(webcam_settings_kcm) << "format index " << this->m_current_device->getFormatIndex();
	Q_EMIT deviceIndexChanged();
	Q_EMIT formatIndexChanged();
	Q_EMIT absoluteZoomChanged();
	Q_EMIT brightnessChanged();
	Q_EMIT contrastChanged();
	Q_EMIT saturationChanged();
	Q_EMIT sharpnessChanged();
	Q_EMIT autoFocusChanged();
	Q_EMIT focusChanged();


}

void QWebcamSettings::setFormatIndex(int fmtindex) {
	bool save_needed = this->m_current_device->setFormatIndex(fmtindex);
	Q_EMIT formatIndexChanged();
	if (save_needed){setNeedsSave(true);}
	qCDebug(webcam_settings_kcm) << "QWebcamSettings::setFormatIndex "<< fmtindex << m_current_device->getCurrentFormatName() << m_current_device->getCurrentFormatWidth() << m_current_device->getCurrentFormatHeight();
}

void QWebcamSettings::setAbsoluteZoom(double zoom) {
	qCDebug(webcam_settings_kcm) << "QWebcamSettings::setAbsoluteZoom value: " << QString::number(zoom);
	bool save_needed = m_current_device->setAbsoluteZoom(zoom);
	Q_EMIT absoluteZoomChanged();
	if (save_needed){setNeedsSave(true);}
}

void QWebcamSettings::setBrightness(double brightness) {
	qCDebug(webcam_settings_kcm) << "QWebcamSettings::setBrightness value: " << QString::number(brightness);
	bool save_needed = m_current_device->setBrightness(brightness);
	Q_EMIT brightnessChanged();
	if (save_needed){setNeedsSave(true);}
}

void QWebcamSettings::setContrast(double contrast) {
	qCDebug(webcam_settings_kcm) << "QWebcamSettings::setContrast value: " << QString::number(contrast);
	bool save_needed = m_current_device->setContrast(contrast);
	Q_EMIT contrastChanged();
	if (save_needed){setNeedsSave(true);}
}

void QWebcamSettings::setSharpness(double sharpness) {
	qCDebug(webcam_settings_kcm) << "QWebcamSettings::setSharpness value: " << QString::number(sharpness);
	bool save_needed = m_current_device->setSharpness(sharpness);
	Q_EMIT sharpnessChanged();
	if (save_needed){setNeedsSave(true);}
}

void QWebcamSettings::setSaturation(double saturation) {
	qCDebug(webcam_settings_kcm) << "QWebcamSettings::setSaturation value: " << QString::number(saturation);
	bool save_needed = m_current_device->setSaturation(saturation);
	Q_EMIT saturationChanged();
	if (save_needed){setNeedsSave(true);}
}

void QWebcamSettings::setAutoFocus(int autofocus) {
	qCDebug(webcam_settings_kcm) << "QWebcamSettings::setAutoFocus value: " << QString::number(autofocus);
	bool save_needed = this->m_current_device->setAutoFocus(autofocus);
	Q_EMIT autoFocusChanged();
	if (save_needed){setNeedsSave(true);}
}

void QWebcamSettings::setFocus(double focus) {
	qCDebug(webcam_settings_kcm) << "QWebcamSettings::setFocus value: " << QString::number(focus);
	bool save_needed = m_current_device->setFocus(focus);
	Q_EMIT focusChanged();
	if (save_needed){setNeedsSave(true);}
}

void QWebcamSettings::resetCrtlToDefault(QString ctrl_name) {
	qCDebug(webcam_settings_kcm) << "QWebcamSettings::resetCrtlToDefault";
    bool ret = false;
	ret = m_current_device->resetCrtlToDefault(ctrl_name);
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
    if (ctrl_name == "focus_automatic_continuous") {
		if (ret) {Q_EMIT autoFocusChanged();}
    }
    if (ctrl_name == "focus_absolute") {
		if (ret) {Q_EMIT focusChanged();}
    }
	if (ret) {setNeedsSave(true);}
}


#include "QWebcamSettings.moc"
