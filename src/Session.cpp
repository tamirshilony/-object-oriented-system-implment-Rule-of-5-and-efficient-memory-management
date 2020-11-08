//
// Created by spl211 on 05/11/2020.
//
#include "../include/Session.h"
#include <iostream>
#include <fstream>
#include "../include/json.hpp"
using namespace std;
using json = nlohmann::json ;

Session::Session(const std::string &path):g(vector<vector<int>>()),agents(),infected() {
    ifstream inputJ(path);
    json j;
    j << inputJ;
    treeType = j["tree"];
    g = Graph(j["graph"]);
    //agents = vector<Agent*>(j["agents"]);
    //for (auto agent:j["agents"])


}
Session::Session(const Session& other):g(vector<vector<int>>()),treeType(other.treeType),agents(){
    for(int i = 0;i<other.agents.size();++i){
        Agent* nextAgent = other.agents[i].clone();
        agents.push_back(nextAgent);
    }
}
void Session::simulate() {}

void Session::addAgent(const Agent &agent) {
    Agent* agent2add = agent.clone();
    agents.push_back(agent2add);
}
//Graph methods
void Session::setGraph(const Graph &graph){}
std::vector session::getNodeNeighbors(int node){}

//Agent actions
void session::infectNode(int node); //should update node as infected and use nqueueInfected()
int Session::dequeueInfected() {}
void Session::enqueueInfected(int) {
    //infected.push_back(int);
}

TreeType Session::getTreeType() const {
    return treeType;
}

