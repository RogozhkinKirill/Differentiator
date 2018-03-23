//
// Created by пользователь on 14.03.2018.
//

#include "print_tree.h"



//Write Tree to TeX
void PrintToTex (Node* head , const char* address)
{
    FILE* TeX = fopen (address , "w");

    SetConfig (TeX);

    BeginDocument (TeX);
    BeginFormula  (TeX);
    WriteNode     (TeX , head);
    EndFormula    (TeX);
    EndDocument   (TeX);

    fclose (TeX);

    CompileTeX (address);
}

void SetConfig (FILE* TeX)
{
    fprintf (TeX , "\\documentclass[12pt]{article}\n"
                  "\\usepackage[cp1251]{inputenc}\n"
                   "\\usepackage[russian]{babel}\n"
                   "\\usepackage{soul}\n");
}


void BeginDocument (FILE* TeX)
{
    fprintf (TeX , "\\begin{document}\n");
}

void EndDocument (FILE* TeX)
{
    fprintf (TeX , "\\end{document}\n");
}


void BeginFormula (FILE* TeX)
{
    fprintf (TeX , "\n\n\\[\n");
}
void EndFormula (FILE* TeX)
{
    fprintf (TeX , "\\]\n");
}


void WriteNode (FILE* TeX , Node* head)
{
    if (head)
    {
        switch (head->_define)
        {
            case FUNCTION:
            {
                WriteFunc (TeX , head);//function below this
            }
                break;

            case VARIABLE:
            {
                WriteVar (TeX , head);//function below PrintFunc
            }
                break;

            case CONSTANT:

            default:
            {
                char num[13] = {0};
                fprintf (TeX , itoa (head->_value , num , 10));
            }
        }
    }
}

void WriteFunc (FILE* TeX , Node* head)
{
    switch (head->_value)
    {
        case COS:
        {
            fprintf (TeX , "\\cos(");
            WriteNode (TeX , head->_left);
            fprintf (TeX , ")\n");
        }
            break;

        case SIN:
        {
            fprintf (TeX , "\\sin(");
            WriteNode (TeX , head->_left);
            fprintf (TeX , ")\n");
        }
            break;

        case TG:
        {
            fprintf (TeX , "\\tg(");
            WriteNode (TeX , head->_left);
            fprintf (TeX , ")\n");
        }
            break;

        case CTG:
        {
            fprintf (TeX , "\\ctg(");
            WriteNode (TeX , head->_left);
            fprintf (TeX , ")\n");
        }
            break;

        case SH:
        {
            fprintf (TeX , "\\sh(");
            WriteNode (TeX , head->_left);
            fprintf (TeX , ")\n");
        }
            break;

        case CH:
        {
            fprintf (TeX , "\\ch(");
            WriteNode (TeX , head->_left);
            fprintf (TeX , ")\n");
        }
            break;

        case TH:
        {
            fprintf (TeX , "\\th(");
            WriteNode (TeX , head->_left);
            fprintf (TeX , ")\n");
        }
            break;

        case CTH:
        {
            fprintf (TeX , "\\cth(");
            WriteNode (TeX , head->_left);
            fprintf (TeX , ")\n");
        }
            break;

        case EXP:
        {
            fprintf (TeX , "e^{(");
            WriteNode (TeX , head->_left);
            fprintf (TeX , ")}\n");
        }
            break;

        case LN:
        {
            fprintf (TeX , "\\ln(");
            WriteNode (TeX , head->_left);
            fprintf (TeX , ")\n");
        }
            break;

        case LG:
        {
            fprintf (TeX , "\\lg(");
            WriteNode (TeX , head->_left);
            fprintf (TeX , ")\n");
        }
            break;

        case ADD:
        {
            WriteADD (TeX , head);
        }
            break;

        case SUB:
        {
            WriteSUB (TeX , head);
        }
            break;

        case MUL:
        {
            WriteMUL (TeX , head);
        }
            break;

        case DIV:
        {
            WriteDIV (TeX , head);
        }
            break;

        case LOG:
        {
            WriteLOG (TeX , head);
        }
            break;

        case POW:
        {
            WritePOW (TeX , head);
        }
            break;
    }
}

