#ifndef FARM_H
#define FARM_H

#include "task.h"
#include <queue>
#include <vector>
#include <thread>
#include <mutex>
#include <iostream>

using std::queue;
using std::vector;
using std::thread;
using std::mutex;
using std::cout;

/** A collection of tasks that perform in parallel. */
class Farm {
public:

	/** Add a task to the farm.
		The task will be deleted once it has been run. */
	void add_task(Task* task);

	/** Run all the tasks in the farm.
		This method only returns once all the tasks in the farm
		have been completed. */
	void runLamda();

	/** Tell the farm how many threads they should run*/
	void threadNumber(int t);

private:
	queue<Task*> taskQueue;
	mutex taskMutex;

	vector<thread*> threads;

	//bool WorkerIsRunning = true;
	//bool speak = false;

	int maxCPUThreads;
};

#endif
