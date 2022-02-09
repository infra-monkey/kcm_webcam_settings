#include "VideoDevice.h"
#include "helpers.h"
#include <QString>
#include <QStringList>

VideoDevice::VideoDevice() {
    qCDebug(webcam_settings_kcm) << "VideoDevice::VideoDevice Creating a dummy device";
    m_device_serial = QString("no_device");
    m_device_name = QString("No Video4Linux Device Was Found On The System");
    m_device_vendor_id = QString("0000");
    m_device_model_id = QString("0000");
    m_device_path = QString("/dev/null");
    m_is_dummy_device = true;
    initializeCtrls();
    initializeFormats();
}
VideoDevice::VideoDevice(QString device_serial,QString device_name, QString device_path, QString device_vendorid, QString device_modelid) {
    m_device_serial = QString(device_serial);
    m_device_name = QString(device_name);
    m_device_vendor_id = QString(device_vendorid);
    m_device_model_id = QString(device_modelid);
    m_device_path = QString(device_path);
    qCDebug(webcam_settings_kcm) << "VideoDevice::VideoDevice" << m_device_name << m_device_path << m_device_vendor_id << m_device_model_id;
    initializeCtrls();
    initializeFormats();
    // m_current_format_index = 0;
}
VideoDevice::~VideoDevice() {}

void VideoDevice::initializeCtrls() {
	qCDebug(webcam_settings_kcm) << "VideoDevice::initializeCtrls";
    for (const QString & label: m_ctrl_list){
        initializeCtrl(label);
    }
}

