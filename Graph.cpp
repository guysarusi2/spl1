//
// Created by guy on 06/11/2020.
//

#include "Graph.h"

//todo delete unnecessary CTRS


//DEFAULT CONSTRUCTOR
Graph::Graph(std::vector<std::vector<int>> matrix) : edges(matrix), infectedNodes(matrix.size(), false) {
}

//todo delete
//COPY CONSTRUCTOR
//Graph::Graph(const Graph &graphToCopy) {
//    edges = graphToCopy.edges;
//    infectedNodes = graphToCopy.infectedNodes;
//}

//COPY ASSIGNMENT OPERATOR
//Graph &Graph::operator=(const Graph &graphToCopy) {
//    if (this == &graphToCopy)
//        return *this;
//    clear();
//    edges = graphToCopy.edges;
//    infectedNodes = graphToCopy.infectedNodes;
//    return *this;
//}

//DESTRUCTOR
//Graph::~Graph() {
//    clear();
//}

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

//todo delete
//int Graph::searchVirusFree(int nodeInd) {
//    //const std::vector<int>& neighbors(getNeighbors(nodeInd));
//    const std::vector<int> &neighbors(edges[nodeInd]);
//    for (int i = 0; i < neighbors.size(); ++i) {
//        if (!infectedNodes[neighbors[i]])
//            return i;
//    }
//    return -1;
//}

//todo return vector?
std::vector<int> Graph::getNeighbors(int nodeInd) {
    const std::vector<int> &nodeVector(edges[nodeInd]);
    std::vector<int> neighbors;
    for (int i = 0; i < nodeVector.size(); ++i) {
        if (nodeVector[i] == 1)
            neighbors.push_back(i);
    }
    return neighbors;
}

int Graph::getSize() { return edges.size(); }

const std::vector<std::vector<int>> &Graph::getEdges() {
    std::vector<std::vector<int>> &tmpEdges = edges;
    return tmpEdges;
}

const std::vector<int> Graph::getInfected() {
    std::vector<int> infected;
    for (int i = 0; i < infectedNodes.size(); ++i) {
        if (infectedNodes[i])
            infected.push_back(i);
    }
    return infected;
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

Tree *Graph::bfs(const Session &session, int rootInd) {
    Tree *root = Tree::createTree(session, rootInd);
    std::vector<bool> visited(edges.size(), false);
    visited[rootInd] = true;
    std::queue<Tree *> treesQueue;
    treesQueue.push(root);
    while ((!treesQueue.empty())) {
        Tree *current(treesQueue.front());
        treesQueue.pop();   //todo maybe need to delete queue.front before pop
        std::vector<int> neighbors(getNeighbors(current->getNode()));
        for (int i = 0; i < neighbors.size(); ++i) {
            int nextNeighbor(neighbors[i]);
            if (!visited[nextNeighbor]) {
                Tree *newChild = Tree::createTree(session, nextNeighbor);
                current->addChild(*newChild);
                visited[nextNeighbor] = true;
                treesQueue.push(newChild);
            }
        }
        //todo deleting the tree itself is it good? or maybe it is ok since we copy it to the tree
        //delete current;
    }
    return root;
}
