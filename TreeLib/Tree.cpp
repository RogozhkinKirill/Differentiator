#include "TreeLib.h"


//===============================================
//Tree functions

//-----------------------------------------------
//Constructor
Tree::Tree(value_type value , definision def)
{
    printf ("Constructor Tree called\n");
    this->_head = new Node(value , def);
}

//-----------------------------------------------
//Destructor
Tree::~Tree()
{
    printf ("Destrictor Tree called\n");
    if(this->_head)
        delete this->_head;
}

//-----------------------------------------------
//Functions

bool  Tree::StrToTree (char* funcStr)//Don't realized=========================================================================
{

}

char* Tree::TreeToStr (char* res)//Don't realized======================================================================================
{
    this ? _head->PrintNode(res) : printf("ERROR. Pointer on Tree = NULL\n");
}


//Main function
Tree* Tree::Differentiator()//Don't realized==================================================================================
{
    _head = _head->DiffNode();

    return this;
}