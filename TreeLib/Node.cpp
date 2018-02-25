#include "TreeLib.h"

//===============================================
//Node functions


//-----------------------------------------------
//Constructor
Node::Node(value_type value = NULL , definision def = NULL)
{
    printf ("Constuctor called: Node\n");
    this->_left   = this->_right = this->_parent = NULL;
    this->_value  = value;
    this->_define = def;
}

//-----------------------------------------------
//Destructor
Node::~Node()
{
    printf ("Destructor called: Node\n");
    if(this->_right)
        delete this->_right;

    if(this->_left)
        delete this->_left;

    this->_value = NULL;
}

//-----------------------------------------------
//Functions

//Add node to current node's right node and return its address
//if it does not exist
//Otherwise do the same with left node
Node* Node::AddNodeRight (value_type value , definision def)
{
    if(!this)
    {
        printf("Pointer on Node in Node::AddNodeLeft = NULL");
        return NULL;
    }

    if(!this->_right)
    {
        Node* newNode = new Node(value , def);
        this->_right = newNode;
        this->_right->_parent = this;

        return newNode;
    }
    else
    {
        this->_right->AddNodeRight(value , def);
    }
}

//Add node to current node's left node and return its address
//if it does not exist
//Otherwise do the same with left node
Node* Node::AddNodeLeft (value_type value , definision def)
{
    if(!this)
    {
        printf("Pointer on Node in Node::AddNodeLeft = NULL");
        return NULL;
    }

    if(!this->_left)
    {
        Node* newNode = new Node (value , def);
        this->_left = newNode;
        this->_left->_parent = this;

        return newNode;
    }
    else
    {
        this->_left->AddNodeLeft (value , def);
    }
}
