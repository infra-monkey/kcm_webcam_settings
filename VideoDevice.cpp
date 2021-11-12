#include "VideoDevice.h"
#include "helpers.h"
#include <QString>
#include <QStringList>

VideoDevice::VideoDevice() {
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

void VideoDevice::setBrightness(double value) {
    m_ctrl_brightness.setValue(value);
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

void VideoDevice::setContrast(double value) {
    m_ctrl_contrast.setValue(value);
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

void VideoDevice::setSaturation(double value) {
    m_ctrl_saturation.setValue(value);
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

void VideoDevice::setSharpness(double value) {
    m_ctrl_sharpness.setValue(value);
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
bool VideoDevice::getAbsoluteZoomVisible() {
    m_absolute_zoom_visible = m_ctrl_zoom_absolute.getEnabled();
    return m_absolute_zoom_visible;
}


void VideoDevice::initializeCtrls() {
    printf("Create controls for %s\n",m_device_path.toStdString().c_str());
    m_ctrl_brightness = VideoDeviceCtrl(m_device_path.toStdString(),"brightness");
    m_ctrl_contrast = VideoDeviceCtrl(m_device_path.toStdString(),"contrast");
    m_ctrl_sharpness = VideoDeviceCtrl(m_device_path.toStdString(),"sharpness");
    m_ctrl_saturation = VideoDeviceCtrl(m_device_path.toStdString(),"saturation");
    m_ctrl_zoom_absolute = VideoDeviceCtrl(m_device_path.toStdString(),"zoom_absolute");
}

void VideoDevice::initializeFormats() {
    std::string cmd;
    int i = 0;
    cmd = std::string("v4l2-ctl -d " + m_device_path.toStdString() + " --get-fmt-video | grep \"Pixel Format\"");
    std::string current_fmt = get_str_between_two_str(exec_cmd(cmd)," \'","\' ");
    cmd = std::string("v4l2-ctl -d " + m_device_path.toStdString() + " --list-formats | grep \"\\[\"");
    QStringList output = QString::fromStdString(exec_cmd(cmd)).split(QLatin1Char('\n'));
    for (QString & line : output){
        if (line.length() == 0){break;}
        printf("Line = %s\n",line.toStdString().c_str());
        QString fmt = QString::fromStdString(get_str_between_two_str(line.toStdString().c_str()," \'","\' ")).simplified();
        printf("Format = %s\n",fmt.toStdString().c_str());
        VideoDeviceCapFormat new_fmt = VideoDeviceCapFormat(fmt);
        m_device_formats.push_back(new_fmt);
        m_format_list.append(fmt);
        if (fmt.toStdString() == current_fmt){
            m_current_fmt = new_fmt;
            m_current_format_index = i;
        }
        i++;
    }
}

void VideoDevice::initializeResolutions() {
    std::string cmd;
    int i=0;
    int j=0;
    cmd = std::string("v4l2-ctl -d " + m_device_path.toStdString() + " --get-fmt-video | grep \"Width/Height\"");
    m_current_resolution = QString::fromStdString(get_str_right_of_substr(exec_cmd(cmd),":")).replace(QString::fromStdString("/"), QString::fromStdString("x")).simplified();
    printf("current format index = %i | current resolution = %s\n",m_current_format_index,m_current_resolution.toStdString().c_str());
    for (VideoDeviceCapFormat & fmtobj : m_device_formats){
        if (m_current_format_index == j){i=0;}
        cmd = std::string("v4l2-ctl -d " + m_device_path.toStdString() + " --list-framesizes " + fmtobj.getFormatName().toStdString() + " | grep Size");
        QStringList output = QString::fromStdString(exec_cmd(cmd)).split(QLatin1Char('\n'));
        for (QString & line : output){
            if (line.length() == 0){break;}
            printf("Line = %s\n",line.simplified().trimmed().toStdString().c_str());
            QString fmt = QString::fromStdString(get_str_right_of_substr(line.simplified().trimmed().toStdString(),"Discrete ")).simplified();
            printf("Format = %s\n",fmt.toStdString().c_str());
            printf("current resolution = %s\n",m_current_resolution.toStdString().c_str());
            fmtobj.addResolution(fmt);
            if (m_current_format_index == j && m_current_resolution.toStdString() == fmt.toStdString()){
                m_current_resolution_index = i;
                printf("current resolution index = %i\n",m_current_resolution_index);
            }
            i++;
        }
        j++;
    }
}

QStringList VideoDevice::getResolutionList(){
    int i=0;
    QStringList list;
    for (VideoDeviceCapFormat & fmt : m_device_formats){
        printf("Checking resolutions for format index %i\n",i);
        if (i == m_current_format_index){
            list = fmt.getResList();
            break;
        }
        i++;
    }
    return list;
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

