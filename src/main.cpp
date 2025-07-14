#include "include/filedata.h"
#include "include/clientmanager.h"

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <functional>

int run_simulation(const std::string &filepath)
{
    FileData data(filepath);
    ClientManager manager(data.get_work_hours(), data.get_table_count(), data.get_price());

    const std::unordered_map<int, void (ClientManager::*)(const Event &)> handlers = {
        {EventType::Come, &ClientManager::client_come},
        {EventType::Sit, &ClientManager::client_sit},
        {EventType::Wait, &ClientManager::client_wait},
        {EventType::Leave, &ClientManager::client_leave}
    };

    std::cout << data.get_work_hours().open << '\n';

    std::vector<Event> events = data.get_events();
    for (const auto &event : events) {
        std::cout << event.raw << '\n';

        auto it = handlers.find(event.income_code);
        if (it != handlers.end()) {
            std::invoke(it->second, manager, event);
        } else {
            throw std::invalid_argument(event.raw);
        }
    }
    manager.end_of_work();
    return 0;
}

int main(int argc, char* argv[])
{
    if (argc < 2) {
        std::cerr << "Usage: netcafe <input_file>" << std::endl;
        return 1;
    }

    try {
        return run_simulation(argv[1]);
    } catch (const std::runtime_error &err) {
        std::cerr << "Couldn't open file for reading: " << err.what() << std::endl;
        return 2;
    } catch (const std::invalid_argument &err) {
        std::cerr << "Wrong data format: " << err.what() << std::endl;
        return 3;
    }
}
