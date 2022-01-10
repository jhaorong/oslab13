#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>
static int glob = 1;

pthread_mutex_t mtx;
pthread_cond_t cond1,cond2,cond3;

//static int avail = 0;
static void *One(void *arg)
{
	int loops = *((int *)arg);
	int s,c;
	//s = pthread_mutex_init(&mtx,NULL);
	for(int i=0;i < loops; i++)
	{
		s = pthread_mutex_lock(&mtx);
		if(glob != 1)
		{
			s = pthread_cond_wait(&cond1,&mtx);
		}
		
		printf("%d\t",glob);
		glob = 3;
		c = pthread_cond_signal(&cond2);
		s = pthread_mutex_unlock(&mtx);
		
	}
	return NULL;
}
static void *Three(void *arg)
{
	int loops = *((int *)arg);
	int s,c;
	//s = pthread_mutex_init(&mtx,NULL);
	for(int i=0;i < loops;i++)
	{
		s = pthread_mutex_lock(&mtx);
		if(glob != 3)
		{
			s = pthread_cond_wait(&cond2,&mtx);
		}
		
		printf("%d\t",glob);
		glob = 5;
		c = pthread_cond_signal(&cond3);
		s = pthread_mutex_unlock(&mtx);
		
	}
	return NULL;
}
static void *Five(void *arg)
{
	int loops = *((int *)arg);
	int s,c;
	//s = pthread_mutex_init(&mtx,NULL);
	for(int i=0;i < loops;i++)
	{
		s = pthread_mutex_lock(&mtx);
		if(glob != 5)
		{
			s = pthread_cond_wait(&cond3,&mtx);
		}
		
		printf("%d\t",glob);
		glob = 1;
		c = pthread_cond_signal(&cond1);
		s = pthread_mutex_unlock(&mtx);
		
	}
	return NULL;
}
int main(int argc,char *argv[])
{
	pthread_t t1,t2,t3;
	int loops,s;
	loops = atoi(argv[1]);
	s = pthread_mutex_init(&mtx,NULL);
	s = pthread_cond_init(&cond1,NULL);
	s = pthread_cond_init(&cond2,NULL);
	s = pthread_cond_init(&cond3,NULL);
	s = pthread_create(&t1,NULL,One,&loops);
	s = pthread_create(&t2,NULL,Three,&loops);
	s = pthread_create(&t3,NULL,Five,&loops);
	sleep(1);
	pthread_cond_signal(&cond1);
	s = pthread_join(t1,NULL);
	s = pthread_join(t2,NULL);
	s = pthread_join(t3,NULL);
	s = pthread_mutex_destroy(&mtx);
	s = pthread_cond_destroy(&cond1);
	s = pthread_cond_destroy(&cond2);
	s = pthread_cond_destroy(&cond3);
	return 0;
}
