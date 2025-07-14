#pragma once
#include "types.h"

#include <vector>
#include <string>
#include <regex>

namespace regex_patterns
{
    inline const std::regex number {R"(^\d+\s*\r?$)"};
    inline const std::regex time_work_hours {R"(^(([01]\d|2[0-3]):[0-5]\d) (([01]\d|2[0-3]):[0-5]\d)\s*\r?$)"};
    inline const std::regex time {R"(^([01]\d|2[0-3]):[0-5]\d\s*\r?$)"};
    inline const std::regex event {R"(^(\d{2}:\d{2}) (\d+) ([A-Za-z0-9_-]+)(?: (\d+))?\s*\r?$)"};
};

class FileData
{
private:
    int table_count;
    WorkHours work_hours{"", ""};
    int price;
    std::vector<Event> events;

    const int parse_table_count_from_string(const std::string &table_count_str);
    const WorkHours parse_work_hours_from_string(const std::string &work_hours_str);
    const int parse_price_from_string(const std::string &price_str);
    const Event parse_event_from_string(const std::string &event_string);

public:
    FileData(const std::string &file);

    const int& get_table_count() const;
    const WorkHours& get_work_hours() const;
    const int& get_price() const;
    const std::vector<Event>& get_events() const;
};
