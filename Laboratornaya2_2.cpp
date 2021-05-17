#include <iostream>
#include <semaphore.h>
#include <windows.h>
#define HAVE_STRUCT_TIMESPEC
#include <pthread.h>

using namespace std;

bool flag = true;
sem_t sem;

void* func1(void* args) {
	while (flag) {
		int rv = sem_trywait(&sem);
		if (rv != 0) {
			Sleep(1);
		}
		else {
			sem_trywait(&sem);
			for (int i = 0; i < 10; i++) {
				if (!flag) {
					break;
				}
				std::cout << "1";
				std::cout.flush();
				Sleep(1);
			}
			sem_post(&sem);
			Sleep(1);
		}
		return NULL;
	}
}
void* func2(void* args) {
	while (flag) {
		int rv = sem_trywait(&sem);
		if (rv != 0) {
			Sleep(1);
		}
		else {
			sem_trywait(&sem);
			for (int i = 0; i < 10; i++) {
				if (!flag) {
					break;
				}
				std::cout << "2";
				std::cout.flush();
				Sleep(1);
			}
			sem_post(&sem);
			Sleep(1);
		}
		return NULL;
	}
}

int main()
{
	sem_init(&sem, 0, 1);
	int arg = 10;
	pthread_t thread1, thread2;
	pthread_create(&thread1, NULL, func1, &arg);
	pthread_create(&thread2, NULL, func2, &arg);

	getchar();

	flag = false;
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	sem_destroy(&sem);
	return 0;
}