// Based on Mandelbrot set example
// Adam Sampson <a.sampson@abertay.ac.uk>
// Adapted by Michael Ennis <1902141@uad.ac.uk> Student Number 1902141

// Creates the Librarys required
#include <chrono>
#include <cstdint>
#include <cstdlib>
#include <complex>
#include <fstream>
#include <iostream>
#include <thread>
#include "task.h"
#include "farm.h"
#include "mandlebrotTask.h"
#include "writeTask.h"
#include "Semaphore.h"

using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::cout;
using std::cin;
using std::endl;
using std::ofstream;

// Define the alias "the_clock" for the clock type we're going to use.
typedef std::chrono::steady_clock the_clock;

// The size of the image to generate.
const int WIDTH = 1920;
const int HEIGHT = 1200;

// The number of times to iterate before we assume that a point isn't in the Mandelbrot set.
const int MAX_ITERATIONS = 500;

// The image data.
// Each pixel is represented as 0xRRGGBB.
uint32_t image[HEIGHT][WIDTH];

int main(int argc, char *argv[])
{
	// Defines the Task Based Farm pattern that is used in this mandlebrot set.
	Farm f;

	// Defines a pointer to the original image, and sets it equal to the reference of the original, allowing it to be passed into a function.
	uint32_t(*pointer)[1200][1920];
	pointer = &image; 

	// Defines a semaphore, a semaphore pointer and sets the pointer of the semaphore to equal a reference to the original, allowing it to be passed
	// into a function.
	Semaphore sem;
	Semaphore* pSem;
	pSem = &sem;

	// Defines variables that are used in setting up the Mandlebrot
	int Tasks, maxThreads, Full;

	// Setting up Mandlebrot
	cout << "How many threads do you wish to use? Enter 0 for maximum" << "\n";
	cin >> maxThreads;
	cout << "How many tasks would you like, in multiples of 4?" << "\n";
	cin >> Tasks;
	cout << "And finally, would you like to use full mandlebrot or zoomed in? 1 for Full, 0 for Zoomed" << "\n";
	cin >> Full;
	cout << "Setting up Mandlebrot..." << "\n";

	// Inputs the amount of threads the user wishes to use
	f.threadNumber(maxThreads);

	// Sets up the number of tasks to put into the farm, in multiples of 4. This section is dedicated to the entire mandlebrot, whilst the other is
	// for only the zoomed in part of mandlebrot
	Tasks = Tasks * 4;
	if (Full == 1)
	{
		for (int i = 0; i < Tasks; i++)
		{
			f.add_task(new mandlebrotTask(-2.0, 1.0, 1.125, -1.125, i, 1, Tasks, pointer, pSem));
		}
	}
	if (Full == 0)
	{	
		for (int i = 0; i < Tasks; i++)
		{
			f.add_task(new mandlebrotTask(-0.751085, -0.734975, 0.118378, 0.134488, i, 1, Tasks, pointer, pSem));
		}
	}

	// Adds the writeTask to the task farm, can put this anywhere in the task queue, but saves time if put at the end
	f.add_task(new writeTask(pSem, Tasks, "output.tga", pointer));

	cout << "Finished setting up" << "\n";
	cout << "Running Mandlebrot..." << "\n";

	// Start timing
	the_clock::time_point start = the_clock::now();

	f.runLamda();

	// Stop timing
	the_clock::time_point end = the_clock::now();

	// Compute the difference between the two times in milliseconds
	auto time_taken = duration_cast<milliseconds>(end - start).count();
	cout << "Computing Mandelbrot overall took " << time_taken << " ms." << endl;
	cout << "Enter any number to end" << endl;
	cin >> maxThreads;

	return 0;
}