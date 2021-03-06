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
VideoDevice::VideoDevice(const QCameraInfo camerainfo,QString device_serial, QString device_vendorid, QString device_modelid) {
    m_current_camera = new QCamera(camerainfo);
    m_device_serial = QString(device_serial);
    m_device_name = QString(camerainfo.description());
    m_device_vendor_id = QString(device_vendorid);
    m_device_model_id = QString(device_modelid);
    m_device_path = QString(camerainfo.deviceName());
    m_ctrl_brightness_visible = false;
    m_ctrl_contrast_visible = false;
    m_ctrl_sharpness_visible = false;
    m_ctrl_saturation_visible = false;
    m_ctrl_zoom_absolute_supported = false;
    m_ctrl_zoom_optical_visible = false;
    m_ctrl_zoom_digital_visible = false;
    m_ctrl_auto_focus_visible = false;
    m_ctrl_focus_visible = false;
    qCDebug(webcam_settings_kcm) << "VideoDevice::VideoDevice" << m_device_name << m_device_path << m_device_vendor_id << m_device_model_id;
    initializeCtrls();
    initializeFormats();
}
VideoDevice::~VideoDevice() {
    delete m_current_camera;
}

void VideoDevice::initializeCtrls() {
	qCDebug(webcam_settings_kcm) << "VideoDevice::initializeCtrls";
    std::string cmd = std::string("v4l2-ctl -d " + m_device_path.toStdString() + " --list-ctrls");
    QString output = QString::fromStdString(exec_cmd(cmd));
    QStringList lines = output.split("\n");
    for (const QString & line : lines) {
        for (const QString & label: m_ctrl_list){
            if (line.contains(label)){
                initializeCtrl(label,line);
            }
        }
    }
    // initialize non-v4l2 controls
    initializeCtrl("zoom_optical","");
    initializeCtrl("zoom_digital","");
}

