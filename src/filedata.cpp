#include "include/filedata.h"

#include <regex>
#include <fstream>

FileData::FileData(const std::string& file_path)
{
    std::ifstream file {file_path};
    if (!file.is_open()) {
        throw std::runtime_error(file_path);
    }

    try {
        std::string str;
        std::getline(file, str); table_count = parse_table_count_from_string(str);
        std::getline(file, str); work_hours  = parse_work_hours_from_string(str);
        std::getline(file, str); price       = parse_price_from_string(str);

        while (std::getline(file, str)) {
            events.push_back(parse_event_from_string(str));
        }
    } catch (const std::invalid_argument &err) {
        throw err;
    }
}

const int FileData::parse_table_count_from_string(const std::string &table_count_str)
{
    std::smatch match;
    if (!std::regex_match(table_count_str, match, regex_patterns::number)) {
        throw std::invalid_argument(table_count_str);
    }
    return std::stoi(match[0]);
}

const WorkHours FileData::parse_work_hours_from_string(const std::string &work_hours_str)
{
    std::smatch match;
    if (!std::regex_match(work_hours_str, match, regex_patterns::time_work_hours)) {
        throw std::invalid_argument{work_hours_str};
    }
    return WorkHours{match[1], match[3]};
}

const int FileData::parse_price_from_string(const std::string& price_str)
{
    std::smatch match;
    if (!std::regex_match(price_str, match, regex_patterns::number)) {
        throw std::invalid_argument(price_str);
    }
    return std::stoi(match[0]);
}

const Event FileData::parse_event_from_string(const std::string &event_string)
{
    std::smatch match;
    if (!std::regex_match(event_string, match, regex_patterns::event)) {
        throw std::invalid_argument(event_string);
    }
    std::optional<int> opt_table;
    if (match[4].matched) opt_table = std::stoi(match[4]);

    return Event(match[0], match[1], std::stoi(match[2]), match[3], opt_table);
}

const int& FileData::get_table_count() const
{
    return table_count;
}

const WorkHours& FileData::get_work_hours() const
{
    return work_hours;
}

const int& FileData::get_price() const 
{
    return price;
}

const std::vector<Event>& FileData::get_events() const 
{
    return events;
}