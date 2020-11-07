#ifndef GRAPH_H_
#define GRAPH_H_
#include <iostream> //todo remove-only for printing

#include <vector>

class Graph{
public:
    Graph(std::vector<std::vector<int>> matrix);    //DEFAULT CONSTRUCTOR
    Graph(const Graph& graphToCopy);     //COPY CONSTRUCTOR
    Graph &operator=(const Graph& graphToCopy);  //COPY ASSIGNMENT OPERATOR
    virtual ~Graph();   //DESTRUCTOR

    void infectNode(int nodeInd);
    bool isInfected(int nodeInd);
    void isolate(int nodeInd);

    void print(); //todo delete

private:
    std::vector<std::vector<int>> edges;
    std::vector<bool> infectedNodes;

    void clear();
};
#endif
