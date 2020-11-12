//
// Created by guy on 06/11/2020.
//

#include "Agent.h"

//todo delete unnecessary CTRS


//*******************    CTR ********************
Agent::Agent() {}


//*******************    CTR ********************
ContactTracer::ContactTracer() {}

//ContactTracer::ContactTracer(const ContactTracer &toCopy) {}

void ContactTracer::act(Session &session) {
    //deque
    int nextInfected(session.dequeueInfected());
    if (nextInfected == -1)        //there is no infected node
        return;
    else {
        //bfs->trace->isolate
        Graph &g(session.getGraph());
        Tree *bfsTree = g.bfs(session, nextInfected);
        int nodeToIsolate(bfsTree->traceTree());
        g.isolate(nodeToIsolate);
        delete bfsTree;
    }
}

Agent *ContactTracer::clone() const {
    return new ContactTracer(*this);
}

//*******************    CTR ********************
Virus::Virus(int nodeInd) : nodeInd(nodeInd) {}

//Virus::Virus(const Virus &toCopy) : nodeInd(toCopy.nodeInd) {}

void Virus::act(Session &session) {
    Graph &g(session.getGraph());
    //infect itself
    if (!g.isInfected(nodeInd)) {
        g.infectNode(nodeInd);
        session.enqueueInfected(nodeInd);
    }
    //spread
    int virusFreeNeighbor=-1;
    std::vector<int> neighbors(g.getNeighbors(nodeInd));
    const std::vector<bool> &viruses(session.getViruses());
    for (int i = 0; i < neighbors.size(); ++i) {
        if (!viruses[neighbors[i]]) {
            virusFreeNeighbor = neighbors[i];
            break;
        }
    }
    if (virusFreeNeighbor!=-1) {    //exist virusFree neighbor
        Virus newVirus(virusFreeNeighbor);
        session.setViruses(virusFreeNeighbor);
        session.addAgent(newVirus);
    }
}

Agent *Virus::clone() const {
    return new Virus(*this);
}



