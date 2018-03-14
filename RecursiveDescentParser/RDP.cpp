//
// Created by пользователь on 06.03.2018.
//

#include "RDP.h"

Tree* RDP::StrToTree()
{
    GetBase();
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
        }

        if ( _function[_ptr] >= 'a' && _function[_ptr] <= 'z')
        {
            node_number->_define = VARIABLE;
            node_number->_value = _function[_ptr] - 'a' + a;

            ++_ptr;
        }
    }

    cout << "Return to P" << endl;
    return node_number;
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