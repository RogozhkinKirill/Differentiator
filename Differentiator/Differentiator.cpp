#include <afxres.h>

#include "Differentiator.h"
#include "../RecursiveDescentParser/RDP.h"
#include "../TreeLib/print_tree.h"

char* Differentiator()
{
    //Initialization
    Tree* function = 0;

    //Scan function
    RDP* parser = new RDP();
    function = parser->StrToTree();

    char ress[1000] = {0};
    function->TreeToStr(ress);
    debug_print("\n%s\n\n" , ress);
    function->Simplification();
    PrintToTex (function->_head , "D:\\Study\\Programming\\Projects\\C_C++\\ILab\\Differentiator\\Tex\\Begin.tex");
    char resss[1000] = {0};
    function->TreeToStr(resss);
    debug_print("\n%s\n\n" , resss);

    function = function->Differentiator();

    //Simplification
    function->Simplification();

    char res[1000] = {0};
    function->TreeToStr(res);

    debug_print("%s" , res);
    PrintToTex (function->_head , "D:\\Study\\Programming\\Projects\\C_C++\\ILab\\Differentiator\\Tex\\Finished.tex");

    delete function;

    return res;
}

//-----------------------------------------------
//Describes how to use differentiator
bool GetInfo()//Don't realized==========================================================================================
{
    return TRUE;
}