void VideoDevice::initializeCtrl(const QString ctrl_label, const QString line) {
    bool is_defined;
    if (m_is_dummy_device){
        is_defined = false;
    } else {
        if (line.size() == 0) {
            is_defined = false;
        } else {
            is_defined = true;
        }
    }
    if (ctrl_label == "brightness") {
        m_ctrl_brightness_visible = is_defined;
        m_ctrl_brightness["value"] = 0;
        m_ctrl_brightness["min"] = 0;
        m_ctrl_brightness["max"] = 0;
        m_ctrl_brightness["step"] = 0;
        if (!is_defined){return;}
        m_ctrl_brightness["value"] = m_current_camera->imageProcessing()->brightness();
        m_ctrl_brightness["min"] = static_cast<double>(stoi(get_str_between_two_str(line.toStdString(),std::string("min="),std::string(" "))));
        m_ctrl_brightness["max"] = static_cast<double>(stoi(get_str_between_two_str(line.toStdString(),std::string("max="),std::string(" "))));
        m_ctrl_brightness["step"] = static_cast<double>(stoi(get_str_between_two_str(line.toStdString(),std::string("step="),std::string(" "))));
        qCDebug(webcam_settings_kcm) << "VideoDevice::initializeCtrl Brightness: value: " << QString::number(m_ctrl_brightness["value"])
            << "min: " << m_ctrl_brightness["min"]
            << "max: " << m_ctrl_brightness["max"]
            << "step: " << m_ctrl_brightness["step"];
    }
    if (ctrl_label == "contrast") {
        m_ctrl_contrast_visible = is_defined;
        m_ctrl_contrast["value"] = 0;
        m_ctrl_contrast["min"] = 0;
        m_ctrl_contrast["max"] = 0;
        m_ctrl_contrast["step"] = 0;
        if (!is_defined){return;}
        m_ctrl_contrast["value"] = m_current_camera->imageProcessing()->contrast();
        m_ctrl_contrast["min"] = static_cast<double>(stoi(get_str_between_two_str(line.toStdString(),std::string("min="),std::string(" "))));
        m_ctrl_contrast["max"] = static_cast<double>(stoi(get_str_between_two_str(line.toStdString(),std::string("max="),std::string(" "))));
        m_ctrl_contrast["step"] = static_cast<double>(stoi(get_str_between_two_str(line.toStdString(),std::string("step="),std::string(" "))));
        qCDebug(webcam_settings_kcm) << "VideoDevice::initializeCtrl Contrast: value: " << QString::number(m_ctrl_contrast["value"])
            << "min: " << m_ctrl_contrast["min"]
            << "max: " << m_ctrl_contrast["max"]
            << "step: " << m_ctrl_contrast["step"];
    }
    if (ctrl_label == "sharpness") {
        m_ctrl_sharpness_visible = is_defined;
        m_ctrl_sharpness["value"] = 0;
        m_ctrl_sharpness["min"] = 0;
        m_ctrl_sharpness["max"] = 0;
        m_ctrl_sharpness["step"] = 0;
        if (!is_defined){return;}
        m_ctrl_sharpness["value"] = m_current_camera->imageProcessing()->sharpeningLevel();
        m_ctrl_sharpness["min"] = static_cast<double>(stoi(get_str_between_two_str(line.toStdString(),std::string("min="),std::string(" "))));
        m_ctrl_sharpness["max"] = static_cast<double>(stoi(get_str_between_two_str(line.toStdString(),std::string("max="),std::string(" "))));
        m_ctrl_sharpness["step"] = static_cast<double>(stoi(get_str_between_two_str(line.toStdString(),std::string("step="),std::string(" "))));
        qCDebug(webcam_settings_kcm) << "VideoDevice::initializeCtrl Sharpness: value: " << QString::number(m_ctrl_sharpness["value"])
            << "min: " << m_ctrl_sharpness["min"]
            << "max: " << m_ctrl_sharpness["max"]
            << "step: " << m_ctrl_sharpness["step"];
    }
    if (ctrl_label == "saturation") {
        m_ctrl_saturation_visible = is_defined;
        m_ctrl_saturation["value"] = 0;
        m_ctrl_saturation["min"] = 0;
        m_ctrl_saturation["max"] = 0;
        m_ctrl_saturation["step"] = 0;
        if (!is_defined){return;}
        m_ctrl_saturation["value"] = m_current_camera->imageProcessing()->contrast();
        m_ctrl_saturation["min"] = static_cast<double>(stoi(get_str_between_two_str(line.toStdString(),std::string("min="),std::string(" "))));
        m_ctrl_saturation["max"] = static_cast<double>(stoi(get_str_between_two_str(line.toStdString(),std::string("max="),std::string(" "))));
        m_ctrl_saturation["step"] = static_cast<double>(stoi(get_str_between_two_str(line.toStdString(),std::string("step="),std::string(" "))));
        qCDebug(webcam_settings_kcm) << "VideoDevice::initializeCtrl Saturation: value: " << QString::number(m_ctrl_saturation["value"])
            << "min: " << m_ctrl_saturation["min"]
            << "max: " << m_ctrl_saturation["max"]
            << "step: " << m_ctrl_saturation["step"];
    }
    if (ctrl_label == "zoom_absolute") {
        m_ctrl_zoom_absolute_supported = is_defined;
        qCDebug(webcam_settings_kcm) << "VideoDevice::initializeCtrl Zoom Absolute supported: " << m_ctrl_zoom_absolute_supported;
    }
    if (ctrl_label == "zoom_optical") {
        m_ctrl_zoom_optical["value"] = 0;
        m_ctrl_zoom_optical["min"] = 0;
        m_ctrl_zoom_optical["max"] = 0;
        m_ctrl_zoom_optical["step"] = 0;
        if (m_current_camera->focus()->maximumOpticalZoom() == 1.0){
            m_ctrl_zoom_optical_visible = false;
            return;
        } else {
            m_ctrl_zoom_optical_visible = true;
        }
        m_ctrl_zoom_optical["value"] = m_current_camera->focus()->opticalZoom();
        m_ctrl_zoom_optical["min"] = 0;
        m_ctrl_zoom_optical["max"] = m_current_camera->focus()->maximumOpticalZoom();
        m_ctrl_zoom_optical["step"] = 1;
        qCDebug(webcam_settings_kcm) << "VideoDevice::initializeCtrl Optical Zoom: value: " << QString::number(m_ctrl_zoom_optical["value"])
            << "min: " << m_ctrl_zoom_optical["min"]
            << "max: " << m_ctrl_zoom_optical["max"]
            << "step: " << m_ctrl_zoom_optical["step"];
    }
    if (ctrl_label == "zoom_digital") {
        m_ctrl_zoom_digital["value"] = 0;
        m_ctrl_zoom_digital["min"] = 0;
        m_ctrl_zoom_digital["max"] = 0;
        m_ctrl_zoom_digital["step"] = 0;
        qCDebug(webcam_settings_kcm) << "VideoDevice::initializeCtrl Digital Zoom: value: " << m_current_camera->focus()->maximumDigitalZoom();
        if (m_current_camera->focus()->maximumDigitalZoom() == 1.0){
            m_ctrl_zoom_digital_visible = false;
            return;
        } else {
            if (m_ctrl_zoom_absolute_supported){
                m_ctrl_zoom_digital_visible = true;
            } else {
                m_ctrl_zoom_digital_visible = false;
            }
        }
        m_ctrl_zoom_digital["value"] = m_current_camera->focus()->digitalZoom();
        m_ctrl_zoom_digital["min"] = 0;
        m_ctrl_zoom_digital["max"] = m_current_camera->focus()->maximumDigitalZoom();
        m_ctrl_zoom_digital["step"] = 1;
        qCDebug(webcam_settings_kcm) << "VideoDevice::initializeCtrl Digital Zoom: value: " << QString::number(m_ctrl_zoom_digital["value"])
            << "min: " << m_ctrl_zoom_digital["min"]
            << "max: " << m_ctrl_zoom_digital["max"]
            << "step: " << m_ctrl_zoom_digital["step"];
    }
    if (ctrl_label == "focus_automatic_continuous") {
        m_ctrl_auto_focus_visible = is_defined;
        m_ctrl_auto_focus["value"] = 0;
        m_ctrl_auto_focus["default"] = 0;
        if (!is_defined){return;}
        m_ctrl_auto_focus["value"] = stoi(get_str_between_two_str(line.toStdString(),std::string("value="),std::string(" ")));
        m_ctrl_auto_focus["default"] = stoi(get_str_between_two_str(line.toStdString(),std::string("default="),std::string(" ")));
        qCDebug(webcam_settings_kcm) << "VideoDevice::initializeCtrl Auto Focus: value: " << m_ctrl_auto_focus["value"]
            << "default: " << m_ctrl_auto_focus["default"];
    }
    if (ctrl_label == "focus_absolute") {
        m_ctrl_focus_visible = is_defined;
        m_ctrl_focus["value"] = 0;
        m_ctrl_focus["default"] = 0;
        m_ctrl_focus["min"] = 0;
        m_ctrl_focus["max"] = 0;
        m_ctrl_focus["step"] = 0;
        if (!is_defined){return;}
        m_ctrl_focus["value"] = static_cast<double>(stoi(get_str_between_two_str(line.toStdString(),std::string("value="),std::string(" "))));
        m_ctrl_focus["default"] = static_cast<double>(stoi(get_str_between_two_str(line.toStdString(),std::string("default="),std::string(" "))));
        m_ctrl_focus["min"] = static_cast<double>(stoi(get_str_between_two_str(line.toStdString(),std::string("min="),std::string(" "))));
        m_ctrl_focus["max"] = static_cast<double>(stoi(get_str_between_two_str(line.toStdString(),std::string("max="),std::string(" "))));
        m_ctrl_focus["step"] = static_cast<double>(stoi(get_str_between_two_str(line.toStdString(),std::string("step="),std::string(" "))));
        qCDebug(webcam_settings_kcm) << "VideoDevice::initializeCtrl Focus Absolute: value: " << QString::number(m_ctrl_focus["value"])
            << "min: " << m_ctrl_focus["min"]
            << "max: " << m_ctrl_focus["max"]
            << "step: " << m_ctrl_focus["step"]
            << "default: " << m_ctrl_focus["default"];
    }
}

