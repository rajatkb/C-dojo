#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "process.h"

int isFinished(process_block *blk)
{
	if(blk->info[remaining_time] == 0)
	{
		return 1;
	}
	return 0;
}

int updateJob(process_block *blk , int quanta)
{
	blk->info[remaining_time]-=quanta;
}


int setStartTime(process_block *blk , int startTime )
{
	if(blk->info[start_time] == -1)
		blk->info[start_time] = startTime;
}

int setEndTime(process_block *blk , int endTime)
{
	if(blk->info[end_time] == -1)
		blk->info[end_time] = endTime;	
}


PROCESS_LIST *schedule_fcfs(PROCESS_LIST *job_qeue)
{
	return job_qeue;
} 


PROCESS_LIST *schedule_round_robin(PROCESS_LIST *job_block , PROCESS_LIST *job_qeue_head)
{
	PROCESS_LIST *temp = job_qeue_head;
	if(job_block->next != NULL)
		temp= job_block->next;
	return temp;
}

PROCESS_LIST *schedule_shortest_job(PROCESS_LIST *job_qeue)
{
	
	PROCESS_LIST *temp=job_qeue;
	while(job_qeue!= NULL)
	{
		if((job_qeue->block)->info[burst_time] < (temp->block)->info[burst_time])
			temp = job_qeue;
		job_qeue = job_qeue->next;
		
	}

	return temp;
}

PROCESS_LIST *schedule_shortest_remainingtime_job(PROCESS_LIST *job_qeue)
{
	
	PROCESS_LIST *temp=job_qeue;
	while(job_qeue!= NULL)
	{
		if((job_qeue->block)->info[remaining_time] < (temp->block)->info[remaining_time])
			temp = job_qeue;
		job_qeue = job_qeue->next;
		
	}

	return temp;
}



// The method takes the head node and the job block that needs to be deleted kind of makes sense so kept it like this
int *delete_process_if_over(PROCESS_LIST **job_qeue, PROCESS_LIST *job_block , int endTime)
{
	int *info=NULL;
	if(job_block==NULL && *job_qeue == NULL){}
	else if(isFinished((job_block)->block))
	{

		setEndTime((job_block->block) , endTime);	
		info = deleteProcessID(job_qeue , (job_block->block)->pid);
	}

	return info;
}