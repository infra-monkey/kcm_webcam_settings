#include "VideoDeviceCapFormat.h"
#include "helpers.h"

VideoDeviceCapFormat::VideoDeviceCapFormat(){}
VideoDeviceCapFormat::VideoDeviceCapFormat(QString format_name) {
    m_format_name = format_name;
}

VideoDeviceCapFormat::~VideoDeviceCapFormat() {

}

void VideoDeviceCapFormat::addResolution(QString res){
    if (!m_resolution_list.contains(res)){
        m_resolution_list.append(res);
    }
}

