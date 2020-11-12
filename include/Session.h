#ifndef SESSION_H_
#define SESSION_H_

#include <vector>
#include <queue>
#include <string>
#include "../include/Graph.h"

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

    //new method
    const Graph& getGraph() const;
    const int getCycle()const;

    //Agent actions

    void enqueueInfected(int node);
    int dequeueInfected();

    //new method
    void infectNode(int node); //should update node as infected
    bool isInfected(int node); //check if node was infected
    TreeType getTreeType() const;
    
private:
    Graph g;
    TreeType treeType;
    std::vector<Agent*> agents;
    //new fields
    std::queue<int>infected;

    int cycleNum;
    Graph components;
    bool isFinish();
    bool allSame(vector<int>comp);
};

#endif
