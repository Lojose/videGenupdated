#pragma once
#include <vector>
#include "Global.h"
class Rectangle {
public:
	Rectangle(double h, double w, double x, double y); 
	void draw_rect(); 
	void setColor(byte r, byte g, byte b); 
	void setVelocity(double dx, double dy); 
	void update(double dt); 
private:
	byte r; 
	byte g; 
	byte b;  
	double h;
	double w;  
	double dx; 
	double dy; 
	double x; 
	double y; 

};