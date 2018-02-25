#include <afxres.h>
#include "Differentiator.h"


char* Differentiator()//Don't realized
{
/*=============================================== Don't realized
    //Initialization
    bool resAns = FALSE;
    DiffTree* function = new DiffTree();

    //Scan function
    while (resAns == FALSE)
    {
        printf ("Print function or info for more information(NULL to excape)\n");

        char* funcStr = 0;
        scanf (%s , &funcStr);

        if (funcStr == "info") // ???
            GetInfo();
        else if (funcStr != NULL)
        {
            bool res = CheckCorrect (funcStr); //Don't realized
            if (res == TRUE)
            {
                function->StrToDiffTree (funcStr); //Don't realized
                resAns = TRUE;
            }
        }
        else if (funcStr == "NULL")
            return TRUE;
    }
*/


    DiffTree* resDiff = function->Differentatiotor();//Don't realized


    return resDiff->DiffTreeToStr();//Don't realized
}


/*
 *Checking string for right spelling of formula
 */
bool CheckCorrect (char* funcStr)//Don't realized
{
    return TRUE;
}


/*
 *DiffTree functions
 */

bool  DiffTree::StrToDiffTree (char* funcStr)//Don't realized
{
}

char* DiffTree::DiffTreeToStr()//Don't realized
{
}


//If function has one variable, it writes to right branch and to left branch write NULL
DiffTree* DiffTree::Differentiator()//Don't realizing
{
    if (this)
    {

    }
    else
    {
        printf ("ERROR. Pointer on DiffTree = NULL;");
        return 0;
    }
}


/*
 *DiffTreeNode functions
 */
DiffTreeNode::DiffTreeNode(value_type value , definision define)
{
    this->_value  = value;
    this->_define = define;
}

DiffTreeNode::~DiffTreeNode()
{
    if (_right)
        delete _right;
    if (_left);
}
