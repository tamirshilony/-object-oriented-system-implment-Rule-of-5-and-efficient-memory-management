#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include "Tree.h"

using namespace std;

class Graph{
public:

    Graph(std::vector<std::vector<int>> matrix);
    
    void infectNode(int nodeInd);
    bool isInfected(int nodeInd);

    //new methods
    std::vector<int> getNonInfNeighbors(int nodeInd);
    Tree* BFS(int nodeInd,const Session& session);
    void clear();
    void removeEdges(int nodeInd);

private:
    std::vector<std::vector<int>> edges;
    //new field
    vector<bool> infectedNode;
};

#endif
