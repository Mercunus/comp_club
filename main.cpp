#include "CompClub.h"
#include <fstream>
#include <sstream>
#include <ctime>
#include <iostream>
#include <regex>

int main(int argc, char *argv[]) {

    if (argc == 1) {
        std::cout << "NeedATextFile" << std::endl;
        return 0; 
    }
    std::regex time_pattern{"[0-9]{2}:[0-9]{2}"};
    std::regex names_pattern{"[a-z0-9_/-]+"};
    std::regex num_pattern{"[0-9]+"};
    std::ifstream in{argv[1]};
    std::string line;
    //std::ifstream in{"test_file.txt"};
    if (in.is_open())
    {
        
        std::getline(in, line);
        int found_r = line.find('\r');
        if (found_r > 0 && found_r < line.size()) line.replace(found_r, 1, "");
        if (!std::regex_match(line, num_pattern))
        {
            std::cout << line << std::endl;
            return(0);
        }
        int number_of_tables = stoi(line);

        std::getline(in, line, ' ');
        found_r = line.find('\r');
        if (found_r > 0 && found_r < line.size()) line.replace(found_r, 1, "");
        std::string start_time = line;
        
        std::getline(in, line);
        found_r = line.find('\r');
        if (found_r > 0 && found_r < line.size()) line.replace(found_r, 1, "");
        std::string end_time = line;
        if (!std::regex_match(start_time, time_pattern) || !std::regex_match(end_time, time_pattern))
        {
            std::cout << start_time << " " << end_time << std::endl;
            return(0);
        }

        std::getline(in, line);
        found_r = line.find('\r');
        if (found_r > 0 && found_r < line.size()) line.replace(found_r, 1, "");
        if (!std::regex_match(line, num_pattern))
        {
            std::cout << line << std::endl;
            return(0);
        }
        int cost_of_hour = stoi(line);
        std::vector<std::string> parsed_lines{};
        int curr_time = 0;
        while (std::getline(in, line))
        {
            std::string word;
            std::vector<std::string> words;
            std::stringstream file_read{line};
            while (std::getline(file_read, word, ' '))
            {
                int found_r = word.find('\r');
                if (found_r < word.size()) word.replace(found_r, 1, "");
                words.push_back(word);
            }

            if (words.size() < 3 ||
                !std::regex_match(words[0], time_pattern) ||
                !std::regex_match(words[1], num_pattern) ||
                !std::regex_match(words[2], names_pattern))
            {
                std::cout << line << std::endl;
                return(0);
            }

            if (words.size() == 4 && !std::regex_match(words[3], num_pattern))
            {
                std::cout << line << std::endl;
                return(0);
            }
            if (curr_time > prepare_time(words[0]))
            {
                std::cout << line << std::endl;
                return(0);
            }
            curr_time = prepare_time(words[0]);
            parsed_lines.push_back(line);
        }

        Logger logger{};
        CompClub club{start_time, end_time, cost_of_hour, number_of_tables, logger};

        for (const auto& line: parsed_lines)
        {
            std::cout << line << std::endl;
            std::stringstream file_read{line};
            std::string word;
            std::vector<std::string> words;
            while (std::getline(file_read, word, ' '))
            {
                int found_r = word.find('\r');
                if (found_r < word.size()) word.replace(found_r, 1, "");
                words.push_back(word);
            }
            int op_stat;
            switch (stoi(words[1]))
            {
            case 1: // ID 1 клиент пришел
                /* code */
                
                op_stat = club.AddClient(words[2], words[0]);
                if (op_stat == 1){
                    std::cout << words[0] << " 13" << " " << "YouShallNotPass" << std::endl;  
                }
                 else if (op_stat == 2){
                    std::cout << words[0] << " 13" << " " << "NotOpenYet" << std::endl;  
                }
                break;
            case 2: // ID 2 клиент сел за стол
                 op_stat = club.SitClient(words[2], words[3], words[0]);
                if (op_stat == 3){
                    std::cout << words[0] << " 13" << " " << "ClientUnknown" << std::endl;  
                }
                 else if (op_stat == 4){
                    std::cout << words[0] << " 13" << " " << "PlaceIsBusy" << std::endl;  
                }
                break;
            case 3: // ID 3 клиент ожидает
                op_stat = club.WaitForTable(words[2], words[0]);
                if (op_stat == 5){
                    std::cout << words[0] << " 13" << " " << "ICanWaitNoLonger!" << std::endl;  
                }
                 else if (op_stat == 11){
                    std::cout << words[0] << " 11" << " " << words[2] << std::endl;  
                }
                break;
            case 4: // ID 4 клиент ушел
                op_stat = club.RemoveClient(words[2], words[0]);
                if (op_stat == -3){
                    std::cout << words[0] << " 13" << " " << "ClientUnknown" << std::endl;  
                }
                 else if (op_stat > 0){
                    std::cout << words[0] << " 12" << " " << words[2] << " " << op_stat << std::endl;  
                }
                break;
            
            default:
                break;
            }
        }
        club.Close();
    }
    
    // CompClub CLUB;
    in.close();     
    return 0;
}