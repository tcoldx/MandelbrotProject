#include <iostream>
#include <SFML/Graphics.hpp> 
#include <vector>
#include "ComplexPlane.h"

using namespace sf;
using namespace std;


int deskHeight = (VideoMode::getDesktopMode().width) / 2; // gets width of screen
int deskWidth = (VideoMode::getDesktopMode().height) / 2; // gets height of the screen
VideoMode vm(deskHeight, deskWidth); // construct the mode for the graphics module
RenderWindow window(vm, "Mandelbrot", Style::Default); // constructed graphics module for the 2d drawings.

int main() {
 
	

	 return 0;
};