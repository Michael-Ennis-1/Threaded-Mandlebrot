#include "farm.h"

// Adds a task to the task queue
void Farm::add_task(Task* task)
{
	taskQueue.push(task);
}

// Runs the task farm
void Farm::runLamda()
{
	for (int i = 0; i < maxCPUThreads; i++)
	{
		// Pushes a new thread back, with a thread task Lamda function
		threads.push_back(new thread([&] {
			while (taskQueue.size() > 0)
			{
				// Protects the taskqueue whilst the thread takes a task from the stack. Puts the task into a Task pointer, that the program can then run without
				// any interference with the original task stack, preventing deadlock from occuring.
				taskMutex.lock();
				Task* t = taskQueue.front();
				taskQueue.pop();
				taskMutex.unlock();
				t->run();
				delete t;

				if (taskQueue.empty() == true)
				{
					return;
				}

			}
			}));
	}

	// Joins all the threads after they are finished running.
	for (int i = 0; i < maxCPUThreads; i++)
	{
		threads[i]->join();
	}
}

// Takes in the amount of threads to use, if 0 then uses max threads available
void Farm::threadNumber(int t)
{
	if (t == 0)
	{
		maxCPUThreads = thread::hardware_concurrency();
	}
	else
	{
		maxCPUThreads = t;
	}
}