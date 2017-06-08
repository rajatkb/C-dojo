/*
Q. Implement a 2 dimensional Array using linked list
Sol : a structure consisting of columns and one as rows. rows will also hold the column list
		r - c - c - c - ....
		|	
		r - c - c -	c - ....
		|	
		r - c - c - c -	....
		.	.	.	........
		.	.	.	........
*/
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
// Standard structure definition 
// One for col_node and the other one for row_node
typedef struct col_node
{
	int data;
	struct col_node *next;
}col_node;

typedef struct row_node
{
	int data;
	struct col_node *selfcol;
	struct row_node *next;
}row_node;
// a macro for having Linked2D as the data type name for the array variable
#define Linked2D row_node
///////* Deffinition ends here *////////

//// * Routines *////////////
//insert into Row structure node  and create linked list of row structure sort///
int insertRowNode(row_node **head)
{
	if((*head)==NULL)
	{
		(*head)=(row_node *)malloc(sizeof(row_node *));
		(*head)->next = NULL; 
		(*head)->selfcol = NULL;
		(*head)->data = 0;
		return 1;
	}
	row_node *t = (row_node *)malloc(sizeof(row_node *));
	t->next = (*head);
	t->selfcol = NULL;
	t->data = 0;
	(*head) = t; 
}
// end of function //
//insert into Column structure node  and create linked list of row structure sort///
int insertColNode(col_node **head)
{
	if((*head)==NULL)
	{
		(*head)=(col_node *)malloc(sizeof(col_node *));
		(*head)->next =  NULL;
		(*head)->data = 0;
		return 1;
	}
	col_node *t = (col_node *)malloc(sizeof(col_node *));
	t->next = (*head);
	t->data = 0;
	(*head) = t; 
}
//end of function //

// Creates the entire matrix of the structure shown above in figure at the top
int createMatrix(row_node **head, int r , int c)
{
	if(*head == NULL)
	{
		col_node *temp=NULL;
		for(int i=0;i < r ; i++)
		{
			insertRowNode(head);
			temp = NULL;
			for(int i=1 ; i<c ; i++)
			{
				insertColNode(&temp);
			}
			(*head)->selfcol = temp;		
		}
	}

}
// end of fun`ction

// returns a pointer to the data for that particular node that is accessed.
// Allows for easier manipulation of matrix values
int* putValue(Linked2D *head,int ri,int ci )
{
	if(head == NULL)
	{
		return NULL; // return -1 on failure
	}
	else{

		for(int i =0; i < ri ;i++)
		{
			head= head->next;
			if(head == NULL)
				return NULL; // returns -1 on failure 
		}

		int *data = &(head->data);
		col_node *t = head->selfcol;
		for(int i= 0; i < ci; i++)
		{
			if(t == NULL)
				return NULL; // returns -1 on failure	
			data = &(t->data);
			t=t->next;
		}	
		return data;
	}
}
// a macro redefintion of putValue with a dereferencing
// returns the value at the data loaction of that particular node
#define valueOf(a,b,c) *putValue(a,b,c)
/// End of Create Matrix function ////

// this funtion fills the matrix with random values
int fillRandom(Linked2D *node)
{
	if(node == NULL)
	{	
		printf("\n empty matrix \n");
		return -1;
	}
	else{
		srand(time(NULL));
		row_node *t = node;
		col_node *tc = t->selfcol;
		int rowCount =0;
		int colCount =1;
		while(t!= NULL)
		{
			rowCount++;
			t=t->next;
		}
		while(tc!= NULL)
		{
			colCount++;
			tc=tc->next;
		}
		for(int i =0 ;i <rowCount ; i++)
		{
			for(int j=0;j<colCount; j++)
				*putValue(node,i,j) = rand()%100;
		}

	}
}
// fills the matrix with random value above function : ends////

// Displayfunctinos //
int displayCol(col_node *node )
{
	
	while(node != NULL)
	{
		printf(" %d ,", node->data);
		node= node->next;
	}
	printf("]\n");
}
int display(row_node *node )
{
	while(node != NULL)
	{
		printf("[");
		printf(" %d ,", node->data);
		displayCol(node->selfcol);
		node= node->next;
	}
}
// Display function ends//

// Link2D is the linked list array data type
//createMatrix, creates a fixed dimension matrix
// valueOf gives value at particular index
// putValue gives address of particular index data
//fillRandom fills matrix with random Values


int main()
{
	Linked2D *arr=NULL;
	createMatrix(&arr, 5, 6);
	display(arr);
	fillRandom(arr);
	display(arr);
	printf("\n %d \n",valueOf(arr,2,1));
	return 0;
}
