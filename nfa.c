#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct state
{
	char curState[10];
	char *transitions[2];
	int oldState;
	struct state *next;
};

void print(struct state *head)
{
	struct state *cur = head;
	
	while(cur != NULL)
	{
		printf("%s <-\n", cur -> curState);
		printf("%s %s\n", cur -> transitions[0], cur -> transitions[1]);
		cur = cur -> next;
	}
}
int checkString(char *str, char *sub)
{
	int i = 0, k = 0;
	char ch = malloc(1000);
	while(i < strlen(sub))
	{
		
		if(!strcmp(ch, subch))
			return 1;
	}
}


void tokenize(struct state *head, char *str)
{
	int i = 0, k = 0;
	char *ch = malloc(1000), *state0 = malloc(1000), *state1 = malloc(1000);
	struct state *temp = malloc(sizeof(struct state)), *cur = head;
	temp -> oldState = 0;
	strcpy(temp -> curState, str);
	while(i < strlen(str))
	{
		if(str[i] == ' ')
		{
			k = 0;
			cur = head;
			while(cur != NULL)
			{
				if(!strcmp(cur -> curState, ch))
				{
					state0 = cur -> transitions[0];
					state1 = cur -> transitions[1];
				}
				cur = cur -> next;
			}
			ch = malloc(1000);
			i++;
		}
		else if(str[i] == ',')
			i++;
		else
		{
			ch[k++] = str[i++];
		}
	}
	cur = head;
	while(cur != NULL)
	{
		if(!strcmp(cur -> curState, ch))
			{
				strcat(state0, cur -> transitions[0]);
				strcat(state1,  cur -> transitions[1]);
			}
		cur = cur -> next;
	}
	temp -> transitions[0] = state0;
	temp -> transitions[1] = state1;
	cur = head;
	while(cur -> next != NULL)
		cur = cur -> next;
	cur -> next = temp;
}

void genState(struct state *head)
{
	struct state *cur = head, *traverse, *temp;
	int flag = 0;
	while(cur != NULL)
	{
		temp = head;
		flag = 0;
		while(temp != NULL)
		{
			if(!strcmp(temp -> curState, cur -> transitions[0]))
			{
				flag = 1;
				break;
			}	
			temp = temp -> next;
		}
		if(!flag)
			tokenize(head, cur -> transitions[0]);
		cur = cur -> next;
	}
	print(head);
} 


struct state* makeState(char *subStr, struct state *head)
{
	struct state *temp, *cur = NULL;
	int i = 0, k = 0, j = 0, setState = 0;
	char *ch = malloc(1000);
	temp = malloc(sizeof(struct state));
	temp -> oldState = 1;
	while(i < strlen(subStr))
	{
		if(i > 0)
		{
			if(subStr[i] == ' ' && subStr[i - 1] != ',' || subStr[i] == '\n')
			{
				ch[k] = '\0';
				k = 0;
				if(head == NULL)
				{			
					strcpy(temp -> curState, ch);
					temp -> next = NULL;
					head = temp;
					cur = head;
					setState = 1;
				}
				else if(!setState)
				{
					strcpy(temp -> curState, ch);
					temp -> next = NULL;
					cur = head;
					while(cur -> next != NULL)
						cur = cur -> next;
					cur -> next = temp;
					cur = cur -> next;
					setState = 1;
					ch = NULL;
				}
				else
				{
					cur -> transitions[j++] = ch;
				}
				ch = malloc(1000);
				i++;
			}
			else
				ch[k++] = subStr[i++];
		}
		else
			ch[k++] = subStr[i++];
	}
	return head;
}
void process(char *str, struct state *head)
{
	int i = 0, k;
	char *subStr = malloc(1000);
	while(i < strlen(str))
	{	
		k = 0;
		while(str[i] != '\n')
			subStr[k++]  = str[i++];
		subStr[k] = '\n';
		i = i + 1;
		head = makeState(subStr, head);
		free(subStr);
		subStr = malloc(1000);
	}
	genState(head);	
}

void main()
{
	char str[] = {"q0 q0 q1\nq1 q1, q2 q1\nq2 q2 q1, q2\n"};
	struct state *head = NULL;
	process(str, head);
}