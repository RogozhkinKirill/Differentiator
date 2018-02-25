#include "TreeLib.h"


//===============================================
//Tree functions
Tree::Tree(value_type value , definision def)
{
    this->_head = new Node(value , def);
}

Tree::~Tree()
{
    if(this->_head)
        delete this->_head;
}

