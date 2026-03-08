#include "json.h"

#include <regex>

json::json(const std::map<std::string, std::string> &key_value_list) : key_value_list(key_value_list) {}

std::string &json::operator[](const std::string &key) {
    if (!key_value_list.contains(key)) {
        throw std::out_of_range("The specified key (" + key + ") does not exist in the JSON object.");
    }
    return key_value_list.find(key)->second;
}

std::string json::stringify() {
    std::string json_string = "{";
    for (const auto &[key, value]: key_value_list) {
        json_string += "\n    \"" + key + "\": \"" += value + "\",";
    }
    json_string.pop_back();
    json_string += "\n}";
    return json_string;
}

json json::parse(const std::string &json_string) {
    std::map<std::string, std::string> finished_json_map{};
    const std::regex pattern(R"""("((?:[^"\\]|\\.)*)"\s*:\s*"((?:[^"\\]|\\.)*)")"""); // God I HATE regex

    const auto begin = std::sregex_iterator(json_string.begin(), json_string.end(), pattern);
    const auto end = std::sregex_iterator();

    for (auto it = begin; it != end; ++it) {
        const std::smatch &match = *it;
        finished_json_map[match[1].str()] = match[2].str();
    }

    return json(finished_json_map);
}
