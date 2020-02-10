#include "Huff_lib.h"
#include "header.h"


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


void BuiltMinHeap(Heap *heap,int *Frequency)
{
int i;
Node *node;
for(i = 0;i < 256;i++)
{
if(Frequency[i])
{
node = CreateNode(Frequency[i],i);
push(heap,node);
}
}
}

FILE *GetFrequency(int *Frequency,char *FileName)
{
unsigned char element;
FILE *pFile;
pFile = fopen(FileName,"rb");
while(fscanf(pFile,"%c",&element) != EOF)
{ 
Frequency[element]++;
}
return pFile;
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

void Save(unsigned char *Array,NewBytes *Bytes,int key,int size)
{
    int i;
    printf("%c ",key);
    for(i = 0;i < size;i++)
    {
        Bytes->Element[key].byte[i] = Array[i];
    }
    printf("%s",Bytes->Element[key].byte);
    printf("\n");
}

void GetNewBytes(Node *HuffmanTree,NewBytes *Bytes,unsigned char *Array,int i)
{
    if(HuffmanTree->left)
    {
        Array[i] = '0';
        GetNewBytes(HuffmanTree->left,Bytes,Array,i+1);
    }
    if(HuffmanTree->right)
    {
        Array[i] = '1';
        GetNewBytes(HuffmanTree->right,Bytes,Array,i+1);
    }
    if(HuffmanTree->left == NULL && HuffmanTree->right == NULL)
    {
     unsigned char key = HuffmanTree->character;
     Save(Array,Bytes,key,i);
    }
}

void get_tree(Node *huff,unsigned char *string,int *SizeTree)
{
	if (huff != NULL)
	{
		if(huff->left == NULL && huff->right == NULL)
        {
			if(huff->character == '*'  || huff->character == '\\')
			{
				string[*SizeTree] = '\\';
				*SizeTree+=1;
			}
			string[*SizeTree] = huff->character;
			*SizeTree += 1;
		}
		else
        {
			string[*SizeTree] = huff->character;
			*SizeTree += 1;
			get_tree(huff->left, string, SizeTree);
			get_tree(huff->right, string, SizeTree);
		}
	}

}

void GetTrash(NewBytes *Bytes,int *Frequency,int *Trash)
{
    int i;
    for(i = 0;i < 256;i++)
    {
        *Trash+= strlen(Bytes->Element[i].byte) * Frequency[i];
    }
}

int is_bit_i_set(unsigned char c, int i)
{
    unsigned char mask = 1 << i;
    return mask & c;
}

unsigned char set_bit(unsigned char c, int i)
{
    unsigned char mask = 1 << i;
    return mask | c;
}

void Write_Bytes(FILE *FileHeader,unsigned char *string,int SizeTrash,int SizeTree)
{
    short int aux = SizeTrash;

    aux  = (aux << 13) | SizeTree; 

    fprintf(FileHeader,"%c%c",aux >> 8,aux);

    fwrite(string,1,SizeTree,FileHeader);
}

void Write_CompressedBytes(FILE *FileHeader,FILE *file,NewBytes *Bytes)
{
    unsigned char idx,NewByte = 0;
	int bits = 7;
	while(fscanf(file,"%c", &idx) != EOF)
	{
       int key = (int)idx;
       for(int i = 0; Bytes->Element[key].byte[i] != '\0';i++)
	   {
		   if(bits < 0)
		   {
			   fprintf(FileHeader,"%c",NewByte);
			   NewByte = 0;
			   bits = 7;
		   }
		   if(Bytes->Element[key].byte[i] == '1')
		   {
			   NewByte = set_bit(NewByte,bits);
		   }
		   bits--;
	   }
	}
	fprintf(FileHeader,"%c",NewByte);
}

void Header(char *FileName,unsigned char *string,int SizeTrash,int SizeTree,FILE *file,NewBytes *Bytes)
{
    FILE *FileHeader;

    strcat(FileName,".huff");

    FileHeader = fopen(FileName,"wb");

    Write_Bytes(FileHeader,string,SizeTrash,SizeTree);

    Write_CompressedBytes(FileHeader,file,Bytes);

    fclose(FileHeader);
}

void Compressor(char *FileName)
{  
int Trash,SizeTree;
int Frequency[256];
SizeTree = Trash = 0;

Heap *heap = Create_Heap();

/*Frequency(array of frequency) like paramater*/
NewBytes *Bytes = CreateNewBytes(Frequency);

/*Get frequency of each character*/
FILE *file = GetFrequency(Frequency,FileName);

BuiltMinHeap(heap,Frequency);

/*keep the huffman tree and new byte*/
unsigned char string[MAX],Array[MAX];

/*Create Huffman Tree*/
Node *HuffmanTree = BuildHuffmanTree(heap);

/*New bytes for each character*/
GetNewBytes(HuffmanTree,Bytes,Array,0);

/*Save the pre ordem on a string*/
get_tree(HuffmanTree,string,&SizeTree);

printf("\nWe've took the tree size! %d\n",SizeTree);
/*take trash of the tree*/

GetTrash(Bytes,Frequency,&Trash);
Trash = (8 - (Trash % 8)) % 8;
printf("Size Trash %d\n",Trash);

printf("Writing header\n");

rewind(file);
Header(FileName,string,Trash,SizeTree,file,Bytes);

printf("Done!!\n");

}
