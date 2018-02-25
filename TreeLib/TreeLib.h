#ifndef TREE_TREELIB_H
#define TREE_TREELIB_H

#include <stdio.h>

#include "../decoder/decoder.h"

//===============================================
//Code of symbol (cos, x, 5, etc.)
typedef encoding value_type;

//===============================================
//NODE
class Node
{
protected:
    Node* _right = NULL;
    Node* _left  = NULL;
    Node* _parent  = NULL;

    value_type _value  = NULL;

public:
    Node();
    Node(value_type);
    ~Node();

    Node* AddNodeRight(value_type);
    Node* AddNodeLeft(value_type);

    Node* AddSort(value_type);

    void PrintTree();
};



//===============================================
//TREE
class Tree
{
protected:
    Node* _head = NULL;

public:
    Tree();
    Tree(value_type);
    ~Tree();
};

#endif //TREE_TREELIB_H
