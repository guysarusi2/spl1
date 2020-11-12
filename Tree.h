#ifndef TREE_H_
#define TREE_H_

#include <vector>
//#include "Session.h"

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
    //void addChild(Tree *child);       //todo??
    static Tree *createTree(const Session &session, int rootLabel);
    virtual int traceTree() = 0;

    virtual Tree *clone() const = 0;
    int getNode() const;
    virtual void setValuesAs(const Tree& tree) ;

protected:
    int node;
    void deleteChildren();
    std::vector<Tree *> children;
};

class CycleTree : public Tree {
public:
    CycleTree(int rootLabel, int currCycle); //DEFAULT CONSTRUCTOR
    CycleTree(const CycleTree &cycleTreeToCopy); //COPY CONSTRUCTOR
    CycleTree &operator=(const CycleTree &cycleTreeToCopy);  //COPY ASSIGNMENT OPERATOR
    //No need for destructor

    virtual int traceTree();
    virtual int traceTree(int cycle);

    virtual Tree *clone() const;
    int getCycle() const;

private:
    int currCycle;

public:
    void setFigure3(){
        CycleTree* ct1=new CycleTree(1,currCycle);
        CycleTree* ct2=new CycleTree(2,currCycle);
        CycleTree* ct3=new CycleTree(3,currCycle);
        CycleTree* ct4=new CycleTree(4,currCycle);
        CycleTree* ct5=new CycleTree(5,currCycle);
        CycleTree* ct6=new CycleTree(6,currCycle);
        CycleTree* ct7=new CycleTree(7,currCycle);
        CycleTree* ct8=new CycleTree(8,currCycle);
        CycleTree* ct9=new CycleTree(9,currCycle);
        CycleTree* ct10=new CycleTree(10,currCycle);
        CycleTree* ct11=new CycleTree(11,currCycle);

        children.push_back(ct1);         //node 0 children
        children.push_back(ct4);

        ct1->children.push_back(ct2);       //node 1 children
        ct1->children.push_back(ct3);
        ct1->children.push_back(ct5);
        ct1->children.push_back(ct6);

        ct5->children.push_back(ct7);

        ct6->children.push_back(ct8);
        ct6->children.push_back(ct9);
        ct6->children.push_back(ct10);
        ct6->children.push_back(ct11);

        CycleTree* ct30=new CycleTree(30,2);
        ct2->children.push_back(ct30);
    }       //todo REMOVE
};

class MaxRankTree : public Tree {
public:
    MaxRankTree(int rootLabel);

    MaxRankTree(const MaxRankTree &maxRankTreeToCopy); //COPY CONSTRUCTOR
    MaxRankTree &operator=(const MaxRankTree &maxRankTreeToCopy);  //COPY ASSIGNMENT OPERATOR
    //No need for destructor

    virtual int traceTree();
    virtual MaxRankTree& traceTree(MaxRankTree& child);

    virtual Tree *clone() const;

    void setFigure2(){
        MaxRankTree* ct1=new MaxRankTree(1);
        MaxRankTree* ct2=new MaxRankTree(2);
        MaxRankTree* ct3=new MaxRankTree(3);
        MaxRankTree* ct4=new MaxRankTree(4);
        MaxRankTree* ct5=new MaxRankTree(5);
        MaxRankTree* ct6=new MaxRankTree(6);
        MaxRankTree* ct7=new MaxRankTree(7);
        MaxRankTree* ct8=new MaxRankTree(8);
        MaxRankTree* ct9=new MaxRankTree(9);
        MaxRankTree* ct10=new MaxRankTree(10);
        MaxRankTree* ct11=new MaxRankTree(11);
        MaxRankTree* ct12=new MaxRankTree(12);


        children.push_back(ct1);         //node 0 children
        children.push_back(ct4);

        ct1->children.push_back(ct2);       //node 1 children
        ct1->children.push_back(ct3);
        ct1->children.push_back(ct5);
        ct1->children.push_back(ct6);

        ct5->children.push_back(ct7);

        ct6->children.push_back(ct8);

        ct4->children.push_back(ct9);
        ct4->children.push_back(ct10);
        ct4->children.push_back(ct11);
        ct4->children.push_back(ct12);


        MaxRankTree* ct30=new MaxRankTree(30);
        ct1->children.push_back(ct30);

    }       //todo REMOVE
};

class RootTree : public Tree {
public:
    RootTree(int rootLabel);    // CONSTRUCTOR

    RootTree(const RootTree &rootTreeToCopy);              //COPY CONSTRUCTOR
    RootTree &operator=(const RootTree &rootTreeToCopy);  //COPY ASSIGNMENT OPERATOR
    //No need for destructor

    virtual int traceTree();

    virtual Tree *clone() const;
};

#endif
