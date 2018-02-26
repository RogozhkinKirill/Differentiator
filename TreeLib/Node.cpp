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

//Copy functions
//Fully copy all Nodes from donor Node to current
Node* Node::CopyNode (Node* donor)//Don't realized======================================================================
{}


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
//For more information look ../Differentiator/Differentiator.h


//Realized rule 1)Sum
Node* Node::DiffSum()
{
    if (_right->_define == FUNCTION)
        _right->DiffNode();

    if (_left->_define == FUNCTION)
        _left->DiffNode();

    return this;
}

//Realized rule 2)Multiplication
Node* Node::DiffMul()
{
    //Change FUNCTION in this Node from * to +
    _value = add;

    //Create new Nodes
    Node* firstLeft  = new Node (mul , FUNCTION);
    Node* firstRight = new Node (mul , FUNCTION);

    //Connect new Nodes this parent Node
    firstLeft->_parent  = this;
    firstRight->_parent = this;


    //Create new chilren Nodes to new Nodes
    //and
    //connect with parent's Nodes
    //
    //New will be differentiate

    //To firstLeft
    Node* secondLeftLeft = new Node (_right->_value , _right->_define);
    secondLeftLeft->CopyNode (_left);
    secondLeftLeft->_parent = firstLeft;
    firstLeft->_right = secondLeftLeft;

    //To firstRight
    Node* secondRightRight = new Node (_left->_value , _left->_define);
    secondRightRight->CopyNode (_right);
    secondRightRight->_parent = firstRight;
    firstRight->_left = secondRightRight;


    //Reconnect parent's children nodes with new Nodes
    _right->_parent = firstLeft;
    firstLeft->_left   = _right;

    _left->_parent = firstRight;
    firstRight->_right = _left;


    _right = firstRight;
    _left  = firstLeft;

   //Diff. firstLeft/Right
    secondLeftLeft->DiffNode();
    secondRightRight->DiffNode();

    return this;
}

//Realized rule 3)Divide
Node* Node::DiffDiv()
{
    //Create Nodes of first level
    Node* firstLeft = new Node (sub , FUNCTION);
    firstLeft->_parent = this;

    Node* firstRight = new Node (mul , FUNCTION);
    firstRight->_parent = this;


    //Create Nodes of second level
    Node* secondLeftLeft = new Node (mul , FUNCTION);
    secondLeftLeft->_parent = firstLeft;
    firstLeft->_left = secondLeftLeft;

    Node* secondLeftRight = new Node (mul , FUNCTION);
    secondLeftRight->_parent = firstLeft;
    firstLeft->_right = secondLeftRight;


    Node* secondRightLeft = new Node (_right->_value , _right->_define);
    secondRightLeft->_parent = firstRight;
    firstRight->_left = secondRightLeft;
    secondRightLeft->CopyNode(_right);

    Node* secondRightRight = new Node (_right->_value , _right->_define);
    secondRightRight->_parent = firstRight;
    firstRight->_left = secondRightRight;
    secondRightRight->CopyNode(_right);

    //Create Nodes of third level
    Node* thirdLeftLeftLeft = new Node (_left->_value , _left->_define);
    thirdLeftLeftLeft->_parent = secondLeftLeft;
    secondLeftLeft->_left = thirdLeftLeftLeft;
    thirdLeftLeftLeft->CopyNode(_left);

    Node* thirdLeftRightRight = new Node (_right->_value , _right->_define);
    thirdLeftRightRight->_parent = secondLeftRight;
    secondLeftRight->_right = thirdLeftRightRight;
    thirdLeftRightRight->CopyNode (_right);

    //Reconnect _right and _left
    _right->_parent = secondLeftLeft;
    secondLeftLeft->_right = _right;

    _left->_parent = secondLeftRight;
    secondLeftRight->_left = _left;

    _right = firstRight;
    _left  = firstLeft;

    //Diff. the necessary Nodes
    thirdLeftLeftLeft->DiffNode();
    thirdLeftRightRight->DiffNode();
}

//Realized rule 4)Power
Node* Node::DiffPow()
{
    //Create Nodes of first level
    Node* firstLeft = new Node (sub , FUNCTION);
    firstLeft->_parent = this;

    Node* firstRight = new Node (pow , FUNCTION);
    firstRight->_parent = this;


    //CreateNodes of second level
    Node* secondLeftLeft = new Node (mul , FUNCTION);
    secondLeftLeft->_parent = firstLeft;
    firstLeft->_left = secondLeftLeft;

    Node* secondLeftRight = new Node (mul , FUNCTION);
    secondLeftRight->_parent = firstLeft;
    firstLeft->_right = secondLeftRight;



    Node* secondRightLeft = new Node (_left->_value , _left->_define);
    secondRightLeft->_parent = firstRight;
    firstRight->_left = secondRightLeft;
    secondRightLeft->CopyNode(_left);

    Node* secondRightRight = new Node (_right->_value , _right->_define);
    secondRightRight->_parent = firstRight;
    firstRight->_left = secondRightRight;
    secondRightRight->CopyNode(_right);


    //Create Nodes of third level
    Node* thirdLeftLeftLeft = new Node (_right->_value , _right->_define);
    thirdLeftLeftLeft->_parent = secondLeftLeft;
    secondLeftLeft->_left = thirdLeftLeftLeft;
    thirdLeftLeftLeft->CopyNode (_right);

    Node* thirdLeftLeftRight = new Node (ln , FUNCTION);
    thirdLeftLeftRight->_parent = secondLeftLeft;
    secondLeftLeft->_right = thirdLeftLeftRight;



    Node* thirdLeftRightRight = new Node (_left->_value , _left->_define);
    thirdLeftRightRight->_parent = secondLeftRight;
    secondLeftRight->_right = thirdLeftRightRight;
    thirdLeftRightRight->CopyNode (_left);

    Node* thirdLeftRightLeft = new Node (div , FUNCTION);
    thirdLeftRightLeft->_parent = secondLeftRight;
    secondLeftRight->_left = thirdLeftRightLeft;


    //Create Nodes of forth level
    Node* forthLeftLeftRightLeft = new Node (_left->_value , _left->_define);
    forthLeftLeftRightLeft->_parent = thirdLeftLeftRight;
    thirdLeftLeftRight->_left = forthLeftLeftRightLeft;
    forthLeftLeftRightLeft->CopyNode(_left);



    //Reconnect _right and _left
    _right->_parent = thirdLeftRightLeft;
    thirdLeftRightLeft->_left = _right;

    _left->_parent = thirdLeftRightLeft;
    thirdLeftRightLeft->_right = _left;

    _right = firstRight;
    _left  = firstLeft;


    //Diff. the necessary Nodes
    thirdLeftLeftLeft->DiffNode();
    thirdLeftRightRight->DiffNode();
}

}

//Diff. trig. function
Node* Node::DiffTrig();//Don't realized=================================================================================

//Diff. logarithm
Node* Node::DiffLog();//Don't realized==================================================================================

//Diff. exp
Node* Node::DiffExp();//Don't realized==================================================================================