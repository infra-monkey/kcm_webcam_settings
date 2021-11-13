#include "VideoDeviceCapFormat.h"
#include "helpers.h"

VideoDeviceCapFormat::VideoDeviceCapFormat(){}
VideoDeviceCapFormat::VideoDeviceCapFormat(QString format_name, QString devpath) {
    m_format_name = format_name;
    m_device_path = devpath;
}

VideoDeviceCapFormat::~VideoDeviceCapFormat() {

}

void VideoDeviceCapFormat::addResolution(QString res){
    VideoDeviceResolution new_res = VideoDeviceResolution(res,m_format_name,m_device_path);
    m_resolutions.push_back(new_res);
    if (!m_resolution_list.contains(new_res.getLabel())){
        m_resolution_list.append(new_res.getLabel());
    }
}

