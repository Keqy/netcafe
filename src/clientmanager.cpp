#include "include/clientmanager.h"
#include "include/table.h"

#include <algorithm>
#include <format>
#include <iostream>

ClientManager::ClientManager(const WorkHours &hours, 
    const int &table_count, const int &price_per_hour)
  : work_hours(hours)
{
    for (int i = 0; i < table_count; ++i)
        tables.push_back(Table(price_per_hour));
}

const bool ClientManager::is_open_at(const std::string &event_time)
{
    return ((work_hours.open <= event_time) && (event_time < work_hours.close))
    || (work_hours.night_switch && 
      ((work_hours.open <= event_time) || (event_time < work_hours.close)));
}

void ClientManager::client_come(const Event &event)
{
    if (clients.contains(event.client)) {
        print_error(event.time, "YouShallNotPass");
        return;
    }
    if (!is_open_at(event.time)) {
        print_error(event.time, "NotOpenYet");
        return;
    }
    if (client_queue.size() > tables.size()) {
        leave_on_queue_overflow(event.client, event.time);
        return;
    }

    clients.insert(event.client);
    client_queue.push_back(event.client);
}

void ClientManager::client_sit(const Event &event)
{
    if (!clients.contains(event.client)) {
        print_error(event.time, "ClientUnknown");
        return;
    }
    if (event.table > tables.size()) {
        print_error(event.time, "NoSuchATable");
        return;
    }
    if (tables[event.table.value()].is_occupied()) {
        print_error(event.time, "PlaceIsBusy");
        return;
    }

    for (auto &t : tables) {
        if (t.get_client() == event.client) {
            t.remove_client_and_count_time(event.time);
            break;
        }
    }

    tables[event.table.value()].set_client(event);
    std::erase(client_queue, event.client);
}

void ClientManager::client_wait(const Event &event)
{
    for (const auto &t : tables) {
        if (!t.is_occupied()) {
            print_error(event.time, "ICanWaitNoLonger!");
            return;
        }
    }
    if (client_queue.size() > tables.size()) {
        leave_on_queue_overflow(event.client, event.time);
    }
}

void ClientManager::client_leave(const Event &event)
{
    if (!clients.contains(event.client)) {
        print_error(event.time, "ClientUnknown");
        return;
    }

    clients.erase(event.client);

    for (int i = 0; i < tables.size(); ++i) {
        if (tables[i].get_client() == event.client) {
            tables[i].remove_client_and_count_time(event.time);

            if(!client_queue.empty()) {
                const std::string next_client = client_queue.front();
                client_queue.pop_front();

                tables[i].set_client_from_queue(next_client, event.time);
                std::cout << std::format("{} 12 {} {}\n", event.time, next_client, i + 1);
            }

            break;
        }
    }
}

void ClientManager::leave_on_close(const std::string &client_name, const std::string &close_time)
{
    for (int i = 0; i < tables.size(); ++i) {
        if (tables[i].get_client() == client_name) {
            tables[i].remove_client_and_count_time(close_time);
            break;
        }
    }

    std::cout << std::format("{} 11 {}\n", close_time, client_name);
}

void ClientManager::leave_on_queue_overflow(const std::string &client_name, const std::string &event_time)
{
    clients.erase(client_name);
    std::erase(client_queue, client_name);

    std::cout << std::format("{} 11 {}\n", event_time, client_name);
}

void ClientManager::end_of_work()
{
    client_queue.clear();
    for (auto &client : clients) {
        leave_on_close(client, work_hours.close);
    }
    clients.clear();

    print_day_revenue();
}

void ClientManager::print_day_revenue() const
{
    std::cout << work_hours.close << std::endl;
    for (int i = 0; i < tables.size(); ++i) {
        std::cout << std::format("{} {} {}\n", i + 1, tables[i].get_revenue(), tables[i].get_total_time());
    }
}

void ClientManager::print_error(const std::string &event_time, const std::string &error_message) const
{
    std::cout << std::format("{} 13 {}\n", event_time, error_message);
}
