#include "mandlebrotTask.h"

void mandlebrotTask::run()
{
	// These variables are used to create a position for the thread to run from, allowing for multiple threads to work on the same mandlebrot task.
	// The h allows for figuring out what y coord to work on, and offput is the amount of offput per division, which is then multiplied by the number
	// of the threadtask.
	int h, offput;
	offput = HEIGHT / divisions_;
	h = threadNum_ * offput;

	for (int repeat = 0; repeat < reps_; repeat++)
	{
		h = h + (HEIGHT / divisions_);

		// Start timing
		the_clock::time_point start = the_clock::now();

		for (int y = 0; y < h; ++y)
		{
			for (int x = 0; x < WIDTH; ++x)
			{
				// Work out the point in the complex plane that
				// corresponds to this pixel in the output image.
				complex<double> c(left_ + (x * (right_ - left_) / WIDTH),
					top_ + (y * (bottom_ - top_) / HEIGHT));

				// Start off z at (0, 0).
				complex<double> z(0.0, 0.0);

				// Iterate z = z^2 + c until z moves more than 2 units
				// away from (0, 0), or we've iterated too many times.
				int iterations = 0;
				while (abs(z) < 2.0 && iterations < MAX_ITERATIONS)
				{
					z = (z * z) + c;

					++iterations;
				}

				if (iterations == MAX_ITERATIONS)
				{
					// z didn't escape from the circle.
					// This point is in the Mandelbrot set.
					//image[y][x] = 0x000000; // black
					(*pointer_)[y][x] = 0x2F56E9; // blue
				}
				else
				{
					// z escaped within less than MAX_ITERATIONS
					// iterations. This point isn't in the set.
					(*pointer_)[y][x] = 0xFFFFFF; // white
				}
			}
		}

		// Stop timing
		the_clock::time_point end = the_clock::now();

		auto time_taken = duration_cast<milliseconds>(end - start).count();
		cout << "Computing the Mandelbrot set " << repeat + threadNum_ + 1 << " took " << time_taken << " ms." << endl;
	}

	// Notifys the semaphore when the task is complete, meaning that the write.tga function cannot run until all tasks are complete.
	s_->notify();
}
