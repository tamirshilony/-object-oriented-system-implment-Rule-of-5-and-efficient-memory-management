//
// Created by spl211 on 05/11/2020.
//

#include "../include/Tree.h"
Tree::Tree(int rootLabel):node(rootLabel),children(){}
void Tree::addChild(const Tree &child) {
    Tree *toAdd = child.clone();
    children.push_back(toAdd);
}

const int Tree::getNode() const {
    return node;
}

Tree* Tree::createTree(const Session& session, int rootLabel){
    TreeType treeType = session.getTreeType();
    switch (treeType) {
        case MaxRank:
            return new MaxRankTree(rootLabel);
        case Cycle:
            return new CycleTree(rootLabel, session.getCycle());
        case Root:
            return new RootTree(rootLabel);
    }
}


//MAX RANK TREE
MaxRankTree::MaxRankTree(int rootLabel): Tree(rootLabel){}
Tree *MaxRankTree::clone() const {
    return new MaxRankTree(*this);
}
int MaxRankTree::traceTree(){

}

//CYCLE TREE
CycleTree::CycleTree(int rootLabel, int currCycle): Tree(rootLabel), currCycle(currCycle){}
Tree *CycleTree::clone() const {
    return new CycleTree(*this);
}
int CycleTree::traceTree(){
    int stepsLeft = currCycle;
    Tree childTree = children.front();
    while(!children.empty() && stepsLeft)

}


//ROOT TREE
RootTree::RootTree(int rootLabel):Tree(rootLabel) {}
Tree *RootTree::clone() const {
    return new RootTree(*this);
}
int RootTree::traceTree() {
    return node;
}