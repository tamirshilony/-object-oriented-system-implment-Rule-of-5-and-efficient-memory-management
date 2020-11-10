//
// Created by spl211 on 05/11/2020.
//

#include "../include/Agent.h"

using namespace std;

//Agent
Agent::Agent(){
}

//Virus
Virus::Virus(int nodeInd):nodeInd(nodeInd) {

}

Agent * Virus::clone() const{
    return new Virus(*this);
}

int Virus::getMin(vector<int> vec){
    vector<int>::iterator it;
    int min = vec.at(0);
    for(int i = 1; i < vec.size(); i++ ){
        if(min > vec.at(i)){
            min = vec.at(i);
        }
    }
    return min;
}

void Virus::act(Session& session) {
    //1. Get neighbors
    Graph const &g = session.getGraph();
    vector<int> neighbor = g.getNonInfNeighbors(nodeInd);
    //2. Choose next to infect
    int minNeighbor = getMin(neighbor); // need to be implemented
    //3. Change node status and add to queue
    session.infectNode(minNeighbor);
    //4. Create new virus
    Virus *newVirus = new Virus(minNeighbor);
    //5. Add to agent list
    session.addAgent(newVirus);
    //6. Delete resources
    delete neighbor;


}

//ContactTracer
ContactTracer::ContactTracer() {}

Agent * ContactTracer::clone() const{
    return new ContactTracer(*this);
}

void ContactTracer::act(Session& session) {
    //1. Dequeue next infected
    int nextInf = session.dequeueInfected();
    //2. Create tree
    Graph const &g = session.getGraph();
    Tree *t = g.bfsScan(nextInf, session);
    //3. Trace tree
    t->traceTree();
    //4. Remove edges
}


