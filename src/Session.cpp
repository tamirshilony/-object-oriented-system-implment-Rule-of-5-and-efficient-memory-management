//
// Created by spl211 on 05/11/2020.
//
#include "../include/Session.h"

using namespace std;
using json = nlohmann::json ;

Session::Session(const std::string &path):
g(vector<vector<int>>()),
treeType(),
agents(),
infected(),
hasVirus(),
cycleNum(0){
    //import the json file
    std::ifstream inputJ(path);
    json j;
    inputJ >> j ;
    //init the cur graph
    vector<vector<int>> jGraph = j["graph"];
    g = Graph(jGraph);
    hasVirus = vector<bool>(g.getEdges().size(), false);
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
            hasVirus[agent[1]] = true;
            delete newVirus;
        }
        else {
            ContactTracer *CT = new ContactTracer();
            addAgent(*CT);
            delete CT;
        }

    }
    //finding graph components
}

void Session::simulate() {
    while (!g.areCompsUniform(hasVirus)){//checking termination condition
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
    int infVecLen = boolInfectedNode.size();
    for (int i = 0; i < infVecLen; ++i) {
        if (boolInfectedNode[i])
            infectedNodes.push_back(i);
    }
    nlohmann::json j;
    j["infected"] = infectedNodes;
    j["graph"] = g.getEdges();
    ofstream o("output1.json");
    o << j;
    std::cout<<j<<endl;
}

void Session::addAgent(const Agent &agent) {
    Agent *agent2add = agent.clone();
    agents.push_back(agent2add);
}
//Graph methods

void Session::setGraph(const Graph &graph){
    g = graph;
}
//const Graph & Session::getGraph() const {return g;}
//Graph & Session::getGraph() {return g;}

int Session::getCycle() const {return cycleNum;}



//Agent actions
void Session::infectNode(int node){//should update node as infected
    g.infectNode(node);
    enqueueInfected(node);
}
bool Session::isInfected(int node) {
    return g.isInfected(node);
}
const vector<int> Session::getValidNeighbors(int nodeInd) {
    return g.getNonInfNeighbors(nodeInd, hasVirus);
}

int Session::dequeueInfected() {
    if(infected.size() == 0)
        return -1;
    int next = infected.front();
    infected.pop();
    return next;
}
void Session::enqueueInfected(int node) {
    infected.push(node);
}
void Session::addVirus(int nodeInd) {
    hasVirus[nodeInd] = true;
}
const vector<bool> &Session::getViruses() const {
    return hasVirus;
}
bool Session::checkIfInfected(int nodeInd) {
    return g.isInfected(nodeInd);
}
Tree * Session::createTreeBFS(int nextInf) {
    return g.BFS(nextInf, *this);
}

TreeType Session::getTreeType() const {
    return treeType;
}

void Session::isolateNode(int toIsolate) {
    g.removeEdges(toIsolate);
}

//Rule of 5

Session::Session(const Session& other):
g(other.g),
treeType(other.treeType),
agents(),
infected(other.infected),
hasVirus(other.hasVirus),
cycleNum(other.cycleNum){
    int otherNAgents = other.agents.size();
    for(int i = 0;i<otherNAgents;++i){
        agents.push_back(other.agents[i]->clone());

    }
}

Session & Session::operator=(const Session &other) {
    if (this != &other){
        g = other.g;
        treeType = other.treeType;
        infected = other.infected;
        hasVirus = other.hasVirus;
        cycleNum = other.cycleNum;
        int nAgents = agents.size();
        for (int i = 0; i < nAgents; ++i) {
            if (agents[i] != nullptr)
                delete agents[i];
        }
        int otherNAgents = other.agents.size();
        for (int i = 0; i < otherNAgents; ++i) {
            this->addAgent(*other.agents[i]);
        }
    }
    return *this;
}
Session::~Session() {
    int nAgents = agents.size();
    for (int i = 0; i < nAgents; ++i) {
        if (agents[i] != nullptr)
            delete agents[i];
    }
}
Session::Session(Session &&other):
g(other.g),
treeType(other.treeType),
agents(other.agents),
infected(other.infected),
hasVirus(other.hasVirus),
cycleNum(other.cycleNum) {
    int otherNAgents = other.agents.size();
    for (int i = 0; i < otherNAgents; ++i) {
        other.agents[i] = nullptr;
    }
}
Session & Session::operator=(Session &&other) {
    if (this != &other){
        g = other.g;
        treeType = other.treeType;
        infected = other.infected;
        hasVirus = other.hasVirus;
        cycleNum = other.cycleNum;
        int nAgents = agents.size();
        for (int i = 0; i < nAgents; ++i) {
            if (agents[i] != nullptr)
                delete agents[i];
        }
        agents = other.agents;
        int otherNAgents = other.agents.size();
        for (int i = 0; i < otherNAgents; ++i) {
            agents[i] = nullptr;
        }
    }
    return *this;
}



