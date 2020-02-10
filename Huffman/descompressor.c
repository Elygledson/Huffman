#include "Huff_lib.h"
#include "header.h"

int Trash_size;
short int Tree_size;
FILE *file;

void InitialInformation(unsigned char *huff_tree,unsigned char B_Trash,unsigned char B_Tree)
{
    int i = 0;
    Trash_size = B_Trash >> 5;
    B_Trash  = B_Trash << 3;
    B_Trash  = B_Trash >> 3;
    Tree_size = B_Trash;
    Tree_size = (Tree_size << 8) | B_Tree;
    printf("Size Trash %d\nSize Tree %d\n",Trash_size,Tree_size);
    while(i != Tree_size)
    fscanf(file,"%c",&huff_tree[i++]);
}

Node *get_HuffTree(unsigned char *huff_tree,int *i)
{
    Node *Huff;
    if (huff_tree[*i] != '*')
    {
        if (huff_tree[*i] == '\\')
        *i += 1;

       Node *aux = CreateNode(-1,huff_tree[*i]);
       *i+=1;
       return aux;
    }
    else{
    Huff = CreateNode(-1,huff_tree[*i]);*
    i+=1;
    Huff->left  = get_HuffTree(huff_tree,i);
    Huff->right = get_HuffTree(huff_tree,i);
    }
    return Huff;
}

void WritingCharaters(Node *HuffmanTree,char *FileName,long Size_File)
{
    unsigned char byte;

    FILE *SourceFile;

    FileName[strlen(FileName)- 5] = '\0';

    SourceFile = fopen(FileName,"wb");

    Node *Copy = HuffmanTree;

    long BytesRead = 1;

    int reach,rest;

    rest = (Size_File - Tree_size) - 2;
    printf("Remaining bytes %d\n",rest);
    while(fscanf(file,"%c",&byte) != EOF)
    {
        reach = (BytesRead == rest) ? Trash_size : 0;

        for(int i = 7;i >= reach;i--)
        {
            if(is_bit_i_set(byte,i))
            HuffmanTree = HuffmanTree->right;

            else
            HuffmanTree = HuffmanTree->left;

            if(!HuffmanTree->left && !HuffmanTree->right){
              fprintf(SourceFile,"%c",HuffmanTree->character);
              HuffmanTree = Copy;
            }
        }
        BytesRead++;
    }
    printf("Bytes Read %ld\n",BytesRead - 1);
    printf("Done!!");
    fclose(SourceFile);
    return;
}

void Descompressor(char *FileName)
{
    file = fopen(FileName,"rb");

    fseek(file,0,SEEK_END);

    long Size_File = ftell(file);

    printf("Size_file  %ld bytes\n",Size_File);

    rewind(file);

    unsigned char B_Trash,B_Tree;

    fscanf(file,"%c%c",&B_Trash,&B_Tree);

    Trash_size = Tree_size = 0;

    unsigned char huff_tree[MAX]; 

    InitialInformation(huff_tree,B_Trash,B_Tree);

    int i = 0;

    Node *HuffmanTree = get_HuffTree(huff_tree,&i);

    WritingCharaters(HuffmanTree,FileName,Size_File);
    fclose(file);
}
