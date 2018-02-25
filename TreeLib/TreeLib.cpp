#include "TreeLib.h"

/*
 * Node functions
 */
Node::Node()
{
    printf ("Constuctor called: Node\n");
    this->_left = this->_right = this->_parent = NULL;
    this->_value = NULL;
}

Node::Node(value_type value)
{
    printf ("Constuctor called: Node\n");
    this->_left = this->_right = this->_parent = NULL;
    this->_value = value;
}

Node::~Node()
{
    printf ("Destructor called: Node\n");
    if(this->_right)
        delete this->_right;

    if(this->_left)
        delete this->_left;

    this->_value = NULL;
}

Node* Node::AddNodeRight(value_type value)
{
    if(!this)
    {
        printf("Pointer on Node in Node::AddNodeLeft = NULL");
        return NULL;
    }

    if(!this->_right)
    {
        Node* newNode = new Node(value);
        this->_right = newNode;
        this->_right->_parent = this;

        return newNode;
    }
    else
    {
        this->_right->AddNodeRight(value);
    }
}

Node* Node::AddNodeLeft(value_type value)
{
    if(!this)
    {
        printf("Pointer on Node in Node::AddNodeLeft = NULL");
        return NULL;
    }

    if(!this->_left)
    {
        Node* newNode = new Node(value);
        this->_left = newNode;
        this->_left->_parent = this;

        return newNode;
    }
    else
    {
        this->_left->AddNodeLeft(value);
    }
}

Node* Node::AddSort(value_type value)
{
    if(!this)
    {
        printf("Pointer on Node in Node::AddSort = NULL\n");
        return NULL;
    }

    if(this->_value >= value)
    {
        if(!this->_left)
        {
            Node* newNode = new Node(value);;
            this->_left = newNode;
            return newNode;
        }
        this->_left->AddSort(value);
    }
    else
    {
        if(!this->_right)
        {
            Node* newNode = new Node(value);;
            this->_right = newNode;
            return newNode;
        }
        this->_right->AddSort(value);
    }
}

void Node::PrintTree()
{
    if(!this)
    {
        printf("Pointer on Node in Node::AddNodeLeft = NULL");
        return;
    }

    if(this->_left)
    {
        this->_left->PrintTree();
    }


    printf("%d " , this->_value);

    if(this->_right)
    {
        this->_right->PrintTree();
    }

    return;
}


/*
 * Tree functions
 */
Tree::Tree()
{
    this->_head = new Node();
}

Tree::Tree(value_type value)
{
    this->_head = new Node(value);
}

Tree::~Tree()
{
    if(this->_head)
        delete this->_head;
}

