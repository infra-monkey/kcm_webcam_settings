#ifndef HELPERS_H
#define HELPERS_H

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
bool stob(std::string);
int btoi(bool);

#endif
