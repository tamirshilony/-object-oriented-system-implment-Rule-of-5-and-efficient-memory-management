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
    //1. get neighbors
    vector<int> *neighbor = session.getNonInfNeighbors(nodeInd);
    //2. choose next to infect
    int Virus::minNeighbor = getMin(*neighbor); // need to be implemented
    //3. change node status and add to queue
    session.infectNode(minNeighbor);
    //4. create new virus
    Virus newVirus = new Virus(minNeighbor);
    //5. add to agent list
    session.addAgent(&newVirus);
    //6. delete resources
    delete neighbor;


}

//ContactTracer
ContactTracer::ContactTracer(Session &session) {}

Agent * ContactTracer::clone() const{
    return new ContactTracer(*this);
}

void ContactTracer::act(Session& session) {}


