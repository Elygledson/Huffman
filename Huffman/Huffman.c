#include "compressor.c"
#include "descompressor.c"


int main() 
{

while(true)
{
int option;
char FileName[50];
printf("\nSelect one option: \n");
printf("--------------------\n");
printf("1 - Compress \n");
printf("2 - Descompress \n");
printf("3 - Exit\n");
printf("--------------------\n");
scanf("%d",&option);
switch (option){
case 1:
printf("Type the file name:\n");
scanf("%s",FileName);
Compressor(FileName);
break;
case 2:
printf("Type the file name:\n");
scanf("%s",FileName);
Descompressor(FileName);
break;
case 3:
return 0;
default:
printf("Invalid option\n");
break;
}
}
return 0;
}
