#include "ComplexPlane.h"
#include <cmath>
#include <iostream>
#include <sstream>

using namespace sf;
using namespace std;

//constructor
ComplexPlane::ComplexPlane(int pixelWidth, int pixelHeight)
    : m_pixel_size({ pixelWidth, pixelHeight }),
      m_vArray(Points, pixelWidth* pixelHeight),
      m_zoomCount(0),
      m_plane_center({ 0, 0 }),
      m_plane_size({ BASE_WIDTH, BASE_HEIGHT * static_cast<float>(pixelHeight) / pixelWidth }),
      m_state(State::CALCULATING) {
    m_aspectRatio = static_cast<float>(pixelHeight) / pixelWidth;
}