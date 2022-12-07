#pragma once
#include "task.h"
#include <iostream>
#include "Semaphore.h"
#include <fstream>

using std::ofstream;

class writeTask : public Task
{
public:
	// Takes in a pointer to a semaphore, a total(for number of tasks), a filename and a pointer to a 2d array, where the image is stored
	writeTask(Semaphore *s, int total, const char* filename, uint32_t(*pointer)[1200][1920])
		: s_(s), total_(total), filename_(filename), pointer_(pointer)
	{
	}

	void run();
private:
	// Stores pointers to the original semaphore and 2d Image array defined in main.
	Semaphore* s_;
	uint32_t(*pointer_)[1200][1920];

	// Stores the filename and the total number of tasks.
	const char* filename_;
	int total_;

	const int WIDTH = 1920;
	const int HEIGHT = 1200;
};
// Slight variation from the original "Task" class, adding in all the appropriate variables to pass through to the write.tga function. Also
// includes a Semaphore, to make sure that write.tga only runs when all the other threads are finished running their Mandlebrot functions.