#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "process.h"

//pl stands for the head pointer of list head pointer

process_block *getProcessBlock(int pid,int bt,int at ,int priority)
{
	process_block *pr=(process_block *)malloc(sizeof(process_block));
	if(pr == NULL)
	{
		printf("log: memory could not be allocated\n");
		exit(0);
	}
	pr->pid=pid;
	pr->info[burst_time]=bt;
	pr->info[remaining_time]=bt;
	pr->info[arival_time]=at;
	pr->info[start_time]=-1;
	pr->info[end_time]=-1;
	pr->priority=priority;
	return pr;
}

int displayProcessBlock(process_block *obj)
{
	printf("pid: %d burst_time: %d remaining_time: %d  priority: %d \n",
	 obj->pid,obj->info[burst_time],obj->info[remaining_time],obj->priority);
}

int addToProcessList(PROCESS_LIST **pl,int pid, int bt, int at , int priority)
{
	PROCESS_LIST *list=(*pl);
	if(list == NULL)
	{
		list=(PROCESS_LIST *)malloc(sizeof(PROCESS_LIST));
		if(list == NULL)
		{
			printf("log: memory could not be allocated addToProcessList\n");
			exit(0);
		}
		list->block=getProcessBlock(pid, bt, at, priority);
		list->next=NULL;
		(*pl)=list;
	}
	else{
		while(list->next != NULL)
		{
			list=list->next;
		}
		list->next=(PROCESS_LIST *)malloc(sizeof(PROCESS_LIST));
		if(list->next == NULL)
		{
			printf("log: memory could not be allocated addToProcessList\n");
			exit(0);
		}
		(list->next)->block=getProcessBlock(pid, bt, at, priority);
		(list->next)->next=NULL;
	}

	return 1;
}

int displayProcessList(PROCESS_LIST *pl)
{
	while(pl!=NULL)
	{
		displayProcessBlock(pl->block);
		pl=pl->next;
	}
}

int deleteProcessList(PROCESS_LIST **pl)
{
	PROCESS_LIST *list=(*pl);
	PROCESS_LIST *temp;

	while(list!=NULL)
	{
		temp=list->next;
		free(list->block);
		free(list);
		list=temp;
	}
	(*pl)=NULL;
}

int *deleteProcessID(PROCESS_LIST **pl,int pid)
{

	for(PROCESS_LIST **current = pl; *current ; current= (&(*current)->next))
	{
		if(((*current)->block)->pid == pid)
		{
			PROCESS_LIST *temp= *current;
			(*current)=(*current)->next;

			int *info=(int *)malloc(sizeof(int)*5);
			for(int i=0;i<5;i++)
			{
				info[i]=(temp->block)->info[i];
			}

			free(temp->block);
			free(temp);
			return info;
		}
	}

	return NULL;
}

int viewActiveBlock(PROCESS_LIST *block)
{
	printf("ACTIEV JOB : \n JOB_BLOCK: %p \n NEXT_BLOCK: %p ,\n PROCESS_ID: %d \n", block ,block->next, block->block->pid);	
}


// int *dequeProcess(PROCESS_LIST **process)
// {
// 	PROCESS_LIST *temp = (*process);
// 	(*process)=(*process)->next;
// 	int *info=(int *)malloc(sizeof(int)*5);
// 	for(int i=0;i<5;i++)
// 	{
// 		info[i]=(temp->block)->info[i];
// 	}
// 	free(temp->block);
// 	free(temp);
// 	return info;
// }




