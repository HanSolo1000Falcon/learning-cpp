#ifndef LEARNING_PROJECTS_JSON_H
#define LEARNING_PROJECTS_JSON_H
#include <map>
#include <string>

class json {
    std::map<std::string, std::string> key_value_list;

public:
    json(const std::map<std::string, std::string> &key_value_list);
    std::string &operator[](const std::string &key);
    std::string stringify();

    static json parse(const std::string &json_string);
};

#endif // LEARNING_PROJECTS_JSON_H