void VideoDevice::initializeCtrl(const QString ctrl_label) {
	// qCDebug(webcam_settings_kcm) << "VideoDevice::initializeCtrl for device " << m_device_name;
    bool is_defined;
    std::string line,cmd;
    if (m_is_dummy_device){
        is_defined = false;
    } else {
        cmd = std::string("v4l2-ctl -d " + m_device_path.toStdString() + " --list-ctrls | grep " + ctrl_label.toStdString());
        line = exec_cmd(cmd);
        if (line.size() == 0) {
            is_defined = false;
        } else {
            is_defined = true;
        }
    }
    if (ctrl_label == "brightness") {
        m_ctrl_brightness_visible = is_defined;
        m_ctrl_brightness["value"] = 0;
        m_ctrl_brightness["default"] = 0;
        m_ctrl_brightness["min"] = 0;
        m_ctrl_brightness["max"] = 0;
        m_ctrl_brightness["step"] = 0;
        if (!is_defined){return;}
        m_ctrl_brightness["value"] = static_cast<double>(stoi(get_str_between_two_str(line,std::string("value="),std::string(" "))));
        m_ctrl_brightness["default"] = static_cast<double>(stoi(get_str_between_two_str(line,std::string("default="),std::string(" "))));
        m_ctrl_brightness["min"] = static_cast<double>(stoi(get_str_between_two_str(line,std::string("min="),std::string(" "))));
        m_ctrl_brightness["max"] = static_cast<double>(stoi(get_str_between_two_str(line,std::string("max="),std::string(" "))));
        m_ctrl_brightness["step"] = static_cast<double>(stoi(get_str_between_two_str(line,std::string("step="),std::string(" "))));
        qCDebug(webcam_settings_kcm) << "VideoDevice::initializeCtrl Brightness: value: " << QString::number(m_ctrl_brightness["value"])
            << "min: " << m_ctrl_brightness["min"]
            << "max: " << m_ctrl_brightness["max"]
            << "step: " << m_ctrl_brightness["step"]
            << "default: " << m_ctrl_brightness["default"];
    }
    if (ctrl_label == "contrast") {
        m_ctrl_contrast_visible = is_defined;
        m_ctrl_contrast["value"] = 0;
        m_ctrl_contrast["default"] = 0;
        m_ctrl_contrast["min"] = 0;
        m_ctrl_contrast["max"] = 0;
        m_ctrl_contrast["step"] = 0;
        if (!is_defined){return;}
        m_ctrl_contrast["value"] = static_cast<double>(stoi(get_str_between_two_str(line,std::string("value="),std::string(" "))));
        m_ctrl_contrast["default"] = static_cast<double>(stoi(get_str_between_two_str(line,std::string("default="),std::string(" "))));
        m_ctrl_contrast["min"] = static_cast<double>(stoi(get_str_between_two_str(line,std::string("min="),std::string(" "))));
        m_ctrl_contrast["max"] = static_cast<double>(stoi(get_str_between_two_str(line,std::string("max="),std::string(" "))));
        m_ctrl_contrast["step"] = static_cast<double>(stoi(get_str_between_two_str(line,std::string("step="),std::string(" "))));
        qCDebug(webcam_settings_kcm) << "VideoDevice::initializeCtrl Contrast: value: " << QString::number(m_ctrl_contrast["value"])
            << "min: " << m_ctrl_contrast["min"]
            << "max: " << m_ctrl_contrast["max"]
            << "step: " << m_ctrl_contrast["step"]
            << "default: " << m_ctrl_contrast["default"];
    }
    if (ctrl_label == "sharpness") {
        m_ctrl_sharpness_visible = is_defined;
        m_ctrl_sharpness["value"] = 0;
        m_ctrl_sharpness["default"] = 0;
        m_ctrl_sharpness["min"] = 0;
        m_ctrl_sharpness["max"] = 0;
        m_ctrl_sharpness["step"] = 0;
        if (!is_defined){return;}
        m_ctrl_sharpness["value"] = static_cast<double>(stoi(get_str_between_two_str(line,std::string("value="),std::string(" "))));
        m_ctrl_sharpness["default"] = static_cast<double>(stoi(get_str_between_two_str(line,std::string("default="),std::string(" "))));
        m_ctrl_sharpness["min"] = static_cast<double>(stoi(get_str_between_two_str(line,std::string("min="),std::string(" "))));
        m_ctrl_sharpness["max"] = static_cast<double>(stoi(get_str_between_two_str(line,std::string("max="),std::string(" "))));
        m_ctrl_sharpness["step"] = static_cast<double>(stoi(get_str_between_two_str(line,std::string("step="),std::string(" "))));
        qCDebug(webcam_settings_kcm) << "VideoDevice::initializeCtrl Sharpness: value: " << QString::number(m_ctrl_sharpness["value"])
            << "min: " << m_ctrl_sharpness["min"]
            << "max: " << m_ctrl_sharpness["max"]
            << "step: " << m_ctrl_sharpness["step"]
            << "default: " << m_ctrl_sharpness["default"];
    }
    if (ctrl_label == "saturation") {
        m_ctrl_saturation_visible = is_defined;
        m_ctrl_saturation["value"] = 0;
        m_ctrl_saturation["default"] = 0;
        m_ctrl_saturation["min"] = 0;
        m_ctrl_saturation["max"] = 0;
        m_ctrl_saturation["step"] = 0;
        if (!is_defined){return;}
        m_ctrl_saturation["value"] = static_cast<double>(stoi(get_str_between_two_str(line,std::string("value="),std::string(" "))));
        m_ctrl_saturation["default"] = static_cast<double>(stoi(get_str_between_two_str(line,std::string("default="),std::string(" "))));
        m_ctrl_saturation["min"] = static_cast<double>(stoi(get_str_between_two_str(line,std::string("min="),std::string(" "))));
        m_ctrl_saturation["max"] = static_cast<double>(stoi(get_str_between_two_str(line,std::string("max="),std::string(" "))));
        m_ctrl_saturation["step"] = static_cast<double>(stoi(get_str_between_two_str(line,std::string("step="),std::string(" "))));
        qCDebug(webcam_settings_kcm) << "VideoDevice::initializeCtrl Saturation: value: " << QString::number(m_ctrl_saturation["value"])
            << "min: " << m_ctrl_saturation["min"]
            << "max: " << m_ctrl_saturation["max"]
            << "step: " << m_ctrl_saturation["step"]
            << "default: " << m_ctrl_saturation["default"];
    }
    if (ctrl_label == "zoom_absolute") {
        m_ctrl_zoom_absolute_visible = is_defined;
        m_ctrl_zoom_absolute["value"] = 0;
        m_ctrl_zoom_absolute["default"] = 0;
        m_ctrl_zoom_absolute["min"] = 0;
        m_ctrl_zoom_absolute["max"] = 0;
        m_ctrl_zoom_absolute["step"] = 0;
        if (!is_defined){return;}
        m_ctrl_zoom_absolute["value"] = static_cast<double>(stoi(get_str_between_two_str(line,std::string("value="),std::string(" "))));
        m_ctrl_zoom_absolute["default"] = static_cast<double>(stoi(get_str_between_two_str(line,std::string("default="),std::string(" "))));
        m_ctrl_zoom_absolute["min"] = static_cast<double>(stoi(get_str_between_two_str(line,std::string("min="),std::string(" "))));
        m_ctrl_zoom_absolute["max"] = static_cast<double>(stoi(get_str_between_two_str(line,std::string("max="),std::string(" "))));
        m_ctrl_zoom_absolute["step"] = static_cast<double>(stoi(get_str_between_two_str(line,std::string("step="),std::string(" "))));
        qCDebug(webcam_settings_kcm) << "VideoDevice::initializeCtrl Zoom Absolute: value: " << QString::number(m_ctrl_zoom_absolute["value"])
            << "min: " << m_ctrl_zoom_absolute["min"]
            << "max: " << m_ctrl_zoom_absolute["max"]
            << "step: " << m_ctrl_zoom_absolute["step"]
            << "default: " << m_ctrl_zoom_absolute["default"];
    }
    if (ctrl_label == "focus_automatic_continuous") {
        m_ctrl_auto_focus_visible = is_defined;
        m_ctrl_auto_focus["value"] = 0;
        m_ctrl_auto_focus["default"] = 0;
        if (!is_defined){return;}
        m_ctrl_auto_focus["value"] = stoi(get_str_between_two_str(line,std::string("value="),std::string(" ")));
        m_ctrl_auto_focus["default"] = stoi(get_str_between_two_str(line,std::string("default="),std::string(" ")));
        qCDebug(webcam_settings_kcm) << "VideoDevice::initializeCtrl Auto Focus: value: " << m_ctrl_auto_focus["value"]
            << "default: " << m_ctrl_auto_focus["default"];
    }
}

