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

static const char *prefixes[] = {
	"video",
	"radio",
	"vbi",
	"swradio",
	"v4l-subdev",
	"v4l-touch",
	"media",
	nullptr
};

static int calc_node_val(const char *s)
{
	int n = 0;

	s = strrchr(s, '/') + 1;

	for (unsigned i = 0; prefixes[i]; i++) {
		unsigned l = strlen(prefixes[i]);

		if (!memcmp(s, prefixes[i], l)) {
			n = i << 8;
			n += atol(s + l);
			return n;
		}
	}
	return 0;
}

static bool sort_on_device_name(const std::string &s1, const std::string &s2)
{
	int n1 = calc_node_val(s1.c_str());
	int n2 = calc_node_val(s2.c_str());

	return n1 < n2;
}

static bool is_v4l_dev(const char *name)
{
	for (unsigned i = 0; prefixes[i]; i++) {
		unsigned l = strlen(prefixes[i]);

		if (!memcmp(name, prefixes[i], l)) {
			if (isdigit(name[l]))
				return true;
		}
	}
	return false;
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
    populateDeviceList(m_device_list);
    setAboutData(aboutData);
    setButtons(Apply | Default);
}

void QWebcamSettings::populateDeviceList(VideoDeviceList devlist) {
    DIR *dp;
	struct dirent *ep;
	dev_vec files;
	dev_map links;
	dev_map cards;
	struct v4l2_capability vcap;

	dp = opendir("/dev");
	if (dp == nullptr) {
		perror ("Couldn't open the directory");
		return;
	}
	while ((ep = readdir(dp)))
		if (is_v4l_dev(ep->d_name))
			files.push_back(std::string("/dev/") + ep->d_name);
	closedir(dp);

	/* Find device nodes which are links to other device nodes */
	for (auto iter = files.begin();
			iter != files.end(); ) {
		char link[64+1];
		int link_len;
		std::string target;

		link_len = readlink(iter->c_str(), link, 64);
		if (link_len < 0) {	/* Not a link or error */
			iter++;
			continue;
		}
		link[link_len] = '\0';

		/* Only remove from files list if target itself is in list */
		if (link[0] != '/')	/* Relative link */
			target = std::string("/dev/");
		target += link;
		if (find(files.begin(), files.end(), target) == files.end()) {
			iter++;
			continue;
		}

		/* Move the device node from files to links */
		if (links[target].empty())
			links[target] = *iter;
		else
			links[target] += ", " + *iter;
		iter = files.erase(iter);
	}

	std::sort(files.begin(), files.end(), sort_on_device_name);

	for (const auto &file : files) {
		int fd = open(file.c_str(), O_RDWR);
		std::string bus_info;
		std::string card;

		if (fd < 0)
			continue;
		int err = ioctl(fd, VIDIOC_QUERYCAP, &vcap);
		if (err) {
			struct media_device_info mdi;

			err = ioctl(fd, MEDIA_IOC_DEVICE_INFO, &mdi);
			if (!err) {
				if (mdi.bus_info[0])
					bus_info = mdi.bus_info;
				else
					bus_info = std::string("platform:") + mdi.driver;
				if (mdi.model[0])
					card = mdi.model;
				else
					card = mdi.driver;
			}
		} else {
			bus_info = reinterpret_cast<const char *>(vcap.bus_info);
			card = reinterpret_cast<const char *>(vcap.card);
		}
		devlist.addVideoDevice(QString::fromStdString(card),QString::fromStdString(bus_info),QString::fromStdString(file));
        
		close(fd);
		if (err)
			continue;
	}
	devlist.printVideoDeviceInfo();
	m_devname_list = getDeviceList();
}

QStringList QWebcamSettings::getDeviceList(){
	return m_device_list.getDeviceNameList();
}



#include "QWebcamSettings.moc"
