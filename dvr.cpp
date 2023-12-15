#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <utility>

int totalNodes = 5;
int max = 999;

class node {
    public:
        // int cost;
        char nodeName;
        std::unordered_map <char, std::pair<int, std::string>> routingTable;
        std::vector <char> neighborsList;
        std::vector<node*> neighbors;

    public:
        node () {};

        void printTable() {
            std::cout << "Routing Table for Node " << nodeName << std::endl;
            std::cout << "+-----------+-----------+-----------+" << std::endl;
            for (const auto& key_value: routingTable) {
                char key = key_value.first;
                int value = key_value.second.first;
                std::string nextHop = key_value.second.second;
                std::cout << key << " | " << value << " | " << nextHop << std::endl;
            }
        };

        // parametrized constructor initializes routing table
        node (char name, int neighbours, std::vector<node*>& allNodes) {

            nodeName = name;

            for (int itr = 0; itr < totalNodes; itr++){
                char alph = 'A' + itr;

                if (alph == nodeName) {
                    routingTable[alph] = std::make_pair(0, "-");
                    continue;
                }
                routingTable[alph] = std::make_pair(max, "-");
            }

            std::cout << nodeName <<  " Table Initialization: " << std::endl;
            std::cout << "-----------------------------------------------------" << std::endl;

            printTable();

            int cost;
            char nodeID; // neighbour ID
            // adding neighbors
            for (int itr = 0; itr < neighbours; itr++){
                std::cout << "Please provide name of neighboring node: ";
                std::cin >> nodeID;
                neighborsList.push_back(nodeID);
                std::cout << std::endl;

                std::cout << "Cost of link to neighbor node " << nodeID << " ? : ";
                std::cin >> cost;
                std::cout << std::endl;

                routingTable[nodeID] = std::make_pair(cost, "-");
            }

            printTable();
            std::cout << std::endl;
        };

        void updateTable(std::vector<node *> &allNodes)
        {
            // for (int i = 0; i<neighborsList.size(); i++) {
            //     std::cout << neighborsList[i] << " ";
            // }
            // std::cout << std::endl;

            for (const auto neighborName : neighborsList)
            {
                for (auto neighborNode : allNodes)
                {
                    // std:: cout << neighborName << " skipped" << std::endl;
                    if (neighborNode->nodeName == neighborName)
                    {
                    // std:: cout << neighborName << " found same" << std::endl;
                        auto neighborTable = neighborNode->routingTable;

                        for (const auto neighborEntry : neighborTable)
                        {
                            char destination = neighborEntry.first;
                            int neighborCost = neighborEntry.second.first;

                            int newDistance = routingTable[neighborName].first + neighborCost;

                            if (newDistance < routingTable[destination].first)
                            {
                                routingTable[destination] = std::make_pair(newDistance, neighborNode->nodeName);
                            }
                        }
                    }
                    else {
                        continue;
                    }
                }
            }
            std::cout << "-------------------------------" << std::endl;
            printTable();
            std::cout << "-------------------------------" << std::endl;
        }

};

int main() {
    std::vector<node*> allNodes;
    
    node router0('A', 3, allNodes);
    allNodes.push_back(&router0);

    node router1('B', 2, allNodes);
    allNodes.push_back(&router1);

    node router2('C', 1, allNodes);
    allNodes.push_back(&router2);

    node router3('D', 2, allNodes);
    allNodes.push_back(&router3);

    node router4('E', 2, allNodes);
    allNodes.push_back(&router4);

    for (int itr = 0; itr < 3; itr++){
        router0.updateTable(allNodes);
        router1.updateTable(allNodes);
        router2.updateTable(allNodes);
        router3.updateTable(allNodes);
        router4.updateTable(allNodes);
    }

    return 0;
}