void VideoDevice::initializeFormats() {
	qCDebug(webcam_settings_kcm) << "VideoDevice::initializeFormats";
    qCDebug(webcam_settings_kcm) << "Initializing pixel formats for video device with path " << m_device_path;
    std::string current_fmt,current_resolution,current_width,current_height;
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
        cmd = std::string("v4l2-ctl -d " + m_device_path.toStdString() + " --get-fmt-video");
        QString cmdoutput = QString::fromStdString(exec_cmd(cmd));
        QStringList lines = cmdoutput.split("\n");
        for (const QString & line : lines) {
            if (line.contains("Pixel Format")) {
                current_fmt = get_str_between_two_str(line.toStdString()," \'","\' ");
            }
            if (line.contains("Width/Height")) {
                current_resolution = get_str_between_two_str(line.toStdString(),": ","\n");
                current_width = get_str_left_of_substr(current_resolution,"/");
                current_height = get_str_right_of_substr(current_resolution,"/");
            }
        }
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
                if (!m_device_formats.contains(list)){
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


bool VideoDevice::setBrightness(qreal value){
    qCDebug(webcam_settings_kcm) << "VideoDevice::setBrightness" << value;
    bool save_needed = false;
    if (m_ctrl_brightness_visible && value != m_ctrl_brightness["value"]){
        save_needed = true;
        m_ctrl_brightness["value"] = value;
        m_current_camera->imageProcessing()->setBrightness(value);
        applyControlValue(true,"brightness",value,m_ctrl_brightness["max"],m_ctrl_brightness["step"]);
    }
    return save_needed;
}

bool VideoDevice::setContrast(qreal value){
    qCDebug(webcam_settings_kcm) << "VideoDevice::setContrast" << value;
    bool save_needed = false;
    if (m_ctrl_contrast_visible && value != m_ctrl_contrast["value"]){
        save_needed = true;
        m_ctrl_contrast["value"] = value;
        m_current_camera->imageProcessing()->setContrast(value);
        applyControlValue(true,"contrast",value,m_ctrl_contrast["max"],m_ctrl_contrast["step"]);
    }
    return save_needed;
}

bool VideoDevice::setSharpness(qreal value){
    qCDebug(webcam_settings_kcm) << "VideoDevice::setSharpness" << value;
    bool save_needed = false;
    if (m_ctrl_sharpness_visible && value != m_ctrl_sharpness["value"]){
        save_needed = true;
        m_ctrl_sharpness["value"] = value;
        m_current_camera->imageProcessing()->setSharpeningLevel(value);
        applyControlValue(true,"sharpness",value,m_ctrl_sharpness["max"],m_ctrl_sharpness["step"]);
    }
    return save_needed;
}

bool VideoDevice::setSaturation(qreal value){
    qCDebug(webcam_settings_kcm) << "VideoDevice::setSaturation" << value;
    bool save_needed = false;
    if (m_ctrl_saturation_visible && value != m_ctrl_saturation["value"]){
        save_needed = true;
        m_ctrl_saturation["value"] = value;
        m_current_camera->imageProcessing()->setSaturation(value);
        applyControlValue(true,"saturation",value,m_ctrl_saturation["max"],m_ctrl_saturation["step"]);
    }
    return save_needed;
}

void VideoDevice::setZoom(qreal optical_value,qreal digital_value){
    qCDebug(webcam_settings_kcm) << "VideoDevice::setZoom" << optical_value << digital_value;
    m_current_camera->focus()->zoomTo(optical_value,digital_value);
}

bool VideoDevice::setOpticalZoom(qreal value){
    qCDebug(webcam_settings_kcm) << "VideoDevice::setOpticalZoom" << value;
    bool save_needed = false;
    if (m_ctrl_zoom_optical_visible && value != m_ctrl_zoom_optical["value"]){
        save_needed = true;
        m_ctrl_zoom_optical["value"] = value;
        setZoom(value,m_ctrl_zoom_digital["value"]);
    }
    return save_needed;
}

bool VideoDevice::setDigitalZoom(qreal value){
    qCDebug(webcam_settings_kcm) << "VideoDevice::setDigitalZoom" << value;
    bool save_needed = false;
    if (m_ctrl_zoom_digital_visible && value != m_ctrl_zoom_digital["value"]){
        save_needed = true;
        if ((int)value != (int)m_ctrl_zoom_digital["value"]){
            applyControlValue(false,"zoom_absolute",value,m_ctrl_saturation["max"],m_ctrl_saturation["step"]);
        }
        m_ctrl_zoom_digital["value"] = value;
        setZoom(m_ctrl_zoom_optical["value"],value);
    }
    return save_needed;
}

bool VideoDevice::setAutoFocus(int value){
    qCDebug(webcam_settings_kcm) << "VideoDevice::setAutoFocus" << value;
    bool save_needed = false;
    if (m_ctrl_auto_focus_visible && value != m_ctrl_auto_focus["value"]){
        save_needed = true;
        m_ctrl_auto_focus["value"] = value;
        applyControlValue("focus_automatic_continuous",QString::number(value));
    }
    return save_needed;
}

bool VideoDevice::setFocus(double value){
    qCDebug(webcam_settings_kcm) << "VideoDevice::setFocus" << value;
    bool save_needed = false;
    if (m_ctrl_focus_visible && value != m_ctrl_focus["value"]){
        save_needed = true;
        m_ctrl_focus["value"] = value;
        applyControlValue("focus_absolute",QString::number(value));
    }
    return save_needed;
}

bool VideoDevice::resetCrtlToDefault(QString ctrl_name) {
	qCDebug(webcam_settings_kcm) << "VideoDevice::resetCrtlToDefault" << ctrl_name;
    bool ret = false;
	if (ctrl_name == "brightness") {
		ret = setBrightness(0);
    }
    if (ctrl_name == "contrast") {
		ret = setContrast(0);
    }
    if (ctrl_name == "sharpness") {
		ret = setSharpness(0);
    }
    if (ctrl_name == "saturation") {
		ret = setSaturation(0);
    }
    if (ctrl_name == "zoom_optical") {
		ret = setOpticalZoom(0);
    }
    if (ctrl_name == "zoom_digital") {
		ret = setDigitalZoom(0);
    }
    if (ctrl_name == "focus_automatic_continuous") {
		ret = setAutoFocus(m_ctrl_auto_focus["default"]);
    }
    if (ctrl_name == "focus_absolute") {
		ret = setFocus(m_ctrl_focus["default"]);
    }
    return ret;
}

QString VideoDevice::getCtrlOptions(){
    bool first_control = true;
    QString ctrl_options = QString();
    if (getDigitalZoomVisible()) {
        if (!first_control){ctrl_options.append(",");}
        ctrl_options.append("zoom_absolute=" + QString::number(getControlValueV4L(false,m_ctrl_zoom_digital["value"],m_ctrl_zoom_digital["max"],m_ctrl_zoom_digital["step"])));
        first_control=false;
        }
    if (getBrightnessVisible()) {
        if (!first_control){ctrl_options.append(",");}
        ctrl_options.append("brightness=" + QString::number(getControlValueV4L(true,m_ctrl_brightness["value"],m_ctrl_brightness["max"],m_ctrl_brightness["step"])));
        first_control=false;
        }
    if (getContrastVisible()) {
        if (!first_control){ctrl_options.append(",");}
        ctrl_options.append("contrast=" + QString::number(getControlValueV4L(true,m_ctrl_contrast["value"],m_ctrl_contrast["max"],m_ctrl_contrast["step"])));
        first_control=false;
    }
    if (getSaturationVisible()) {
        if (!first_control){ctrl_options.append(",");}
        ctrl_options.append("saturation=" + QString::number(getControlValueV4L(true,m_ctrl_saturation["value"],m_ctrl_saturation["max"],m_ctrl_saturation["step"])));
        first_control=false;
    }
    if (getSharpnessVisible()) {
        if (!first_control){ctrl_options.append(",");}
        ctrl_options.append("sharpness=" + QString::number(getControlValueV4L(true,m_ctrl_sharpness["value"],m_ctrl_sharpness["max"],m_ctrl_sharpness["step"])));
        first_control=false;
    }if (getAutoFocusVisible()) {
        if (!first_control){ctrl_options.append(",");}
        ctrl_options.append("focus_automatic_continuous=" + QString::number(getAutoFocus()));
        first_control=false;
    }if (getFocusVisible()) {
        if (!first_control){ctrl_options.append(",");}
        ctrl_options.append("focus_absolute=" + QString::number(getFocus()));
        first_control=false;
    }
    qCDebug(webcam_settings_kcm) << "VideoDevice::getCtrlOptions: " << ctrl_options;
    return ctrl_options;
}


//Still needed for the focus controls. To be changed if possible
void VideoDevice::applyControlValue(QString ctrl_name,QString value){
    qCDebug(webcam_settings_kcm) << "VideoDevice::applyControlValue: " << "v4l2-ctl -d " + getVideoDevicePath() + " --set-ctrl " + ctrl_name + "=" + value;
	std::string cmd;
    cmd = std::string("v4l2-ctl -d " + getVideoDevicePath().toStdString() + " --set-ctrl " + ctrl_name.toStdString() +"=" + value.toStdString());
    exec_cmd(cmd);
}

int VideoDevice::getControlValueV4L(bool scaled,qreal value, qreal ctrl_max, qreal ctrl_step){
    int converted_value;
    if (scaled) {
        converted_value = (int)((((value + 1)*ctrl_max)/2)/ctrl_step) * (int)ctrl_step;
    } else {
        converted_value = value;
    }
    return converted_value;
}
void VideoDevice::applyControlValue(bool scaled,QString ctrl_name,qreal value, qreal ctrl_max, qreal ctrl_step){
    int converted_value = getControlValueV4L(scaled,value,ctrl_max,ctrl_step);
    qCDebug(webcam_settings_kcm) << "VideoDevice::applyControlValue: " << "v4l2-ctl -d " + getVideoDevicePath() + " --set-ctrl " + ctrl_name + "=" + QString::number(converted_value);
	std::string cmd;
    cmd = std::string("v4l2-ctl -d " + getVideoDevicePath().toStdString() + " --set-ctrl " + ctrl_name.toStdString() +"=" + std::to_string(converted_value));
    exec_cmd(cmd);
}

void VideoDevice::applyConfiguration(){
    qCDebug(webcam_settings_kcm) << "VideoDevice::applyConfiguration: " << "v4l2-ctl -d " + getVideoDevicePath() + " --set-ctrl " + getCtrlOptions() + " --set-fmt-video width=" + QString::number(getCurrentFormatWidth()) + ",height=" + QString::number(getCurrentFormatHeight()) + ",pixelformat=" + getCurrentFormatName() + ",field=none";
	std::string cmd;
    cmd = std::string("v4l2-ctl -d " + getVideoDevicePath().toStdString() + " --set-ctrl " + getCtrlOptions().toStdString() + " --set-fmt-video width=" + std::to_string(getCurrentFormatWidth()) + ",height=" + std::to_string(getCurrentFormatHeight()) + ",pixelformat=" + getCurrentFormatName().toStdString()) + ",field=none";
    exec_cmd(cmd);
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
    qCDebug(webcam_settings_kcm) << "VideoDevice::getUdevRules for device" << getVideoDevicePath() << getVideoDeviceVendorId() << getVideoDeviceModelId();
    qCDebug(webcam_settings_kcm) << "VideoDevice::getUdevRules resolution" << getCurrentFormatName() ;
    QString rule = "SUBSYSTEMS==\"usb\", ATTRS{idVendor}==\"" + getVideoDeviceVendorId() + "\", ATTRS{idProduct}==\"" + getVideoDeviceModelId() + "\", PROGRAM=\"/usr/bin/v4l2-ctl --set-ctrl " + getCtrlOptions();
    rule.append(" --set-fmt-video width=" + QString::number(getCurrentFormatWidth()) + ",height=" + QString::number(getCurrentFormatHeight()) + ",pixelformat=" + getCurrentFormatName() + ",field=none --device /dev/%k\"");
    qCDebug(webcam_settings_kcm) << "VideoDevice::getUdevRules Udev rule : " << rule;
    return rule;
}
