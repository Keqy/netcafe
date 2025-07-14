#include "include/types.h"

#include <string>

WorkHours::WorkHours(const std::string open_time,
    const std::string close_time)
  : open(open_time), 
    close(close_time),
    night_switch(open_time > close_time) {}

Event::Event(std::string raw_str,
    std::string event_time, 
    int income, 
    std::string client_name, 
    std::optional<int> table_number)
  : raw(std::move(raw_str)), 
    time(std::move(event_time)), 
    income_code(std::move(income)), 
    client(std::move(client_name)),
    table(table_number ? std::make_optional(*table_number - 1) : std::nullopt) {}
