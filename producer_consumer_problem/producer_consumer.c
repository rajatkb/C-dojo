// Solves the problem of multiple producer and consumers
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <semaphore.h>
#include "buffer.h"

// for mutual exclusion between all process.
// i.e no two threads can run together
// every thread must be exclusive
pthread_mutex_t lock;

// semaphors for mutual exclusion of producer and consumer
// i.e not consuming when it souldnt
// not producing when it shouldnt

sem_t empty; // 0 when buffer is empty
sem_t full; // 0 when buffer is full 

int init_shared()
{
	pthread_mutex_init(&lock , NULL);	
	sem_init(&empty,0 , 0);
	sem_init(&full,0 ,BUFFER_SIZE);
}

// variable turn for ensuring that after every producer there is a conumer running
// though which one NO GARAUNTEE !!
#define producer 0
#define consumer 1
static int turn=producer;

// We need to cancel of all the threads after some time then well
// we can use a cooperative method of doing so , again ensuring no data concurrently accessing it
static int QuitFlag = 0;
static pthread_mutex_t QuitMutex = PTHREAD_MUTEX_INITIALIZER;

void setQuitFlag( void )
{
    pthread_mutex_lock( &QuitMutex );
    QuitFlag = 1;
    pthread_mutex_unlock( &QuitMutex );
}

int shouldQuit( void )
{
    int temp;
    pthread_mutex_lock( &QuitMutex );
    temp = QuitFlag;
    pthread_mutex_unlock( &QuitMutex );
    return temp;
}
// ensuring multiple thread not reading wierd values so ... 
// mutex locks for reads and write in it

#define max_data 100

// producer
void *producer_thread(void *arg)
{	
	int thread_number = *((int *)arg);
	while(!shouldQuit())
	{	
		while(turn == consumer);
		sem_wait(&full);
			pthread_mutex_lock(&lock);
			{	
				int temp = rand()%max_data;
				insert_buffer(temp);
				printf("Produced from %d : %d ", thread_number , temp);
				display_buffer();
				printf("\n");
				turn = consumer;
			}
			pthread_mutex_unlock(&lock);
		sem_post(&empty);	
	}
	// Well this is done
	// because sometimes it might happen that a producer was to give chance to a consumer
	// but since it ends it never happen give it so
	// the underlying code is to fix it
	pthread_mutex_lock(&lock);
		turn = consumer;
	pthread_mutex_unlock(&lock);	
}

// consumer
void *consumer_thread(void *arg)
{	
	int thread_number = *((int *)arg);
	while(!shouldQuit())
	{
		while(turn == producer);
		sem_wait(&empty);
			pthread_mutex_lock(&lock);
			{	
				int temp = remove_buffer();
				printf("Consumed from %d : %d ", thread_number , temp);
				display_buffer();
				printf("\n");
				turn = producer;
			}
			pthread_mutex_unlock(&lock);
		sem_post(&full);
	}
	// same as above reason
	pthread_mutex_lock(&lock);
		turn = producer;
	pthread_mutex_unlock(&lock);
}


int wait_and_kill(pthread_t *producer_threadID ,int max_producer_thread, pthread_t *consumer_threadID ,int max_consumer_thread)
{
	for(int i=0; i < max_producer_thread ; i++)
		pthread_join(producer_threadID[i], NULL);

	for(int i=0; i < max_consumer_thread ; i++)
		pthread_join(consumer_threadID[i], NULL);
	sleep(1);
}


int main(int argc , char *argv[])
{

	if(argc < 3)
	{
		printf("err: NOT ENOUGH ARGUEMENTS !!\n./name wait_time_seconds producer consumer\n");
		exit(0);
	}

	srand(time(NULL));
	int exec_time = atoi(argv[1])-1 ;
	int max_consumer_thread = atoi(argv[3]);
	int max_producer_thread = atoi(argv[2]);
	
	// initialising buffer with all zeroes and settin up counter=-1
	init_buffer();

	// intialising mutex and the semaphors 
	init_shared();


	// starting up the threads
	pthread_t producer_threadID[max_producer_thread];
	pthread_t consumer_threadID[max_consumer_thread];

	for(int i=0; i < max_producer_thread ; i++)
		{	
			int temp = i; // temp since otherwise i changes even before reading in the thread
			pthread_create( &producer_threadID[temp], NULL, producer_thread, (void *)&temp);
		}	
	
	for(int k=0; k < max_consumer_thread ; k++)
		{
			int temp = k; // same reason as above
			pthread_create( &consumer_threadID[temp], NULL, consumer_thread, (void *)&temp);
		}	

	sleep(exec_time);

	setQuitFlag();

	wait_and_kill(producer_threadID , max_producer_thread , consumer_threadID , max_consumer_thread);
	
	exit(0);
	return 0;
}