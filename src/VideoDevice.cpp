#include "VideoDevice.h"
#include "helpers.h"
#include <QString>
#include <QStringList>

VideoDevice::VideoDevice() {
}
VideoDevice::VideoDevice(QString device_name, QString device_path, QString device_vendorid, QString device_modelid) {
    m_device_name = QString(device_name);
    m_device_vendor_id = QString(device_vendorid);
    m_device_model_id = QString(device_modelid);
    m_device_path = QString(device_path);
    qCDebug(webcam_settings_kcm) << "VideoDevice::VideoDevice" << m_device_name << m_device_path << m_device_vendor_id << m_device_model_id;
    initializeCtrls();
    initializeFormats();
}
VideoDevice::~VideoDevice() {}

void VideoDevice::initializeCtrls() {
	qCDebug(webcam_settings_kcm) << "VideoDevice::initializeCtrls";
    for (const QString & label: m_ctrl_list){
        initializeCtrl(label);
    }
}

void VideoDevice::initializeCtrl(const QString ctrl_label) {
	qCDebug(webcam_settings_kcm) << "VideoDevice::initializeCtrl for device " << m_device_name;
    bool is_defined;
    std::string cmd = std::string("v4l2-ctl -d " + m_device_path.toStdString() + " --list-ctrls | grep " + ctrl_label.toStdString());
    std::string line = exec_cmd(cmd);
    if (line.size() == 0) {
        is_defined = false;
        return;
    } else {
        is_defined = true;
    }
    if (ctrl_label == "brightness") {
        m_ctrl_brightness["value"] = static_cast<double>(stoi(get_str_between_two_str(line,std::string("value="),std::string(" "))));
        m_ctrl_brightness["default"] = static_cast<double>(stoi(get_str_between_two_str(line,std::string("default="),std::string(" "))));
        m_ctrl_brightness["min"] = static_cast<double>(stoi(get_str_between_two_str(line,std::string("min="),std::string(" "))));
        m_ctrl_brightness["max"] = static_cast<double>(stoi(get_str_between_two_str(line,std::string("max="),std::string(" "))));
        m_ctrl_brightness["step"] = static_cast<double>(stoi(get_str_between_two_str(line,std::string("step="),std::string(" "))));
        m_ctrl_brightness_visible = is_defined;
        qCDebug(webcam_settings_kcm) << "VideoDevice::initializeCtrl Brightness: value: " << QString::number(m_ctrl_brightness["value"])
            << "min: " << m_ctrl_brightness["min"]
            << "max: " << m_ctrl_brightness["max"]
            << "step: " << m_ctrl_brightness["step"]
            << "default: " << m_ctrl_brightness["default"];
    }
    if (ctrl_label == "contrast") {
        m_ctrl_contrast["value"] = static_cast<double>(stoi(get_str_between_two_str(line,std::string("value="),std::string(" "))));
        m_ctrl_contrast["default"] = static_cast<double>(stoi(get_str_between_two_str(line,std::string("default="),std::string(" "))));
        m_ctrl_contrast["min"] = static_cast<double>(stoi(get_str_between_two_str(line,std::string("min="),std::string(" "))));
        m_ctrl_contrast["max"] = static_cast<double>(stoi(get_str_between_two_str(line,std::string("max="),std::string(" "))));
        m_ctrl_contrast["step"] = static_cast<double>(stoi(get_str_between_two_str(line,std::string("step="),std::string(" "))));
        m_ctrl_contrast_visible = is_defined;
        qCDebug(webcam_settings_kcm) << "VideoDevice::initializeCtrl Contrast: value: " << QString::number(m_ctrl_contrast["value"])
            << "min: " << m_ctrl_contrast["min"]
            << "max: " << m_ctrl_contrast["max"]
            << "step: " << m_ctrl_contrast["step"]
            << "default: " << m_ctrl_contrast["default"];
    }
    if (ctrl_label == "sharpness") {
        m_ctrl_sharpness["value"] = static_cast<double>(stoi(get_str_between_two_str(line,std::string("value="),std::string(" "))));
        m_ctrl_sharpness["default"] = static_cast<double>(stoi(get_str_between_two_str(line,std::string("default="),std::string(" "))));
        m_ctrl_sharpness["min"] = static_cast<double>(stoi(get_str_between_two_str(line,std::string("min="),std::string(" "))));
        m_ctrl_sharpness["max"] = static_cast<double>(stoi(get_str_between_two_str(line,std::string("max="),std::string(" "))));
        m_ctrl_sharpness["step"] = static_cast<double>(stoi(get_str_between_two_str(line,std::string("step="),std::string(" "))));
        m_ctrl_sharpness_visible = is_defined;
        qCDebug(webcam_settings_kcm) << "VideoDevice::initializeCtrl Sharpness: value: " << QString::number(m_ctrl_sharpness["value"])
            << "min: " << m_ctrl_sharpness["min"]
            << "max: " << m_ctrl_sharpness["max"]
            << "step: " << m_ctrl_sharpness["step"]
            << "default: " << m_ctrl_sharpness["default"];
    }
    if (ctrl_label == "saturation") {
        m_ctrl_saturation["value"] = static_cast<double>(stoi(get_str_between_two_str(line,std::string("value="),std::string(" "))));
        m_ctrl_saturation["default"] = static_cast<double>(stoi(get_str_between_two_str(line,std::string("default="),std::string(" "))));
        m_ctrl_saturation["min"] = static_cast<double>(stoi(get_str_between_two_str(line,std::string("min="),std::string(" "))));
        m_ctrl_saturation["max"] = static_cast<double>(stoi(get_str_between_two_str(line,std::string("max="),std::string(" "))));
        m_ctrl_saturation["step"] = static_cast<double>(stoi(get_str_between_two_str(line,std::string("step="),std::string(" "))));
        m_ctrl_saturation_visible = is_defined;
        qCDebug(webcam_settings_kcm) << "VideoDevice::initializeCtrl Saturation: value: " << QString::number(m_ctrl_saturation["value"])
            << "min: " << m_ctrl_saturation["min"]
            << "max: " << m_ctrl_saturation["max"]
            << "step: " << m_ctrl_saturation["step"]
            << "default: " << m_ctrl_saturation["default"];
    }
    if (ctrl_label == "zoom_absolute") {
        m_ctrl_zoom_absolute["value"] = static_cast<double>(stoi(get_str_between_two_str(line,std::string("value="),std::string(" "))));
        m_ctrl_zoom_absolute["default"] = static_cast<double>(stoi(get_str_between_two_str(line,std::string("default="),std::string(" "))));
        m_ctrl_zoom_absolute["min"] = static_cast<double>(stoi(get_str_between_two_str(line,std::string("min="),std::string(" "))));
        m_ctrl_zoom_absolute["max"] = static_cast<double>(stoi(get_str_between_two_str(line,std::string("max="),std::string(" "))));
        m_ctrl_zoom_absolute["step"] = static_cast<double>(stoi(get_str_between_two_str(line,std::string("step="),std::string(" "))));
        m_ctrl_zoom_absolute_visible = is_defined;
        qCDebug(webcam_settings_kcm) << "VideoDevice::initializeCtrl Zoom Absolute: value: " << QString::number(m_ctrl_zoom_absolute["value"])
            << "min: " << m_ctrl_zoom_absolute["min"]
            << "max: " << m_ctrl_zoom_absolute["max"]
            << "step: " << m_ctrl_zoom_absolute["step"]
            << "default: " << m_ctrl_zoom_absolute["default"];
    }
}

