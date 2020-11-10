//
// Created by spl211 on 05/11/2020.
//
#include ""
#include "../include/Tree.h"
Tree::Tree(int rootLabel):node(rootLabel),children(){}
const int Tree::getNode() const {
    return node;
}
void Tree::addChild(const Tree &child) {

}

static Tree* createTree(const Session& session, int rootLabel){
    Tree * newTree;
    if(session.getTreeType() == MaxRank){
        newTree = new MaxRankTree(rootLabel);
    } else if(session.getTreeType() == Cycle){
        newTree = new CycleTree(rootLabel, session.getCycle());
    } else
        newTree = new RootTree(rootLabel);
    return newTree;
}

MaxRankTree::MaxRankTree(int rootLabel): Tree(rootLabel){}


CycleTree::CycleTree(int rootLabel, int currCycle): Tree(rootLabel), currCycle(currCycle){}


RootTree::RootTree(int rootLabel):Tree(rootLabel) {}
int RootTree::traceTree() {
    return this->getNode();
}