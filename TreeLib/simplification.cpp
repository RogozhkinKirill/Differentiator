//
// Created by пользователь on 17.03.2018.
//

#include "simplification.h"


void* Tree::Simplification()
{
    void* res = 0;

    do
    {
        res = 0;
        double tmp = 0;
        res = (void*)((int)res + (int)CountNodes(_head , &tmp));
        res = (void*)((int)res + (int)SumSimplification(_head));
        res = (void*)((int)res + (int)MulSimplification(_head));

        printf ("\n\nresult = %d\n\n" , res);
        }while(res);
}


void* Tree::CountNodes(Node* node , double* number)
{
    void* res = 0;

    if (node && node->_define == FUNCTION)
    {
        if (node->_left->_define == CONSTANT && node->_right->_define == CONSTANT)
        {
            switch (node->_value)
            {
                case ADD:
                {
                    node->_define = CONSTANT;
                    node->_value = node->_left->_value + node->_right->_value;
                    *number = node->_value;

                    delete node->_right;
                    delete node->_left;
                    node->_right = node->_left = NULL;

                    return (void*)1;
                }
                    break;

                case SUB:
                {
                    node->_define = CONSTANT;
                    node->_value = node->_left->_value - node->_right->_value;
                    *number = node->_value;

                    delete node->_right;
                    delete node->_left;
                    node->_right = node->_left = NULL;

                    return (void*)1;
                }

                default:
                    break;
            }
        }
        else
        {
            if (node->_left->_define == FUNCTION)
            {
                double tmp = 0;
                res = CountNodes(node->_left , &tmp);
                if (res)
                {
                    node->_left->_define = CONSTANT;
                    node->_left->_value = (int)tmp;

                    delete node->_left->_left;
                    node->_left->_left = NULL;

                    if (node->_left->_right)
                    {
                        delete node->_left->_right;
                        node->_left->_right = NULL;
                    }

                    return (void*)1;
                }
            }

            if (node->_right->_define == FUNCTION)
            {
                double tmp = 0;
                res = CountNodes(node->_right , &tmp);

                if (res)
                {
                    node->_right->_define = CONSTANT;
                    node->_right->_value = (int)tmp;

                    delete node->_right->_left;
                    node->_right->_left = NULL;

                    if (node->_right->_right)
                    {
                        delete node->_right->_right;
                        node->_right->_right = NULL;
                    }

                    return (void*)1;
                }
            }
        }
    }

    return res;
}

void* Tree::SumSimplification (Node* node)
{
    void* res = 0;
    if (node && node->_define == FUNCTION && node->_value == ADD)
    {
        if (node->_left->_define == CONSTANT && node->_left->_value == 0)
        {
            if (node->_parent)
            {
                if (node->_parent->_left == node)
                {
                    node->_parent->_left = node->_right;
                    node->_right->_parent = node->_parent;
                    node->_right = NULL;

                    delete node;
                    return (void*)1;
                }
                else
                {
                    node->_parent->_right = node->_right;
                    node->_right->_parent = node->_parent;
                    node->_right = NULL;

                    delete node;
                    return (void*)1;
                }
            }
            else
            {
                node->_right->_parent = NULL;

                Node* tmp = _head;
                _head = node->_right;

                tmp->_right = NULL;
                delete tmp;
                return (void*)1;
            }
        }
        else if (node->_right->_define == CONSTANT && node->_right->_value == 0)
        {
            if (node->_parent)
            {
                if (node->_parent->_left == node)
                {
                    node->_parent->_left = node->_left;
                    node->_right->_parent = node->_parent;
                    node->_left = NULL;

                    delete node;
                    return (void*)1;
                }
                else
                {
                    node->_parent->_right = node->_left;
                    node->_left->_parent = node->_parent;
                    node->_left = NULL;

                    delete node;
                    return (void*)1;
                }
            }
            else
            {
                node->_left->_parent = NULL;

                Node* tmp = _head;
                _head = node->_left;

                tmp->_left = NULL;
                delete tmp;
                return (void*)1;
            }
        }
        else
        {
            if (node->_left && node->_left->_define == FUNCTION)
                res = (void*)((int)res + (int)SumSimplification(node->_left));
            if  (node->_right && node->_right->_define == FUNCTION)
                res = (void*)((int)res + (int)SumSimplification(node->_right));
        }
    }
    else
    {
        if (node && node->_left && node->_left->_define == FUNCTION)
            res = (void*)((int)res + (int)SumSimplification(node->_left));
        if (node && node->_right && node->_right->_define == FUNCTION)
            res = (void*)((int)res + (int)SumSimplification(node->_right));
    }

    return res;
}

void* Tree::MulSimplification (Node* node)
{
    void* res = 0;

    if (node                && node->_define == FUNCTION
                            &&
       node->_value == MUL)
    {
        if ((node->_right->_define == CONSTANT && node->_right->_value == 0)
                                               ||
             (node->_left->_define == CONSTANT && node->_left->_value == 0))
        {
            delete node->_right;
            node->_right = NULL;

            delete node->_left;
            node->_left = NULL;

            node->_define = CONSTANT;
            node->_value  = 0;

            return (void*)1;
        }

        if (node->_left->_define == CONSTANT && node->_left->_value == 1)
        {
            if (node->_parent)
            {
                if (node->_parent->_left == node)
                {
                    node->_parent->_left = node->_right;
                    node->_right->_parent = node->_parent;
                    node->_right = NULL;

                    delete node;
                    return (void*)1;
                }
                else
                {
                    node->_parent->_right = node->_right;
                    node->_right->_parent = node->_parent;
                    node->_right = NULL;

                    delete node;
                    return (void*)1;
                }
            }
            else
            {
                node->_right->_parent = NULL;

                Node* tmp = _head;
                _head = node->_right;

                tmp->_right = NULL;
                delete tmp;
                return (void*)1;
            }
        }
        else if (node->_right->_define == CONSTANT && node->_right->_value == 1)
        {
            if (node->_parent)
            {
                if (node->_parent->_left == node)
                {
                    node->_parent->_left = node->_left;
                    node->_right->_parent = node->_parent;
                    node->_left = NULL;

                    delete node;
                    return (void*)1;
                }
                else
                {
                    node->_parent->_right = node->_left;
                    node->_left->_parent = node->_parent;
                    node->_left = NULL;

                    delete node;
                    return (void*)1;
                }
            }
            else
            {
                node->_left->_parent = NULL;

                Node* tmp = _head;
                _head = node->_left;

                tmp->_left = NULL;
                delete tmp;
                return (void*)1;
            }
        }
        else
        {
            if (node->_left && node->_left->_define == FUNCTION)
                res = (void*)((int)res + (int)MulSimplification(node->_left));
            if  (node->_right && node->_right->_define == FUNCTION)
                res = (void*)((int)res + (int)MulSimplification(node->_right));
        }
    }
    else
    {
        if (node && node->_left && node->_left->_define == FUNCTION)
            res = (void*)((int)res + (int)MulSimplification(node->_left));
        if (node && node->_right && node->_right->_define == FUNCTION)
            res = (void*)((int)res + (int)MulSimplification(node->_right));
    }

    return res;
}