#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
using namespace std;

class Graph{
public:

    Graph(std::vector<std::vector<int>> matrix);
    
    void infectNode(int nodeInd);
    bool isInfected(int nodeInd);

    std::vector<int> getNonInfNeighbors(int nodeInd);

private:
    std::vector<std::vector<int>> edges;
    //new field
    vector<bool> infectedNode;
};

#endif
