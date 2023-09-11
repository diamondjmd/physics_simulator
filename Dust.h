#pragma once

#include "Ball.hpp"

class Dust : public Ball {
    public:
        Dust();
        Dust(const Point &center, const Velocity &velocity, size_t display_time);
        Dust(const Point &center, const Velocity &velocity,size_t display_time, const Color &color, const double radius);
        Dust(const Point &center, const Velocity &velocity,size_t display_time, const Color &color, const double radius, const bool isCollidable);

        size_t get_display_time() const;
        void set_display_time(const size_t);
    private:
        //ticks to display or iterations
        size_t m_display_time{300};
};
