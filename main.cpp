#include "CompClub.h"
#include <fstream>
#include <sstream>
#include <ctime>
#include <iostream>

int main(){
    std::string line;
    std::ifstream in("test_file.txt");
    if (in.is_open())
    {
        
        std::getline(in, line);
        int number_of_tables = stoi(line);

        std::getline(in, line, ' ');
        std::string start_time = line;

        std::getline(in, line);
        std::string end_time = line;


        std::getline(in, line);
        int cost_of_hour = stoi(line);

        Logger logger{};

        CompClub club{start_time, end_time, cost_of_hour, number_of_tables, logger};

        while (std::getline(in, line))
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