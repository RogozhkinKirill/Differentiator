#include <afxres.h>
#include <iostream>
#include "TreeLib.h"
#include "print_tree.h"

#define CASE(x , y) case y: {strcat (x , #y);} break;

//===============================================
//Node functions


//-----------------------------------------------
//Constructor
Node::Node()
{
    printf ("Simple Constructor called\n");
    _define = NLL;
    _value = 0;
    _parent = _left = _right = NULL;
}

Node::Node(value_type value , definision def)
{
    char smt[10] = {0};
    if (def == FUNCTION)
        strcat(smt , "fun");
    if (def == VARIABLE)
        strcat(smt , "var");

    printf ("Constuctor called: Node define = %s\n" , smt);
    this->_left   = this->_right = this->_parent = NULL;
    this->_value  = value;
    this->_define = def;
}

//-----------------------------------------------
//Destructor
Node::~Node()
{
    printf ("Destructor called: Node\n");


    if (this->_right)
        delete this->_right;

    if (this->_left)
        delete this->_left;


    this->_value = 0;
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
Node* Node::CopyNode (Node* donor)
{
    if (this)
    {
        //Copy data from donor Node
        _value  = donor->_value;
        _define = donor->_define;

        if (donor->_right)
        {
            _right = new Node (donor->_right->_value , donor->_right->_define);
            _right->CopyNode(donor->_right);
        }

        if (donor->_left)
        {
            _left = new Node (donor->_left->_value , donor->_left->_define);
            _left->CopyNode(donor->_left);
        }
    }
    else
        return NULL;

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
        switch (_define)
        {

            case FUNCTION:
            {
                /*
                 * Here _value mean code of FUNCTION
                 *
                 * For more info use ../decoder/decoder.h
                 */
                switch (_value)
                {
                    case ADD:
                    case SUB: {
                        DiffSum();
                    };
                        break;

                    case MUL: {
                        DiffMul();
                    };
                        break;

                    case DIV: {
                        DiffDiv();
                    };
                        break;

                    case POW: {
                        DiffPow();
                    };
                        break;

                    case SIN:
                    case COS:
                    case TG:
                    case CTG:
                    case SH:
                    case CH:
                    case TH:
                    case CTH: {
                        DiffTrig();
                    };
                        break;

                    case EXP: {
                        DiffExp();
                    };
                        break;

                    case LG:
                    case LN:
                    case LOG: {
                        DiffLog();
                    };
                    default:break;
                }
            };
                break;

            case CONSTANT:
            {
                _value = 0;
            };
                break;

            case VARIABLE:
            {
                _define = CONSTANT;
                _value  = 1;
                printf ("12233\n\n");
            };
                break;
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
    if (this)
    {
        _right->DiffNode();
        _left ->DiffNode();

        return this;
    }
    else return NULL;
}

//Realized rule 2)Multiplication
Node* Node::DiffMul()
{
    if (this)
    {
        //Change FUNCTION in this Node from * to +
        _value = ADD;

        //Create new Nodes
        Node *firstLeft = new Node(MUL, FUNCTION);
        Node *firstRight = new Node(MUL, FUNCTION);

        //Connect new Nodes this parent Node
        firstLeft->_parent = this;
        firstRight->_parent = this;


        //Create new chilren Nodes to new Nodes
        //and
        //connect with parent's Nodes
        //
        //New will be differentiate

        //Create second level
        Node* secondLeftLeft = new Node(_left->_value, _left->_define);
        secondLeftLeft->CopyNode(_left);
        secondLeftLeft->_parent = firstLeft;
        firstLeft->_left = secondLeftLeft;

        Node* secondRightRight = new Node(_right->_value, _right->_define);
        secondRightRight->CopyNode(_right);
        secondRightRight->_parent = firstRight;
        firstRight->_right = secondRightRight;


        //Reconnect parent's children nodes with new Nodes
        _right->_parent = firstLeft;
        firstLeft->_right = _right;

        _left->_parent = firstRight;
        firstRight->_left = _left;


        _right = firstRight;
        _left = firstLeft;

        //Diff. firstLeft/Right
        printf ("Diff left Node\n");
        secondLeftLeft->DiffNode();
        printf ("Diff right Node\n");
        secondRightRight->DiffNode();

        return this;
    }
    else return NULL;
}

//Realized rule 3)Divide
Node* Node::DiffDiv()
{
    if (this)
    {
        //Create Nodes of first level
        Node *firstLeft = new Node(SUB, FUNCTION);
        firstLeft->_parent = this;

        Node *firstRight = new Node(MUL, FUNCTION);
        firstRight->_parent = this;


        //Create Nodes of second level
        Node *secondLeftLeft = new Node(MUL, FUNCTION);
        secondLeftLeft->_parent = firstLeft;
        firstLeft->_left = secondLeftLeft;

        Node *secondLeftRight = new Node(MUL, FUNCTION);
        secondLeftRight->_parent = firstLeft;
        firstLeft->_right = secondLeftRight;


        Node *secondRightLeft = new Node(_right->_value, _right->_define);
        secondRightLeft->_parent = firstRight;
        firstRight->_left = secondRightLeft;
        secondRightLeft->CopyNode(_right);

        Node *secondRightRight = new Node(_right->_value, _right->_define);
        secondRightRight->_parent = firstRight;
        firstRight->_right = secondRightRight;
        secondRightRight->CopyNode(_right);

        //Create Nodes of third level
        Node *thirdLeftLeftLeft = new Node(_left->_value, _left->_define);
        thirdLeftLeftLeft->_parent = secondLeftLeft;
        secondLeftLeft->_left = thirdLeftLeftLeft;
        thirdLeftLeftLeft->CopyNode(_left);

        Node *thirdLeftRightRight = new Node(_right->_value, _right->_define);
        thirdLeftRightRight->_parent = secondLeftRight;
        secondLeftRight->_right = thirdLeftRightRight;
        thirdLeftRightRight->CopyNode(_right);

        //Reconnect _right and _left
        _right->_parent = secondLeftLeft;
        secondLeftLeft->_right = _right;

        _left->_parent = secondLeftRight;
        secondLeftRight->_left = _left;

        _right = firstRight;
        _left = firstLeft;

        //Diff. the necessary Nodes
        thirdLeftLeftLeft->DiffNode();
        thirdLeftRightRight->DiffNode();
    }
    else return NULL;
}

//Realized rule 4)Power
Node* Node::DiffPow()
{
    if (this)
    {
        //Change FUNCTION in this Node from ^ to *
        _value = MUL;


        //Create Nodes of first level
        Node *firstLeft = new Node(ADD, FUNCTION);
        firstLeft->_parent = this;

        Node *firstRight = new Node(POW, FUNCTION);
        firstRight->_parent = this;


        //CreateNodes of second level
        Node *secondLeftLeft = new Node(MUL, FUNCTION);
        secondLeftLeft->_parent = firstLeft;
        firstLeft->_left = secondLeftLeft;

        Node *secondLeftRight = new Node(MUL, FUNCTION);
        secondLeftRight->_parent = firstLeft;
        firstLeft->_right = secondLeftRight;


        Node *secondRightLeft = new Node(_left->_value, _left->_define);
        secondRightLeft->_parent = firstRight;
        firstRight->_left = secondRightLeft;
        secondRightLeft->CopyNode(_left);

        Node *secondRightRight = new Node(_right->_value, _right->_define);
        secondRightRight->_parent = firstRight;
        firstRight->_right = secondRightRight;
        secondRightRight->CopyNode(_right);


        //Create Nodes of third level
        Node *thirdLeftLeftLeft = new Node(_right->_value, _right->_define);
        thirdLeftLeftLeft->_parent = secondLeftLeft;
        secondLeftLeft->_left = thirdLeftLeftLeft;
        thirdLeftLeftLeft->CopyNode(_right);

        Node *thirdLeftLeftRight = new Node(LN, FUNCTION);
        thirdLeftLeftRight->_parent = secondLeftLeft;
        secondLeftLeft->_right = thirdLeftLeftRight;


        Node *thirdLeftRightRight = new Node(_left->_value, _left->_define);
        thirdLeftRightRight->_parent = secondLeftRight;
        secondLeftRight->_right = thirdLeftRightRight;
        thirdLeftRightRight->CopyNode(_left);

        Node *thirdLeftRightLeft = new Node(DIV, FUNCTION);
        thirdLeftRightLeft->_parent = secondLeftRight;
        secondLeftRight->_left = thirdLeftRightLeft;


        //Create Nodes of forth level
        Node *forthLeftLeftRightLeft = new Node(_left->_value, _left->_define);
        forthLeftLeftRightLeft->_parent = thirdLeftLeftRight;
        thirdLeftLeftRight->_left = forthLeftLeftRightLeft;
        forthLeftLeftRightLeft->CopyNode(_left);



        //Reconnect _right and _left
        _right->_parent = thirdLeftRightLeft;
        thirdLeftRightLeft->_left = _right;

        _left->_parent = thirdLeftRightLeft;
        thirdLeftRightLeft->_right = _left;

        _right = firstRight;
        _left = firstLeft;


        //Diff. the necessary Nodes
        thirdLeftLeftLeft->DiffNode();
        thirdLeftRightRight->DiffNode();
    }
    else return NULL;
}

//Diff. trig. function
Node* Node::DiffTrig()
{
    if (this)
    {
        switch (_value) {

            case COS: {
                //Change FUNCTION in this Node from FUNCTION to *
                _value = MUL;

                //Create first level
                Node *firstRight = new Node (MUL, FUNCTION);
                firstRight->_parent = this;
                _right = firstRight;

                Node *firstLeft = new Node (-1, CONSTANT);
                firstLeft->_parent = this;


                //Create second level
                Node *secondRightRight = new Node (_left->_value , _left->_define);
                firstRight->_right = secondRightRight;
                secondRightRight->_parent = firstRight;

                Node* secondRightLeft = new Node (SIN , FUNCTION);
                firstRight->_left = secondRightLeft;
                secondRightLeft->_parent = firstRight;

                //Create third level and reconnect
                secondRightLeft->_left = _left;
                _left = firstLeft;

                //Diff.
                secondRightRight->DiffNode();
            }
                break;

            case SIN: {
                //Change FUNCTION in this Node from FUNCTION to *
                _value = MUL;

                //Create first level
                Node *firstRight = new Node (MUL, FUNCTION);
                firstRight->_parent = this;
                _right = firstRight;

                Node *firstLeft = new Node (1, CONSTANT);
                firstLeft->_parent = this;


                //Create second level
                Node *secondRightRight = new Node (_left->_value , _left->_define);
                firstRight->_right = secondRightRight;
                secondRightRight->_parent = firstRight;

                Node* secondRightLeft = new Node (COS , FUNCTION);
                firstRight->_left = secondRightLeft;
                secondRightLeft->_parent = firstRight;

                //Create third level and reconnect
                secondRightLeft->_left = _left;
                _left = firstLeft;

                //Diff.
                secondRightRight->DiffNode();
            }
                break;

            case SH: {
                //Change FUNCTION in this Node from FUNCTION to *
                _value = MUL;

                //Create first level
                Node *firstRight = new Node (MUL, FUNCTION);
                firstRight->_parent = this;
                _right = firstRight;

                Node *firstLeft = new Node (1, CONSTANT);
                firstLeft->_parent = this;


                //Create second level
                Node *secondRightRight = new Node (_left->_value , _left->_define);
                firstRight->_right = secondRightRight;
                secondRightRight->_parent = firstRight;

                Node* secondRightLeft = new Node (CH , FUNCTION);
                firstRight->_left = secondRightLeft;
                secondRightLeft->_parent = firstRight;

                //Create third level and reconnect
                secondRightLeft->_left = _left;
                _left = firstLeft;

                //Diff.
                secondRightRight->DiffNode();
            }
                break;

            case CH: {
                //Change FUNCTION in this Node from FUNCTION to *
                _value = MUL;

                //Create first level
                Node *firstRight = new Node (MUL, FUNCTION);
                firstRight->_parent = this;
                _right = firstRight;

                Node *firstLeft = new Node (1, CONSTANT);
                firstLeft->_parent = this;


                //Create second level
                Node *secondRightRight = new Node (_left->_value , _left->_define);
                firstRight->_right = secondRightRight;
                secondRightRight->_parent = firstRight;

                Node* secondRightLeft = new Node (SH , FUNCTION);
                firstRight->_left = secondRightLeft;
                secondRightLeft->_parent = firstRight;

                //Create third level and reconnect
                secondRightLeft->_left = _left;
                _left = firstLeft;

                //Diff.
                secondRightRight->DiffNode();
            }
                break;

            case TG: {
                //Change FUNCTION in this Node from FUNCTION to /
                _value = DIV;

                //Create first level
                Node *firstRight = new Node(POW, FUNCTION);
                firstRight->_parent = this;
                _right = firstRight;

                //Create second level
                Node *secondRightRight = new Node(2, CONSTANT);
                secondRightRight->_parent = firstRight;
                firstRight->_right = secondRightRight;

                Node *secondRightLeft = new Node(COS, FUNCTION);
                secondRightLeft->_parent = firstRight;
                firstRight->_left = secondRightLeft;

                //Create third level
                Node *thirdRightLeftLeft = new Node(_left->_value, _left->_define);
                thirdRightLeftLeft->_parent = secondRightLeft;
                secondRightLeft->_left = thirdRightLeftLeft;

                //Diff.
                _left->DiffNode();
            }
                break;

            case TH: {
                //Change FUNCTION in this Node from FUNCTION to /
                _value = DIV;

                //Create first level
                Node *firstRight = new Node(POW, FUNCTION);
                firstRight->_parent = this;
                _right = firstRight;

                //Create second level
                Node *secondRightRight = new Node(2, CONSTANT);
                secondRightRight->_parent = firstRight;
                firstRight->_right = secondRightRight;

                Node *secondRightLeft = new Node(CH, FUNCTION);
                secondRightLeft->_parent = firstRight;
                firstRight->_left = secondRightLeft;

                //Create third level
                Node *thirdRightLeftLeft = new Node(_left->_value, _left->_define);
                thirdRightLeftLeft->_parent = secondRightLeft;
                secondRightLeft->_left = thirdRightLeftLeft;
                thirdRightLeftLeft->CopyNode(_left);

                //Diff.
                _left->DiffNode();
            }
                break;

            case CTG: {
                //Change FUNCTION in this Node from FUNCTION to /
                _value = DIV;

                //Create first level
                Node *firstRight = new Node(POW, FUNCTION);
                firstRight->_parent = this;
                _right = firstRight;

                Node *firstLeft = new Node(MUL, FUNCTION);
                firstLeft->_parent = this;

                //Create second level
                Node *secondRightRight = new Node(2, CONSTANT);
                secondRightRight->_parent = firstRight;
                firstRight->_right = secondRightRight;

                Node *secondRightLeft = new Node(SIN, FUNCTION);
                secondRightLeft->_parent = firstRight;
                firstRight->_left = secondRightLeft;


                Node *secondLeftLeft = new Node(-1, CONSTANT);
                secondLeftLeft->_parent = firstLeft;
                firstLeft->_left = secondLeftLeft;

                Node *secondLeftRight = new Node(_left->_value, _left->_define);
                secondLeftRight->_parent = firstLeft;
                firstLeft->_right = secondLeftRight;
                secondLeftRight->CopyNode(_left);

                //Reconnect _left
                _left->_parent = secondRightLeft;
                secondRightLeft->_left = _left;

                _left = firstLeft;

                //Diff.
                secondLeftRight->DiffNode();
            }
                break;


            case CTH: {
                //Change FUNCTION in this Node from FUNCTION to /
                _value = DIV;

                //Create first level
                Node *firstRight = new Node(POW, FUNCTION);
                firstRight->_parent = this;
                _right = firstRight;

                Node *firstLeft = new Node(MUL, FUNCTION);
                firstLeft->_parent = this;

                //Create second level
                Node *secondRightRight = new Node(2, CONSTANT);
                secondRightRight->_parent = firstRight;
                firstRight->_right = secondRightRight;

                Node *secondRightLeft = new Node(SH, FUNCTION);
                secondRightLeft->_parent = firstRight;
                firstRight->_left = secondRightLeft;


                Node *secondLeftLeft = new Node(-1, CONSTANT);
                secondLeftLeft->_parent = firstLeft;
                firstLeft->_left = secondLeftLeft;

                Node *secondLeftRight = new Node(_left->_value, _left->_define);
                secondLeftRight->_parent = firstLeft;
                firstLeft->_right = secondLeftRight;
                secondLeftRight->CopyNode(_left);

                //Reconnect _left
                _left->_parent = secondRightLeft;
                secondRightLeft->_left = _left;

                _left = firstLeft;

                //Diff.
                secondLeftRight->DiffNode();
            }
                break;
            default:break;
        }
    }
    else return NULL;
}

//Diff. logarithm
Node* Node::DiffLog()
{
    if (this)
    {
        switch (_value)
        {
            case LG:
            {
                _value = DIV;

                //Create first level
                Node* firstLeft = new Node (LN , FUNCTION);
                firstLeft->_left = _left;
                _left->_parent = firstLeft;
                firstLeft->_parent = this;
                _left = firstLeft;

                Node* firstRight = new Node (LN , FUNCTION);
                _right = firstRight;
                firstRight->_parent = this;

                //Create second level
                Node* secondRightLeft = new Node (10 , CONSTANT);
                secondRightLeft->_parent = firstRight;
                firstRight->_left = secondRightLeft;

                //Diff.
                this->DiffNode();
            }
                break;

            case LN:
            {
                _value = DIV;

                //Create first level
                Node* firstRight = new Node (_left->_value , _left->_define);
                _right = firstRight;
                firstRight->_parent = this;
                firstRight->CopyNode(_left);

                //Diff.
                _left->DiffNode();
            }
                break;

            case LOG:
            {
                _value = DIV;

                //Create first level
                Node* firstLeft = new Node (LN , FUNCTION);
                firstLeft->_left   = _right;
                firstLeft->_parent = this;

                Node* firstRight = new Node (LN , FUNCTION);
                firstRight->_left   = _left;
                firstRight->_parent = this;

                //Reconnect
                _left  = firstLeft;
                _right = firstRight;

                //Diff.
                this->DiffNode();
            }
                break;

            default:break;
        }
    }
    else return NULL;
}

//Diff. exp
Node* Node::DiffExp()
{
    if (this)
    {
        _value = MUL;

        //Create first level
        Node* firstRight = new Node (EXP , FUNCTION);
        _right = firstRight;
        firstRight->_parent = this;

        //Create second level
        Node* secondRightLeft = new Node (_left->_value , _left->_define);
        secondRightLeft->_parent = firstRight;
        firstRight->_left = secondRightLeft;
        secondRightLeft->CopyNode(_left);

        //Diff.
        _left->DiffNode();
    }
    else return NULL;
}


//Check checker Node and his branches
bool Node::IsEqual (Node* checker)
{
    bool res = 0;
    if (_value == checker->_value && _define == checker->_define)
    {
        //if ()
    }

    return res;
}