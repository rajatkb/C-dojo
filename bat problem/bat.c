#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <semaphore.h>
#include <ctype.h>


#define number_of_crossings 4

#define TRUE 1
#define FALSE 0

// THE MUTEXES USED FOR LOCKING EACH OF THE particular resources
// in this case it is the crossing point. i.e 4 crossing points
// hence 4 crossing points . Named according to the direction of first arrival 
#define EAST 0
#define NORTH 1
#define WEST 2
#define SOUTH 3
const char direction_array[]={'E','N','W','S'};

int direction_int(char ch)
{
	switch(ch)
	{
		case 'e':	return EAST;
		case 'n':	return NORTH;
		case 'w':	return WEST;
		case 's':	return SOUTH;
		default :	return 0;
	}
}

pthread_mutex_t resource_crossing[number_of_crossings]={PTHREAD_MUTEX_INITIALIZER , PTHREAD_MUTEX_INITIALIZER , PTHREAD_MUTEX_INITIALIZER , PTHREAD_MUTEX_INITIALIZER};
// muetex done
// indexing above started from east for programming convinience

// The condition variable for signaling the next thread waiting to access a nearby subsequent
// reource i.e the mutex lock 
pthread_cond_t cond_next_signal[number_of_crossings] = {PTHREAD_COND_INITIALIZER,PTHREAD_COND_INITIALIZER,PTHREAD_COND_INITIALIZER,PTHREAD_COND_INITIALIZER};
//

// conditional variable to qeue up the threads from one direction
pthread_cond_t thread_qeue[number_of_crossings] = {PTHREAD_COND_INITIALIZER,PTHREAD_COND_INITIALIZER,PTHREAD_COND_INITIALIZER,PTHREAD_COND_INITIALIZER};
pthread_mutex_t qeueLock[number_of_crossings]={PTHREAD_MUTEX_INITIALIZER , PTHREAD_MUTEX_INITIALIZER , PTHREAD_MUTEX_INITIALIZER , PTHREAD_MUTEX_INITIALIZER};;
int wait[number_of_crossings]={FALSE ,FALSE,FALSE,FALSE};
// bunch of conditionals required



//////////////////////////////////////////////////////////////////////////////////////////////////////

typedef struct data{
	int direction;
	int thread_number;
}data;


void *BAT(void *arg) // Each thread for carrying bat information. 
//i.e performing critical section task by doing lock on resource of single instance
{
	data dt = *((data *)arg); free(arg);
	int direction = dt.direction;

	// Aquired a lock and make this thread run only
	// rest all same DIRECTION bounded threads will wait since
	// each one is asked to wait 
	pthread_mutex_lock(&qeueLock[direction]);
	while(wait[direction])
	{
		pthread_cond_wait( &thread_qeue[direction], &qeueLock[direction]);
	}
	wait[direction]=TRUE;
	pthread_mutex_unlock(&qeueLock[direction]);
	// The thread just started
	printf("%d Arrived thread from %c \n" , dt.thread_number , direction_array[dt.direction]);

	// >>>>>>>>>>>>>>>>>> GETING FIRST RESOURCE LOCK <<<<<<<<<<<<<<<<<<<<<<<<<< //
	//pthread_cond_signal(&cond_next_signal[(direction+1)%number_of_crossings]);
	pthread_mutex_lock(&resource_crossing[direction]);
	//pthread_cond_wait(&cond_next_signal[direction],&resource_crossing[direction]); 
	// >>>>>>>>>>>>>>>>>>> BEFORE LEAVING GET ANOTHER LOCK <<<<<<<<<<<<<<<<<<<<//
	pthread_mutex_lock(&resource_crossing[(direction+1)%number_of_crossings]);
	// // Signal the incoming qeued threads in the same direction
	
	// spirudial wake in making -_-
	pthread_mutex_lock(&qeueLock[direction]);
	wait[direction]=FALSE;
	pthread_cond_signal( &thread_qeue[direction]);
	pthread_mutex_unlock(&qeueLock[direction]);
	//signalling qeued threads to come in

	// TASK DELAY of 1s
	sleep(1); 
	// >>>>>>>>>>>>>>>>>>>>>>>>>> THE MID GROUND STATE <<<<<<<<<<<<<<<<<<<<<<<///
	// LEAVING THE FIRST MUTEX ////////////////
	pthread_mutex_unlock(&resource_crossing[direction]);
	//pthread_cond_wait(&cond_next_signal[(direction+1)%number_of_crossings],&resource_crossing[(direction+1)%number_of_crossings]); 
	// LEAVING THE SECOND MUTEX
	pthread_mutex_unlock(&resource_crossing[(direction+1)%number_of_crossings]);


	printf("%d Leaving thread from %c \n" , dt.thread_number , direction_array[dt.direction]);
	
	
}

