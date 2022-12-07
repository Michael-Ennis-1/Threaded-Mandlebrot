#pragma once

#include <chrono>
#include <cstdint>
#include <cstdlib>
#include <complex>
#include <fstream>
#include <iostream>
#include <thread>
#include "task.h"
#include "Semaphore.h"

using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::complex;
using std::cout;
using std::endl;
using std::ofstream;

/** Task that runs a mandlebrot slice on the Y axis */
class mandlebrotTask : public Task
{
public:
	// Slices the mandlebrot up along the Y axis, using the threadNum and Divisions to workout the offput for how far down the Y axis the next thread should begin.
	mandlebrotTask(double left, double right, double top, double bottom, int threadNum, int reps, int divisions, uint32_t(*pointer)[1200][1920], Semaphore *s)
		: left_(left), right_(right), top_(top), bottom_(bottom), threadNum_(threadNum), reps_(reps), divisions_(divisions), pointer_(pointer), s_(s)
	{
	}

	// Runs the mandlebrot slice
	void run();

private:
	// Defines constant variables relating to the
	const int WIDTH = 1920;
	const int HEIGHT = 1200;
	const int MAX_ITERATIONS = 500;

	// Defines the clock for later use
	typedef std::chrono::steady_clock the_clock;

	// Takes in variables from the Constructor for later use
	double left_, right_, top_, bottom_;
	int threadNum_, reps_, divisions_;

	// Defines a 2D array pointer, same size as the original image2D array
	uint32_t(*pointer_)[1200][1920];

	// Defines a semaphore pointer to use in the mandlebrot task
	Semaphore* s_;
};