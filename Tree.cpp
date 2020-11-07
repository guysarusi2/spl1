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

//DEFAULT CONSTRUCTOR
CycleTree::CycleTree(int rootLabel, int currCycle)
:Tree(rootLabel) {
    //    return *this;
}

//COPY CONSTRUCTOR
CycleTree::CycleTree(const CycleTree &cycleTreeToCopy)
:Tree(cycleTreeToCopy){
    //return *this;
}

//COPY ASSIGNMENT OPERATOR
CycleTree & CycleTree::operator=(const CycleTree &cycleTreeToCopy) {

}
//DESTRUCTOR
CycleTree::~CycleTree() noexcept {

}



Tree * CycleTree::clone() {
    CycleTree temp = new CycleTree(this->node,currCycle); //todo
            int i= this.
}

// class MaxRankTree: public Tree
Tree * MaxRankTree::clone() {

}
// class RootTree: public Tree
Tree * RootTree::clone() {

}