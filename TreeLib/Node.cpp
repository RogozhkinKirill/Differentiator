#include <afxres.h>
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
Node::~Node(bool delete_full)
{
    printf ("Destructor called: Node\n");

    if (delete_full == TRUE)
    {
        if (this->_right)
            delete this->_right;

        if (this->_left)
            delete this->_left;
    }

    this->_value = NULL;
}

//-----------------------------------------------
//Functions

/*
 *Add node to current node's right node and return its address
 *if it does not exist
 *Otherwise do the same with left node
 */
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

/*
 *Add node to current node's left node and return its address
 *if it does not exist
 *Otherwise do the same with left node
 */
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

//Differentiate node using differentiation rules(look ..\Differentiator\Differentiator.h)
Node* Node::DiffNode()
{
    if (this != 0)
    {
        //Check _define
        /*
         * FUNCTION
         *
         * In this case realize rules of differentiation
         * 1)Sum
         * 2)Multiplication
         * 3)Divide
         * 4)Power
         *
         * For more info use ../Differentiator/Differentiator.h
         */
        if (_define == FUNCTION)
        {
            /*
             * Here _value mean code of FUNCTION
             *
             * For more info use ../decoder/decoder.h
             */
            switch (_value)
            {
                case add:
                case sub:
                {
                    DiffSum();
                };
                    break;

                case mul:
                {
                    DiffMul();
                };
                    break;

                case div:
                {
                    DiffDiv();
                };
                    break;

                case pow:
                {
                    DiffPow();
                };
                    break;

                case sin:
                case cos:
                case tg:
                case ctg:
                case sh:
                case ch:
                case th:
                case cth:
                {
                    DiffTrig();
                };
                    break;

                case exp:
                {
                    DiffExp();
                };
                    break;

                case lg:
                case ln:
                case log:
                {
                    DiffLog();
                };
            }
        }
    }
    else
    {
        printf("Pointer on Node in DiffeNode = NULL");
        return NULL;
    }

    return this;
}

//Diff. functions

//Realized rule 1)Sum
Node* Node::DiffSum();//Don't realized==================================================================================

//Realized rule 2)Multiplication
Node* Node::DiffMul();//Don't realized==================================================================================

//Realized rule 3)Divide
Node* Node::DiffDiv();//Don't realized==================================================================================

//Realized rule 4)Power
Node* Node::DiffPow();//Don't realized==================================================================================

//Diff. trig. function
Node* Node::DiffTrig();//Don't realized=================================================================================

//Diff. logarithm
Node* Node::DiffLog();//Don't realized==================================================================================

//Diff. exp
Node* Node::DiffExp();//Don't realized==================================================================================