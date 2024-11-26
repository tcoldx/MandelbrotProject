#include <iostream>
#include <SFML/Graphics.hpp> 
#include "ComplexPlane.h"

using namespace sf;
using namespace std;

int main() {
    VideoMode desktop = VideoMode::getDesktopMode();
    //screen dimentions
    unsigned int width = desktop.width / 4;
    unsigned int height = desktop.height / 4; 

    RenderWindow window(VideoMode(width, height), "Mandelbrot Set Viewer");
    ComplexPlane complexPlane(width, height);

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
            if (event.type == Event::MouseButtonPressed) {
                if (event.mouseButton.button == Mouse::Left) {
                    complexPlane.zoomIn();
                    complexPlane.setCenter({ event.mouseButton.x, event.mouseButton.y });
                }
                else if (event.mouseButton.button == Mouse::Right) {
                    complexPlane.zoomOut();
                    complexPlane.setCenter({ event.mouseButton.x, event.mouseButton.y });
                }
            }
            if (event.type == Event::MouseMoved) {
                complexPlane.setMouseLocation({ event.mouseMove.x, event.mouseMove.y });
            }
        }

        if (Keyboard::isKeyPressed(Keyboard::Escape)) {
            window.close();
        }

        complexPlane.updateRender();
        complexPlane.loadText(text);

        window.clear();
        window.draw(complexPlane);
        window.draw(text);
        window.display();
    }

    return 0;
}