void VideoDevice::initializeFormats() {
	qCDebug(webcam_settings_kcm) << "VideoDevice::initializeFormats";
    qCDebug(webcam_settings_kcm) << "Initializing pixel formats for video device with path " << m_device_path;
    

    std::string cmd;
    cmd = std::string("v4l2-ctl -d " + m_device_path.toStdString() + " --get-fmt-video | grep \"Pixel Format\"");
    std::string current_fmt = get_str_between_two_str(exec_cmd(cmd)," \'","\' ");
    cmd = std::string("v4l2-ctl -d " + m_device_path.toStdString() + " --list-formats | grep \"\\[\"");
    QStringList output = QString::fromStdString(exec_cmd(cmd)).split(QLatin1Char('\n'));
    for (QString & line : output){
        if (line.length() == 0){break;}
        QString fmt = QString::fromStdString(get_str_between_two_str(line.toStdString().c_str()," \'","\' ")).simplified();

        cmd = std::string("v4l2-ctl -d " + m_device_path.toStdString() + " --list-framesizes " + fmt.toStdString() + " | grep Size");
        QStringList output2 = QString::fromStdString(exec_cmd(cmd)).split(QLatin1Char('\n'));
        for (QString & line2 : output2){
            if (line2.length() == 0){break;}
            QString res = QString::fromStdString(get_str_right_of_substr(line2.simplified().trimmed().toStdString(),"Discrete ")).simplified();
            QString width = QString::fromStdString(get_str_left_of_substr(res.toStdString(),"x"));
            QString height = QString::fromStdString(get_str_right_of_substr(res.toStdString(),"x"));
            QStringList list = QStringList();
            list << fmt << width << height;
            m_device_formats << list;
            m_format_list << QString(fmt + " - " + width + "x" + height);
        }
    }
}

void VideoDevice::setFormatIndex(int fmtindex){
	qCDebug(webcam_settings_kcm) << "VideoDevice::setFormatIndex";
    m_current_format_index = fmtindex;
    m_current_fmt = m_format_list.at(fmtindex);
}


double VideoDevice::getCtrlDefaultValue(QString ctrl_name) {
    double default_value;
    if (ctrl_name == "brightness") {
        default_value = m_ctrl_brightness["default"];
    }
    if (ctrl_name == "contrast") {
        default_value = m_ctrl_contrast["default"];
    }
    if (ctrl_name == "sharpness") {
        default_value = m_ctrl_sharpness["default"];
    }
    if (ctrl_name == "saturation") {
        default_value = m_ctrl_saturation["default"];
    }
    if (ctrl_name == "zoom_absolute") {
        default_value = m_ctrl_zoom_absolute["default"];
    }
    return default_value;
}

