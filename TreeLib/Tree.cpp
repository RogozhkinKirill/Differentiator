#include "TreeLib.h"


//===============================================
//Tree functions

//-----------------------------------------------
//Constructor
Tree::Tree(value_type value , definision def)
{
    this->_head = new Node(value , def);
}

//-----------------------------------------------
//Destructor
Tree::~Tree()
{
    if(this->_head)
        delete this->_head;
}

//-----------------------------------------------
//Functions

bool  Tree::StrToTree (char* funcStr)//Don't realized=========================================================================
{}

char* Tree::TreeToStr ()//Don't realized======================================================================================
{}


//Main function
Tree* Tree::Differentiator()//Don't realized==================================================================================
{
    _head = _head->DiffNode();

    return this;
}