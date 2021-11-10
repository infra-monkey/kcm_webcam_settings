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
		if (!qline.startsWith(QString::fromStdString("/"))){
			name = qline.left(qline.indexOf(QString::fromStdString("("))).trimmed();

			QString tmp = qline.left(qline.indexOf(QString::fromStdString(")")));
			bus_info = tmp.right(tmp.size() - tmp.indexOf(QString::fromStdString("(")) - 1);
		} else {
			QString file = qline.trimmed();
			devlist.addVideoDevice(name,bus_info,file);
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

void QWebcamSettings::setDeviceIndex(int devindex) {
	printf("Device index is changed to %i\n",devindex);
	m_device_index = devindex;
	m_current_device = m_device_list.getDeviceFromIndex(devindex);
	m_absolute_zoom = m_current_device.getAbsoluteZoom();
	m_absolute_zoom_min = m_current_device.getAbsoluteZoomMin();
	m_absolute_zoom_max = m_current_device.getAbsoluteZoomMax();
	m_absolute_zoom_step = m_current_device.getAbsoluteZoomStep();
	printf("value = %f\n",m_absolute_zoom);
	printf("min = %f\n",m_absolute_zoom_min);
	printf("max = %f\n",m_absolute_zoom_max);
	printf("step = %f\n",m_absolute_zoom_step);
	Q_EMIT absoluteZoomChanged();

}

void QWebcamSettings::setAbsoluteZoom(double zoom) {
	printf("Absolute zoom index is changed to %f\n",zoom);
	m_absolute_zoom = zoom;
	m_current_device.setAbsoluteZoom(zoom);
}


// void deviceIndexChanged(){}
// void absoluteZoomChanged(){}

#include "QWebcamSettings.moc"
