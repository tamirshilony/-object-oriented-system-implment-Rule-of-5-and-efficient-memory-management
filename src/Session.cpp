//
// Created by spl211 on 05/11/2020.
//
#include "../include/Session.h"

using namespace std;
using json = nlohmann::json ;

Session::Session(const std::string &path):
g(vector<vector<int>>()),agents(),infected(),cycleNum(0),hasVirus(){
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
        }
        else {
            ContactTracer *CT = new ContactTracer();
            addAgent(*CT);
        }

    }
    //finding graph components
}

void Session::simulate() {
    bool init = true;
    while (!g.areCompsUniform(hasVirus) or init){//checking termination condition
        init = false;
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
const Graph & Session::getGraph() const {return g;}
Graph & Session::getGraph() {return g;}
const int Session::getCycle() const {return cycleNum;}


//Agent actions
void Session::infectNode(int node){//should update node as infected
    g.infectNode(node);
    enqueueInfected(node);
}
bool Session::isInfected(int node) {
    return g.isInfected(node);
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
bool Session::checkVirus(int nodeInd) {
    return hasVirus[nodeInd];
}
void Session::addVirus(int nodeInd) {
    hasVirus[nodeInd] = true;
}

TreeType Session::getTreeType() const {
    return treeType;
}

//Rule of 5

Session::Session(const Session& other):
g(other.g),treeType(other.treeType),agents(), infected(other.infected), hasVirus(other.hasVirus){
    for(int i = 0;i<other.agents.size();++i){
        agents.push_back(other.agents[i]->clone());

    }
}

Session & Session::operator=(const Session &other) {
    if (this != &other){
        g = other.getGraph();
        treeType = other.treeType;
        infected = other.infected;
        hasVirus = other.hasVirus;
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
g(other.g),treeType(other.treeType),infected(other.infected),agents(other.agents),hasVirus(other.hasVirus) {
    for (int i = 0; i < other.agents.size(); ++i) {
        other.agents[i] = nullptr;
    }
}
Session & Session::operator=(Session &&other) {
    if (this != &other){
        g = other.g;
        treeType = other.treeType;
        infected = other.infected;
        hasVirus = other.hasVirus;
        for (int i = 0; i < agents.size(); ++i) {
            if (agents[i] != nullptr)
                delete agents[i];
        }
        agents = other.agents;
        for (int i = 0; i < other.agents.size(); ++i) {
            agents[i] = nullptr;
        }
    }
    return *this;
}


