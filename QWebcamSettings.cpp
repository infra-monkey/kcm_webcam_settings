/**
 * SPDX-FileCopyrightText: Year Author <author@domain.com>
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#include "QWebcamSettings.h"
#include <KPluginFactory>
#include <KLocalizedString>
#include <KAboutData>
#include <iostream>
#include <KSharedConfig>
#include <KConfigGroup>


K_PLUGIN_CLASS_WITH_JSON(QWebcamSettings, "metadata.json")


std::string exec_cmd(const std::string& command) {
    system((command + " > temp.txt").c_str());
 
    std::ifstream ifs("temp.txt");
    std::string ret{ std::istreambuf_iterator<char>(ifs), std::istreambuf_iterator<char>() };
    ifs.close(); // must close the inout stream so the file can be cleaned up
    if (std::remove("temp.txt") != 0) {
        perror("Error deleting temporary file");
    }
    return ret;
}

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
		//printf("%s\n",qline.toStdString().c_str());
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


int QWebcamSettings::getDeviceIndex() {
	return m_device_index;
}
void QWebcamSettings::setDeviceIndex(int devindex) {
	printf("Device index is changed to %i\n",devindex);
	m_device_index = devindex;
}
void deviceIndexChanged(int devindex) {
	printf("Device index is changed to %i\n",devindex);

}



#include "QWebcamSettings.moc"
