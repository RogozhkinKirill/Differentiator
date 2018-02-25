#ifndef DIFFERENTIATOR_H_
#define DIFFERENTIATOR_H_

#include "../TreeLib/TreeLib.h"
#include "../decoder/decoder.h"


char* Differentiator();//Don't realized


typedef encoding_type definision;
/*
 *DiffTreeNode
 */
class DiffTreeNode : public Node
{
private:
     definision _define = NULL;

public:
    //Constructor and destructor
    DiffTreeNode() {printf ("Constructor called: DiffTreeNode");};
    DiffTreeNode(value_type , definision);

    ~DiffTreeNode();
};

/*
 *DiffTree
 */
class DiffTree : public Tree
{
public:
    //Constructor and destructor
    DiffTree()  {printf ("Constuctor called: DiffTree \n");};
    ~DiffTree() {printf ("Destructor called: DiffTree \n"); delete _head;}


    //Conventional
    bool  StrToDiffTree (char* funcStr);//Don't realized
    char* DiffTreeToStr ();//Don't realized

    DiffTree* Differentiator(); //Don't realized
};


#endif // DIFFERENTIATOR_H_
