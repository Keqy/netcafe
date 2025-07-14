#pragma once

#include <string>
#include <optional>

struct WorkHours
{
    std::string open;
    std::string close;
    bool night_switch;

    WorkHours(const std::string open_time, const std::string close_time);
    
    WorkHours& operator=(const WorkHours &wh) = default;
};

struct Event
{
    const std::string raw;
    const std::string time;
    const int income_code;
    const std::string client;
    std::optional<int> table;

    Event(std::string raw_str,
        std::string event_time, 
        int income,
        std::string client_name, 
        std::optional<int> table);
};

enum EventType
{
    Come = 1,
    Sit = 2,
    Wait = 3,
    Leave = 4
};