void WriteVar  (FILE* TeX , Node* head)
{
    switch (head->_value)
    {
        CASE_TEX(TeX , a);
        CASE_TEX(TeX , b);
        CASE_TEX(TeX , c);
        CASE_TEX(TeX , d);
        CASE_TEX(TeX , e);
        CASE_TEX(TeX , f);
        CASE_TEX(TeX , g);
        CASE_TEX(TeX , h);
        CASE_TEX(TeX , j);
        CASE_TEX(TeX , i);
        CASE_TEX(TeX , k);
        CASE_TEX(TeX , l);
        CASE_TEX(TeX , m);
        CASE_TEX(TeX , n);
        CASE_TEX(TeX , o);
        CASE_TEX(TeX , p);
        CASE_TEX(TeX , q);
        CASE_TEX(TeX , r);
        CASE_TEX(TeX , s);
        CASE_TEX(TeX , t);
        CASE_TEX(TeX , u);
        CASE_TEX(TeX , v);
        CASE_TEX(TeX , w);
        CASE_TEX(TeX , x);
        CASE_TEX(TeX , y);
        CASE_TEX(TeX , z);
    }
}

void WriteMUL  (FILE* TeX , Node* head)
{
    if (head->_parent && head->_parent->_value > MUL) {
        fprintf(TeX, "(");
        WriteNode(TeX, head->_left);
        fprintf(TeX, "\\cdot ");
        WriteNode(TeX, head->_right);
        fprintf(TeX, ")\n");
    }
    else {
        WriteNode(TeX, head->_left);
        fprintf(TeX, "\\cdot ");
        WriteNode(TeX, head->_right);
    }
}

void WriteSUB  (FILE* TeX , Node* head)
{
    if (head->_parent && head->_parent->_value > SUB) {
        fprintf(TeX, "(");
        WriteNode(TeX, head->_left);
        fprintf(TeX, "-");
        WriteNode(TeX, head->_right);
        fprintf(TeX, ")\n");
    }
    else {
        WriteNode(TeX, head->_left);
        fprintf(TeX, "-");
        WriteNode(TeX, head->_right);
        fprintf(TeX, "\n");
    }
}

void WriteDIV  (FILE* TeX , Node* head)
{
    fprintf (TeX , " \\frac");
    fprintf (TeX , "{");
    WriteNode (TeX , head->_left);
    fprintf (TeX , "}");

    fprintf (TeX , "{");
    WriteNode (TeX , head->_right);
    fprintf (TeX , "} \n");
}

void WriteADD  (FILE* TeX , Node* head)
{
    if (head->_parent && head->_parent->_value > SUB) {
        fprintf(TeX, "(");
        WriteNode(TeX, head->_left);
        fprintf(TeX, "+");
        WriteNode(TeX, head->_right);
        fprintf(TeX, ")\n");
    }
    else {
        WriteNode(TeX, head->_left);
        fprintf(TeX, "+");
        WriteNode(TeX, head->_right);
        fprintf(TeX, "\n");
    }

}

void WritePOW  (FILE* TeX , Node* head)
{
    if (head->_parent && (head->_parent->_define == CONSTANT || head->_parent->_define == VARIABLE)) {
        fprintf(TeX, "(");
        WriteNode(TeX, head->_left);
        fprintf(TeX, ")");
        fprintf(TeX, "^");
        fprintf(TeX, "{");
        WriteNode(TeX, head->_right);
        fprintf(TeX, "}\n");
    }
    else {
        WriteNode(TeX, head->_left);
        fprintf(TeX, "^");
        fprintf(TeX, "{");
        WriteNode(TeX, head->_right);
        fprintf(TeX, "}\n");
    }
}

void WriteLOG  (FILE* TeX , Node* head)
{
    fprintf   (TeX , "\\log");
    fprintf   (TeX , "_{");
    WriteNode (TeX , head->_left);
    fprintf   (TeX , "}{");
    WriteNode (TeX , head->_right);
    fprintf   (TeX , "}\n");
}

void CompileTeX (const char* address)//Partly
{
    string callMikTeX = "pdflatex.exe -output-directory=D:\\Study\\Programming\\Projects\\C_C++\\ILab\\Differentiator\\Tex ";
    string openDVI    = "texify --run-viewer ";

    callMikTeX += address;
    openDVI    += address;

    system (callMikTeX.c_str());
    system (openDVI.c_str());
}


//Print Node and call PrintNode to branches
bool Node::PrintNode (char* res)
{
    if (this)
    {
        switch (_define)
        {
            case FUNCTION:
            {
                PrintFunc (res);//function below this
            }
                break;

            case VARIABLE:
            {
                PrintVar (res);//function below PrintFunc
            }
                break;

            case CONSTANT:

            default:
            {
                char num[13] = {0};
                strcat (res , itoa (_value , num , 10));
            }
        }
    }
    else
    {
        printf ("ERROR Pointer on Node in Node::PrintNode = Null\n");
        return 0;
    }

    return 0;
}

