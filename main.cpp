#include <stdio.h>

#include "Differentiator/Differentiator.h"

int main()
{
    printf ("Programme started\n");

    char* res = Differentiator();//Don't realized=======================================================================

    if (res)
        printf ("\n\n\nRESULT: %s\nDifferentiator finished correct\n\n\n" , res);
    else
        printf ("\n\n\nDifferentiator finished incorrect\n\n\n");

    return 0;
}
