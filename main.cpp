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

	Rectangle rec1 (30, 55, 0, 0);
	rec1.setVelocity(10, 10); 

	Rectangle rec2 (30, 55, 150, 150);
	rec2.setVelocity(10, 10); 

	Rectangle rec3(30, 55, 200, 200);
	rec2.setVelocity(10, 10);

	int num_frames = duration_in_seconds * frames_per_second;
	for (int i = 0; i < num_frames; ++i) {
		double dt = i / frames_per_second;
		if (dt > 1.0 / 60.0) {
			rec1.setColor(255, 255, 255); // white 
			rec1.update(dt); 
			rec1.draw_rect(); 

			rec2.setColor(255, 0, 0); // red 
			rec2.update(dt);
			rec2.draw_rect();

			rec3.setColor(255, 255, 0); // yellow 
			rec3.update(dt);
			rec3.draw_rect();


			frame.write(pipe); 
			frame.clear();
		}
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