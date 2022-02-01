#include "VideoDevice.h"
#include "helpers.h"
#include <QString>
#include <QStringList>

VideoDevice::VideoDevice() {
}
VideoDevice::~VideoDevice() {}

void VideoDevice::setVideoDevicePath(QString path) {
	qCDebug(webcam_settings_kcm) << "VideoDevice::setVideoDevicePath";
    
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
        qCDebug(webcam_settings_kcm) << "Add path " << path << "to video device.";
    }
    if (m_device_paths.size() == 1) {
        m_device_path = m_device_paths.at(0);
    }
}

void VideoDevice::setVideoDeviceName(QString devname){
	qCDebug(webcam_settings_kcm) << "VideoDevice::setVideoDeviceName";
    qCDebug(webcam_settings_kcm) << "Set device name " << devname << " for video device with path " << m_device_path;
    m_device_name = QString(devname);
}

void VideoDevice::setVideoDeviceSerialId(QString devserial){
	qCDebug(webcam_settings_kcm) << "VideoDevice::setVideoDeviceSerialId";
    qCDebug(webcam_settings_kcm) << "Set serial id " << devserial << " for video device with path " << m_device_path;
    m_device_serial_id = QString(devserial);
}

void VideoDevice::setVideoDeviceVendorId(QString devvendorid){
	qCDebug(webcam_settings_kcm) << "VideoDevice::setVideoDeviceVendorId";
    qCDebug(webcam_settings_kcm) << "Set vendor id " << devvendorid << " for video device with path " << m_device_path;
    m_device_vendor_id = QString(devvendorid);
}

void VideoDevice::setVideoDeviceModelId(QString devmodelid){
	qCDebug(webcam_settings_kcm) << "VideoDevice::setVideoDeviceModelId";
    qCDebug(webcam_settings_kcm) << "Set model id " << devmodelid << " for video device with path " << m_device_path;
    m_device_model_id = QString(devmodelid);
}

bool VideoDevice::setBrightness(double value) {
	qCDebug(webcam_settings_kcm) << "VideoDevice::setBrightness";
    return m_ctrl_brightness.setValue(value);
}
double VideoDevice::getBrightness() {
    m_brightness = m_ctrl_brightness.getValue();
    return m_brightness;
}
double VideoDevice::getBrightnessMin() {
    m_brightness_min = m_ctrl_brightness.getValueMin();
    return m_brightness_min;
}
double VideoDevice::getBrightnessMax() {
    m_brightness_max = m_ctrl_brightness.getValueMax();
    return m_brightness_max;
}
double VideoDevice::getBrightnessStep() {
    m_brightness_step = m_ctrl_brightness.getValueStep();
    return m_brightness_step;
}
bool VideoDevice::getBrightnessVisible() {
    m_brightness_visible = m_ctrl_brightness.getEnabled();
    return m_brightness_visible;
}

bool VideoDevice::setContrast(double value) {
	qCDebug(webcam_settings_kcm) << "VideoDevice::setContrast";
    return m_ctrl_contrast.setValue(value);
}
double VideoDevice::getContrast() {
    m_contrast = m_ctrl_contrast.getValue();
    return m_contrast;
}
double VideoDevice::getContrastMin() {
    m_contrast_min = m_ctrl_contrast.getValueMin();
    return m_contrast_min;
}
double VideoDevice::getContrastMax() {
    m_contrast_max = m_ctrl_contrast.getValueMax();
    return m_contrast_max;
}
double VideoDevice::getContrastStep() {
    m_contrast_step = m_ctrl_contrast.getValueStep();
    return m_contrast_step;
}
bool VideoDevice::getContrastVisible() {
    m_contrast_visible = m_ctrl_contrast.getEnabled();
    return m_contrast_visible;
}

bool VideoDevice::setSaturation(double value) {
	qCDebug(webcam_settings_kcm) << "VideoDevice::setSaturation";
    return m_ctrl_saturation.setValue(value);
}
double VideoDevice::getSaturation() {
    m_saturation = m_ctrl_saturation.getValue();
    return m_saturation;
}
double VideoDevice::getSaturationMin() {
    m_saturation_min = m_ctrl_saturation.getValueMin();
    return m_saturation_min;
}
double VideoDevice::getSaturationMax() {
    m_saturation_max = m_ctrl_saturation.getValueMax();
    return m_saturation_max;
}
double VideoDevice::getSaturationStep() {
    m_saturation_step = m_ctrl_saturation.getValueStep();
    return m_saturation_step;
}
bool VideoDevice::getSaturationVisible() {
    m_saturation_visible = m_ctrl_saturation.getEnabled();
    return m_saturation_visible;
}

