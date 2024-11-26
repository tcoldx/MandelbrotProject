#include <iostream>
#include <SFML/Graphics.hpp> 
#include "ComplexPlane.h"

using namespace sf;
using namespace std;

int main() {
    //set screen with desktop resolution
    VideoMode desktop = VideoMode::getDesktopMode();
    unsigned int width = desktop.width / 4;
    unsigned int height = desktop.height / 4; 

    RenderWindow window(VideoMode(width, height), "Mandelbrot Set Viewer");
    ComplexPlane complexPlane(width, height);

    //construct font
    Font font;
    if (!font.loadFromFile("arial.ttf")) {
        cerr << "Error: Could not load font 'arial.ttf'" << endl;
        return -1;  // Exit if font loading fails
    }

    Text text;
    text.setFont(font);
    text.setCharacterSize(16);
    text.setFillColor(Color::White);

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
            if (event.type == Event::MouseButtonPressed) { //input edits the complex plane
                if (event.mouseButton.button == Mouse::Left) {
                    complexPlane.zoomIn();
                    complexPlane.setCenter({ event.mouseButton.x, event.mouseButton.y });
                }
                else if (event.mouseButton.button == Mouse::Right) {
                    complexPlane.zoomOut();
                    complexPlane.setCenter({ event.mouseButton.x, event.mouseButton.y });
                }
            }
            if (event.type == Event::MouseMoved) { //tracks mouse movement
                complexPlane.setMouseLocation({ event.mouseMove.x, event.mouseMove.y });
            }
        }

        if (Keyboard::isKeyPressed(Keyboard::Escape)) {
            window.close(); //exit with esc key
        }

        complexPlane.updateRender();
        complexPlane.loadText(text);
        //updates to display and text
        window.clear();
        window.draw(complexPlane);
        window.draw(text);
        window.display();
    }

    return 0;
}