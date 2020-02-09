#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

typedef struct NodeTree Node;
typedef struct Array Heap;

struct NodeTree{
int frequency;
char character;
struct NodeTree *left;
struct NodeTree *right;
};
struct Array{
int size;
Node *table[259];
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

Node *CreateNode(int value,char character)
{
Node *NewNode      = (Node*)malloc(sizeof(Node));
NewNode->frequency = value;
NewNode->character = character;
NewNode->left      = NewNode->right = NULL;;
return NewNode;
}

void view(Heap *heap)
{
int i;
for(i = 1;i <= heap->size;i++)
{
printf("| %d %c |",heap->table[i]->frequency,heap->table[i]->character);
}
}

void Swap(Node **a, Node **b)
{
Node *t = *a;
*a = *b;
*b = t;
}

int GetParentIndex(int index){return index/2;}

int GetChildrenLeftIndex(int index){return index*2;}

int GetChildrenRightIndex(int index){return index*2+1;}

void DownHeapMin(int index,Heap *heap)
{
if (index * 2 > heap->size)return;
else
{
int left  = GetChildrenLeftIndex(index);
int Right = GetChildrenRightIndex(index);
int smallest = index;
if (left <= heap->size && heap->table[left]->frequency < heap->table[smallest]->frequency)
{
    smallest = left;
}
if (Right <= heap->size && heap->table[Right]->frequency < heap->table[smallest]->frequency)
{
    smallest = Right;
}
if (smallest != index)
{
    Swap(&heap->table[index],&heap->table[smallest]);
    DownHeapMin(smallest,heap);
}
}
}

Node *pop(Heap *heap)
{
Node *smallest = heap->table[1];
heap->table[1] = heap->table[heap->size];
heap->size--;
DownHeapMin(1,heap);
return smallest;
}

void UpHeapMin(Heap *heap,int index) 
{
if (index == 1)return;
else 
{
int Parentidx = GetParentIndex(index);
if(heap->table[index]->frequency < heap->table[Parentidx]->frequency) {
    Swap(&heap->table[index],&heap->table[Parentidx]);
    UpHeapMin(heap,Parentidx);
}
}
}

void push(Heap *heap,Node *node)
{
heap->table[++heap->size] = node;
UpHeapMin(heap,heap->size);
}

void Restart(int array[])
{
int i;
for(i = 0;i < 256;i++)
{
array[i] = 0;
}
}

void BuiltMinHeap(Heap *heap,int *array)
{
int i;
Node *node;
for(i = 0;i < 256;i++)
{
if(array[i] > 0)
{
node = CreateNode(array[i],i);
push(heap,node);
}
}
}

void GetFrequency(int *array,char *FileName)
{
unsigned char element;
FILE *pFile;
pFile = fopen(FileName,"rb");
while(fscanf(pFile," %c ",&element) != EOF)
{ 
array[element]++;
}
}


Node *BuildHuffmanTree(Heap *heap)
{
Node *left,*right;
while(heap->size > 1)
{
left  =  pop(heap);
right =  pop(heap);
Node *node = CreateNode(left->frequency + right->frequency,'*');
node->left = left;
node->right= right; 
push(heap,node);
}
return pop(heap);
}


int main()
{
int array[256]; 
char FileName[50];
scanf("%[^\n]",FileName);

Heap *heap = Create_Heap();

Restart(array);

GetFrequency(array,FileName);

BuiltMinHeap(heap,array);

Node *HuffmanTree = BuildHuffmanTree(heap);

return 0;
}
