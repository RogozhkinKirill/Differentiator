#ifndef TREE_TREELIB_H
#define TREE_TREELIB_H

#include <stdio.h>

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
private:
    Node* _right = NULL;
    Node* _left  = NULL;
    Node* _parent  = NULL;

    value_type _value  = NULL;
    definision _define = NULL;

public:
    Node(value_type value = NULL , definision def = NULL);
    ~Node();

    Node* AddNodeRight (value_type value = NULL , definision def = NULL);
    Node* AddNodeLeft  (value_type value = NULL , definision def = NULL);

    Node* DiffeNode();
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


    //Main function
    Tree* Differentiator(); //Don't realized============================================================================
};

#endif //TREE_TREELIB_H
