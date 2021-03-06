#include "helpers.h"

Q_LOGGING_CATEGORY(webcam_settings_kcm, "kcm.webcam_settings")

std::string exec_cmd(const std::string& command) {
    system((command + " > temp.txt").c_str());
 
    std::ifstream ifs("temp.txt");
    std::string ret{ std::istreambuf_iterator<char>(ifs), std::istreambuf_iterator<char>() };
    ifs.close(); // must close the inout stream so the file can be cleaned up
    if (std::remove("temp.txt") != 0) {
        perror("Error deleting temporary file");
    }
    return ret;
}

std::string get_str_between_two_str(const std::string &s,
        const std::string &start_delim,
        const std::string &stop_delim)
{
    unsigned first_delim_pos = s.find(start_delim);
    unsigned end_pos_of_first_delim = first_delim_pos + start_delim.length();
    unsigned last_delim_pos = s.find_first_of(stop_delim, end_pos_of_first_delim);
    
    return s.substr(end_pos_of_first_delim,
            last_delim_pos - end_pos_of_first_delim);
}

std::string get_str_right_of_substr(const std::string &s,const std::string &delim) {
    unsigned delim_pos = s.find(delim);
    unsigned end_pos_of_delim = delim_pos + delim.length();
    return s.substr(end_pos_of_delim, s.length() - end_pos_of_delim);
}
std::string get_str_left_of_substr(const std::string &s,const std::string &delim) {
    unsigned delim_pos = s.find(delim);
    
    return s.substr(0,delim_pos);
}

bool stob(std::string s)
{
    auto result = false;

    std::string lower = s;
    std::transform( lower.begin(), lower.end(), lower.begin(), ::tolower );

    if (lower == "true" || lower == "1") { result= true;}
    else{result = false;}

    return result;
}

int btoi(bool b)
{
    int result = 0;

    if (b) { result= 1;}
    else{result = 0;}

    return result;
}
