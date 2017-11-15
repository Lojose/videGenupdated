#include <iostream>
#include "Rectangle.h"
#include "Frame.h"
#include "Global.h"

extern Frame frame;
Rectangle::Rectangle(int h, int w): h(h), w(w) {}

void Rectangle::startingPt(int x, int y) {
	this->x = x; 
	this->y = y; 
}

void Rectangle::setColor(byte r, byte g, byte b) {
	this->r = r; 
	this->g = g; 
	this->b = b; 
}

void Rectangle::draw_rect(int x, int y, int w, int h, byte r, byte g, byte b) {
	if (frame.isOutside(&x, &y)) return;
	int x0 = x;
	int x1 = x + w;
	int y0 = y;
	int y1 = y + h;
	frame.clamp(&x0, &y0);
	frame.clamp(&x1, &y1);
	for (int y = y0; y < y1; ++y) {
		for (int x = x0; x < x1; ++x) {
			frame.setPixel(x, y, r, g, b);
		}
	}
}

/*void Rectangle::Recc(Rectangle *rectangle) {
	rectangles.push_back(rectangle);
}
*/
void Rectangle::draw_frame(double t){ 
	const double pps = 80; // pixels per second 
	draw_rect(x + t*pps, y + t*pps, w, h, r, g, b);
}