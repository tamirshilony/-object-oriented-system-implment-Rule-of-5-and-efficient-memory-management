#ifndef AGENT_H_
#define AGENT_H_

#include <vector>
#include "Session.h"

class Agent{
public:
    Agent(Session& session);
    virtual Agent* clone()=0;
    virtual void act(Session& session)=0;

protected:
    Session& session;
};

class ContactTracer: public Agent{
public:
    ContactTracer(Session& session);
    virtual Agent* clone();
    virtual void act(Session& session);
};


class Virus: public Agent{
public:
    Virus(int nodeInd, Session& session);
    virtual Agent* clone();
    virtual void act(Session& session);

private:
    const int nodeInd;
};

#endif
