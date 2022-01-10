#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
static int glob = 0;

pthread_mutex_t mtx;
static void *AddTwo(void *arg)
{
	int loops = *((int *)arg);
	int loc,j,s;
	s = pthread_mutex_init(&mtx,NULL);
	for(int j = 0;j<loops;j++)
	{
		s = pthread_mutex_lock(&mtx);
		glob += 2;
		s = pthread_mutex_unlock(&mtx);
	}
	return NULL;
}
static void *SubTwo(void *arg)
{
	int loops = *((int *)arg);
	int loc,j,s;
	s = pthread_mutex_init(&mtx,NULL);
	for(int j = 0;j<loops;j++)
	{
		s = pthread_mutex_lock(&mtx);
		glob -= 2;
		s = pthread_mutex_unlock(&mtx);
	}
	return NULL;
}
int main(int argc,char *argv[])
{
	pthread_t t1,t2,t3;
	int loops,s;
	loops = atoi(argv[1]);
	s = pthread_create(&t1,NULL,AddTwo,&loops);
	s = pthread_create(&t2,NULL,AddTwo,&loops);
	s = pthread_create(&t3,NULL,SubTwo,&loops);
	s = pthread_join(t1,NULL);
	s = pthread_join(t2,NULL);
	s = pthread_join(t3,NULL);
	printf("glob = %d\n",glob);
	s = pthread_mutex_destroy(&mtx);
	return 0;
}
