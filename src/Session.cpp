//
// Created by spl211 on 05/11/2020.
//
#include "../include/Session.h"
#include <iostream>
#include <fstream>
#include "../include/json.hpp"
#include "../include/Agent.h"


using namespace std;
using json = nlohmann::json ;

Session::Session(const std::string &path):g(vector<vector<int>>()),agents(),infected(),components() {
    cycleNum = 0;
    //import the json file
    ifstream inputJ(path);
    json j;
    j << inputJ;
    //init the cur graph
    g = Graph(j["graph"]);
    //checking and setting the tree type
    string tree = j["tree"];
    if (tree == "C")
        treeType = Cycle;
    else if (tree == "M")
        treeType = MaxRank;
    else
        treeType = Root;
    // creating real agents from the input
    for(auto agent:j["agents"]){
        if (agent[0]=="V") {
            Virus *newVirus = new Virus(agent[1]);
            addAgent(*newVirus);
        }
        else {
            ContactTracer *CT = new ContactTracer();
            addAgent(*CT);
        }

    }
    //finding graph components
    components = g.findComponents();
}

void Session::simulate() {
    while (!this->isFinish()){//checking termination condition
        int curSize = agents.size();//ensure that new agents wont act
        //operate the agents
        for(int i = 0;i<curSize;i++){
            agents[i]->act(*this);
        }
        cycleNum++; // update cycleNumber
    }
    //making the output
    vector<int>infectedNodes;
    vector<bool>boolInfectedNode = g.getInfected();
    for (int i = 0; i < boolInfectedNode.size(); ++i) {
        if (boolInfectedNode[i])
            infectedNodes.push_back(i);
    }
    nlohmann::json j;
    j["infected"] = infectedNodes;
    j["graph"] = g.getEdges();
    ofstream o("output.json");
    o << j;
}

void Session::addAgent(const Agent &agent) {
    Agent *agent2add = agent.clone();
    agents.push_back(agent2add);
}
//Graph methods

void Session::setGraph(const Graph &graph){
    g = graph;
}
const Graph & Session::getGraph() const {return g;}
const int Session::getCycle() const {return cycleNum;}


//Agent actions
void Session::infectNode(int node){//should update node as infected
    g.infectNode(node);
}
bool Session::isInfected(int node) {
    return g.isInfected(node);
}

int Session::dequeueInfected() {
    int next = infected.front();
    infected.pop();
    return next;
}
void Session::enqueueInfected(int node) {
    infected.push(node);
}

TreeType Session::getTreeType() const {
    return treeType;
}

bool Session::isFinish() {
// this function check for termination condition by checking
// if each connected component is either infected or not
// using allSame
    bool ans = true;
    for (int i = 0; i < components.size() and ans; ++i) {
        if (!allSame(components[i]))
            ans = false;
    }
    return ans;
}

bool Session::allSame(vector<int> comp) {
    bool ans =true;
    bool first = isInfected(comp[0]);
    for (int i = 1; i < comp.size() and ans; ++i) {
        if (isInfected(comp[i]) != first)
            ans = false;
    }
}

//rule of 5

Session::Session(const Session& other):g(other.g),treeType(other.treeType),agents(), infected(other.infected){
    for(int i = 0;i<other.agents.size();++i){
        agents.push_back(other.agents[i]->clone());

    }
}

Session & Session::operator=(const Session &other) {
    if (this != &other){
        g = other.getGraph();
        treeType = other.treeType;
        infected = other.infected;
        for (int i = 0; i < agents.size(); ++i) {
            if (agents[i] != nullptr)
                delete agents[i];
        }
        for (int i = 0; i < other.agents.size(); ++i) {
            this->addAgent(*other.agents[i]);
        }
    }
    return *this;
}
Session::~Session() {
    for (int i = 0; i < agents.size(); ++i) {
        if (agents[i] != nullptr)
            delete agents[i];
    }
}
Session::Session(Session &&other):
g(other.g),treeType(other.treeType),
infected(other.infected),agents(other.agents) {
    for (int i = 0; i < other.agents.size(); ++i) {
        other.agents[i] = nullptr;
    }
}
Session & Session::operator=(Session &&other) {
    if (this != &other){
        g = other.g;
        treeType = other.treeType;
        infected = other.infected;
        for (int i = 0; i < agents.size(); ++i) {
            if (agents[i] != nullptr)
                delete agents[i];
        }
        agents = other.agents;
        for (int i = 0; i < other.agents.size(); ++i) {
            agents[i] = nullptr;
        }
    }
}


