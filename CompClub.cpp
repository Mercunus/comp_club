#include "CompClub.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <string>
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
int CompClub::AddClient(const std::string & cli_name) {
    if (std::find(clients.begin(), clients.end(), cli_name) == clients.end()){
        clients.push_back(cli_name);
    }
    else {
       
        return 13;
    }
    return 0;
}
void CompClub::SitClient(const std::string & cli_sit) {

}
void CompClub::RemoveClient(const std::string & cli_left) {

}
void CompClub::Open(){

}
void CompClub::Close(){

}

CompClub::CompClub(std::string start_time, std::string end_time, int cost, int number_tables, Logger& logger) :
    start_time(prepare_time(start_time)),
    end_time(prepare_time(end_time)),
    cost_per_hour(cost),
    tables_count(number_tables),
    logger(logger) 
    {
        isOpen = false;
        std::cout << print_time(this->start_time) << std::endl;
    }