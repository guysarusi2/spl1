#ifndef TREE_H_
#define TREE_H_

#include <vector>

class Session;

class Tree {
public:
    Tree(int rootLabel);                         //CONSTRUCTOR
    Tree(const Tree &treeToCopy);               //COPY CONSTRUCTOR
    virtual ~Tree();                           //DESTRUCTOR
    Tree &operator=(const Tree &treeToCopy);  //COPY ASSIGNMENT OPERATOR
    const Tree &operator=(Tree &&treeToCopy);       // MOVE ASSIGNMENT OPERATOR
    Tree(Tree&& treeToCopy);                       // MOVE CONSTRUCTOR






    void addChild(const Tree &child);

    void addChild(Tree *child);

    int getNode() const;

    static Tree *createTree(const Session &session, int rootLabel);

    virtual int traceTree() = 0;

    virtual Tree *clone() const = 0;


private:
    int node;
    std::vector<Tree *> children;
};

class CycleTree : public Tree {
public:
    CycleTree(int rootLabel, int currCycle); //DEFAULT CONSTRUCTOR
    CycleTree(const CycleTree &cycleTreeToCopy); //COPY CONSTRUCTOR
    CycleTree &operator=(const CycleTree &cycleTreeToCopy);  //COPY ASSIGNMENT OPERATOR
    virtual ~CycleTree();   //DESTRUCTOR
    virtual int traceTree();

    virtual Tree *clone() const;


private:
    int currCycle;

};

class MaxRankTree : public Tree {
public:
    MaxRankTree(int rootLabel);

    MaxRankTree(const CycleTree &cycleTreeToCopy); //COPY CONSTRUCTOR
    CycleTree &operator=(const CycleTree &cycleTreeToCopy);  //COPY ASSIGNMENT OPERATOR
    //No need for destructor

    virtual int traceTree();

    virtual Tree *clone() const;
};

class RootTree : public Tree {
public:
    RootTree(int rootLabel);

    RootTree(const CycleTree &cycleTreeToCopy); //COPY CONSTRUCTOR
    CycleTree &operator=(const CycleTree &cycleTreeToCopy);  //COPY ASSIGNMENT OPERATOR
    //No need for destructor

    virtual int traceTree();

    virtual Tree *clone() const;
};

#endif
