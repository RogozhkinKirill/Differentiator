//
// Created by пользователь on 06.03.2018.
//

#include "RDP.h"

Tree* RDP::StrToTree()
{
    GetBase();

    printf ("%d %d %d\n" , _tree->_head->_value , _tree->_head->_right->_value , _tree->_head->_left->_value);

    return _tree;
}

Node* RDP::GetBase()
{
    cout << "Called G0" << endl;
    Node* res = GetSUM();

    if (_function[_ptr] == '\0')
    {
        cout << "Last _ptr = " << _ptr << endl;
    }

    if (res)
        _tree->_head = res;
    else
        cout << "ERROR" << endl;


    printf ("Define %d\n" , _tree->_head->_define);
    return _tree->_head;
}

Node* RDP::GetSUM()
{
    cout << "Called T" << endl;

    Node* local_head = 0;
    Node* node = 0;
    Node* node_res = GetPOW();
    AddLocalHead (node_res , &local_head);

    while (_function[_ptr] == '+' || _function[_ptr] == '-')
    {
        node = new Node();

        node->_define = FUNCTION;

        if (_function[_ptr] == '+')
        {
            node->_value = ADD;
            AddLocalHead (node , &local_head);
        }

        if (_function[_ptr] == '-')
        {
            node->_value = SUB;
            AddLocalHead (node , &local_head);
        }

        ++_ptr;
        node_res = GetPOW();

        printf ("node_res ptr = 0x%p\n" , node_res);
        if (node_res)
            local_head->_right = node_res;
        else
        {
            cout << "NULL pointer" << endl;
            return NULL;
        }
    }

    cout << "Return to G0" << endl;
    return local_head;
}

Node* RDP::GetPOW()
{
    cout << "Called I" << endl;

    Node* local_head = 0;
    Node* node = 0;
    Node* node_res = GetMUL();
    AddLocalHead (node_res , &local_head);

    while (_function[_ptr] == '^')
    {
        node = new Node();

        node->_define = FUNCTION;
        node->_value  = POW;

        AddLocalHead (node , &local_head);

        ++_ptr;

        node_res = GetMUL();

        if (node_res)
            local_head->_right = node_res;
        else
            return NULL;
    }


    cout << "Return to T" << endl;

    return local_head;
}



Node* RDP::GetMUL()
{
    cout << "Called E" << endl;

    Node* local_head = 0;
    Node* node = 0;
    Node* node_res = GetBrackets();
   // printf ("\nnode_res ptr = 0x%p\nlocal_head ptr = 0x%p\n" , node_res , local_head);

    AddLocalHead (node_res , &local_head);

 //   printf ("node_res ptr = 0x%p\nlocal_head ptr = 0x%p\n\n" , node_res , local_head);
    while (_function[_ptr] == '*' || _function[_ptr] == '/')
    {
        node = new Node();

        node->_define = FUNCTION;
        node->_value  = POW;

        if (_function[_ptr] == '*')
        {
            node->_value = MUL;
            AddLocalHead (node , &local_head);
        }

        if (_function[_ptr] == '/')
        {
            node->_value = DIV;
            AddLocalHead (node , &local_head);
        }

        ++_ptr;

        node_res = GetBrackets();

        if (node_res)
            local_head->_right = node_res;
        else
            return NULL;
    }
    cout << "Return to T" << endl;

    return local_head;
}


Node* RDP::GetBrackets()
{
    cout << "Called P" << endl;

    Node* node_res = 0;

    if (_function[_ptr] == '(')
    {
        cout << "_ptr in brackets = " << _ptr << endl;
        while (_function[_ptr] != ')' )//|| _function[_ptr] != '\0') || _ptr < _length)// I don't know it doesn't work with it
        {
            printf ("In %c ptr = %d\n" , _function[_ptr] , _ptr);
            ++_ptr;
            node_res = GetSUM();
        }
        _ptr++;

        printf ("Out %c\n" , _function[_ptr]);
    }
    else
        node_res = GetNumber();

    cout << "Return to E from P" << endl;
  //  printf ("node_res ptr = 0x%p\n\n" , node_res);

    return node_res;
}

Node* RDP::GetNumber()
{
    cout << "Called N" << endl;

    Node* node_number = 0;//FLAG means ERROR

    while ((_function[_ptr] >= '0' && _function[_ptr] <= '9'
                                  ||
           _function[_ptr] >= 'a' && _function[_ptr] <= 'z')
                                  &&
                          _length > _ptr)
    {
        node_number = new Node();

        while (_function[_ptr] >= '0' && _function[_ptr] <= '9'
                                   &&
                     node_number->_define != VARIABLE)
        {
            node_number->_define = CONSTANT;
            node_number->_value *= 10;
            node_number->_value += _function[_ptr] - '0';
            ++_ptr;

 //           GetNumber();
        }

        if ( _function[_ptr] >= 'a' && _function[_ptr] <= 'z')
        {
            node_number->_define = VARIABLE;
            node_number->_value = _function[_ptr] - 'a' + a;

            ++_ptr;
        }
    }
/*
    if (node_number)
        AddNode(node_number);
*/
    cout << "Return to P" << endl;
 //   printf ("node_number ptr = 0x%p\n\n" , node_number);
    return node_number;
}

//Function replace variable and constant
Node* RDP::AddNode (Node* node  )
{
    printf ("Tree 0x%p ,Head 0x%p\nNode 0x%p Define = %d\n_ptr = %d\n\n" ,
            _tree , _tree->_head , node , node->_define , _ptr);
/*
    if (node)
    {
        if (node->_value < COS || node->_value > LG)
        {
            if (_tree->_head)
            {
                if (_tree->_head->_define == FUNCTION)
                {
                    if (_tree->_head->_right)
                    {
                        node->_left = _tree->_head;
                        _tree->_head->_parent = node;
                        _tree->_head = node;
                        return node;
                    }
                    else if (_tree->_head->_left)
                    {
                        _tree->_head->_right = node;
                        node->_parent = _tree->_head;
                        return node;
                    }
                    else
                    {
                        _tree->_head->_left = node;
                        node->_parent = _tree->_head;
                        return node;
                    }
                }
                else
                {
                    node->_left = _tree->_head;
                    _tree->_head->_parent = node;
                    _tree->_head = node;
                    return node;
                }
            }
            else
            {
                _tree->_head = node;
                return node;
            }
        }
        else
        {
            if (_tree->_head)
            {
                if (_tree->_head->_left)
                {
                    node->_left = _tree->_head;
                    _tree->_head->_parent = node;
                    return node;
                }
                else
                {
                    _tree->_head->_left = node;
                    node->_parent = _tree->_head;
                    return node;
                }
            }
            else
            {
                _tree->_head = node;
                return node;
            }
        }
    }

    */

    return NULL;
}

Node* AddLocalHead(Node* added , Node** receiving)
{
    if (*receiving)
    {
        (*receiving)->_parent = added;
        added->_left = *receiving;
        *receiving = added;
    }
    else
        *receiving = added;


   // printf ("receiving ptr = 0x%p\n" , *receiving);
    return *receiving;
}