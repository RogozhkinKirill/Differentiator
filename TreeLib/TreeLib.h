#ifndef TREE_TREELIB_H
#define TREE_TREELIB_H

#include <stdio.h>

#include "../decoder/decoder.h"

#define FULL   TRUE
#define PARTLY FALSE

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
private:
    Node* _right = NULL;
    Node* _left  = NULL;
    Node* _parent  = NULL;

    value_type _value  = NULL;
    definision _define = NULL;

public:
    //Constructor and Destructor
    Node(value_type value = NULL , definision def = NULL);
    ~Node(bool delete_full); //if  TRUE, delete Node with all branches


    //Increasing tree function adding new node
    Node* AddNodeRight (value_type value = NULL , definision def = NULL);
    Node* AddNodeLeft  (value_type value = NULL , definision def = NULL);

    //Diffintiator functions

    /*
     * Differentiate node using differentiation rules
     */
    Node* DiffNode();


    //In all function below return pointer on top Node

    //Realized rule 1)Sum
    Node* DiffSum();//Don't realized====================================================================================

    //Realized rule 2)Multiplication
    Node* DiffMul();//Don't realized====================================================================================

    //Realized rule 3)Divide
    Node* DiffDiv();//Don't realized====================================================================================

    //Realized rule 4)Power
    Node* DiffPow();//Don't realized====================================================================================

    //Diff. trig. function
    Node* DiffTrig();//Don't realized===================================================================================

    //Diff. logarithm
    Node* DiffLog();//Don't realized====================================================================================

    //Diff. exp
    Node* DiffExp();//Don't realized====================================================================================
};


//===============================================
//TREE
class Tree
{
private:
    Node* _head = NULL;

public:
    Tree(value_type , definision);
    ~Tree();

    //Conventional
    bool  StrToTree (char* funcStr);//Don't realized====================================================================
    char* TreeToStr ();//Don't realized=================================================================================


    //Main functions
    Tree* Differentiator(); //Don't realized============================================================================
};

#endif //TREE_TREELIB_H
