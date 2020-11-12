//
// Created by spl211 on 05/11/2020.
//

#include "../include/Graph.h"
using namespace std;

Graph::Graph(std::vector<std::vector<int>> matrix):edges(matrix),infectedNode(matrix.size(), false){
}
const vector<vector<int>> Graph::getEdges() const {
    return edges;
}
const vector<bool> Graph::getInfected() const {
    return infectedNode;
}

void Graph::infectNode(int nodeInd) {
    infectedNode[nodeInd] = true;
}

bool Graph::isInfected(int nodeInd) {
    return infectedNode[nodeInd];
}

std::vector<int> Graph::getNonInfNeighbors(int nodeInd) {
    vector<int> Neighbors;
    for(int i =0;i<edges[nodeInd].size();i++){
        if (edges[nodeInd][i]==1 and !isInfected(i))
            Neighbors.push_back(i);
    }
    return Neighbors;
}
Tree * Graph::BFS(int nodeInd, const Session &session)const {
    Tree* currTree = Tree::createTree(session,nodeInd);
    //BFS implement
    vector<bool>visited(edges.size(), false);
    vector<int>q;
    q.push_back(nodeInd);
    visited[nodeInd] = true;
    int currNode;
    while (!q.empty()){
        currNode = q[0];
        q.erase(q.cbegin());
        for (int i = 0; i < edges.size(); ++i) {
            if (edges[currNode][i]== 1 and (!visited[i])){
                q.push_back(i);
                visited[i] = true;
                Tree* nextTree = Tree::createTree(session,i);
                currTree->addChild(*nextTree);
            }
        }
    }

    return currTree;
}


void Graph::removeEdges(int nodeInd) {
    for (int i = 0; i < edges[nodeInd].size(); ++i) {
        if (edges[nodeInd][i]==1) {
            edges[nodeInd][i] = 0;
            edges[i][nodeInd] = 0;
        }
    }
}
Graph Graph::findComponents() const{
    vector<vector<int>> componentMatrix;
    int componentNum = 0;
    vector<bool>visited(edges.size(),false);
    for (int i = 0; i < edges.size(); ++i) {
        if (!visited[i]) {
            componentMatrix[componentNum].push_back(i);
            vector<int> q;
            q.push_back(i);
            visited[i] = true;
            while (!q.empty()) {
                q.erase(q.cbegin());
                for (int j = 0; j < edges.size(); j++) {
                    if (edges[i][j] == 1 and (!visited[i])) {
                        q.push_back(j);
                        visited[j] = true;
                        componentMatrix[componentNum].push_back(j);
                    }

                }
            }
            componentNum++;
        }
    }
    return Graph(componentMatrix);
}
