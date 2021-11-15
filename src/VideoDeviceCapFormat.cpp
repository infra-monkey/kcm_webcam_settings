#include "VideoDeviceCapFormat.h"
#include "helpers.h"

VideoDeviceCapFormat::VideoDeviceCapFormat(){}
VideoDeviceCapFormat::VideoDeviceCapFormat(QString format_name, QString devpath) {
    m_format_name = format_name;
    m_device_path = devpath;
    initializeResolutions();
}

VideoDeviceCapFormat::~VideoDeviceCapFormat() {

}

void VideoDeviceCapFormat::initializeResolutions() {
    qCDebug(webcam_settings_kcm) << "Initializing resolutions for video device with path " << m_device_path;
    std::string cmd;
    int i=0;
    bool resolution_exists;

    cmd = std::string("v4l2-ctl -d " + m_device_path.toStdString() + " --get-fmt-video | grep \"Width/Height\"");
    QString current_resolution = QString::fromStdString(get_str_right_of_substr(exec_cmd(cmd),":")).replace(QString::fromStdString("/"), QString::fromStdString("x")).simplified();

    cmd = std::string("v4l2-ctl -d " + m_device_path.toStdString() + " --list-framesizes " + getFormatName().toStdString() + " | grep Size");
    QStringList output = QString::fromStdString(exec_cmd(cmd)).split(QLatin1Char('\n'));
    for (QString & line : output){
        resolution_exists = false;
        if (line.length() == 0){break;}
        QString res = QString::fromStdString(get_str_right_of_substr(line.simplified().trimmed().toStdString(),"Discrete ")).simplified();
        // do not add the resolution if it already exists
        for (VideoDeviceResolution & tmpres : m_resolutions){
            if (tmpres.getRes().toStdString() == res.toStdString()){
                resolution_exists = true;
                break;
            }
        }
        if (!resolution_exists){
            qCDebug(webcam_settings_kcm) << m_device_path << "with format : " << getFormatName() << " add resolution " << res;
            if (current_resolution.toStdString() == res.toStdString()){
                m_current_resolution_index = i;
                addResolution(res,true);
            } else {
                addResolution(res,false);
            }
            i++;
        }
    }
    qCDebug(webcam_settings_kcm) << m_device_path << "with format : " << getFormatName() << " currently uses resolution " << m_current_resolution.getLabel();
}

void VideoDeviceCapFormat::addResolution(QString res, bool is_current){
    VideoDeviceResolution new_res = VideoDeviceResolution(res,m_format_name,m_device_path);
    m_resolutions.push_back(new_res);
    if (!m_resolution_list.contains(new_res.getLabel())){
        m_resolution_list.append(new_res.getLabel());
    }
    if (is_current){
        m_current_resolution = new_res;
    }
}

void VideoDeviceCapFormat::setResolutionIndex(int resindex){
    int i = 0;
    for (VideoDeviceResolution & res : m_resolutions){
        if (i == resindex){
            m_current_resolution = res;
        }
        i++;
    }
    m_current_resolution_index = resindex;
    qCDebug(webcam_settings_kcm) << m_device_path << "with format : " << getFormatName() << " change resolution to " << m_current_resolution.getLabel();

}

void VideoDeviceCapFormat::applyResolution(){
    std::string cmd;
    cmd = std::string("v4l2-ctl -d " + m_device_path.toStdString() + " --set-fmt-video width=" + std::to_string(m_current_resolution.getWidth()) + ",height=" + std::to_string(m_current_resolution.getHeight()) + ",pixelformat=" + getFormatName().toStdString());
    exec_cmd(cmd);
    qCDebug(webcam_settings_kcm) << "applyResolution : " << QString::fromStdString(cmd);
}
