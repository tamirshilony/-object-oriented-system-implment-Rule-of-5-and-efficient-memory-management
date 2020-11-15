#ifndef GRAPH_H_
#define GRAPH_H_

#include "Tree.h"
#include "iostream"

using namespace std;

class Graph{
public:

    Graph(std::vector<std::vector<int>> matrix);
    
    void infectNode(int nodeInd);
    bool isInfected(int nodeInd) const;

    //new methods
    std::vector<int> getNonInfNeighbors(int nodeInd) const;
    Tree* BFS(int nodeInd,const Session& session)const;
    void removeEdges(int nodeInd);
    vector<vector<int>> findComponentsBFS()const;
    const vector<vector<int>> getEdges()const;
    const vector<bool> getInfected()const;
    bool areCompsUniform(vector<bool> hasVirus);


private:
    std::vector<std::vector<int>> edges;
    //new field
    vector<bool> infectedNode;
    std::vector<std::vector<int>>components;

    bool isCompUniform(vector<int> comp);
    bool isCompVirusFree(vector<int> comp , vector<bool>hasVirus);
};

#endif
