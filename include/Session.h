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
    //Rule of 5
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
//    const Graph& getGraph() const;
//    Graph& getGraph();
    int getCycle()const;
    void isolateNode(int toIsolate);


    //Agent actions
    void enqueueInfected(int node);
    int dequeueInfected();
    Tree *createTreeBFS(int nextInf);
    void infectNode(int node); //should update node as infected
    bool isInfected(int node); //check if node was infected
    const vector<int> getValidNeighbors(int nodeInd);
    void addVirus(int nodeInd);
    const vector<bool>& getViruses()const;
    bool checkIfInfected(int nodeInd);

    TreeType getTreeType() const;
    
private:
    Graph g;
    TreeType treeType;
    std::vector<Agent*> agents;
    //new fields
    std::queue<int>infected;
    std::vector<bool>hasVirus;
    int cycleNum;
    void clear();

};

#endif
