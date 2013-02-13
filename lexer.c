#include<stdio.h>
#include<string.h>
int main(int argc,char *argv[])
{
	if(argc!=2)
	{
		printf("Syntax: ./lexer <filename>\n");
		return 1;
	}
	char *source=argv[1],c;
	FILE *ptr=fopen(source,"r");
	if(ptr==NULL)
	{
		printf("Could not open file\n");
		return 1;
	}
	while(fscanf(ptr,"%c",&c)!=EOF)
	{
		printf("%c",c);
	}
	return 0;
}
	
