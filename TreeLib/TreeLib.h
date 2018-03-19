#ifndef TREE_TREELIB_H
#define TREE_TREELIB_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../decoder/decoder.h"

//===============================================
//Code of symbol (cos, x, 5, etc.)
typedef encoding value_type;

//===============================================
//Code of symbol's type
typedef encoding_type definision;


//===============================================
//NODE
class Node
{
//private:
public:
    Node* _right = NULL;
    Node* _left  = NULL;
    Node* _parent  = NULL;

    value_type _value  = 0;
    definision _define;


    //Copy functions
    //Fully copy all Nodes from donor Node to current
    Node* CopyNode (Node* donor);


    //In all function below return pointer on top Node

    //Realized rule 1)Sum
    Node* DiffSum();

    //Realized rule 2)Multiplication
    Node* DiffMul();

    //Realized rule 3)Divide
    Node* DiffDiv();

    //Realized rule 4)Power
    Node* DiffPow();

    //Diff. trig. function
    Node* DiffTrig();

    //Diff. logarithm
    Node* DiffLog();//Don't realized====================================================================================

    //Diff. exp
    Node* DiffExp();


    //Print Tree function for more infomation look PrintTree.cpp
    bool PrintFunc (char*);
    bool PrintVar  (char*);

    bool PrintMUL (char*);
    bool PrintSUB (char*);
    bool PrintDIV (char*);
    bool PrintADD (char*);
    bool PrintPOW (char*);
    bool PrintLOG (char*);

    bool IsEqual (Node*);

public:
    //Constructor and Destructor
    Node();
    Node (value_type value , definision def );
    ~Node(); //if  TRUE, delete Node with all branches


    //Increasing tree function adding new node
    Node* AddNodeRight (value_type value , definision def );
    Node* AddNodeLeft  (value_type value , definision def );


/*
 * Differentiate node using differentiation rules
 */
    Node* DiffNode();

    //Print Node and call PrintNode to branches
    bool PrintNode(char*);

};


//===============================================
//TREE
class Tree
{
//private
public:
    Node* _head;

public:
    Tree()
    {
        _head = NULL;
    }
    Tree(value_type , definision);
    ~Tree();

    //Conventional
    bool  StrToTree (char* funcStr);
    char* TreeToStr (char* res);

    //Simplification
    void* Simplification();
    void* SumSimplification (Node*);
    void* MulSimplification (Node*);
    void* CountNodes        (Node* , int* res);

    //Main functions
    Tree* Differentiator();
};

#endif //TREE_TREELIB_H
