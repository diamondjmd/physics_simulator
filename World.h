#pragma once
#include "Ball.hpp"
#include "Physics.h"
#include "Dust.h"
#include <vector>

class Painter;

std::istream &operator>>(std::istream& stream, Point &point);
std::istream &operator>>(std::istream& stream, Color &color);

class World {
  public:
    World(const std::string& worldFilePath);
    void show(Painter& painter) const;
    void update(double time);



  private:
    // The world boundaries are set by the corners of the rectangle
    Point topLeft;
    Point bottomRight;
    // Physics engine object
    Physics physics;
    // Container with balls
    std::vector<Ball> balls;
    
    // Container with Dust particles
    std::vector<Dust> dusts;

    // The length of the length of time that was not
    // taken into account in the previous simulation. See update implementation
    double restTime = 0.;
};
