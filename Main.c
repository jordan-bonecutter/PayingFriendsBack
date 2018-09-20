#include <stdio.h>
#include <stdlib.h>

typedef struct mem member;
typedef struct memarr memArray;

struct mem
{
	char *name;
	float amountPaid;
};

struct memarr
{
	member *array;
	char length;
};

float avg(memArray members)
{
	float sum = 0;
	for(char n = 0; n < members.length; n++)
	{
		sum += members.array[n].amountPaid;
	}
	return sum/members.length;
}

int main()
{
	memArray members;
	float average;
	float *deltas;
	float *todo;
	while(1)
	{
		printf("How many people are in your group?\t");
		scanf("%d", &members.length);
		if(members.length > 0)
		{
			break;
		}
	}
	members.array = malloc(sizeof(member) * members.length);

	for(char i = 0; i < members.length; i++)
	{
		printf("Enter the name of the %d person:\t", i);
		members.array[i].name = calloc(sizeof(char) * 20, 1);
		scanf("%20s", members.array[i].name);
	}

	for(char i = 0; i < members.length; i++)
	{
		printf("Enter the amount %s paid:\t", members.array[i].name);
		scanf("%f", &members.array[i].amountPaid);
	}

	average = avg(members); 
	deltas = malloc(sizeof(float) * members.length);
	todo = malloc(sizeof(float) * members.length);
	for(char i = 0; i < members.length; i++)
	{
		deltas[i] = members.array[i].amountPaid - average;
	}

	int n = 0, i;

	while(1)
	{
		if(deltas[n] < 0)
		{
			while(1)
			{
				for(i = 0; i < members.length; i++)
				{
					if(deltas[i] > 0)
					{
						break;
					}
				}
				if(deltas[n] <= -deltas[i])
				{
					printf("%s pays %s $%f\n", members.array[n].name, members.array[i].name, deltas[i]);
					deltas[n] += deltas[i];
					deltas[i] = 0;
				}
				else
				{
					printf("%s pays %s $%f\n", members.array[n].name, members.array[i].name, -deltas[n]);
					deltas[i] += deltas[n];
					deltas[n] = 0;
				}
				if(deltas[n] <= 0.001)
				{
					break;
				}
			}
		}
		n++;
		if(n == members.length)
		{
			for(char c = 0; c < members.length; c++)
			{
				if(deltas[c] > 0.01 || deltas[c] < -0.01)
				{
					n = 0;
					break;
				}
			}
			if(n != 0)
			{
				break;
			}
		}
	}

	for(char i = 0; i < members.length; i++)
	{
		free(members.array[i].name);
	}
	free(members.array);
	free(deltas);
	free(todo);
}
