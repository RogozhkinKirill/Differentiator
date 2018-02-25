#include <afxres.h>
#include "Differentiator.h"


char* Differentiator()//Don't realized
{
    //Initialization
    bool resAns = FALSE;
    Tree* function = new Tree( NULL , NULL);

    //Scan function
    while (resAns == FALSE)
    {
        printf ("Print function or info for more information(free string to escape)\n");

        char* funcStr = 0;
        scanf ("%s\n" , funcStr);

        if (funcStr == "info")
            GetInfo(); //Don't realized
        else if (funcStr != NULL)
        {
            bool res = CheckCorrect (funcStr); //Don't realized
            if (res == TRUE)
            {
                function->StrToTree (funcStr); //Don't realized
                resAns = TRUE;
            }
        }
        else if (funcStr == "NULL")
            return 0;
    }



    Tree* resDiff = function->Differentiator();//Don't realized


    return resDiff->TreeToStr();//Don't realized
}


/*
 *Checking string for right spelling of formula
 */
bool CheckCorrect (char* funcStr)//Don't realized
{
    return TRUE;
}




