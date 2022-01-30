#ifndef HELPERS_H
#define HELPERS_H

#undef QT_NO_CAST_FROM_ASCII

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <sys/ioctl.h>
#include <QLoggingCategory>

Q_DECLARE_LOGGING_CATEGORY(webcam_settings_kcm)


std::string exec_cmd(const std::string&);
std::string get_str_between_two_str(const std::string &,const std::string &,const std::string &);
std::string get_str_right_of_substr(const std::string &,const std::string &);
std::string get_str_left_of_substr(const std::string &,const std::string &);

#endif
