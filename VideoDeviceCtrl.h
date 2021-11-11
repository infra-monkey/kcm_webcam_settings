#ifndef VIDEODEVICECTRL_H
#define VIDEODEVICECTRL_H

#include <list>
#include <string>
#include <QString>
#include <QStringList>

class VideoDeviceCtrl {
public:
    VideoDeviceCtrl();
    VideoDeviceCtrl(std::string,std::string);
    virtual ~VideoDeviceCtrl();
    double getValue();
    double getValueMin() {if (m_is_defined){return m_value_min;}else{return static_cast<double>(0);}};
    double getValueMax() {if (m_is_defined){return m_value_max;}else{return static_cast<double>(0);}};
    double getValueStep() {if (m_is_defined){return m_value_step;}else{return static_cast<double>(0);}};
    double getValueDefault() {if (m_is_defined){return m_value_default;}else{return static_cast<double>(0);}};
    bool getEnabled() {return m_is_defined;};
    void getCtrlSettings();
    void setValue(double);
    void resetValueToDefault() {setValue(m_value_default);};
private:
    std::string m_device_path;
    void applyValue();
    bool m_is_defined;
    std::string m_type;
    std::string m_ctrl_name;
    double m_value;
    double m_value_default;
    double m_value_max;
    double m_value_min;
    double m_value_step;
    
};

#endif