bool VideoDevice::setBrightness(double value){
    qCDebug(webcam_settings_kcm) << "VideoDevice::setBrightness" << value;
    bool save_needed = false;
    if (value != m_ctrl_brightness["value"]){save_needed = true;}
    m_ctrl_brightness["value"] = value;
    return save_needed;
}

bool VideoDevice::setContrast(double value){
    qCDebug(webcam_settings_kcm) << "VideoDevice::setContrast" << value;
    bool save_needed = false;
    if (value != m_ctrl_contrast["value"]){save_needed = true;}
    m_ctrl_contrast["value"] = value;
    return save_needed;
}

bool VideoDevice::setSharpness(double value){
    qCDebug(webcam_settings_kcm) << "VideoDevice::setSharpness" << value;
    bool save_needed = false;
    if (value != m_ctrl_sharpness["value"]){save_needed = true;}
    m_ctrl_sharpness["value"] = value;
    return save_needed;
}

bool VideoDevice::setSaturation(double value){
    qCDebug(webcam_settings_kcm) << "VideoDevice::setSaturation" << value;
    bool save_needed = false;
    if (value != m_ctrl_saturation["value"]){save_needed = true;}
    m_ctrl_saturation["value"] = value;
    return save_needed;
}

bool VideoDevice::setAbsoluteZoom(double value){
    qCDebug(webcam_settings_kcm) << "VideoDevice::setAbsoluteZoom" << value;
    bool save_needed = false;
    if (value != m_ctrl_zoom_absolute["value"]){save_needed = true;}
    m_ctrl_zoom_absolute["value"] = value;
    return save_needed;
}

bool VideoDevice::resetCrtlToDefault(QString ctrl_name) {
	qCDebug(webcam_settings_kcm) << "VideoDevice::resetCrtlToDefault" << ctrl_name;
    bool ret = false;
	if (ctrl_name == "brightness") {
		ret = setBrightness(m_ctrl_brightness["default"]);
    }
    if (ctrl_name == "contrast") {
		ret = setContrast(m_ctrl_contrast["default"]);
    }
    if (ctrl_name == "sharpness") {
		ret = setSharpness(m_ctrl_sharpness["default"]);
    }
    if (ctrl_name == "saturation") {
		ret = setSaturation(m_ctrl_saturation["default"]);
    }
    if (ctrl_name == "zoom_absolute") {
		ret = setAbsoluteZoom(m_ctrl_zoom_absolute["default"]);
    }
    return ret;
}

// void VideoDevice::applyResolution(){
// 	qCDebug(webcam_settings_kcm) << "VideoDevice::applyResolution";
// 	//m_current_fmt.applyResolution();
// }

bool VideoDevice::resetToDefault(){
	qCDebug(webcam_settings_kcm) << "VideoDevice::resetToDefault";
    bool ret = false;
    for (const QString & label: m_ctrl_list){
        if (resetCrtlToDefault(label)){ret = true;}
    }
    return ret;
}

// QString VideoDevice::getUdevRule(){
// 	qCDebug(webcam_settings_kcm) << "VideoDevice::getUdevRules";
//     QStringList udevrule;
//     bool first_control = true;
//     qCDebug(webcam_settings_kcm) << "VideoDevice::getUdevRules for device" << getVideoDevicePath() << getVideoDeviceVendorId() << getVideoDeviceModelId();
//     qCDebug(webcam_settings_kcm) << "VideoDevice::getUdevRules resolution" << getCurrentFormatName() << getCurrentFormatWidth() << getCurrentFormatHeight();
// QString rule = "SUBSYSTEMS==\"usb\", ATTRS{idVendor}==\"" + getVideoDeviceVendorId() + "\", ATTRS{idProduct}==\"" + getVideoDeviceModelId() + "\", PROGRAM=\"/usr/bin/v4l2-ctl --set-ctrl ";
//     if (getAbsoluteZoomVisible()) {
//         if (!first_control){rule.append(",");}
//         rule.append("zoom_absolute=" + QString::number(getAbsoluteZoom()));
//         first_control=false;
//         }
//     if (getBrightnessVisible()) {
//         if (!first_control){rule.append(",");}
//         rule.append("brightness=" + QString::number(getBrightness()));
//         first_control=false;
//         }
//     if (getContrastVisible()) {
//         if (!first_control){rule.append(",");}
//         rule.append("contrast=" + QString::number(getContrast()));
//         first_control=false;
//     }
//     if (getSaturationVisible()) {
//         if (!first_control){rule.append(",");}
//         rule.append("saturation=" + QString::number(getSaturation()));
//         first_control=false;
//     }
//     if (getSharpnessVisible()) {
//         if (!first_control){rule.append(",");}
//         rule.append("sharpness=" + QString::number(getSharpness()));
//         first_control=false;
//     }
//     rule.append(" --set-fmt-video width=" + QString::number(getCurrentFormatWidth()) + ",height=" + QString::number(getCurrentFormatHeight()) + ",pixelformat=" + getCurrentFormatName() + ",field=none --device /dev/%k\"");
//     qCDebug(webcam_settings_kcm) << "Udev rule : " << rule;
//     return rule;
// }