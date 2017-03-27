#include <iostream>
#include <pthread.h>
#include <mutex>
#include <condition_variable>

using namespace std;

mutex mtx;
condition_variable cv;

double fredHeight = 1;
double wilmaHeight = 7;
int semaphore1 = 0;
int semaphore2 = 1;

void *fredSee(void *param);
void *wilmaSaw(void *param);
void decrement();
unique_lock<mutex> lck(mtx);


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

void wait(S)
{
  while (s <= 0)
    ;
  s--;
}
void signal(S)
{
  s++;
}
