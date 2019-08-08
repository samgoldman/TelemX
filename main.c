#include "taskManager.h"
#include <time.h>

int main(int argc, char *argv[])
{
	uint32_t tick = 0;

	while (1) 
	{
		taskManager_run(tick);
		tick += 1;

		clock_t start_time = clock();

		while(clock() - start_time < 1) {}

		if (tick > 499) {
			tick = 0;
		}
	}		
}

void *main_p = &main;