void VideoDevice::initializeFormats() {
	qCDebug(webcam_settings_kcm) << "VideoDevice::initializeFormats";
    qCDebug(webcam_settings_kcm) << "Initializing pixel formats for video device with path " << m_device_path;
    
    if (m_is_dummy_device){
        QStringList list = QStringList();
            list.append("UNKOWN");
            list.append("0");
            list.append("0");
            list.append("0");
            m_device_formats << QStringList(list);
            m_format_list.append("UNKOWN - 0x0 - (0 fps)");
            setFormatIndex(0);

    } else {
        int i = 0;
        std::string cmd;
        cmd = std::string("v4l2-ctl -d " + m_device_path.toStdString() + " --get-fmt-video | grep \"Pixel Format\"");
        std::string current_fmt = get_str_between_two_str(exec_cmd(cmd)," \'","\' ");
        cmd = std::string("v4l2-ctl -d " + m_device_path.toStdString() + " --get-fmt-video | grep \"Width/Height\"");
        std::string current_resolution = get_str_between_two_str(exec_cmd(cmd),": ","\n");
        std::string current_width = get_str_left_of_substr(current_resolution,"/");
        std::string current_height = get_str_right_of_substr(current_resolution,"/");
        qCDebug(webcam_settings_kcm) << "Current format " << QString::fromStdString(current_fmt) << QString::fromStdString(current_width) << QString::fromStdString(current_height);


        cmd = std::string("v4l2-ctl -d " + m_device_path.toStdString() + " --list-formats | grep \"\\[\"");
        QStringList output = QString::fromStdString(exec_cmd(cmd)).split(QLatin1Char('\n'));
        for (QString & line : output){
            if (line.length() == 0){break;}
            QString fmt = QString::fromStdString(get_str_between_two_str(line.toStdString().c_str()," \'","\' ")).simplified();
            qCDebug(webcam_settings_kcm) << "VideoDevice::initializeFormats list framesizes for format " << fmt;
            cmd = std::string("v4l2-ctl -d " + m_device_path.toStdString() + " --list-framesizes " + fmt.toStdString() + " | grep Size");
            QStringList output2 = QString::fromStdString(exec_cmd(cmd)).split(QLatin1Char('\n'));
            for (QString & line2 : output2){
                if (line2.length() == 0){break;}
                QString res = QString::fromStdString(get_str_right_of_substr(line2.simplified().trimmed().toStdString(),"Discrete ")).simplified();
                QString width = QString::fromStdString(get_str_left_of_substr(res.toStdString(),"x"));
                QString height = QString::fromStdString(get_str_right_of_substr(res.toStdString(),"x"));
                cmd = std::string("v4l2-ctl -d " + m_device_path.toStdString() + " --list-frameintervals width=" + width.toStdString() + ",height=" + height.toStdString() + ",pixelformat=" + fmt.toStdString() + " | grep Interval");
                QString framerate = QString::fromStdString(get_str_between_two_str(QString::fromStdString(exec_cmd(cmd)).split(QLatin1Char('\n'))[0].simplified().toStdString(),"(","fps )"));
                QStringList list = QStringList();
                list.append(fmt);
                list.append(width);
                list.append(height);
                list.append(framerate);
                m_device_formats << QStringList(list);
                m_format_list.append(fmt + " - " + width + "x" + height + " - (" + framerate + " fps)");
                if (fmt.toStdString() == current_fmt && width.toStdString() == current_width && height.toStdString() == current_height){
                    setFormatIndex(i);
                    qCDebug(webcam_settings_kcm) << "VideoDevice::initializeFormats set index  " << m_current_format_index;
                }
                i++;
            }
        }
    }
    for (QStringList & fmt_list : m_device_formats){
        qCDebug(webcam_settings_kcm) << "VideoDevice::initializeFormats" << fmt_list ;
    }
}

