
#include "Table.h"
#include "Logger.h"
#include <vector>
#include <queue>
#include <string>
class CompClub
{
private:
    std::vector<std::string> clients;
    std::vector<Table> tables;
    std::queue<std::string> queue_to_sit;
    Logger& logger;
    bool isOpen;
    int tables_count;
    int cost_per_hour;

    int start_time, end_time;
public:
    int AddClient(const std::string &add);
    void SitClient(const std::string &sit);
    void RemoveClient(const std::string &remove);
    void Open();
    void Close();
    CompClub(std::string start_time, std::string end_time, int cost, int number_tables, Logger& logger);
    ~CompClub();
};