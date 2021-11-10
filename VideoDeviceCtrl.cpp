#include "VideoDeviceCtrl.h"
#include "helpers.h"
#include <cmath>

VideoDeviceCtrl::VideoDeviceCtrl(){}
VideoDeviceCtrl::VideoDeviceCtrl(std::string path, std::string ctrl_name) {
    m_device_path = path;
    m_ctrl_name = ctrl_name;
    // printf("\tname = %s , path = %s\n",m_ctrl_name.c_str(),m_device_path.c_str());
    getCtrlSettings();
}

VideoDeviceCtrl::~VideoDeviceCtrl() {

}

double VideoDeviceCtrl::getValue() {
    std::string cmd = std::string("v4l2-ctl -d " + m_device_path + " --get-ctrl " + m_ctrl_name);
    // printf("cmd = %s\n",cmd.c_str());
    m_value = static_cast<double>(stoi(get_str_right_of_substr(exec_cmd(cmd),std::string(":"))));
    // printf("value %f\n",m_value);
    return m_value;
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
    m_value_default = static_cast<double>(stoi(get_str_between_two_str(line,std::string("default="),std::string(" "))));
    m_value_min = static_cast<double>(stoi(get_str_between_two_str(line,std::string("min="),std::string(" "))));
    m_value_max = static_cast<double>(stoi(get_str_between_two_str(line,std::string("max="),std::string(" "))));
    m_value_step = static_cast<double>(stoi(get_str_between_two_str(line,std::string("step="),std::string(" "))));
    // printf("\t\tctrl type = %s\n",m_type.c_str());
    // printf("\t\tdefault value = %f\n",m_value_default);
    // printf("\t\tmin value = %f\n",m_value_min);
    // printf("\t\tmax value = %f\n",m_value_max);
    // printf("\t\tstep = %f\n",m_value_step);
}

void VideoDeviceCtrl::setValue(double ctrl_value) {
    m_value = ctrl_value;
    applyValue();
}
void VideoDeviceCtrl::applyValue() {
    int value = (int)round(m_value);
    std::string cmd = std::string("v4l2-ctl -d " + m_device_path + " --set-ctrl " + m_ctrl_name + "=" + std::to_string(value));
    exec_cmd(cmd);
}

