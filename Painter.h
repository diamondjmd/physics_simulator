#pragma once
#include "Color.h"
#include "Point.h"
#include <memory>

class View;
class PainterImpl;

namespace sf {
    class RenderWindow;
}

class Painter {
  public:
    Painter(sf::RenderWindow& window, const View& view);
    ~Painter();
    /**
     * Draws a circle of color
     * @param center circle center
     * @param radius circle radius
     * @param color fill color
     */
    void draw(const Point& center, double radius, const Color& color);
    /**
     * Draws a rectangle of color
     * @param topLeft top left corner coordinate
     * @param bottomRight bottom right corner coordinate
     * @param color fill color
     */
    void draw(const Point& topLeft, const Point& bottomRight,
              const Color& color);

  private:
    std::unique_ptr<PainterImpl> impl;
};