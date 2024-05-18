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
            std::stringstream file_read{line};
            std::string word;
            std::vector<std::string> words;
            while (std::getline(file_read, word, ' '))
            {
                words.push_back(word);
            }
            int op_stat;
            switch (stoi(words[1]))
            {
            case 1:
                /* code */
                std::cout << "User came\n";
                op_stat = club.AddClient(words[2]);
                if (op_stat != 0){
                    std::cout << words[0] << " " << op_stat << " " << "YouShallNotPass" << std::endl;  
                }
                break;
            case 2:
                /* code */
                break;
            case 3:
                /* code */
                break;
            case 4:
                /* code */
                break;
            
            default:
                break;
            }
        }
    }
    
    // CompClub CLUB;
    in.close();     
    return 0;
}