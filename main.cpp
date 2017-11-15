#include <iostream>
#include <sstream>
#include <sys/stat.h>
#include <stdio.h>
#include <cassert>
#include <cstring>
#include "Global.h"
#include "Frame.h"
#include "Rectangle.h"

Frame frame;
int main(int argc, char * argv[]) {
	const char * cmd =
		"ffmpeg\\bin\\ffmpeg.exe "
		"-y                  "
		"-hide_banner        "
		"-f rawvideo         " // input to be raw video data
		"-pixel_format rgb24 "
		"-video_size 720x480 "
		"-r 60               " // frames per second
		"-i -                " // read data from the standard input stream
		"-pix_fmt yuv420p    " // to render with Quicktime
		"-vcodec mpeg4       "
		"-an                 " // no audio
		"-q:v 5              " // quality level; 1 <= q <= 32
		"output.mp4          ";

#ifdef _WIN32
	FILE * pipe = _popen(cmd, "wb");
#else
	FILE * pipe = popen(cmd, "w");
#endif
	if (pipe == 0) {
		std::cout << "error: " << strerror(errno) << std::endl;
		return 1;
	}

	Rectangle *rec1; 
	rec1 = new Rectangle(30, 50); // white
	rec1->setColor(255, 255, 255); 
	rec1->startingPt(0, 0); 

	Rectangle *rec2; 
	rec2 = new Rectangle(30, 40); // red
	rec2->setColor(255, 0, 0);
	rec2->startingPt(250, 400); 


	int num_frames = duration_in_seconds * frames_per_second;
	for (int i = 0; i < num_frames; ++i) {
		double time_in_seconds = i / frames_per_second; 
		rec1->draw_frame(time_in_seconds); 
		rec2->draw_frame(time_in_seconds); 
		frame.write(pipe);
		frame.clear(); 
	}
	fflush(pipe);
#ifdef _WIN32
	_pclose(pipe);
#else
	pclose(pipe);
#endif
	std::cout << "num_frames: " << num_frames << std::endl;
	std::cout << "Done." << std::endl;
	return 0;
}