//
// Created by spl211 on 05/11/2020.
//

#include "Tree.h"

// class Tree

//DEFAULT CONSTRUCTOR
Tree::Tree(int rootLabel) {
    this->node=rootLabel;
}

//COPY CONSTRUCTOR
Tree::Tree(const Tree &treeToCopy) {
    treeToCopy.copy();
}

//COPY ASSIGNMENT OPERATOR
Tree &Tree::operator=(const Tree &treeToCopy) {
    if (this == &treeToCopy)
        return *this;

    return *this;
}

//DESTRUCTOR
Tree::~Tree() {
    children.clear();
}

void Tree::addChild(const Tree& child) {
   // Tree toadd(child);
  //  this->children.push_back((Tree*) (child));  //todo
}
void Tree::addChild(Tree* child) {
    this->children.push_back((Tree*) (child));  //todo
}

Tree * Tree::createTree(const Session &session, int rootLabel) {}

int Tree::traceTree() {}

Tree * Tree::copy() const {
    Tree a = new Tree(4);
}





// class CycleTree: public Tree

// class MaxRankTree: public Tree

// class RootTree: public Tree
