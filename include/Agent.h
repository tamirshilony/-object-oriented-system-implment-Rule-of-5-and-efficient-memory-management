#ifndef AGENT_H_
#define AGENT_H_

#include <vector>
#include "Session.h"
//Agent
class Agent{
public:
    Agent();
    virtual Agent* clone() const=0;
    virtual void act(Session& session)=0;

};


//ContactTracer
class ContactTracer: public Agent{
public:
    ContactTracer(Session& session);
    virtual Agent* clone() const;
    virtual void act(Session& session);
};

//Virus
class Virus: public Agent{
public:
    Virus(int nodeInd, Session& session);
    virtual Agent* clone() const;
    virtual void act(Session& session);

private:
    const int nodeInd;

    int getMin(vector<int> vec);

};

#endif
