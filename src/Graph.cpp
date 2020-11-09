//
// Created by spl211 on 05/11/2020.
//

#include "../include/Graph.h"
using namespace std;

Graph::Graph(std::vector<std::vector<int>> matrix):edges(matrix),infectedNode(matrix.size(), false){
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