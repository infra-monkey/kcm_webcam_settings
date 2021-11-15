#include "VideoDeviceCtrl.h"
#include "helpers.h"
#include <cmath>

VideoDeviceCtrl::VideoDeviceCtrl(){}
VideoDeviceCtrl::VideoDeviceCtrl(std::string path, std::string ctrl_name) {
    m_device_path = path;
    m_ctrl_name = ctrl_name;
    getCtrlSettings();
    qCDebug(webcam_settings_kcm) << QString::fromStdString(m_device_path) << "Created control" << QString::fromStdString(m_ctrl_name) << ": min=" << QString::number(m_value_min) << " max=" << QString::number(m_value_max) << "default=" << QString::number(m_value_default) << " value=" << QString::number(m_value) << " step=" << QString::number(m_value_step);
}

VideoDeviceCtrl::~VideoDeviceCtrl() {

}

double VideoDeviceCtrl::getValue() {
    if (m_is_defined){
        std::string cmd = std::string("v4l2-ctl -d " + m_device_path + " --get-ctrl " + m_ctrl_name);
        m_value = static_cast<double>(stoi(get_str_right_of_substr(exec_cmd(cmd),std::string(":"))));
        return m_value;
    } else {
        return static_cast<double>(0);
    }
}

void VideoDeviceCtrl::getCtrlSettings() {
    std::string cmd = std::string("v4l2-ctl -d " + m_device_path + " --list-ctrls | grep " + m_ctrl_name);
    std::string line = exec_cmd(cmd);
    if (line.size() == 0) {
        m_is_defined = false;
        return;
    } else {
        m_is_defined = true;
    }
    m_type = get_str_between_two_str(line,std::string("("),std::string(")"));
    setValue(getValue());
    m_value_default = static_cast<double>(stoi(get_str_between_two_str(line,std::string("default="),std::string(" "))));
    m_value_min = static_cast<double>(stoi(get_str_between_two_str(line,std::string("min="),std::string(" "))));
    m_value_max = static_cast<double>(stoi(get_str_between_two_str(line,std::string("max="),std::string(" "))));
    m_value_step = static_cast<double>(stoi(get_str_between_two_str(line,std::string("step="),std::string(" "))));
}

void VideoDeviceCtrl::setValue(double ctrl_value) {
    if (ctrl_value != m_value){
        qCDebug(webcam_settings_kcm) << "Control " << QString::fromStdString(m_ctrl_name) << " value changed to " << QString::number(ctrl_value);
        m_value = ctrl_value;
        applyValue();
    }
}
void VideoDeviceCtrl::applyValue() {
    int value = (int)round(m_value);
    std::string cmd = std::string("v4l2-ctl -d " + m_device_path + " --set-ctrl " + m_ctrl_name + "=" + std::to_string(value));
    exec_cmd(cmd);
}

