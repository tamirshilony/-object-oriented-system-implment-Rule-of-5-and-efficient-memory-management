//
// Created by spl211 on 05/11/2020.
//

#include "../include/Agent.h"
using namespace std;

//Agent
Agent::Agent():{

}

//Virus
Virus::Virus(int nodeInd):nodeInd(nodeInd) {

}

Agent * Virus::clone() {
    return new Virus(*this);
}

void Virus::act(Session& session) {
    //1. get neighbors
    std::vector *neighbor = session->getNodeNeighbors(nodeInd);
    //2. choose next to infect
    int Virus::minNeighbor = getMin(neighbor); // need to be implemented
    //3. change node status and add to queue
    session->infectNode(minNeighbor);
    //4. create new virus
    Virus newVirus = new Virus(minNeighbor);
    //5. add to agent list
    session->addAgent(&newVirus);


}

int getMin(int[] arr){}

//ContactTracer
ContactTracer::ContactTracer(Session &session) {}

Agent * ContactTracer::clone() {
    return new ContactTracer(*this);
}

void ContactTracer::act(Session& session) {}


