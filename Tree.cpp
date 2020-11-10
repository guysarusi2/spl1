// Created by spl211 on 05/11/2020.

#include "Tree.h"

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
    node=treeToCopy.node;
    for (int i = 0; i < treeToCopy.children.size(); ++i) {
        children.push_back(treeToCopy.children[i]);
        treeToCopy.children[i]= nullptr;
    }
    treeToCopy.children.clear();
}                   // MOVE CONSTRUCTOR
const Tree &Tree::operator=(Tree &&treeToCopy) {
    node =treeToCopy.node;
    for (int i = 0; i < children.size(); ++i) {         //destructing all 'my' children
        delete children[i];
    }
    children.clear();

    for (int i = 0; i < treeToCopy.children.size(); ++i) {
        children.push_back(children[i]);
    }

    return *this;
}   // MOVE ASSIGNMENT OPERATOR


void Tree::addChild(const Tree &child) {
     Tree* toAdd = child.clone();

     int n= child.getNode();
     std::vector<Tree*> newVec;
     int i=0;
     bool found = false;




         for (i = 0; i < children.size() && !found; ++i) {
             if ()

                 if (n <= children[i]->getNode())
                     found = true;
         }
         if (n >= children[children.size() - 1]->getNode())
             i = children.size();
         else
             i--;


    children.push_back(nullptr);

    for (int j = children.size()-2; j > i; --j) {
        children[j]=children[j+1];
        if(j==i)

    }

    //  this->children.push_back((Tree*) (child));  //todo
}

void Tree::addChild(Tree *child) {
    this->children.push_back((Tree *) (child));  //todo
}


Tree *Tree::createTree(const Session &session, int rootLabel) {}

int Tree::traceTree() {}


//********************* class CycleTree: public Tree ****************************
CycleTree::CycleTree(int _rootLabel, int _currCycle) : Tree(_rootLabel), currCycle(_currCycle) {}   //CONSTRUCTOR
// Rule of 3
CycleTree::CycleTree(const CycleTree &cycleTreeToCopy) : Tree(cycleTreeToCopy) {
    currCycle = cycleTreeToCopy.currCycle;
}         //COPY CONSTRUCTOR
CycleTree::~CycleTree() {

}               //DESTRUCTOR??
CycleTree &CycleTree::operator=(const CycleTree &cycleTreeToCopy) {
    Tree *temp = cycleTreeToCopy.clone();
}           //COPY ASSIGNMENT OPERATOR


Tree *CycleTree::clone() const {
    return new CycleTree(*this);
}


// ************************  class MaxRankTree: public Tree ***********************
MaxRankTree::MaxRankTree(int rootLabel) : Tree(rootLabel) {}         // CONSTRUCTOR
MaxRankTree::MaxRankTree(const CycleTree &cycleTreeToCopy) : Tree(cycleTreeToCopy) {

}

CycleTree &MaxRankTree::operator=(const CycleTree &cycleTreeToCopy) {

}

Tree *MaxRankTree::clone() const {
    return new MaxRankTree(*this);
}

// ************************  class RootTree: public Tree ****************************
RootTree::RootTree(int rootLabel) : Tree(rootLabel) {}         // CONSTRUCTOR


Tree *RootTree::clone() const {
    return new RootTree(*this);
}

int Tree::getNode() const {
    return this->node;
};



