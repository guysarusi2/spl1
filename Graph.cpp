//
// Created by guy on 06/11/2020.
//

#include "Graph.h"

//DEFAULT CONSTRUCTOR
Graph::Graph(std::vector<std::vector<int>> matrix) : edges(matrix), infectedNodes(matrix.size(), false) {
    //todo delete

//        edges =  std::vector<std::vector<int>>(matrix.size());
//        for (int i = 0; i < matrix.size(); ++i) {
//            for (int j = 0; j < matrix[i].size(); ++j) {
//                edges[i].push_back(matrix[i][j]);
//            }
//        }
//        for (int j = 0; j < edges.size(); ++j) {
//                infectedNodes.push_back(false);
//        }
}


//COPY CONSTRUCTOR
Graph::Graph(const Graph &graphToCopy) {
    edges = graphToCopy.edges;
    infectedNodes = graphToCopy.infectedNodes;
}

//COPY ASSIGNMENT OPERATOR
Graph &Graph::operator=(const Graph &graphToCopy) {
    if (this == &graphToCopy)
        return *this;
    clear();
    edges = graphToCopy.edges;
    infectedNodes = graphToCopy.infectedNodes;
    return *this;
}

//DESTRUCTOR
Graph::~Graph() {
    clear();
}

void Graph::infectNode(int nodeInd) {
    infectedNodes[nodeInd] = true;
}

bool Graph::isInfected(int nodeInd) {
    return infectedNodes[nodeInd];
}

void Graph::isolate(int nodeInd) {
    for (int i = 0; i < edges.size(); ++i) {
        edges[nodeInd][i] = 0;
        edges[i][nodeInd] = 0;
    }
}


void Graph::print() {
    std::cout << "graph:" << std::endl;
    for (int i = 0; i < edges.size(); ++i) {
        for (int j = 0; j < edges[i].size(); ++j) {
            std::cout << edges[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "infected:" << std::endl;

    for (int i = 0; i < infectedNodes.size(); ++i) {
        std::cout << infectedNodes[i] << " ";
    }
    std::cout << " " << std::endl;
}

void Graph::clear() {
    edges.clear();
    infectedNodes.clear();
}

