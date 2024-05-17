#include <iostream>
#include "CompClub.h"
#include <fstream>
#include <string>
#include <sstream>

int main(){
    std::string line;
    std::ifstream in("test_file.txt");
    if (in.is_open())
    {
        
        std::getline(in, line);
        int number_of_tables = stoi(line);
        std::getline(in, line, ' ');
        std::string open_time = line;
        std::getline(in, line);
        std::string close_time = line;
        std::getline(in, line);
        int cost_of_hour = stoi(line);

        while (std::getline(in, line))
        {
            std::stringstream file_read{line};
            std::string word;
            while (std::getline(file_read, word, ' '))
            {
                std::cout << word << std::endl;
            }
            //std::cout << line << std::endl;
        }
    }
    
    CompClub CLUB;
    in.close();     
    return 0;
}