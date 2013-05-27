#include <stdio.h>
#include <pthread.h>

static int n = 0;
static pthread_mutex_t Mutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t Cond = PTHREAD_COND_INITIALIZER;
static const int MAX = 6;

void *func(void *arg)
{
  int id = (int)arg;

  //printf("thread %d entering ...\n", id);
  
  pthread_mutex_lock(&Mutex);    
  while(n < MAX)
  {
    printf("thread %d, %d\n", id, n);
    n++;
    pthread_cond_signal(&Cond);
    pthread_cond_wait(&Cond, &Mutex);
  }
  pthread_mutex_unlock(&Mutex);
  pthread_cond_signal(&Cond);

  printf("thread %d exiting ...\n", id);

  return NULL;
}

static const int MAX_THREADS = 2;

int main()
{
  pthread_t threads[MAX_THREADS];
  int i = 0;

  for(i = 0; i < MAX_THREADS; i++)
    {
      pthread_create(&threads[i], NULL, func, (void *)i);
    }

  for(i = 0; i < MAX_THREADS; i++)
    {
      pthread_join(threads[i], NULL);
    }

  pthread_cond_destroy(&Cond);
  pthread_mutex_destroy(&Mutex);

  return 0;
}
