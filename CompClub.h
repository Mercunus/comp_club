
#include "Table.h"
#include "Logger.h"
#include <vector>
#include <queue>
#include <string>

int prepare_time (const std::string &got_time);

struct Client
{
    std::string name;
    int table;
};
class CompClub
{
private:
    std::vector<Client> clients;
    std::vector<Table> tables;
    std::queue<Client*> queue_to_sit;
    Logger& logger;
    bool isOpen;
    int tables_count;
    int cost_per_hour;

    int start_time, end_time;
public:
    int AddClient(const std::string &add, const std::string &time);
    int SitClient(const std::string &sit, const std::string &table, const std::string &time);
    int WaitForTable(const std::string &name, const std::string &time);
    int RemoveClient(const std::string &remove, const std::string &time);
    void Open();
    void Close();
    CompClub(std::string start_time, std::string end_time, int cost, int number_tables, Logger& logger);
    ~CompClub();
};