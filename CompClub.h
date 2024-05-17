#include "Client.h"
#include "Table.h"
#include "Logger.h"
#include <vector>
#include <queue>
class CompClub
{
private:
    std::vector<Client*> clients;
    std::vector<Table> tables;
    std::queue<Client*> queue_to_sit;
    Logger logger;
    bool isOpen;
    int tables_count;
    int cost_per_hour;
public:
    void AddClient(Client &);
    void SitClient(Client &);
    void RemoveClient(Client &);
    void Open();
    void Close();
    CompClub(/* args */);
    ~CompClub();
};