#ifndef process_h
#define process_h

#define burst_time 0
#define remaining_time 1
#define arival_time 2
#define start_time 3
#define end_time 4



//Process as an individual entity
typedef struct process_block{

	int pid;
	int info[5];
	// 0 burst_time
	// 1 remtime
	// 2 arival time
	// 3 start time
	// 4 end time
	int priority;
}process_block;

process_block *getProcessBlock(int pid,int bt,int at ,int priority); 
int displayProcessBlock(process_block *);
//===================================================================//

//Process list or table structure
typedef struct PROCESS_LIST
{
	process_block *block;
	struct PROCESS_LIST *next;
}PROCESS_LIST;
/////////////////////////////////

int addToProcessList(PROCESS_LIST **,int , int ,int , int);
int displayProcessList(PROCESS_LIST *pl);
//delete entire process linked list
int deleteProcessList(PROCESS_LIST **pl);
//delete a single process of particular PID
int *deleteProcessID(PROCESS_LIST **pl,int pid);
// pops of the first process subroutine for FCFS and others like it
int *dequeProcess(PROCESS_LIST **process);
// view active block of process list
int viewActiveBlock(PROCESS_LIST *block);
#endif	