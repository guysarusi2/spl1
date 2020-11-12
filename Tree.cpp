// Created by spl211 on 05/11/2020.

#include "Tree.h"
#include "Session.h"


// *************************************  class Tree  **************************
Tree::Tree(int rootLabel) : node(rootLabel) {}        //CONSTRUCTOR
// Rule of 3
Tree::Tree(const Tree &treeToCopy) {
    node = treeToCopy.node;
    for (int i = 0; i < treeToCopy.children.size(); ++i) {
        children.push_back(treeToCopy.children[i]->clone());
    }
}               //COPY CONSTRUCTOR
Tree::~Tree() {
    for (int i = 0; i < children.size(); ++i) {
        delete children[i];
    }
}                                    //DESTRUCTOR
Tree &Tree::operator=(const Tree &treeToCopy) {
    if (this != &treeToCopy) {
        node = treeToCopy.node;

        for (int i = 0; i < children.size(); ++i) {         //destructing all 'my' children
            delete children[i];
        }
        children.clear();
        for (int i = 0; i < treeToCopy.children.size(); ++i) {
            children.push_back(treeToCopy.children[i]->clone());
        }
    }

    return *this;
}       //COPY ASSIGNMENT OPERATOR
//Rule of 5
Tree::Tree(Tree &&treeToCopy) {
    node = treeToCopy.node;
    for (int i = 0; i < treeToCopy.children.size(); ++i) {
        children.push_back(treeToCopy.children[i]);
        treeToCopy.children[i] = nullptr;
    }
    treeToCopy.children.clear();
}                   // MOVE CONSTRUCTOR
const Tree &Tree::operator=(Tree &&treeToCopy) {
    node = treeToCopy.node;
    deleteChildren();

    for (int i = 0; i < treeToCopy.children.size(); ++i) {
        children.push_back(children[i]);
    }

    return *this;
}   // MOVE ASSIGNMENT OPERATOR

void Tree::addChild(const Tree &child) {
    Tree *toAdd = child.clone();
    int n = child.getNode();
    int i = 0;

    if (children.empty() ||
        n >= children[children.size() - 1]->getNode()) {      //check if needs to be added at the end of the array
        i = -1;
        children.push_back(toAdd);
    } else if (n <= children[0]->getNode())        //check if needs to be added at index 0
        i = 0;

    else {
        bool found = false;
        for (i = 1; i < children.size() && !found; ++i) {
            if (n >= children[i - 1]->getNode() && n <= children[i]->getNode())
                found = true;
        }
        i--;
    }
    if (i != -1) {
        children.push_back(nullptr);
        for (int j = children.size() - 2; j >= i; --j) {
            children[j + 1] = children[j];
        }
        children[i] = toAdd;
    }
}

//void Tree::addChild(const Tree &child) {
//    Tree *toAdd = child.clone();
//    children.push_back(toAdd);
//}


Tree *Tree::createTree(const Session &session, int rootLabel) {
    switch (session.getTreeType()) {
        case MaxRank:
            return new MaxRankTree(rootLabel);
            break;
        case Cycle:
            return new CycleTree(rootLabel, session.getCycle());
            break;
        case Root:
            return new RootTree(rootLabel);
            break;
    }
    throw "no valid TreeType in session";
}

int Tree::getNode() const {
    return node;
}

void Tree::deleteChildren() {
    for (int i = 0; i < children.size(); ++i) {         //destructing all 'my' children
        delete children[i];
    }
    children.clear();
}

void Tree::setValuesAs(const Tree &tree) {
    node = tree.getNode();
    deleteChildren();
    for (int i = 0; i < tree.children.size(); ++i) {
        children.push_back(tree.children[i]->clone());
    }
}

//********************* class CycleTree: public Tree ****************************
CycleTree::CycleTree(int _rootLabel, int _currCycle) : Tree(_rootLabel), currCycle(_currCycle) {}   //CONSTRUCTOR
// Rule of 3ish
CycleTree::CycleTree(const CycleTree &cycleTreeToCopy) : Tree(cycleTreeToCopy) {
    currCycle = cycleTreeToCopy.currCycle;
}         //COPY CONSTRUCTOR
CycleTree &CycleTree::operator=(const CycleTree &cycleTreeToCopy) {
    if (this != &cycleTreeToCopy) {
        currCycle = cycleTreeToCopy.getCycle();
        Tree::setValuesAs(cycleTreeToCopy);
    }

    return *this;
}                   //COPY ASSIGNMENT OPERATOR

int CycleTree::traceTree() {
    return traceTree(getCycle());
}

int CycleTree::traceTree(int cycle) {
    if (cycle == 0 || children.empty())
        return getNode();

    return ((CycleTree *) children[0])->traceTree(cycle - 1);
}

Tree *CycleTree::clone() const {
    return new CycleTree(*this);
}

int CycleTree::getCycle() const {
    return currCycle;
}

// ************************  class MaxRankTree: public Tree ***********************
MaxRankTree::MaxRankTree(int rootLabel) : Tree(rootLabel) {}         // CONSTRUCTOR
// Rule of 3ish
MaxRankTree::MaxRankTree(const MaxRankTree &maxRankTreeToCopy) : Tree(maxRankTreeToCopy) {} //COPY CONSTRUCTOR
MaxRankTree &MaxRankTree::operator=(const MaxRankTree &maxRankTreeToCopy) {
    if (this != &maxRankTreeToCopy)
        Tree::setValuesAs(maxRankTreeToCopy);

    return *this;
}   //COPY ASSIGNMENT OPERATOR

int MaxRankTree::traceTree() {
    return traceTree(*this).getNode();
}

MaxRankTree &MaxRankTree::traceTree(MaxRankTree &child) {
    if (children.empty())
        return child;
    MaxRankTree *max = &child;
    if (child.children.size() < ((MaxRankTree *) child.children[0])->children.size())
        max = (MaxRankTree *) child.children[0];

    for (int i = 1; i < children.size(); ++i) {
        if (child.children[i]->traceTree() > max->children.size())
            max = (MaxRankTree *) child.children[i];
    }
    return *max;
}


Tree *MaxRankTree::clone() const {
    return new MaxRankTree(*this);
}

// ************************  class RootTree: public Tree ****************************
RootTree::RootTree(int rootLabel) : Tree(rootLabel) {}         // CONSTRUCTOR
// Rule of 3ish
RootTree::RootTree(const RootTree &rootTreeToCopy) : Tree(rootTreeToCopy) {}           //COPY CONSTRUCTOR
RootTree &RootTree::operator=(const RootTree &rootTreeToCopy) {
    if (this != &rootTreeToCopy)
        Tree::setValuesAs(rootTreeToCopy);
    return *this;
}   //COPY ASSIGNMENT OPERATOR

int RootTree::traceTree() {
    return getNode();
}

Tree *RootTree::clone() const {
    return new RootTree(*this);
}