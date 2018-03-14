#include <afxres.h>

#include "Differentiator.h"
#include "../RecursiveDescentParser/RDP.h"
#include "../TreeLib/print_tree.h"

char* Differentiator()//Don't realized==================================================================================
{
    //Initialization
    bool resAns = 0;
    Tree* function = new Tree( MUL , FUNCTION);

    //Scan function
    RDP* parser = new RDP();
    function = parser->StrToTree();

    char ress[1000] = {0};
    function->TreeToStr(ress);
    printf ("\n%s\n\n" , ress);
    PrintToTex (function->_head , "D:\\Study\\Programming\\Projects\\C_C++\\ILab\\Differentiator\\Tex\\Begin.tex");

    Tree* resDiff = function->Differentiator();//Don't realized=========================================================

    char res[1000] = {0};
    resDiff->TreeToStr(res);//Don't realized===================================================================

    printf ("%s" , res);
    PrintToTex (function->_head , "D:\\Study\\Programming\\Projects\\C_C++\\ILab\\Differentiator\\Tex\\Finished.tex");

    delete resDiff;

    return res;//Don't realized
}

//-----------------------------------------------
//Describes how to use differentiator
bool GetInfo()//Don't realized==========================================================================================
{
    return TRUE;
}