// a deadlock check for 
// 1. all the processes qeueing up for resource
pthread_mutex_t check_mutex=PTHREAD_MUTEX_INITIALIZER;

int check()
{
	pthread_mutex_lock(&check_mutex);
	int t= (wait[0] && wait[1] && wait[2] && wait[3]);
	pthread_mutex_unlock(&check_mutex);
	return t;
}

// int fix_wait_lock()
// {
// 	pthread_mutex_lock(&check_mutex);
// 	wait[NORTH]=TRUE;
// 	pthread_mutex_unlock(&check_mutex);
// }


void *MAN(void *arg)
{
	int wait_flag = 1;
	while(1)
	{
		if(check() && wait_flag)
		{
			printf("DEADLOCK DETECTED\n");
			wait_flag=0;
		}
		if(!check())
		{
			wait_flag=1;
		}
		
	}
}

// the thread to initialize and manege all the mishaps
void *BATMAN(void *arg) // bidirectional_autonomous_trolley_manager
//1. initializes th bat threads
//2. also initializes the manger thread
//3. Finally kills of manager when BATS are done
{
	char *sequence = (char *)arg;
	int seq_len = strlen(sequence);
 	
 	
 	////////////////////////////////////////////////////
	pthread_t man_thread;
	pthread_create(&man_thread, NULL , MAN , NULL);		


 	pthread_t *bat_threads = (pthread_t *)malloc(sizeof(pthread_t) * seq_len); 
 	data *dt;
	// start the threads with the necessary information
	for(int i=0; i < seq_len ; i++)
	{
		dt=(data *)malloc(sizeof(data));
		dt->direction = direction_int(sequence[i]);
		dt->thread_number=i+1;
		pthread_create(&bat_threads[i], NULL , BAT ,(void *)dt);
	}
	


	// wait for the threads to finish up the job
	for(int i=0; i < seq_len ; i++)
		pthread_join(bat_threads[i],NULL);

}

// INITIAIZATION AND DELETION OF SHARED RESOURCES
void init_shared_resource()
{
	pthread_mutex_init(&check_mutex , NULL);
	for(int i=0 ; i < number_of_crossings ; i++)
	{
		pthread_mutex_init(&resource_crossing[i],NULL);
		pthread_cond_init(&cond_next_signal[i],NULL);
		pthread_cond_init(&thread_qeue[i] , NULL);
		pthread_mutex_init(&qeueLock[i], NULL);
	}
}

void delete_shared_resource()
{
	pthread_mutex_destroy(&check_mutex);
	for(int i=0 ; i < number_of_crossings ; i++)
	{
		pthread_mutex_destroy(&resource_crossing[i]);
		pthread_cond_destroy(&cond_next_signal[i]);
		pthread_cond_destroy(&thread_qeue[i]);
		pthread_mutex_destroy(&qeueLock[i]);
	}		
}
// DONE




int main(int argc , char *argv[])
{

	if(argc < 2)
	{	
		printf(":enter directions\n");
		exit(0);
	}

	init_shared_resource();
	pthread_t bat_threadID;
	pthread_create(&bat_threadID ,NULL , BATMAN , argv[1]);
	pthread_join(bat_threadID, NULL);
	delete_shared_resource();	
	exit(0);
	return 0;
}