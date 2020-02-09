#ifndef  Huff_lib
#define  Huff_lib

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#define MAX 1000000

typedef struct NodeTree Node;
typedef struct Array Heap;
typedef struct DATA DATA;
typedef struct NewBytes NewBytes;


struct NodeTree
{
int frequency;
unsigned char character;
struct NodeTree *left;
struct NodeTree *right;
};

struct Array{
int size;
Node *table[259];
};

struct DATA
{
    unsigned char byte[100];
};

struct NewBytes
{
    DATA Element[256];
};

Heap *Create_Heap()
{
int i;
Heap *NewHeap = (Heap*)malloc(sizeof(Heap));
NewHeap->size = 0;
for(i = 1;i <= 256;i++)
{
NewHeap->table[i] = NULL;
}
return NewHeap;
}

Node *CreateNode(int value,unsigned char character)
{
Node *NewNode      = (Node*)malloc(sizeof(Node));
NewNode->frequency = value;
NewNode->character = character;
NewNode->left      = NewNode->right = NULL;;
return NewNode;
}


NewBytes *CreateNewBytes(int *Frequency)
{
    int i;
    NewBytes *Bytes = (NewBytes*)malloc(sizeof(NewBytes));
    for(i = 0;i < 256;i++)
    {
        Bytes->Element[i].byte[0] = '\0';
        Frequency[i] = 0;

    }
    return Bytes;
}

#endif
