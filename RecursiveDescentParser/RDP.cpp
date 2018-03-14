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
    {
        if (_function[_ptr] >= '0' && _function[_ptr] <= '9')
            node_res = GetNumber();
        else if (_function[_ptr] >= 'a' && _function[_ptr] <= 'z')
            node_res = GetImagine();
    }

    cout << "Return to E from P" << endl;

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

Node* RDP::GetImagine()
{
    cout << "Called Im" << endl;

    Node* node_variable = 0;//FLAG means ERROR

    while (_function[_ptr] >= 'a' && _function[_ptr] <= 'z'
                                  &&
                          _length > _ptr)
    {
        printf ("Start _ptr = %d\n" , _ptr);
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
                        node_variable->_left->_parent = node_variable;
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
            printf ("Right Way");
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

        //EXp
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

    cout << "Return to P from Im" << endl;
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


   // printf ("receiving ptr = 0x%p\n" , *receiving);
    return *receiving;
}