#include "VideoDeviceResolution.h"
#include "helpers.h"

VideoDeviceResolution::VideoDeviceResolution(){}
VideoDeviceResolution::VideoDeviceResolution(QString res, QString fmt, QString devpath) {
    std::string cmd;
    m_width = stoi(get_str_left_of_substr(res.toStdString(),"x"));
    m_height = stoi(get_str_right_of_substr(res.toStdString(),"x"));
    m_format = fmt;
    cmd = std::string("v4l2-ctl -d " + devpath.toStdString() + " --list-frameintervals width=" + QString::number(m_width).toStdString() + ",height=" + QString::number(m_height).toStdString() + ",pixelformat=" + m_format.toStdString() + " | grep Interval");
    QStringList output = QString::fromStdString(exec_cmd(cmd)).split(QLatin1Char('\n'));
    m_res_label =res;
    m_res_label.append(QString::fromStdString(" ("));
    m_res_label.append(QString::fromStdString(get_str_between_two_str(output.at(0).simplified().toStdString(),"(",")")));
    m_res_label.append(QString::fromStdString(")"));
    qCDebug(webcam_settings_kcm) << "New resolution " << m_res_label << ": height=" << QString::number(m_height) << " width=" << QString::number(m_width);
}

VideoDeviceResolution::~VideoDeviceResolution(){}