bool VideoDevice::setSharpness(double value) {
	qCDebug(webcam_settings_kcm) << "VideoDevice::setSharpness";
    return m_ctrl_sharpness.setValue(value);
}
double VideoDevice::getSharpness() {
    m_sharpness = m_ctrl_sharpness.getValue();
    return m_sharpness;
}
double VideoDevice::getSharpnessMin() {
    m_sharpness_min = m_ctrl_sharpness.getValueMin();
    return m_sharpness_min;
}
double VideoDevice::getSharpnessMax() {
    m_sharpness_max = m_ctrl_sharpness.getValueMax();
    return m_sharpness_max;
}
double VideoDevice::getSharpnessStep() {
    m_sharpness_step = m_ctrl_sharpness.getValueStep();
    return m_sharpness_step;
}
bool VideoDevice::getSharpnessVisible() {
    m_sharpness_visible = m_ctrl_sharpness.getEnabled();
    return m_sharpness_visible;
}

bool VideoDevice::setAbsoluteZoom(double value) {
	qCDebug(webcam_settings_kcm) << "VideoDevice::setAbsoluteZoom";
    return m_ctrl_zoom_absolute.setValue(value);
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
bool VideoDevice::getAbsoluteZoomVisible() {
    m_absolute_zoom_visible = m_ctrl_zoom_absolute.getEnabled();
    return m_absolute_zoom_visible;
}


void VideoDevice::initializeCtrls() {
	qCDebug(webcam_settings_kcm) << "VideoDevice::initializeCtrls";
    qCDebug(webcam_settings_kcm) << "Initializing controls for video device with path " << m_device_path;
    m_ctrl_brightness = VideoDeviceCtrl(m_device_path.toStdString(),"brightness");
    m_ctrl_contrast = VideoDeviceCtrl(m_device_path.toStdString(),"contrast");
    m_ctrl_sharpness = VideoDeviceCtrl(m_device_path.toStdString(),"sharpness");
    m_ctrl_saturation = VideoDeviceCtrl(m_device_path.toStdString(),"saturation");
    m_ctrl_zoom_absolute = VideoDeviceCtrl(m_device_path.toStdString(),"zoom_absolute");
}

void VideoDevice::initializeFormats() {
	qCDebug(webcam_settings_kcm) << "VideoDevice::initializeFormats";
    qCDebug(webcam_settings_kcm) << "Initializing pixel formats for video device with path " << m_device_path;
    std::string cmd;
    int i = 0;
    cmd = std::string("v4l2-ctl -d " + m_device_path.toStdString() + " --get-fmt-video | grep \"Pixel Format\"");
    std::string current_fmt = get_str_between_two_str(exec_cmd(cmd)," \'","\' ");
    cmd = std::string("v4l2-ctl -d " + m_device_path.toStdString() + " --list-formats | grep \"\\[\"");
    QStringList output = QString::fromStdString(exec_cmd(cmd)).split(QLatin1Char('\n'));
    for (QString & line : output){
        if (line.length() == 0){break;}
        QString fmt = QString::fromStdString(get_str_between_two_str(line.toStdString().c_str()," \'","\' ")).simplified();
        qCDebug(webcam_settings_kcm) << m_device_path << "Created format : " << fmt;
        VideoDeviceCapFormat new_fmt = VideoDeviceCapFormat(fmt,m_device_path);
        m_device_formats.push_back(new_fmt);
        m_format_list.append(fmt);
        if (fmt.toStdString() == current_fmt){
            m_current_fmt = new_fmt;
            m_current_format_index = i;
        }
        i++;
    }
	qCDebug(webcam_settings_kcm) << "VideoDevice::initializeFormats format path " << m_current_fmt.getFormatName();
}


QStringList VideoDevice::getResolutionList(){
    int i=0;
    QStringList list;
    for (VideoDeviceCapFormat & fmt : m_device_formats){
        if (i == m_current_format_index){
            list = fmt.getResList();
            break;
        }
        i++;
    }
    return list;
}

void VideoDevice::setResolutionIndex(int resindex){
	qCDebug(webcam_settings_kcm) << "VideoDevice::setResolutionIndex";
    m_current_fmt.setResolutionIndex(resindex);    
    qCDebug(webcam_settings_kcm) << "VideoDevice::setResolutionIndex" << m_device_path << "with format : " << m_current_fmt.getFormatName() << " change resolution to width " << m_current_fmt.getCurrentFormatWidth() << "height" << m_current_fmt.getCurrentFormatHeight();
}

void VideoDevice::setFormatIndex(int fmtindex){
	qCDebug(webcam_settings_kcm) << "VideoDevice::setFormatIndex";
    int i = 0;
    for (VideoDeviceCapFormat & fmt : m_device_formats){
        if (i == fmtindex){
            m_current_fmt = fmt;
            qCDebug(webcam_settings_kcm) << m_device_path << "Changed format to " << m_current_fmt.getFormatName();
        }
        i++;
    }
    m_current_format_index = fmtindex;
}


double VideoDevice::getCtrlDefaultValue(QString ctrl_name) {
    double default_value;
    if (ctrl_name.toStdString() == "brightness") {
        default_value = m_ctrl_brightness.getValueDefault();
    }
    if (ctrl_name.toStdString() == "contrast") {
        default_value = m_ctrl_contrast.getValueDefault();
    }
    if (ctrl_name.toStdString() == "sharpness") {
        default_value = m_ctrl_sharpness.getValueDefault();
    }
    if (ctrl_name.toStdString() == "saturation") {
        default_value = m_ctrl_saturation.getValueDefault();
    }
    if (ctrl_name.toStdString() == "zoom_absolute") {
        default_value = m_ctrl_zoom_absolute.getValueDefault();
    }
    return default_value;
}

void VideoDevice::applyResolution(){
	qCDebug(webcam_settings_kcm) << "VideoDevice::applyResolution";
	m_current_fmt.applyResolution();
}

bool VideoDevice::resetToDefault(){
	qCDebug(webcam_settings_kcm) << "VideoDevice::resetToDefault";
    bool ret = false;
	if (m_ctrl_brightness.resetValueToDefault()){ ret = true;}
    if (m_ctrl_contrast.resetValueToDefault()){ ret = true;}
    if (m_ctrl_sharpness.resetValueToDefault()){ ret = true;}
    if (m_ctrl_saturation.resetValueToDefault()){ ret = true;}
    if (m_ctrl_zoom_absolute.resetValueToDefault()){ ret = true;}
    return ret;
}

QString VideoDevice::getUdevRule(){
	qCDebug(webcam_settings_kcm) << "VideoDevice::getUdevRules";
    QStringList udevrule;
    bool first_control = true;
    qCDebug(webcam_settings_kcm) << "VideoDevice::getUdevRules for device" << getVideoDevicePath() << getVideoDeviceVendorId() << getVideoDeviceModelId();
    qCDebug(webcam_settings_kcm) << "VideoDevice::getUdevRules resolution" << getCurrentFormatName() << getCurrentFormatWidth() << getCurrentFormatHeight();
QString rule = "SUBSYSTEMS==\"usb\", ATTRS{idVendor}==\"" + getVideoDeviceVendorId() + "\", ATTRS{idProduct}==\"" + getVideoDeviceModelId() + "\", PROGRAM=\"/usr/bin/v4l2-ctl --set-ctrl ";
    if (getAbsoluteZoomVisible()) {
        if (!first_control){rule.append(",");}
        rule.append("zoom_absolute=" + QString::number(getAbsoluteZoom()));
        first_control=false;
        }
    if (getBrightnessVisible()) {
        if (!first_control){rule.append(",");}
        rule.append("brightness=" + QString::number(getBrightness()));
        first_control=false;
        }
    if (getContrastVisible()) {
        if (!first_control){rule.append(",");}
        rule.append("contrast=" + QString::number(getContrast()));
        first_control=false;
    }
    if (getSaturationVisible()) {
        if (!first_control){rule.append(",");}
        rule.append("saturation=" + QString::number(getSaturation()));
        first_control=false;
    }
    if (getSharpnessVisible()) {
        if (!first_control){rule.append(",");}
        rule.append("sharpness=" + QString::number(getSharpness()));
        first_control=false;
    }
    rule.append(" --set-fmt-video width=" + QString::number(getCurrentFormatWidth()) + ",height=" + QString::number(getCurrentFormatHeight()) + ",pixelformat=" + getCurrentFormatName() + ",field=none --device /dev/%k\"");
    qCDebug(webcam_settings_kcm) << "Udev rule : " << rule;
    return rule;
}