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

Session::Session(const std::string &path):g(vector<vector<int>>()),agents(),infected() {
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
}

void Session::simulate() {
    int t = 2;
    while (t>0){
        int curSize = agents.size();//ensure that new agents wont act
        for(int i = 0;i<curSize;i++){
            agents[i]->act(*this);
        }
        t--;
    }
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

//std::vector<int> Session::getNonInfNeighbors(int node) {
//    return g.getNonInfNeighbors(node);
//}


//Agent actions
void Session::infectNode(int node){//should update node as infected
    g.infectNode(node);
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

//rule of 5

Session::Session(const Session& other):g(vector<vector<int>>()),treeType(other.treeType),agents(){
    for(int i = 0;i<other.agents.size();++i){
        agents.push_back(other.agents[i]->clone());

    }
}

Session & Session::operator=(const Session &other) {
    if (this != &other){
        g = other.getGraph();
        treeType = getTreeType();
        infected = other.infected;
        for (int i = 0; i < agents.size(); ++i) {
            delete agents[i];
        }
        for (int i = 0; i < other.agents.size(); ++i) {
            this->addAgent(*other.agents[i]);
        }
    }
    return *this;
}

