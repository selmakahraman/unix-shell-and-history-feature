#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 80 


typedef struct {
	char commandName[15];
	int usageCounter;
} history;

history hist[30];
int count = -1;

void usagedCommands()
{
	printf("\nList of usaged command:\n");
	
	int scanning,i;
	
	for(scanning = 0; scanning <= count; scanning++)
	{
		
		for(i = 0; i< ((count+1) - scanning -1); i++)
		{
			if(hist[i].usageCounter < hist[i+1].usageCounter)
			{
				history temp;
				temp = hist[i];
				hist[i] = hist[i+1];
				hist[i+1] = temp;				
			}
		}		
	}
	
	if(count <= 10)
	{	
		for(i=0; i<=count; i++)
		{
			printf("%d.",(i+1));
			printf("Command name :%s Usaged count: %d\n", hist[i].commandName,hist[i].usageCounter);
		}
	}
	
	else
	{
		for(i=0; i<10; i++)
		{
			printf("%d.",(i+1));
			printf("Command name :%s Usaged count: %d\n", hist[i].commandName,hist[i].usageCounter);
		}
	}
	
	printf("\n");
}


int commands(char inputBuffer[], char *args[], int *flag)
{

	int length,i,start,count2=0;
		
	length = read(STDIN_FILENO,inputBuffer,MAX_LINE); 
	start = -1;
	
	if(length == 0)
		exit(0);

	if(length < 0)
	{
		printf("Command not read.. \n");
		exit(-1);
	}

	for(i=0;i<length;i++)
	{
		switch(inputBuffer[i])
		{
			case ' ':
			case '\t':
				if(start != -1)
				{	
					args[count2]=&inputBuffer[start];
					count2++;
				}
				inputBuffer[i]='\0';
				start = -1;
				break;

			case '\n':
				if(start != -1)
				{
					args[count2] = &inputBuffer[start];
					count2++;
				}
				inputBuffer[i]='\0';
				start = -1;
				break;

			default :
				if(start == -1)
					start = i;
				if(inputBuffer[i] == '&')
				{
					*flag=1;
					inputBuffer[i] ='\0';
				}				
		}	
	}
	
	args[count2] = NULL;
	if(strcmp(args[0],"history") == 0)
	{
			
		if(count>-1)
			usagedCommands();
		else 
			printf("No Commands in the history..\n");

		return -1;
	}
	
	else if(strcmp(args[0],"exit")==0)
	{
		exit(0);
	}

	else 
	{	
		count++;
		int a = 0;
		
		for(i=0;i<=count;i++)	
		{	
				
			if(strcmp(inputBuffer,hist[i].commandName) == 0)
			{
				a=1;
				hist[i].usageCounter++;
				count--;
				break;
			}
							
			else 
			{					
				continue;		
			}		
		}
		
		if(a==0)
		{	
			strcpy(hist[count].commandName,inputBuffer);
			hist[count].usageCounter=1;
		}	
	}
}

int main(void)
{

	char inputBuffer[MAX_LINE];
	int flag;
	char *args[MAX_LINE/2 + 1];
	int should_run=1;

	pid_t pid, tpid;
	int i;
		
	while(should_run)
	{

		flag=0;
		printf("osh>");
		fflush(stdout); 
				
		if(-1 != commands(inputBuffer,args,&flag))
		{
			pid = fork();
			if(pid < 0)
			{
				printf("Fork failed.\n");
				exit(1);		
			}

			else if(pid==0)
			{
				if(execvp(args[0],args) == -1)
				printf("Error executing command\n");
			}

			else
			{
				i++;
				if(flag==0)
				{
					i++;
					wait(NULL);
				}		
			}
		}	
	}
}
