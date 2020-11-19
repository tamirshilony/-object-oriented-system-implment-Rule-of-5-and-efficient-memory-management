#ifndef TREE_H_
#define TREE_H_

#include <vector>

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
    virtual int traceTree()=0;

    void addChild(const Tree& child);
    static Tree* createTree(const Session& session, int rootLabel);

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
    CycleTree(const CycleTree &other);
    virtual Tree* clone() const;
    virtual int traceTree() ;
    int recursiveTrace(int stepsLeft);
    int getCycle() const;
private:
    int currCycle;


};

//MAX RANK TREE
class MaxRankTree: public Tree{
public:
    MaxRankTree(int rootLabel);
    MaxRankTree(const MaxRankTree &other);
    virtual Tree* clone() const;
    virtual int traceTree() ;
    int recursiveTrace(int maxNode,int &maxRank);
};

//ROOT TREE
class RootTree: public Tree{
public:
    RootTree(int rootLabel);
    RootTree(const RootTree &other);
    virtual Tree* clone() const;
    virtual int traceTree() ;
};

#endif
