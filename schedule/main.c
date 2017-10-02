#include <stdio.h>
#include <stdlib.h>
#include "process.h"
#include "schedule.h"
#include <time.h>

// Get process at 0 arrival time i.e at same time
// also priority is set to 0 for highest at all time

// arrival time same at 0

PROCESS_LIST  *generateRandomJobs(int count)
{
	srand(time(NULL));
	PROCESS_LIST *job_queue=NULL;
	for(int i=0;i < count ; i++)
	{
		addToProcessList(&job_queue,i, rand()%10+1, 0 , rand()%5);
	}

	return job_queue;
}

int freeInfo(int **info , int numberOfJobs)
{
	for(int i=0; i< numberOfJobs ; i++)
		free(info[i]);
	free(info);	
}

int displayAccountingInfo(int **info, int jobs , int timeUnit)
{

// 	burst_time 0
// 	remaining_time 1
// 	arival_time 2
// 	start_time 3
//  end_time 4
	for(int i=0;i< jobs ; i++)
	{
		printf("pid: %d arrival_time: %d burst_time: %d start_time: %d end_time: %d \n", i, info[i][arival_time],info[i][burst_time], info[i][start_time], info[i][end_time]);
	}

	float throughPut = (float)timeUnit / (float)jobs;
	float average_wait_time = 0;

	for(int i=0; i < jobs ; i++)
	{
		average_wait_time += (info[i][end_time] - info[i][arival_time]) - info[i][burst_time];
	}

	average_wait_time /= jobs; 

	printf("\n ThroughPut : %f  average_wait_time : %f \n", throughPut , average_wait_time);
}

int main()
{
	int numberOfJobs;
	int quanta=1;
	printf("Enter the number of Jobs: \n");
	scanf("%d", &numberOfJobs);
	printf("Enter quanta for round robin: \n");
	scanf("%d", &quanta);

	// get list of randomly generated jobs
	PROCESS_LIST *job_queue=generateRandomJobs(numberOfJobs);
	// jobs_qeue : is the list of job and will allow us for scheduling

	
	
	// accounting table array
	int **info=(int **)malloc(sizeof(int *)*numberOfJobs);
	// accounting
	
	// temp variables used repeatedly
	int pid=-1;
	int flag=0;
	//

	int timeUnit = 0;

	// job block is the block of job that is being used in the job_qeue or list
	// job_qeue holds the first node and is used for reference job block changes constantly
	PROCESS_LIST *job_block=job_queue;
	while(1){

		printf(">>>>>>>>>>>>>>>> time unit : %d <<<<<<<<<<<<<<<<<<<<<\n", timeUnit);
		displayProcessList(job_queue);

		
		pid = (job_block->block)->pid;
		info[pid]=delete_process_if_over(&job_queue, job_block , timeUnit);
		// break of the process if job qeue is empty duhh!!!!
		if(job_queue == NULL)
			{	
				break;
				timeUnit++;
			}
		// buh bye !! breaking off	
//>>>>>>>>>>>>>>>>>>>>> FCFS <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<//
		
		// if(info[pid] != NULL)  // THIS WOULD MEAN THAT THE LAST OR THE CURRENT JOB ENDED WITH AN ACCOUNTING INFO GIVEN
		// 	job_block = schedule_fcfs(job_queue); // this is only used in NON PREEMPTIVE METHODS SINCE
//			// IN PREEMTPIVE METHODS THE SCHEDULER IS REPEATEDLY CALLED. REPEATEDLY
		
//>>>>>>>>>>>>>>>>>>>>>> ROUND ROBIN <<<<<<<<<<<<<<<<<<<<<<<<<<//

		if(info[pid] != NULL || ((timeUnit%quanta)==0) && timeUnit!=0) // Either the time quanta is filled or the last process was just deleted
		{		
			printf("\nSwitching Job\n");
			job_block = schedule_round_robin(job_block , job_queue); // in that case call the scheduler

		}	

// //>>>>>>>>>>>>>>>>>>>>>>>SJF<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<//

// 		if(info[pid] != NULL || timeUnit==0)
// 			job_block = schedule_shortest_job(job_queue);

// >>>>>>>>>>>>>>>>>>>>>>>> SRTF : basically calling the SJF method every frigging time. <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> although in this one i have kept burst time and remaining time separately so ya not an issue sepparate functions			

//		job_block = schedule_shortest_remainingtime_job(job_queue);	

// >>>>>>>>>>>>>>>>>>>>>>>> Priority scheduling <<<<<<<<<<<<<<<<<<<<//		


		viewActiveBlock(job_block);

		if(job_block != NULL)
		{
			setStartTime( (job_block->block), timeUnit );
			updateJob((job_block->block),1);
		}
		timeUnit++;
	}
	
	printf("\naccounting :\n");
	displayAccountingInfo(info , numberOfJobs , (--timeUnit));


	// deleting all accounting info and job qeues
	freeInfo(info, numberOfJobs);	
	deleteProcessList(&job_queue);
}
