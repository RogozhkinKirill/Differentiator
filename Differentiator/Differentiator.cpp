#include <afxres.h>

#include "Differentiator.h"



char* Differentiator()//Don't realized==================================================================================
{
    //Initialization
    bool resAns = 0;
    Tree* function = new Tree( NULL , NULL);

    //Scan function
    while (resAns == FALSE)
    {
        printf ("Print function or info for more information(free string to escape)\n");

        char* funcStr = 0;
        scanf ("%s\n" , &funcStr);

        if (funcStr == "info")
            GetInfo(); //Don't realized=================================================================================
        else if (funcStr != NULL)
        {
            bool res = CheckCorrect (funcStr); //Don't realized=========================================================
            if (res == TRUE)
            {
                function->StrToTree (funcStr); //Don't realized=========================================================
                resAns = TRUE;
            }
        }
        else if (funcStr == "NULL")
            return 0;
    }



    Tree* resDiff = function->Differentiator();//Don't realized=========================================================

    char* res = resDiff->TreeToStr();//Don't realized===================================================================

    printf ("%s" , res);

    return resDiff->TreeToStr();//Don't realized
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



