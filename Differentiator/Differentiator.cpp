#include <afxres.h>

#include "Differentiator.h"
#include "../RecursiveDescentParser/RDP.h"


char* Differentiator()//Don't realized==================================================================================
{
    //Initialization
    bool resAns = 0;
    Tree* function = new Tree( MUL , FUNCTION);

    //Scan function
    RDP* parser = new RDP();
    function = parser->StrToTree();




    /*function->_head->_left  = new Node (x , VARIABLE);
    function->_head->_right = new Node (MUL , FUNCTION);


    Node* left  = new Node (x , VARIABLE);
    left->_parent = function->_head->_right;
    function->_head->_right->_left = left;

    Node* right = new Node (x , VARIABLE);
    right->_parent = function->_head->_right;
    function->_head->_right->_right = right;
*/
    char ress[1000] = {0};
    function->TreeToStr(ress);
    printf ("\n%s\n\n" , ress);
    Tree* resDiff = function->Differentiator();//Don't realized=========================================================

    char res[1000] = {0};
    resDiff->TreeToStr(res);//Don't realized===================================================================

    printf ("%s" , res);

    delete resDiff;

    return res;//Don't realized
}


/*
 *Checking string for right spelling of formula
 */
bool CheckCorrect (char* funcStr)//Don't realized=======================================================================
{
    return TRUE;
}


//-----------------------------------------------
//Describes how to use differentiator
bool GetInfo()//Don't realized==========================================================================================
{
    return TRUE;
}



