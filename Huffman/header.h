#ifndef  header
#define  header

#include "Huff_lib.h"

Heap *Create_Heap();

Node *CreateNode(int value,unsigned char character);

NewBytes *CreateNewBytes(int *Frequency);

void Swap(Node **a, Node **b);

int GetParentIndex(int index);

int GetChildrenLeftIndex(int index);

int GetChildrenRightIndex(int index);

void DownHeapMin(int index,Heap *heap);

Node *pop(Heap *heap);

void UpHeapMin(Heap *heap,int index); 

void push(Heap *heap,Node *node);

void BuiltMinHeap(Heap *heap,int *Frequency);

FILE *GetFrequency(int *Frequency,char *FileName);

Node *BuildHuffmanTree(Heap *heap);

void GetNewBytes(Node *HuffmanTree,NewBytes *Bytes,unsigned char *Array,int i);

void GetTrash(NewBytes *Bytes,int *Frequency,int *Trash);

int is_bit_i_set(unsigned char c, int i);

unsigned char set_bit(unsigned char c, int i);

void Write_Bytes(FILE *FileHeader,unsigned char *string,int SizeTrash,int SizeTree);

void Write_CompressedBytes(FILE *FileHeader,FILE *file,NewBytes *Bytes);

void Header(char *FileName,unsigned char *string,int SizeTrash,int SizeTree,FILE *file,NewBytes *Bytes);

void Descompressor(char *FileName);

void Compressor(char *FileName);

#endif
