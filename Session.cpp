//
// Created by guy on 06/11/2020.
//

#include "Session.h"
#include <iostream>
#include <fstream>
#include "json.hpp"

using json = nlohmann::json;


//*******************    CTR ********************
Session::Session(const std::string &path) : g({}), treeType(), agents(), infectedQueue(), cycle(0) {
    //read from jason and initial the fields
    //initial viruses vector
    ifstream file(path);
    json j;
    file >> j;
    g = Graph(j["graph"]);
    for (int k = 0; k < g.getSize(); ++k) {
        viruses.push_back(false);
    }
    string type = j["tree"];
    checkType(type);
    for (int k = 0; k < j["agents"].size(); ++k) {
        if (j["agents"][k][0] == "V") {
            int virusInd = j["agents"][k][1];
            Agent *newAgent = new Virus(virusInd);
            agents.push_back(newAgent);
            viruses[virusInd] = true;

        } else {
            Agent *newContact = new ContactTracer();
            agents.push_back(newContact);
        }
    }
}

//*******************  COPY CTR ********************
Session::Session(const Session &session) : g(session.g), treeType(session.treeType),
                                           infectedQueue(session.infectedQueue), viruses(session.viruses),
                                           cycle(session.cycle) {
    int agentsSize = session.agents.size();
    for (int i = 0; i < agentsSize; ++i) {
        agents.push_back(session.agents[i]->clone());
    }
}

//*******************  COPY ASSIGNMENT CTR ********************
Session &Session::operator=(const Session &session) {
    //todo why endless loop?
    if (this != &session) {
        this->clear();
        g = session.g;
        treeType = session.treeType;
        infectedQueue = session.infectedQueue;
        viruses = session.viruses;
        cycle = session.cycle;
        int agentsSize = session.agents.size();
        for (int i = 0; i < agentsSize; ++i) {
            agents.push_back(session.agents[i]->clone());
        }
    }
    return *this;
}


//*******************  MOVE CTR ********************
Session::Session(Session &&session) : g(session.g), treeType(session.treeType), agents(session.agents),
                                      infectedQueue(session.infectedQueue), viruses(session.viruses),
                                      cycle(session.cycle) {
    int agentsSize = session.agents.size();
    for (int i = 0; i < agentsSize; ++i) {
        session.agents[i] = nullptr;
    }
}

//*******************  MOVE ASSIGNMENT CTR ********************
Session &Session::operator=(Session &&session) {
    if (this != &session) {
        this->clear();
        g = session.g;
        treeType = session.treeType;
        infectedQueue = session.infectedQueue;
        viruses = session.viruses;
        agents = session.agents;
        cycle = session.cycle;
        int agentsSize = session.agents.size();
        for (int i = 0; i < agentsSize; ++i) {
            session.agents[i] = nullptr;
        }
    }
    return *this;
}

//*******************  DESTRUCTOR ********************
Session::~Session() {
    clear();
}

void Session::clear() {
    //todo delete something else?
    int agentsSize = agents.size();
    for (int i = 0; i < agentsSize; ++i) {
        delete agents[i];
    }
    agents.clear();
}

void Session::checkType(string &type) {
    if (type == "M")
        treeType = MaxRank;
    else if (type == "R")
        treeType = Root;
    else
        treeType = Cycle;
}

void Session::simulate() {
    while (!terminate()) {
        int agentsSize(agents.size());
        for (int i = 0; i < agentsSize; ++i) {
            agents[i]->act(*this);
        }
        cycle++;
    }
    output();
}

void Session::output() {
    json j;
    j["graph"] = g.getEdges();
    j["infected"] = g.getInfected();
    ofstream i("output.json");
    j >> i;
}

void Session::addAgent(const Agent &agent) {
    agents.push_back(agent.clone());
}

void Session::setGraph(const Graph &graph) {
    g = graph;
}

Graph &Session::getGraph() {
    Graph &gTmp = g;
    return gTmp;
}

const std::vector<bool> &Session::getViruses() {
    std::vector<bool> &tmp = viruses;
    return tmp;
}

int Session::getCycle() const {
    return cycle;
}

void Session::setViruses(int newVirusInd) {
    viruses[newVirusInd] = true;
}

void Session::enqueueInfected(int nodeInd) {
    infectedQueue.push(nodeInd);
}

int Session::dequeueInfected() {
    if (!infectedQueue.empty()) {
        int dequeInd(infectedQueue.front());
        infectedQueue.pop();
        return dequeInd;
    }
    return (-1);
}


TreeType Session::getTreeType() const { return treeType; }


bool Session::terminate() {
    for (int i = 0; i < viruses.size(); ++i) {
        if (viruses[i]) {           //checking each virus neighbors
            std::vector<int> neighbors(g.getNeighbors(i));
            for (int j = 0; j < neighbors.size(); ++j) {
                if (!viruses[neighbors[j]])
                    return false;      //continue simulate
            }
        }
    }
    return true;                //end simulate
}