#include<stdio.h>
#include<string.h>
#define IDENTIFIER 0
#define WS 1
#define PARANTHESIS 2
#define KEYWORD 3
typedef struct Symbol
{
	int type;
	char *name;
};
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
	int lc=1;
	int nl=1;
	while(fscanf(ptr,"%c",&c)!=EOF)
	{
		if(nl)
		{
			printf("%d\t",lc);
			nl=0;
		}
		printf("%c",c);
		if(c=='\n')
		{
			lc++;
			nl=1;
		}
	}
	return 0;
}
	
