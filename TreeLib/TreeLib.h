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
};



//===============================================
//TREE
class Tree
{
public:
    Node* _head = NULL;


    Tree(value_type , definision);
    ~Tree();

    //Conventional
    bool  StrToTree (char* funcStr);//Don't realized
    char* TreeToStr ();//Don't realized

    Tree* Differentiator(); //Don't realized
};

#endif //TREE_TREELIB_H
