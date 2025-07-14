#pragma once

#include "types.h"

#include <string>
#include <optional>

class Table
{
public:
    Table(const int &price_per_hour);

    void set_client(const Event &event);
    void set_client_from_queue(const std::string &new_client, const std::string &event_time);
    
    void remove_client_and_count_time(const std::string &event_time);

    const bool is_occupied() const;
    const std::optional<std::string>& get_client() const;
    const int& get_revenue() const;
    const std::string get_total_time() const;
    
private:
    std::optional<std::string> client;
    int revenue = 0;
    int total_minutes = 0;
    std::string session_start_time;
    const int price;

    int count_client_minutes(const std::string &event_time);
    int pay_for(const int &minutes);
};
