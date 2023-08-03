#pragma once
#include "Ball.hpp"
#include "Physics.h"
#include <vector>

class Painter;

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
    // The length of the length of time that was not
    // taken into account in the previous simulation. See update implementation
    double restTime = 0.;
};