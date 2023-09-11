#pragma once
#include "Ball.hpp"
#include "Dust.h"
#include <vector>
#include <cstdlib>
#include <ctime>

class Physics {
  public:
    Physics(double timePerTick = 0.001);
    void setWorldBox(const Point& topLeft, const Point& bottomRight);
    void update(std::vector<Ball>& balls, size_t ticks) const;
    void update(std::vector<Ball>& balls, std::vector<Dust> &dusts,  const size_t ticks) const;


  private:
    void collideBalls(std::vector<Ball>& balls) const;
    void collideBalls(std::vector<Ball>& balls, std::vector<Dust> &dusts) const;
    void collideWithBox(std::vector<Ball>& balls) const;
    void move(std::vector<Ball>& balls) const;
    void move(std::vector<Dust>& dusts) const;
    void processCollision(Ball& a, Ball& b,
                          double distanceBetweenCenters2) const;
    void processCollision(Ball& a, Ball& b,
                          double distanceBetweenCenters2,
                          std::vector<Dust> &dusts) const;
    void createDust(const Ball &a, const Ball &b,
                    std::vector<Dust> &dusts,
                    const size_t nParticles) const;

   const double PI = 3.141592653589793238463;
  private:
    Point topLeft;
    Point bottomRight;
    double timePerTick;
};
