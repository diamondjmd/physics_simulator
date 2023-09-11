#include "Dust.h"

Dust::Dust() =  default;

Dust::Dust(const Point &center, const Velocity &velocity, size_t display_time)
    : Ball(center, velocity,Color(0.98, 0.83, 0.2), 10, false),m_display_time{display_time} {}
Dust::Dust(const Point &center, const Velocity &velocity, size_t display_time, const Color &color, const double radius)
    : Ball (center, velocity, color, radius, false), m_display_time{display_time} {}
Dust::Dust(const Point &center, const Velocity &velocity, size_t display_time, const Color &color, const double radius, const bool isCollidable)
    : Ball(center, velocity, color, radius, isCollidable), m_display_time{display_time} {}

size_t Dust::get_display_time() const{ 
    return m_display_time;
}

void Dust::set_display_time(const size_t display_time){ 
    m_display_time = display_time;
}
