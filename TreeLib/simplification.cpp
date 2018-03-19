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
        int tmp = 0;
        res = (void*)((int)res + (int)CountNodes(_head , &tmp));
        res = (void*)((int)res + (int)SumSimplification(_head));
        res = (void*)((int)res + (int)MulSimplification(_head));
    }while(res);
}


void* Tree::CountNodes(Node* node , int* number)
{
    debug_print("Called CountNodes\n ");
    void* res = 0;

    if (node && node->_define == FUNCTION)
    {
        debug_print("Case FUNCTION\nnode->_value = 0x%p\n" , node->_value);
        if (node->_left->_define == CONSTANT && node->_right && node->_right->_define == CONSTANT)
        {
            switch (node->_value)
            {
                case ADD:
                {
                    debug_print("Case ADD\n");
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
                    debug_print("Case SUB\n");
                    node->_define = CONSTANT;
                    node->_value = node->_left->_value - node->_right->_value;
                    *number = node->_value;

                    delete node->_right;
                    delete node->_left;
                    node->_right = node->_left = NULL;

                    return (void*)1;
                }
                    break;

                case MUL:
                {
                    debug_print("Case MUL\n");
                    node->_define = CONSTANT;
                    node->_value = node->_left->_value * node->_right->_value;
                    *number = node->_value;

                    delete node->_right;
                    delete node->_left;
                    node->_right = node->_left = NULL;

                    return (void*)1;
                }
                    break;

                case DIV:
                {
                    debug_print("Case DIV\n");
                    node->_define = CONSTANT;
                    node->_value = node->_left->_value / node->_right->_value;
                    *number = node->_value;

                    delete node->_right;
                    delete node->_left;
                    node->_right = node->_left = NULL;

                    return (void*)1;
                }
                    break;

                case POW:
                {
                    debug_print("Case POW\n");
                    node->_define = CONSTANT;

                    int tmp = node->_left->_value;
                    node->_value = 1;

                    if (node->_right->_value > 0)
                        for (int i=0; i<node->_right->_value; ++i)
                            node->_value *= tmp;

                    delete node->_right;
                    node->_right = NULL;

                    delete node->_left;
                    node->_left = NULL;

                    *number = node->_value;

                    delete node->_right;
                    delete node->_left;
                    node->_right = node->_left = NULL;

                    return (void*)1;
                }
                    break;

                default:
                    break;
            }
        }
        else
        {
            debug_print("Case UN-FUNCTION\n");
            void* tmp_res = 0;
            if (node->_left->_define == FUNCTION)
            {
                int tmp = 0;
                tmp_res = CountNodes(node->_left , &tmp);

                if (tmp_res)
                    return (void*)1;
            }

            if (node->_right && node->_right->_define == FUNCTION)
            {
                int tmp = 0;
                tmp_res = CountNodes(node->_right , &tmp);


                if (tmp_res)
                    return (void*)1;
            }
        }
    }

    debug_print("Return from CountNodes\n");
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
                    node->_right->_parent = node->_parent;
                    node->_parent->_left = node->_right;
                    node->_right = NULL;

                    printf ("0x%p\nLine = %d\n" , node , __LINE__);
                    delete node;
                    return (void*)1;
                }
                else
                {
                    node->_right->_parent = node->_parent;
                    node->_parent->_right = node->_right;
                    node->_right = NULL;

                    printf ("0x%p\nLine = %d\n" , node , __LINE__);
                    delete node;
                    return (void*)1;
                }
            }
            else
            {

                node->_right->_parent = NULL;
                Node* tmp = node->_right;
                node->_right = NULL;
                delete _head;
                _head = tmp;

                return (void*)1;
            }
        }
        else if (node->_right->_define == CONSTANT && node->_right->_value == 0)
        {
            if (node->_parent)
            {
                if (node->_parent->_left == node)
                {
                    node->_right->_parent = node->_parent;
                    node->_parent->_left = node->_left;
                    node->_left = NULL;

                    printf ("0x%p\nLine = %d\n" , node , __LINE__);
                    delete node;
                    return (void*)1;
                }
                else
                {
                    node->_left->_parent = node->_parent;
                    node->_parent->_right = node->_left;
                    node->_left = NULL;

                    printf ("0x%p\nLine = %d\n" , node , __LINE__);
                    delete node;
                    return (void*)1;
                }
            }
            else
            {
                node->_left->_parent = NULL;
                Node* tmp = node->_left;
                node->_left = NULL;
                delete _head;
                _head = tmp;

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



