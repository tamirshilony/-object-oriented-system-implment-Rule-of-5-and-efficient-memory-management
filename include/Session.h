#ifndef SESSION_H_
#define SESSION_H_

#include <vector>
#include <queue>
#include <string>
#include <iostream>
#include <fstream>
#include "json.hpp"
#include "Graph.h"
#include "Agent.h"

class Agent;

enum TreeType{
  Cycle,
  MaxRank,
  Root
};

class Session{
public:
    //rule of five
    Session(const Session& other);
    Session & operator=(const Session &other);
    virtual ~Session();
    Session(Session&& other);
    Session & operator=(Session &&other);



    Session(const std::string& path);
    void simulate();
    void addAgent(const Agent& agent);

    //Graph methods
    void setGraph(const Graph& graph);

    const Graph& getGraph() const;
    Graph& getGraph();
    const int getCycle()const;


    //Agent actions
    void enqueueInfected(int node);
    int dequeueInfected();

    void infectNode(int node); //should update node as infected
    bool isInfected(int node); //check if node was infected
    bool checkVirus(int nodeInd);
    void addVirus(int nodeInd);
    TreeType getTreeType() const;
    
private:
    Graph g;
    TreeType treeType;
    std::vector<Agent*> agents;
    //new fields
    std::queue<int>infected;
    std::vector<bool>hasVirus;
    int cycleNum;

};

#endif
