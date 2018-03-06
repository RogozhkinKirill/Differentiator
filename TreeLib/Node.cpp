#include <afxres.h>
#include "TreeLib.h"

#define CASE(x , y) case y: {strcat (x , #y);} break;

//===============================================
//Node functions


//-----------------------------------------------
//Constructor
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
        if (_right->_define == FUNCTION)
            _right->DiffNode();

        if (_left->_define == FUNCTION)
            _left->DiffNode();

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
Node* Node::DiffLog()//Don't realized===================================================================================
{
    if (this)
    {
        switch (_value)
        {
            case LG:
            {
                _value = DIV;

                //Create first level
                Node* firstRight = new Node (MUL , FUNCTION);
                firstRight->_parent = this;

                //Create second level
                Node* secondRightLeft = new Node (LN , FUNCTION);
                secondRightLeft->_parent = firstRight;
                firstRight->_left = secondRightLeft;

                Node* secondRightRight = new Node (_left->_value , _left->_define);
                secondRightRight->_parent = firstRight;
                firstRight->_right = secondRightRight;
                secondRightRight->CopyNode(_left);

                //Create third level
                Node* thirdRightLeftLeft = new Node (10 , CONSTANT);
                thirdRightLeftLeft->_parent = secondRightLeft;
                secondRightLeft->_left = thirdRightLeftLeft;

                //Diff.
                _left->DiffNode();
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


//Print Node and call PrintNode to branches
bool Node::PrintNode(char* res)
{
    if (this)
    {
        switch (_define)
        {
            case FUNCTION:
            {
                PrintFunc (res);//function below this
            }
                break;

            case VARIABLE:
            {
                PrintVar (res);//function below PrintFunc
            }
                break;

            case CONSTANT:

            default:
            {
                char num[13] = {0};
                strcat (res , itoa (_value , num , 10));
            }
        }
    }
    else
    {
        printf ("ERROR Pointer on Node in Node::PrintNode = Null\n");
        return 0;
    }

    return 0;
}

bool Node::PrintFunc (char* res)
{
    switch (_value)
    {
        case COS:
        {
            strcat (res , "cos(");
            _left->PrintNode(res);
            strcat (res , ")");
        }
            break;

        case SIN:
        {
            strcat (res , "sin(");
            _left->PrintNode(res);
            strcat (res , ")");
        }
            break;

        case TG:
        {
            strcat (res , "tg(");
            _left->PrintNode(res);
            strcat (res , ")");
        }
            break;

        case CTG:
        {
            strcat (res , "ctg(");
            _left->PrintNode(res);
            strcat (res , ")");
        }
            break;

        case SH:
        {
            strcat (res , "sh(");
            _left->PrintNode(res);
            strcat (res , ")");
        }
            break;

        case CH:
        {
            strcat (res , "ch(");
            _left->PrintNode(res);
            strcat (res , ")");
        }
            break;

        case TH:
        {
            strcat (res , "th(");
            _left->PrintNode(res);
            strcat (res , ")");
        }
            break;

        case CTH:
        {
            strcat (res , "sin(");
            _left->PrintNode(res);
            strcat (res , ")");
        }
            break;

        case EXP:
        {
            strcat (res , "exp(");
            _left->PrintNode(res);
            strcat (res , ")");
        }
            break;

        case LN:
        {
            strcat (res , "ln(");
            _left->PrintNode(res);
            strcat (res , ")");
        }
            break;

        case LG:
        {
            strcat (res , "lg(");
            _left->PrintNode(res);
            strcat (res , ")");
        }
            break;

        case ADD:
        {
            strcat (res , "(");
            _left->PrintNode (res);
            strcat (res , "+");
            _right->PrintNode (res);
            strcat (res , ")");
        }
            break;

        case SUB:
        {
            if (_left->_value != -1 &&
                    _right->_value != -1 &&
                    _left->_value  != 1 &&
                    _right->_value != 1)
            {
                strcat(res, "(");
                _left->PrintNode(res);
                strcat(res, "-");
                _right->PrintNode(res);
                strcat(res, ")");
            }
            else if (_left->_value == -1 &&
                     _right->_value != -1 &&
                     _left->_value  != 1 &&
                     _right->_value != 1)
            {
                strcat(res , "(-");
                _right->PrintNode(res);
                strcat(res , ")");
            }
            else if (_left->_value != -1 &&
                    _right->_value == -1 &&
                    _left->_value  != 1 &&
                    _right->_value != 1)
            {
                strcat(res , "(-");
                _left->PrintNode(res);
                strcat(res , ")");
            }
            else if (_left->_value != -1 &&
                  _right->_value != -1 &&
                  _left->_value  == 1 &&
                  _right->_value != 1)
                _right->PrintNode(res);
            else if(_left->_value != -1 &&
                    _right->_value != -1 &&
                    _left->_value  != 1 &&
                    _right->_value == 1)
                _left->PrintNode(res);
        }
            break;

        case MUL:
        {
            if (_left->_value != -1 &&
                _right->_value != -1 &&
                _left->_value  != 1 &&
                _right->_value != 1)
            {
                strcat(res, "(");
                _left->PrintNode(res);
                strcat(res, "*");
                _right->PrintNode(res);
                strcat(res, ")");
            }
            else if (_left->_value == -1 &&
                     _right->_value != -1 &&
                     _left->_value  != 1 &&
                     _right->_value != 1)
            {
                strcat(res , "(-");
                _right->PrintNode(res);
                strcat(res , ")");
            }
            else if (_left->_value != -1 &&
                     _right->_value == -1 &&
                     _left->_value  != 1 &&
                     _right->_value != 1)
            {
                strcat(res , "(-");
                _left->PrintNode(res);
                strcat(res , ")");
            }
            else if (_left->_value != -1 &&
                     _right->_value != -1 &&
                     _left->_value  == 1 &&
                     _right->_value != 1)
                _right->PrintNode(res);
            else if(_left->_value != -1 &&
                    _right->_value != -1 &&
                    _left->_value  != 1 &&
                    _right->_value == 1)
                _left->PrintNode(res);
        }
            break;

        case DIV:
        {
            if (_left->_value != -1 &&
                _right->_value != -1 &&
                _left->_value  != 1 &&
                _right->_value != 1)
            {
                strcat(res, "(");
                _left->PrintNode(res);
                strcat(res, "/");
                _right->PrintNode(res);
                strcat(res, ")");
            }
            else if (_left->_value == -1 &&
                     _right->_value != -1 &&
                     _left->_value  != 1 &&
                     _right->_value != 1)
            {
                strcat(res , "(-1/");
                _right->PrintNode(res);
                strcat(res , ")");
            }
            else if (_left->_value != -1 &&
                     _right->_value == -1 &&
                     _left->_value  != 1 &&
                     _right->_value != 1)
            {
                strcat(res , "(-");
                _left->PrintNode(res);
                strcat(res , ")");
            }
            else if (_left->_value != -1 &&
                     _right->_value != -1 &&
                     _left->_value  == 1 &&
                     _right->_value != 1)
            {
                strcat (res , "1/(");
                _right->PrintNode(res);
                strcat (res , ")");
            }
            else if(_left->_value != -1 &&
                    _right->_value != -1 &&
                    _left->_value  != 1 &&
                    _right->_value == 1)
                _left->PrintNode(res);
        }
            break;

        case LOG:
        {
            strcat (res , "log(");
            _left->PrintNode (res);
            strcat (res , ",");
            _right->PrintNode (res);
            strcat (res , ")");
        }
            break;

        case POW:
        {
            strcat (res , "((");
            _left->PrintNode (res);
            strcat (res , ")^(");
            _right->PrintNode (res);
            strcat (res , "))");
        }
            break;
    }

    return TRUE;
}

bool Node::PrintVar (char* res)
    {
    switch (_value)
    {
        CASE(res , a);
        CASE(res , b);
        CASE(res , c);
        CASE(res , d);
        CASE(res , e);
        CASE(res , f);
        CASE(res , g);
        CASE(res , h);
        CASE(res , j);
        CASE(res , i);
        CASE(res , k);
        CASE(res , l);
        CASE(res , m);
        CASE(res , n);
        CASE(res , o);
        CASE(res , p);
        CASE(res , q);
        CASE(res , r);
        CASE(res , s);
        CASE(res , t);
        CASE(res , u);
        CASE(res , v);
        CASE(res , w);
        CASE(res , x);
        CASE(res , y);
        CASE(res , z);
    }

    return TRUE;
}