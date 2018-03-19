//
// Created by пользователь on 06.03.2018.
//
/**============================================================================
 *
 *
 *
 *                       To do Recursive Descent Parser
 *                    let's create functions with priority
 *                     (Then higher then bigger priority)
 *                        Higher function call lower
 *                                   or
 *                               print lower
 *
 *
 *Designation                  Function's Name   Short description
 *
 *G0                             GetBase()      //Look after \0
 *T                               GetSUM()      //Look after addition and subtraction
 *I                               GetPOW()      //Look after power
 *E                               GetMULL()     //Look after multiplication and divide
 *P                             GetBrackets()   //Look after brackets
 *N                              GetNumber()    //Look after number
 *I                             GetImagine()    //Look after variables 'n LOG-functions 'n TRIG-functions
 *
 *
 *
 *                          Function's descriptions
 *
 *                             * :   number of iterations
 *                             + :   read number
 *
 *                             G0:   T '\0'
 *                        |--->T :   I(('+' | '-') , I)*
 *                        |    I :   E(('^') , E)*
 *                        |    E :   P(('*' | '/') , P)*
 *                        |----P :   (T) | N | Im
 *               N :   [0-9]+  || Im :   ([a-z] & [TRIG-functions] & [LOG-functions])
 *
 *
 *
 *=============================================================================
 */


#ifndef DIFF_RDP_H
#define DIFF_RDP_H

#include <string>
#include <iostream>
#include <stdio.h>

#include "../TreeLib/debug.h"
#include "../TreeLib/TreeLib.h"

using namespace std;

class RDP
{
    string _function;
    size_t _ptr;
    size_t _length;

    Tree* _tree;

public:
    //Constructor and Destructor
    RDP():
    _tree()
    {
        cout << "Print function" << endl;
        cin  >> _function;


        _tree = new Tree();
        _length = _function.size();
        cout << "Length = " << _length << endl;
        _ptr    = 0;
    }

    ~RDP()
    {
        cout << "Destructor RDP called" << endl;

        delete _tree;
    }

    Tree* StrToTree();

private:

    Node* GetBase();
    Node* GetSUM();
    Node* GetPOW();
    Node* GetMUL();
    Node* GetBrackets();
    Node* GetNumber();
    Node* GetImagine();
};


Node* AddLocalHead(Node* added , Node** receiving);

#endif //DIFF_RDP_H
