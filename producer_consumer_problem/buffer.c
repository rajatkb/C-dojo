#include <stdio.h>
#include "buffer.h"


int display_buffer()
{
	printf("[ ");
	for (int i = 0; i < BUFFER_SIZE; i++)
	{
		printf(" %d ", buffer[i]);
	}
	printf("]");
}

int init_buffer()
{
	counter = -1;
	for (int i = 0; i < BUFFER_SIZE; i++)
	{
		buffer[i]=0;
	}
}

int insert_buffer(int buffer_content)
{
	if( !(counter < BUFFER_SIZE))
		printf("\nBUFFER OVERFLOW\n");
	else
		buffer[++counter]=buffer_content;
}

int remove_buffer()
{
	int temp;
	if(counter < 0)
	{	
		printf("\nBUFFER UNDERFLOW\n");
		temp=-1;
	}	
	else{
		temp = buffer[counter];
		buffer[counter--]=0;
	}
	return temp;
}