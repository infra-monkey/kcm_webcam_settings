#include "VideoDevice.h"
#include "helpers.h"
#include <QString>
#include <QStringList>

VideoDevice::VideoDevice() {
    printf("Video Device Creator called\n");
}
VideoDevice::~VideoDevice() {}

void VideoDevice::setVideoDevicePath(QString path) {
    bool path_exists = false;
    for (QString & devpath : m_device_paths)
    {
        if ( devpath == path ) {
            path_exists = true;
        }
    }
    if (!path_exists){
        QString devpath = QString(path);
        m_device_paths.append(devpath);
    }
    if (m_device_paths.size() == 1) {
        m_device_path = m_device_paths.at(0);
    }
}
void VideoDevice::setAbsoluteZoom(double value) {
    m_ctrl_zoom_absolute.setValue(value);
}
double VideoDevice::getAbsoluteZoom() {
    m_zoom_absolute = m_ctrl_zoom_absolute.getValue();
    return m_zoom_absolute;
}
double VideoDevice::getAbsoluteZoomMin() {
    m_zoom_absolute_min = m_ctrl_zoom_absolute.getValueMin();
    return m_zoom_absolute_min;
}
double VideoDevice::getAbsoluteZoomMax() {
    m_zoom_absolute_max = m_ctrl_zoom_absolute.getValueMax();
    return m_zoom_absolute_max;
}
double VideoDevice::getAbsoluteZoomStep() {
    m_zoom_absolute_step = m_ctrl_zoom_absolute.getValueStep();
    return m_zoom_absolute_step;
}


void VideoDevice::initializeCtrls() {
    printf("Create controls for %s\n",m_device_path.toStdString().c_str());
    m_ctrl_brightness = VideoDeviceCtrl(m_device_path.toStdString(),"brightness");
    m_ctrl_contrast = VideoDeviceCtrl(m_device_path.toStdString(),"contrast");
    m_ctrl_sharpness = VideoDeviceCtrl(m_device_path.toStdString(),"sharpness");
    m_ctrl_saturation = VideoDeviceCtrl(m_device_path.toStdString(),"saturation");
    m_ctrl_zoom_absolute = VideoDeviceCtrl(m_device_path.toStdString(),"zoom_absolute");
}


void VideoDevice::printVideoDeviceInfo() {
    printf("Name : %s\n", m_device_name.toStdString().c_str());
    printf("Bus info : %s\n", m_device_bus_info.toStdString().c_str());
    printf("Paths :\n");
    for (QString & devpath : m_device_paths)
    {
        printf("\t%s\n",devpath.toStdString().c_str());
    }
}


