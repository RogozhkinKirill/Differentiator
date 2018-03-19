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
    debug_print("Called G0\n");
    Node* res = GetSUM();

    if (_function[_ptr] == '\0')
    {
        debug_print("Last _ptr = %d\n" , _ptr);
    }

    if (res)
        _tree->_head = res;
    else
        debug_print("ERROR\n");

    return _tree->_head;
}

Node* RDP::GetSUM()
{
    debug_print("Called T\n");

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

        debug_print("node_res ptr = 0x%p\n" , node_res);
        if (node_res)
        {
            local_head->_right = node_res;
            node_res->_parent = local_head;
        }
        else
        {
            debug_print("NULL pointer\n");
            return NULL;
        }
    }

    debug_print("Return to G0\n");
    return local_head;
}

Node* RDP::GetPOW()
{
    debug_print("Called I\n");

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
        {
            local_head->_right = node_res;
            node_res->_parent = local_head;
        }
        else
            return NULL;
    }


    debug_print("Return to T\n");

    return local_head;
}

Node* RDP::GetMUL()
{
    debug_print("Called E\n");

    Node* local_head = 0;
    Node* node = 0;
    Node* node_res = GetBrackets();

    AddLocalHead (node_res , &local_head);

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
        {
            local_head->_right = node_res;
            node_res->_parent = local_head;
        }
        else
            return NULL;
    }
    debug_print("Return to T\n");

    return local_head;
}


Node* RDP::GetBrackets()
{
    debug_print("Called P\n");

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

        debug_print("Out %c\n" , _function[_ptr]);
    }
    else
    {
        if (_function[_ptr] >= '0' && _function[_ptr] <= '9')
            node_res = GetNumber();
        else if (_function[_ptr] >= 'a' && _function[_ptr] <= 'z')
            node_res = GetImagine();
    }

    debug_print("Return to E from P\n");

    return node_res;
}

Node* RDP::GetNumber()
{
    debug_print("Called N\n");

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

Node* RDP::GetImagine()
{
    debug_print("Called Im\n");

    Node* node_variable = 0;//FLAG means ERROR

    while (_function[_ptr] >= 'a' && _function[_ptr] <= 'z'
                                  &&
                          _length > _ptr)
    {
        debug_print("Start _ptr = %d\n" , _ptr);
        //COS, CTH, CTG
        if ( _function[_ptr] == 'c')
        {
            if (_function[_ptr+1] == 'o')
            {
                ++_ptr;
                if (_function[++_ptr] == 's' &&  _length > _ptr)
                {
                    node_variable = new Node(COS, FUNCTION);
                    ++_ptr;
                    node_variable->_left = GetBrackets();

                    if (node_variable->_left)
                    {
                        node_variable->_left->_parent = node_variable;
                    }
                }
            }

            if (_function[_ptr+1] == 't')
            {
                _ptr += 2;
                if (_function[_ptr] == 'h' &&  _length > _ptr)
                {
                    node_variable = new Node(CTH, FUNCTION);
                    node_variable->_left = GetBrackets();
                }
                else if (_function[_ptr] == 'g' &&  _length > _ptr)
                {
                    node_variable = new Node(CTG, FUNCTION);
                    node_variable->_left = GetBrackets();
                }

                if (node_variable->_left)
                    node_variable->_left->_parent = node_variable;
            }
        }

        //SIN, SH
        if (_function[_ptr] == 's')
        {
            if (_length > _ptr && _function[_ptr+1] == 'i' && _function[_ptr+2] == 'n')
            {
                _ptr += 3;
                node_variable = new Node(SIN, FUNCTION);
                node_variable->_left = GetBrackets();
            }
            else if (_length > _ptr && _function[_ptr+1] == 'h')
            {
                _ptr += 2;
                node_variable = new Node(SH, FUNCTION);
                node_variable->_left = GetBrackets();
            }


            if (node_variable->_left)
                node_variable->_left->_parent = node_variable;
        }

        //TG, TH
        if (_function[_ptr] == 't')
        {

            if (_function[_ptr+1] == 'h' &&  _length > _ptr)
            {
                _ptr += 2;
                node_variable = new Node(TH, FUNCTION);
                node_variable->_left = GetBrackets();
            }
            else if (_function[_ptr+1] == 'g' &&  _length > _ptr)
            {
                _ptr += 2;
                node_variable = new Node(TG, FUNCTION);
                node_variable->_left = GetBrackets();
            }

            if (node_variable->_left)
                node_variable->_left->_parent = node_variable;
        }

        //EXP
        if (_function[_ptr] == 'e' && _function[_ptr+1] == 'x' && _function[_ptr+2] == 'p'
                                   && _length > _ptr)
        {
            _ptr += 3;
            node_variable = new Node(EXP, FUNCTION);
            node_variable->_left = GetBrackets();

            if (node_variable)
                node_variable->_left->_parent = node_variable;
        }

        if (_function[_ptr] == 'l')
        {
            if (_function[_ptr+1] == 'n')
            {
                _ptr += 2;
                node_variable = new Node(LN, FUNCTION);
                node_variable->_left = GetBrackets();
            }

            if (_function[_ptr+1] == 'g')
            {
                _ptr += 2;
                node_variable = new Node(LG, FUNCTION);
                node_variable->_left = GetBrackets();
            }
        }


        if ( _function[_ptr] >= 'a' && _function[_ptr] <= 'z')
        {
            printf ("xxx\n");
            node_variable = new Node (_function[_ptr] - 'a' + a , VARIABLE);
            ++_ptr;
        }
    }

    debug_print("Return to P from Im\n");
    return node_variable;
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

    return *receiving;
}