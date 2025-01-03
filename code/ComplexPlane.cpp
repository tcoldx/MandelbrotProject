#include "ComplexPlane.h"
#include <cmath>
#include <iostream>
#include <sstream>
#include <complex>

using namespace sf;
using namespace std;

//constructor
ComplexPlane::ComplexPlane(int pixelWidth, int pixelHeight)
    : m_pixel_size({pixelWidth, pixelHeight}),
      m_vArray(Points, pixelWidth* pixelHeight),
      m_zoomCount(0),
      m_plane_center({ 0, 0 }),
      m_plane_size({BASE_WIDTH, BASE_HEIGHT * static_cast<float>(pixelHeight) / pixelWidth}),
      m_state(State::CALCULATING) {
    m_aspectRatio = static_cast<float>(pixelHeight) / pixelWidth;
}

//Draws the vertex array (Mandelbrot set) onto the window
void ComplexPlane::draw(RenderTarget& target, RenderStates states) const {
    target.draw(m_vArray);
}

void ComplexPlane::updateRender() {
    if (m_state == State::CALCULATING) {
        //iterate over each pixel
        for (int i = 0; i < m_pixel_size.y; ++i) {
            for (int j = 0; j < m_pixel_size.x; ++j) {
                Vector2f coord = mapPixelToCoords({ j, i }); //map pixel
                int iterCount = countIterations(coord); //calculate iterations

                //convert count to rgb
                Uint8 r, g, b;
                iterationsToRGB(iterCount, r, g, b);

                //update vertex array colors depending on pixel location
                int index = j + i * m_pixel_size.x;
                m_vArray[index].position = { static_cast<float>(j), static_cast<float>(i) };
                m_vArray[index].color = Color(r, g, b);
            }
        }
        m_state = State::DISPLAYING;  //switch state
    }
}

void ComplexPlane::zoomIn() {
    //increment and adjust viewable area
    m_zoomCount++;
    m_plane_size.x = BASE_WIDTH * pow(BASE_ZOOM, m_zoomCount);
    m_plane_size.y = BASE_HEIGHT * m_aspectRatio * pow(BASE_ZOOM, m_zoomCount);
    m_state = State::CALCULATING;  //switch state
}

void ComplexPlane::zoomOut() {
    //decrement and adjust viewable area
    m_zoomCount--;
    m_plane_size.x = BASE_WIDTH * pow(BASE_ZOOM, m_zoomCount);
    m_plane_size.y = BASE_HEIGHT * m_aspectRatio * pow(BASE_ZOOM, m_zoomCount);
    m_state = State::CALCULATING;  //switch state
}

//sets center depending on location clicked
void ComplexPlane::setCenter(Vector2i mousePixel) {
    m_plane_center = mapPixelToCoords(mousePixel);
    m_state = State::CALCULATING;
}

//updates the mouse location
void ComplexPlane::setMouseLocation(Vector2i mousePixel) {
    m_mouseLocation = mapPixelToCoords(mousePixel);
}

//updates text location
void ComplexPlane::loadText(Text& text) {
    ostringstream ss;
    ss << "Center: (" << m_plane_center.x << ", " << m_plane_center.y << ")\n";
    ss << "Mouse: (" << m_mouseLocation.x << ", " << m_mouseLocation.y << ")";
    text.setString(ss.str());
}

//calculates how quickly the point escapes infinity
int ComplexPlane::countIterations(Vector2f coord) {
    std::complex<float> c(coord.x, coord.y);
    std::complex<float> z = c;
    int iter = 0;

    while (abs(z) < 2.0f && iter < MAX_ITER) {
        z = z * z + c;  //Mandelbrot formula
        iter++;
    }

    return iter;
}

//the number of iterations determines the color
void ComplexPlane::iterationsToRGB(size_t count, Uint8& r, Uint8& g, Uint8& b) {
    if (count == MAX_ITER) {
        r = g = b = 0;  // Black
    }
    else {
        r = (count * 5) % 256;
        g = (count * 10) % 256;
        b = (count * 15) % 256;
    }
}


Vector2f ComplexPlane::mapPixelToCoords(Vector2i pixel) {
    //locate top left corner
    Vector2f offset(m_plane_center.x - m_plane_size.x / 2.0f,
        m_plane_center.y - m_plane_size.y / 2.0f);
    return {
        ((static_cast<float>(pixel.x) / m_pixel_size.x) * m_plane_size.x) + offset.x,
        ((static_cast<float>(m_pixel_size.y - pixel.y) / m_pixel_size.y) * m_plane_size.y) + offset.y
    };
}