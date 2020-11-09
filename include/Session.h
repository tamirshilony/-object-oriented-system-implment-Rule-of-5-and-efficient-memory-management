#ifndef SESSION_H_
#define SESSION_H_

#include <vector>
#include <queue>
#include <string>
#include "Graph.h"

class Agent;

enum TreeType{
  Cycle,
  MaxRank,
  Root
};

class Session{
public:
    Session(const std::string& path);
    Session(const Session& other);

    void simulate();
    void addAgent(const Agent& agent);

    //Graph methods
    void setGraph(const Graph& graph);
    std::vector<int>* getNonInfNeighbors(int node);

    //Agent actions
    void infectNode(int node); //should update node as infected and use nqueueInfected()
    void enqueueInfected(int node);
    int dequeueInfected();
    TreeType getTreeType() const;
    
private:
    Graph g;
    TreeType treeType;
    std::vector<Agent*> agents;
    std::queue<int>infected;
};

#endif