bool Node::PrintFunc (char* res)
{
    switch (_value)
    {
        case COS:
        {
            strcat (res , "cos(");
            _left->PrintNode(res);
            strcat (res , ")");
        }
            break;

        case SIN:
        {
            strcat (res , "sin(");
            _left->PrintNode(res);
            strcat (res , ")");
        }
            break;

        case TG:
        {
            strcat (res , "tg(");
            _left->PrintNode(res);
            strcat (res , ")");
        }
            break;

        case CTG:
        {
            strcat (res , "ctg(");
            _left->PrintNode(res);
            strcat (res , ")");
        }
            break;

        case SH:
        {
            strcat (res , "sh(");
            _left->PrintNode(res);
            strcat (res , ")");
        }
            break;

        case CH:
        {
            strcat (res , "ch(");
            _left->PrintNode(res);
            strcat (res , ")");
        }
            break;

        case TH:
        {
            strcat (res , "th(");
            _left->PrintNode(res);
            strcat (res , ")");
        }
            break;

        case CTH:
        {
            strcat (res , "sin(");
            _left->PrintNode(res);
            strcat (res , ")");
        }
            break;

        case EXP:
        {
            strcat (res , "exp(");
            _left->PrintNode(res);
            strcat (res , ")");
        }
            break;

        case LN:
        {
            strcat (res , "ln(");
            _left->PrintNode(res);
            strcat (res , ")");
        }
            break;

        case LG:
        {
            strcat (res , "lg(");
            _left->PrintNode(res);
            strcat (res , ")");
        }
            break;

        case ADD:
        {
            PrintADD (res);
        }
            break;

        case SUB:
        {
            PrintSUB (res);
        }
            break;

        case MUL:
        {
            PrintMUL(res);
        }
            break;

        case DIV:
        {
            PrintDIV (res);
        }
            break;

        case LOG:
        {
            PrintLOG (res);
        }
            break;

        case POW:
        {
            PrintPOW (res);
        }
            break;
    }

    return TRUE;
}

bool Node::PrintVar (char* res)
{
    switch (_value)
    {
        CASE(res , a);
        CASE(res , b);
        CASE(res , c);
        CASE(res , d);
        CASE(res , e);
        CASE(res , f);
        CASE(res , g);
        CASE(res , h);
        CASE(res , j);
        CASE(res , i);
        CASE(res , k);
        CASE(res , l);
        CASE(res , m);
        CASE(res , n);
        CASE(res , o);
        CASE(res , p);
        CASE(res , q);
        CASE(res , r);
        CASE(res , s);
        CASE(res , t);
        CASE(res , u);
        CASE(res , v);
        CASE(res , w);
        CASE(res , x);
        CASE(res , y);
        CASE(res , z);
    }

    return TRUE;
}

bool Node::PrintMUL (char* res)
{
    strcat(res, "(");
    _left->PrintNode(res);
    strcat(res, "*");
    _right->PrintNode(res);
    strcat(res, ")");

    return TRUE;
}

bool Node::PrintSUB (char* res)
{
    if (_left->_value != -1 &&
        _right->_value != -1 &&
        _left->_value  != 1 &&
        _right->_value != 1)
    {
        strcat(res, "(");
        _left->PrintNode(res);
        strcat(res, "-");
        _right->PrintNode(res);
        strcat(res, ")");
    }
    else if (_left->_value == -1 &&
             _right->_value != -1 &&
             _left->_value  != 1 &&
             _right->_value != 1)
    {
        strcat(res , "(-");
        _right->PrintNode(res);
        strcat(res , ")");
    }
    else if (_left->_value != -1 &&
             _right->_value == -1 &&
             _left->_value  != 1 &&
             _right->_value != 1)
    {
        strcat(res , "(-");
        _left->PrintNode(res);
        strcat(res , ")");
    }
    else if (_left->_value != -1 &&
             _right->_value != -1 &&
             _left->_value  == 1 &&
             _right->_value != 1)
        _right->PrintNode(res);
    else if(_left->_value != -1 &&
            _right->_value != -1 &&
            _left->_value  != 1 &&
            _right->_value == 1)
        _left->PrintNode(res);
}

bool Node::PrintDIV (char* res)
{
    strcat(res, "(");
    _left->PrintNode(res);
    strcat(res, "/");
    _right->PrintNode(res);
    strcat(res, ")");
}

bool Node::PrintADD (char* res)
{
    strcat (res , "(");
    _left->PrintNode (res);
    strcat (res , "+");
    _right->PrintNode (res);
    strcat (res , ")");

    return 0;
}

bool Node::PrintPOW (char* res)
{
    strcat (res , "((");
    _left->PrintNode (res);
    strcat (res , ")^(");
    _right->PrintNode (res);
    strcat (res , "))");

    return TRUE;
}

bool Node::PrintLOG (char* res)
{
    strcat (res , "log(");
    _left->PrintNode (res);
    strcat (res , ",");
    _right->PrintNode (res);
    strcat (res , ")");

    return TRUE;
}

