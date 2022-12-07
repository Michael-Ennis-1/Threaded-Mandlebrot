#include "writeTask.h"

// Write a task to a TGA file with a given name
void writeTask::run()
{
	// Beginning of Semaphore loop
	// This loop uses a Semaphore's function of passing over the wait() function only if it's internal counter is higher than 0. It then decrements
	// the total_ counter, until it reaches 0 then begins the write.tga function. If it does not recieve enough signals, it will not start.
	while (total_ > 0)
	{
		s_->wait();
		total_--;
	}

	cout << "Creating the TGA file" << "\n";

	ofstream outfile(filename_, ofstream::binary);

	uint8_t header[18] = {
		0, // no image ID
		0, // no colour map
		2, // uncompressed 24-bit image
		0, 0, 0, 0, 0, // empty colour map specification
		0, 0, // X origin
		0, 0, // Y origin
		WIDTH & 0xFF, (WIDTH >> 8) & 0xFF, // width
		HEIGHT & 0xFF, (HEIGHT >> 8) & 0xFF, // height
		24, // bits per pixel
		0, // image descriptor
	};
	outfile.write((const char*)header, 18);

	for (int y = 0; y < HEIGHT; ++y)
	{
		for (int x = 0; x < WIDTH; ++x)
		{
			uint8_t pixel[3] = {
				(*pointer_)[y][x] & 0xFF, // blue channel
				((*pointer_)[y][x] >> 8) & 0xFF, // green channel
				((*pointer_)[y][x] >> 16) & 0xFF, // red channel
			};
			outfile.write((const char*)pixel, 3);
		}
	}

	outfile.close();
	if (!outfile)
	{
		// An error has occurred at some point since we opened the file.
		cout << "Error writing to " << filename_ << endl;
		exit(1);
	}
	cout << "\n" << "Finished creating TGA file" << "\n";
}

// This was slightly adapted from the original http://www.gamers.org/dEngine/quake3/TGA.txt