#include "include/table.h"

#include <format>

Table::Table(const int &price_per_hour)
    : price(price_per_hour) {}

const bool Table::is_occupied() const
{
    return client.has_value();
}

void Table::set_client(const Event &event)
{
    client = event.client;
    session_start_time = event.time;
}

void Table::set_client_from_queue(const std::string &new_client, const std::string &event_time)
{
    client = new_client;
    session_start_time = event_time;
}

void Table::remove_client_and_count_time(const std::string &event_time) {
    client.reset();
    int client_minutes = count_client_minutes(event_time);
    total_minutes += client_minutes;
    revenue += pay_for(client_minutes);
}

int Table::count_client_minutes(const std::string& event_time)
{
    int end_session_hour = std::stoi(event_time.substr(0, 2));
    int end_session_minutes = std::stoi(event_time.substr(3, 2));
    int start_session_hour = std::stoi(session_start_time.substr(0, 2));
    int start_session_minutes = std::stoi(session_start_time.substr(3, 2));
    
    int start_minutes = start_session_hour * 60 + start_session_minutes;
    int end_minutes = end_session_hour * 60 + end_session_minutes;

    if (end_minutes < start_minutes) {
        end_minutes += 24 * 60;
    }

    return end_minutes - start_minutes;
}

int Table::pay_for(const int &minutes)
{
    return ((minutes + 60 - 1) / 60) * price;
}

const std::optional<std::string>& Table::get_client() const
{
    return client;
}

const int& Table::get_revenue() const
{
    return revenue;
}

const std::string Table::get_total_time() const
{
    int hours = total_minutes / 60;
    int minutes = total_minutes - (hours * 60);
    return std::format("{:02d}:{:02d}", hours, minutes);
}