#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include "../include/Tree.h"

using namespace std;

class Graph{
public:

    Graph(std::vector<std::vector<int>> matrix);
    
    void infectNode(int nodeInd);
    bool isInfected(int nodeInd);

    //new methods
    std::vector<int> getNonInfNeighbors(int nodeInd) ;
    Tree* BFS(int nodeInd,const Session& session)const;
    void removeEdges(int nodeInd);
    vector<vector<int>> findComponents()const;
    const vector<vector<int>> getEdges()const;
    const vector<bool> getInfected()const;


private:
    std::vector<std::vector<int>> edges;
    //new field
    vector<bool> infectedNode;
};

#endif
