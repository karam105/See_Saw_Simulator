#include <iostream>
#include <pthread.h>
#include <mutex>
#include <condition_variable>
#include <unistd.h>

using namespace std;

double fredHeight = 1;
double wilmaHeight = 7;
int fredSem = 1;
int wilmaSem = 1;
int value = 1;

void *fredSee(void *param);
void *wilmaSaw(void *param);
void fredWait();
void wilmaWait();
void fredSignal();
void wilmaSignal();

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
  while (value <= 10)
  {
    fredWait();
    while (fredHeight < 7)
    {
      cout << "Fred's Height: " << fredHeight << endl;
      cout << "Wilma's Height: " << wilmaHeight << endl;
      fredHeight++;
      wilmaHeight--;
      sleep(1);
    }
    cout << "Going down..." << endl;
    cout << endl;
    wilmaSignal();
  }
  pthread_exit(NULL);
}

void *wilmaSaw(void *param)
{
  while (value <= 10)
  {
    wilmaWait();
    while (fredHeight > 1)
    {
      cout << "Fred's Height: " << fredHeight << endl;
      cout << "Wilma's Height: " << wilmaHeight << endl;
      wilmaHeight = wilmaHeight + 1.5;
      fredHeight = fredHeight - 1.5;
      sleep(1);
    }
    cout << "Going up..." << endl;
    cout << endl;
    fredSignal();
    value++;
  }
  pthread_exit(NULL);
}

void fredWait()
{
  while(fredSem <= 0);
  fredSem--;
}

void wilmaWait()
{
  while(wilmaSem <= 0);
  wilmaSem--;
}

void fredSignal()
{
  fredSem++;
}

void wilmaSignal()
{
  wilmaSem++;
}
