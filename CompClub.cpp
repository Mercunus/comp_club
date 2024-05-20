#include "CompClub.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <string>
#include <cstring>
#include <sstream>

int prepare_time (const std::string &got_time){
        std::string delimeter = ":";
        std::string hours = got_time.substr(0, got_time.find(delimeter));
        std::string minuties = got_time.substr((got_time.find(delimeter)+1), (got_time.size()-1));

        // std::cout << hours << std::endl;
        // std::cout << minuties << std::endl;
        return stoi(hours)*60 + stoi(minuties);
}

int find_time_diff(const std::string &sit, const std::string &leave){
        int start = prepare_time(sit);
        int stop = prepare_time(leave);
        int result = stop - start;
        return result; 
}

std::string print_time(int time_in_minutes) {
    std::stringstream ret_stream;
    ret_stream << std::setfill('0') << std::setw(2) << time_in_minutes / 60 <<
    ':' << std::setfill('0') << std::setw(2) << time_in_minutes % 60;
    return ret_stream.str();
}

CompClub::~CompClub()
{
}
int CompClub::AddClient(const std::string & cli_name, const std::string &cli_time) {
    if ((prepare_time(cli_time) < (this->start_time)) || (prepare_time(cli_time) > (this->end_time))){
        return 2; //NotOpenYet
    }

    if (std::find_if(clients.begin(), clients.end(), [cli_name](const Client& client){
        return client.name == cli_name;
    }) == clients.end()){
        clients.push_back({cli_name, -1});
    }
    else {
        return 1; //YouShallNotPass
    }
    return -1;
}
int CompClub::SitClient(const std::string & cli_name, const std::string &cli_table, const std::string &time) {
    auto found_client = std::find_if(clients.begin(), clients.end(), [cli_name](const Client& client){
        return (cli_name.compare(client.name) == 0);
    });
    if ( found_client == clients.end()){
        
        return 3; //ClientUnknown
    }
    if (tables[stoi(cli_table)-1].free == true){
        tables[stoi(cli_table)-1].free = false;
        tables[stoi(cli_table)-1].acquire_time = prepare_time(time);
        // освободить старый стол
        if (found_client->table != -1) {
            tables[found_client->table - 1].free = true;
            int dur_cur = prepare_time(time) - tables[found_client->table - 1].acquire_time;
            tables[found_client->table - 1].duration += dur_cur;

            int hours = dur_cur / 60;
            if (dur_cur % 60) hours += 1;
            tables[found_client->table - 1].earned_money += cost_per_hour * hours;
        }
        if (!queue_to_sit.empty() && queue_to_sit.front()->name == cli_name)
        {
            queue_to_sit.pop();
        }

        found_client->table=stoi(cli_table);
    }
    else 
    {
        return 4; //PlaceIsBusy
    }
    
    return -1;
}

int CompClub::WaitForTable(const std::string &name, const std::string &time){
    auto found_client = std::find_if(clients.begin(), clients.end(), [name](const Client& client){
        return client.name == name;
    });
    for (const auto &table: tables){
        if (table.free){
            return 5; // ICanWaitNoLonger!
        }
    }
    if (queue_to_sit.size() > this->tables_count ){
        RemoveClient(name, time);
        return 11; // ID 11 клиент ушел
    }
    else{
        queue_to_sit.push(&(*found_client));
    }
    return -1;
 }


int CompClub::RemoveClient(const std::string & cli_left, const std::string &time) {
    auto found_client = std::find_if(clients.begin(), clients.end(), [cli_left](const Client& client){
    return client.name == cli_left;
    });
    if ( found_client == clients.end()){
        return -3; //ClientUnknown
    }
    if (queue_to_sit.empty()){
        tables[found_client->table-1].free = true;

        int dur_cur = prepare_time(time) - tables[found_client->table - 1].acquire_time;
        int hours = dur_cur / 60;
        if (dur_cur % 60) hours += 1;
        tables[(found_client->table)-1].duration += dur_cur;
        tables[found_client->table - 1].earned_money += cost_per_hour * hours;

        clients.erase(found_client);
    }
    else{

        int dur_cur = prepare_time(time) - tables[found_client->table - 1].acquire_time;
        int hours = dur_cur / 60;
        if (dur_cur % 60) hours += 1;
        tables[found_client->table - 1].earned_money += cost_per_hour * hours;
        tables[(found_client->table)-1].duration += dur_cur;

        queue_to_sit.front()->table = found_client->table;
        tables[found_client->table - 1].acquire_time = prepare_time(time);
        std::cout << time << " 12 " << queue_to_sit.front()->name << ' ' << queue_to_sit.front()->table << std::endl;
        queue_to_sit.pop();
        clients.erase(found_client);
        return -2; // ID 12
    }
    
    return -1;
}
void CompClub::Open(){

}
void CompClub::Close(){
    std::sort(clients.begin(), clients.end(), [](const Client& client1, const Client& client2){
    return client1.name < client2.name;
    });
    for (const auto &name: clients) {
        std::cout << print_time(end_time) << " 11 " << name.name << std::endl;
        RemoveClient(name.name, print_time(end_time));
    }
    std::cout << print_time(end_time) << std::endl;
    for (unsigned i = 1; const auto &table: tables) {
        std::cout << i << ' ' << table.earned_money << ' ' << print_time(table.duration) << std::endl;
        ++i;
    }
}

CompClub::CompClub(std::string start_time, std::string end_time, int cost, int number_tables, Logger& logger) :
    start_time(prepare_time(start_time)),
    end_time(prepare_time(end_time)),
    cost_per_hour(cost),
    tables_count(number_tables),
    tables(number_tables, Table()),
    logger(logger) 
    {
        isOpen = false;
        std::cout << print_time(this->start_time) << std::endl;
    }