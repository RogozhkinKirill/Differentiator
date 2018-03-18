//
// Created by пользователь on 14.03.2018.
//


#ifndef DIFF_PRINT_TREE_H
#define DIFF_PRINT_TREE_H

#include <afxres.h>
#include <stdlib.h>
#include <string>

#include "TreeLib.h"
#include "debug.h"


#ifndef CASE
    #define CASE(x , y) case y: {strcat (x , #y);} break;

    #define CASE_TEX(file , y) case y: {fprintf (file , #y);} break;
#endif// CASE


using namespace std;


//Write Tree to TeX
void PrintToTex (Node* head , const char* address);
void SetConfig  (FILE* TeX);

void BeginDocument (FILE* TeX);
void EndDocument   (FILE* TeX);
void BeginFormula  (FILE* TeX);
void EndFormula    (FILE* TeX);

void WriteNode (FILE* TeX , Node* head);
void WriteFunc (FILE* TeX , Node* head);
void WriteVar  (FILE* TeX , Node* head);
void WriteMUL  (FILE* TeX , Node* head);
void WriteSUB  (FILE* TeX , Node* head);
void WriteDIV  (FILE* TeX , Node* head);
void WriteADD  (FILE* TeX , Node* head);
void WritePOW  (FILE* TeX , Node* head);
void WriteLOG  (FILE* TeX , Node* head);

void CompileTeX (const char* address);


#endif //DIFF_PRINT_TREE_H