bool VideoDevice::setFormatIndex(int fmtindex){
	qCDebug(webcam_settings_kcm) << "VideoDevice::setFormatIndex";
    bool save_needed = false;
    if (m_current_format_index != fmtindex){save_needed = true;}
    m_current_format_index = fmtindex;

    setCurrentFormatName(m_device_formats.at(m_current_format_index).at(0));
    setCurrentFormatWidth(m_device_formats.at(m_current_format_index).at(1).toInt());
    setCurrentFormatHeight(m_device_formats.at(m_current_format_index).at(2).toInt());
    return save_needed;
}

bool VideoDevice::setCurrentFormatName(QString value){
    qCDebug(webcam_settings_kcm) << "VideoDevice::setCurrentFormatName" << value;
    bool save_needed = false;
    if (value != m_current_fmt){save_needed = true;}
    m_current_fmt = value;
    return save_needed;
}

bool VideoDevice::setCurrentFormatWidth(int value){
    qCDebug(webcam_settings_kcm) << "VideoDevice::setCurrentFormatWidth" << value;
    bool save_needed = false;
    if (value != m_current_width){save_needed = true;}
    m_current_width = value;
    return save_needed;
}

bool VideoDevice::setCurrentFormatHeight(int value){
    qCDebug(webcam_settings_kcm) << "VideoDevice::setCurrentFormatHeight" << value;
    bool save_needed = false;
    if (value != m_current_height){save_needed = true;}
    m_current_height = value;
    return save_needed;
}


// double VideoDevice::getCtrlDefaultValue(QString ctrl_name) {
//     double default_value;
//     if (ctrl_name == "brightness") {
//         default_value = m_ctrl_brightness["default"];
//     }
//     if (ctrl_name == "contrast") {
//         default_value = m_ctrl_contrast["default"];
//     }
//     if (ctrl_name == "sharpness") {
//         default_value = m_ctrl_sharpness["default"];
//     }
//     if (ctrl_name == "saturation") {
//         default_value = m_ctrl_saturation["default"];
//     }
//     if (ctrl_name == "zoom_absolute") {
//         default_value = m_ctrl_zoom_absolute["default"];
//     }
//     return default_value;
// }

bool VideoDevice::setBrightness(double value){
    qCDebug(webcam_settings_kcm) << "VideoDevice::setBrightness" << value;
    bool save_needed = false;
    if (m_ctrl_brightness_visible && value != m_ctrl_brightness["value"]){
        save_needed = true;
        m_ctrl_brightness["value"] = value;
    }
    return save_needed;
}

bool VideoDevice::setContrast(double value){
    qCDebug(webcam_settings_kcm) << "VideoDevice::setContrast" << value;
    bool save_needed = false;
    if (m_ctrl_contrast_visible && value != m_ctrl_contrast["value"]){
        save_needed = true;
        m_ctrl_contrast["value"] = value;
    }
    return save_needed;
}

bool VideoDevice::setSharpness(double value){
    qCDebug(webcam_settings_kcm) << "VideoDevice::setSharpness" << value;
    bool save_needed = false;
    if (m_ctrl_sharpness_visible && value != m_ctrl_sharpness["value"]){
        save_needed = true;
        m_ctrl_sharpness["value"] = value;
    }
    return save_needed;
}

bool VideoDevice::setSaturation(double value){
    qCDebug(webcam_settings_kcm) << "VideoDevice::setSaturation" << value;
    bool save_needed = false;
    if (m_ctrl_saturation_visible && value != m_ctrl_saturation["value"]){
        save_needed = true;
        m_ctrl_saturation["value"] = value;
    }
    return save_needed;
}

bool VideoDevice::setAbsoluteZoom(double value){
    qCDebug(webcam_settings_kcm) << "VideoDevice::setAbsoluteZoom" << value;
    bool save_needed = false;
    if (m_ctrl_zoom_absolute_visible && value != m_ctrl_zoom_absolute["value"]){
        save_needed = true;
        m_ctrl_zoom_absolute["value"] = value;
    }
    return save_needed;
}

