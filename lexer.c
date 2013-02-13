#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define ID 0
#define WS 1
#define BS 2
#define KW 3
struct Symbol
{
	int type;
	int line;
	char name[20];
	struct Symbol *next;
};
struct Symbol *list=NULL;

void checkbuffer(char *buffer,int i,int lc)
{
	if(i>0)
	{
		buffer[i]=0;
		struct Symbol *new=(struct Symbol *)malloc(sizeof(struct Symbol));
		strcpy(new->name,buffer);
		new->line=lc;
		if(!strcmp(buffer,"include")||!strcmp(buffer,"printf")||!strcmp(buffer,"void")||!strcmp(buffer,"int")||!strcmp(buffer,"float")||!strcmp(buffer,"char")||!strcmp(buffer,"main")||!strcmp(buffer,"return"))
			new->type=KW;
		else
			new->type=ID;
		new->next=NULL;
		if(list==NULL)
			list=new;
		else
		{
			struct Symbol *temp=list;
			while(temp->next!=NULL)
				temp=temp->next;
			temp->next=new;
		}
	}
}
void display()
{
	struct Symbol *temp=list;
	printf("_________________________________________\n");
	printf("Line-No\tType\t\tName(if)\n");
	printf("_________________________________________\n");
	while(temp->next!=NULL)
	{
		printf("%d\t",temp->line);
		switch(temp->type)
		{
			case WS : printf("White space");
				break;
			case KW : printf("Key Word");
				break;
			case ID : printf("Identifier");
				break;
			case BS : printf("Braces\t");
				break;
		}
		printf("\t%s\n",temp->name);
		temp=temp->next;
	}
	printf("%d\t",temp->line);
	switch(temp->type)
	{
		case WS : printf("White space");
			break;
		case KW : printf("Key Word");
			break;
		case ID : printf("Identifier");
			break;
		case BS : printf("Braces\t");
			break;
	}
	printf("\t%s\n",temp->name);
}
void unitialize()
{
	
	while(list->next!=NULL)
	{
		struct Symbol *temp=list;
		list=list->next;
		free(temp);
	}
	free(list);
}
	
	
		
int main(int argc,char *argv[])
{
	if(argc!=2)
	{
		printf("Syntax: ./lexer <filename>\n");
		return 1;
	}
	char *source=argv[1],c,buffer[20];
	int i=0;
	FILE *ptr=fopen(source,"r");
	if(ptr==NULL)
	{
		printf("Could not open file\n");
		return 1;
	}
	int lc=1;
	int nl=1;
	printf("Going to read file \n");
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
			checkbuffer(buffer,i,lc);
			lc++;
			nl=1;
			i=0;
		}
		else if(c==' ')
		{
			checkbuffer(buffer,i,lc);
			struct Symbol *new=(struct Symbol *)malloc(sizeof(struct Symbol));
			strcpy(new->name,"space");
			new->line=lc;
			new->type=WS;
			new->next=NULL;
			if(list==NULL)
				list=new;
			else
			{
				struct Symbol *temp=list;
				while(temp->next!=NULL)
					temp=temp->next;
				temp->next=new;
			}
			i=0;
		}
		else if(c=='}'||c=='{')
		{
			checkbuffer(buffer,i,lc);

			struct Symbol *new=(struct Symbol *)malloc(sizeof(struct Symbol));
			strcpy(new->name,(c=='}')?"}":"{");
			new->line=lc;
			new->type=BS;
			new->next=NULL;
			if(list==NULL)
				list=new;
			else
			{
				struct Symbol *temp=list;
				while(temp->next!=NULL)
					temp=temp->next;
				temp->next=new;
			}
			i=0;
		}
		else if((c>='A'&&c<='Z')||(c>='a'&&c<='z'))
		{	
			buffer[i]=c;
			i++;
		}
		else
		{
			checkbuffer(buffer,i,lc);
			i=0;
		}	
	}
	//display list;
	display();
	//unitialize memory
	unitialize();
	fclose(ptr);
	return 0;
}
	
