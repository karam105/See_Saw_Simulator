#include <iostream>
#include <pthread.h>
#include <mutex>
#include <condition_variable>
#include <semaphore.h>

using namespace std;

double fredHeight = 1;
double wilmaHeight = 7;

sem_t semaphore1;
sem_init(&semaphore1, 0, 0); //error

void *fredSee(void *param);
void *wilmaSaw(void *param);

int main()
{
  pthread_t thread1;
  pthread_t thread2;

  pthread_create(&thread1, NULL, fredSee, NULL);
  pthread_create(&thread2, NULL, wilmaSaw, NULL);

  pthread_join(thread1, NULL);
  pthread_join(thread2, NULL);

  return 0;
}

void *fredSee(void *param)
{
  while (fredHeight < 7)
  {
    fredHeight++;
    wilmaHeight--;
    cout << "Fred's Height: " << fredHeight << endl;
    cout << "Wilma's Height: " << wilmaHeight << endl;
  }
  cout << "Going down..." << endl;
  cout << endl;
  pthread_exit(NULL);
}

void *wilmaSaw(void *param)
{
  while (fredHeight > 1)
  {
    wilmaHeight = wilmaHeight + 1.5;
    fredHeight = fredHeight - 1.5;
    cout << "Fred's Height: " << fredHeight << endl;
    cout << "Wilma's Height: " << wilmaHeight << endl;
  }
  cout << "Going up..." << endl;
  cout << endl;
  pthread_exit(NULL);
}
