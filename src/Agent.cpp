//
// Created by spl211 on 05/11/2020.
//

#include "../include/Agent.h"
using namespace std;

Agent::Agent(Session &session):session(session){

}

Virus::Virus(int nodeInd, Session &session):nodeInd(nodeInd) {

}

Agent * Virus::clone() {
    return new Virus(*this);
}

void Virus::act(Session& session) {
    //1. get neighbors

    //2. choose next to infect

    //3. change node status

    //4. add node to queue

    //5. create new virus

    //6. add to agent list
}

ContactTracer::ContactTracer(Session &session) {}

Agent * ContactTracer::clone() {
    return new ContactTracer(*this);
}

void ContactTracer::act(Session& session) {}


