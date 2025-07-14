#pragma once
#include "types.h"
#include "table.h"

#include <string>
#include <deque>
#include <vector>
#include <set>

class ClientManager
{
public:
    ClientManager(const WorkHours &hours, const int &table_count, const int &price);

    void client_come(const Event &event);
    void client_sit(const Event &event);
    void client_wait(const Event &event);
    void client_leave(const Event &event);
    
    void end_of_work();

private:
    const WorkHours work_hours;
    std::set<std::string> clients;
    std::deque<std::string> client_queue;
    std::vector<Table> tables;
    
    void leave_on_close(const std::string &client_name, const std::string &close_time);
    void leave_on_queue_overflow(const std::string &client_name, const std::string &close_time);

    const bool is_open_at(const std::string &event_time);
    void print_day_revenue() const;
    void print_error(const std::string &event_time, const std::string &error_message) const;
};
