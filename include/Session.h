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
    Session & operator=(const Session &other);

    void simulate();
    void addAgent(const Agent& agent);

    //Graph methods

    void setGraph(const Graph& graph);
    //new method

    const Graph& getGraph() const;

    //Agent actions

    void enqueueInfected(int node);
    int dequeueInfected();

    //new method
    void infectNode(int node); //should update node as infected

    TreeType getTreeType() const;
    
private:
    Graph g;
    TreeType treeType;
    std::vector<Agent*> agents;
    //new fields
    std::queue<int>infected;
};

#endif
