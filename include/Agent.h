#ifndef AGENT_H_
#define AGENT_H_

#include <vector>
#include "Session.h"
//Agent
class Agent{
public:
    Agent(Session& session);
    virtual Agent* clone()=0;
    virtual void act(Session& session)=0;

protected:
    Session& session;
};


//ContactTracer
class ContactTracer: public Agent{
public:
    ContactTracer(Session& session);
    virtual Agent* clone();
    virtual void act(Session& session);
};

//Virus
class Virus: public Agent{
public:
    Virus(int nodeInd, Session& session);
    virtual Agent* clone();
    virtual void act(Session& session);

private:
    const int nodeInd;

    int getMin(vector<int> vec);

};

#endif
