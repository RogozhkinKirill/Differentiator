//
// Created by пользователь on 18.03.2018.
//

#ifndef DIFF_DEBUG_H
#define DIFF_DEBUG_H

#ifdef DEBUG
    #include <stdio.h>
    #include <string>
    #include <stdlib.h>
    #define debug_print_function(x);  BeginFormula (debug_file);\
                                          WriteNode    (debug_file , x);\
                                          EndFormula   (debug_file);

#else
    #define debug_print(...);
    #define debug_print_function(x);
#endif// DEBUG

#endif //DIFF_DEBUG_H
