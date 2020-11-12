#ifndef TREE_H_
#define TREE_H_

#include <vector>
#include "../include/Session.h"


class Session;

class Tree{
public:
    Tree(int rootLabel);

    //Rule of five
    Tree(const Tree& other);
    Tree & operator=(const Tree &other);
    virtual ~Tree();
    Tree(Tree&& other);
    Tree & operator=(Tree &&other);

    virtual Tree * clone() const= 0;
    void addChild(const Tree& child);


    static Tree* createTree(const Session& session, int rootLabel);
    virtual int traceTree()=0;

    int getNode() const;
    const std::vector<Tree*> getChildren() const;


private:
    int node;
    std::vector<Tree*> children;
};


//CYCLE TREE
class CycleTree: public Tree{
public:
    CycleTree(int rootLabel, int currCycle);
    virtual Tree* clone() const;
    virtual int traceTree() ;
    int recursiveTrace(stepsLeft);
private:
    int currCycle;
};

//MAX RANK TREE
class MaxRankTree: public Tree{
public:
    MaxRankTree(int rootLabel);
    virtual Tree* clone() const;
    virtual int traceTree() ;
    int recursiveTrace();
};

//ROOT TREE
class RootTree: public Tree{
public:
    RootTree(int rootLabel);
    virtual Tree* clone() const;
    virtual int traceTree() ;
};

#endif
