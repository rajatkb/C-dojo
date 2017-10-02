#ifndef schedule_h
#define schedule_h

int isFinished(process_block *blk);
int updateJob(process_block *blk , int quanta);
int setStartTime(process_block *blk , int startTime );



// list of schedulers // 
// 1. first come first serve 'process_block schedule_fcfs( job_qeue  )'
// 2. Round Robin 
// 3. SJF 
PROCESS_LIST *schedule_fcfs(PROCESS_LIST *job_qeue);
PROCESS_LIST *schedule_round_robin(PROCESS_LIST *job_block , PROCESS_LIST *job_qeue_head);
PROCESS_LIST *schedule_shortest_job(PROCESS_LIST *job_qeue);
PROCESS_LIST *schedule_shortest_remainingtime_job(PROCESS_LIST *job_qeue);

int *delete_process_if_over(PROCESS_LIST **job_qeue, PROCESS_LIST *job_block , int endTime);

#endif