bool VideoDevice::setAutoFocus(int value){
    qCDebug(webcam_settings_kcm) << "VideoDevice::setAutoFocus" << value;
    bool save_needed = false;
    if (m_ctrl_auto_focus_visible && value != m_ctrl_auto_focus["value"]){
        save_needed = true;
        m_ctrl_auto_focus["value"] = value;
    }
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
    if (ctrl_name == "focus_automatic_continuous") {
		ret = setAutoFocus(m_ctrl_auto_focus["default"]);
    }
    return ret;
}

QString VideoDevice::getCtrlOptions(){
    bool first_control = true;
    QString ctrl_options = QString();
    if (getAbsoluteZoomVisible()) {
        if (!first_control){ctrl_options.append(",");}
        ctrl_options.append("zoom_absolute=" + QString::number(getAbsoluteZoom()));
        first_control=false;
        }
    if (getBrightnessVisible()) {
        if (!first_control){ctrl_options.append(",");}
        ctrl_options.append("brightness=" + QString::number(getBrightness()));
        first_control=false;
        }
    if (getContrastVisible()) {
        if (!first_control){ctrl_options.append(",");}
        ctrl_options.append("contrast=" + QString::number(getContrast()));
        first_control=false;
    }
    if (getSaturationVisible()) {
        if (!first_control){ctrl_options.append(",");}
        ctrl_options.append("saturation=" + QString::number(getSaturation()));
        first_control=false;
    }
    if (getSharpnessVisible()) {
        if (!first_control){ctrl_options.append(",");}
        ctrl_options.append("sharpness=" + QString::number(getSharpness()));
        first_control=false;
    }if (getAutoFocusVisible()) {
        if (!first_control){ctrl_options.append(",");}
        ctrl_options.append("focus_automatic_continuous=" + QString::number(getAutoFocus()));
        first_control=false;
    }
    qCDebug(webcam_settings_kcm) << "VideoDevice::getCtrlOptions: " << ctrl_options;
    return ctrl_options;
}

void VideoDevice::applyConfiguration(){
	qCDebug(webcam_settings_kcm) << "VideoDevice::applyConfiguration";
	std::string cmd;
    cmd = std::string("v4l2-ctl -d " + getVideoDevicePath().toStdString() + " --set-ctrl " + getCtrlOptions().toStdString() + " --set-fmt-video width=" + std::to_string(getCurrentFormatWidth()) + ",height=" + std::to_string(getCurrentFormatHeight()) + ",pixelformat=" + getCurrentFormatName().toStdString()) + ",field=none";
    exec_cmd(cmd);
    qCDebug(webcam_settings_kcm) << "VideoDevice::applyConfiguration: " << "v4l2-ctl -d " + getVideoDevicePath() + " --set-ctrl " + getCtrlOptions() + " --set-fmt-video width=" + QString::number(getCurrentFormatWidth()) + ",height=" + QString::number(getCurrentFormatHeight()) + ",pixelformat=" + getCurrentFormatName() + ",field=none";
}

bool VideoDevice::resetToDefault(){
	qCDebug(webcam_settings_kcm) << "VideoDevice::resetToDefault";
    bool ret = false;
    for (const QString & label: m_ctrl_list){
        if (resetCrtlToDefault(label)){ret = true;}
    }
    return ret;
}

QString VideoDevice::getUdevRule(){
	qCDebug(webcam_settings_kcm) << "VideoDevice::getUdevRules";
    qCDebug(webcam_settings_kcm) << "VideoDevice::getUdevRules for device" << getVideoDevicePath() << getVideoDeviceVendorId() << getVideoDeviceModelId();
    qCDebug(webcam_settings_kcm) << "VideoDevice::getUdevRules resolution" << getCurrentFormatName() ;
    QString rule = "SUBSYSTEMS==\"usb\", ATTRS{idVendor}==\"" + getVideoDeviceVendorId() + "\", ATTRS{idProduct}==\"" + getVideoDeviceModelId() + "\", PROGRAM=\"/usr/bin/v4l2-ctl --set-ctrl " + getCtrlOptions();
    rule.append(" --set-fmt-video width=" + QString::number(getCurrentFormatWidth()) + ",height=" + QString::number(getCurrentFormatHeight()) + ",pixelformat=" + getCurrentFormatName() + ",field=none --device /dev/%k\"");
    qCDebug(webcam_settings_kcm) << "VideoDevice::getUdevRules Udev rule : " << rule;
    return rule;
}
