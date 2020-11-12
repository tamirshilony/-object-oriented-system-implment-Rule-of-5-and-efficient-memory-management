//
// Created by spl211 on 05/11/2020.
//

#include "../include/Tree.h"
Tree::Tree(int rootLabel):node(rootLabel),children(){}

//Rule of five
Tree::Tree(const Tree &other):children(),node(other.node) {
    for (int i = 0; i < other.children.size(); ++i) {
        children.push_back(other.children[i]->clone());
    }
}
Tree & Tree::operator=(const Tree &other) {
    if (this != &other){
        node = other.node;
        for (int i = 0; i < children.size(); ++i) {
            delete children[i];
        }
        for (int i = 0; i < other.children.size(); ++i) {
            children.push_back(other.children[i]->clone());
        }
    }
    return *this;
}
Tree::~Tree() noexcept {
    if (!children.empty())
        for (int i = 0; i < children.size(); ++i) {
            delete children[i];
        }
}
Tree & Tree::operator=(Tree &&other) {
    if (this != &other){
        node = other.node;
        for (int i = 0; i < children.size(); ++i) {
            delete children[i];
        }
        children = other.children;
        for (int i = 0; i < other.children.size(); ++i) {
            other.children[i] = nullptr;
        }
    }
}


Tree::Tree(Tree &&other):node(other.node),children(other.children) {
    for (int i = 0; i < other.children.size(); ++i) {
        other.children[i] = nullptr;
    }
}


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
    return this->recursiveTrace();
}
int MaxRankTree::recursiveTrace() {
    int nChild = children.size();
    if(!nChild)
        return 0;
    int maxRank = nChild;
    for(int i = 0; i < nChild; i++){
        MaxRankTree *nextChild = dynamic_cast<MaxRankTree *>(children[i]);
        int temp = nextChild->recursiveTrace();
        if(temp > maxRank)
            maxRank = temp;
    }
    return maxRank;
}

//CYCLE TREE
CycleTree::CycleTree(int rootLabel, int currCycle): Tree(rootLabel), currCycle(currCycle){}
Tree *CycleTree::clone() const {
    return new CycleTree(*this);
}
int CycleTree::traceTree(){
    return this->recursiveTrace(currCycle);
}

int CycleTree::recursiveTrace(int stepsLeft) {
    if(children.empty() or stepsLeft == 0){
        return node;
    }
    CycleTree *leftChild = dynamic_cast<CycleTree *>(children[0]);
    leftChild->recursiveTrace(stepsLeft-1);
}


//ROOT TREE
RootTree::RootTree(int rootLabel):Tree(rootLabel) {}
Tree *RootTree::clone() const {
    return new RootTree(*this);
}
int RootTree::traceTree() {
    return node;
}