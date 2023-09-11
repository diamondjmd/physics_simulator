#pragma once
#include "Painter.h"
#include "Point.h"
#include "Velocity.h"

#include <ostream>

class Ball {
    public:

        Ball();
        Ball(const Point &center, const Velocity &velocity, const Color &color, const double radius, const bool isCollidable);
        Ball(const Point &center, const Velocity &velocity, const Color &color, const double radius, const bool isCollidable, const double mass);
        Ball(const Ball &ball);

        void setVelocity(const Velocity& velocity);
        Velocity getVelocity() const;
        void draw(Painter& painter) const;
        void setCenter(const Point& center);
        Point getCenter() const;
        double getRadius() const;
        double getMass() const;
        Color getColor() const;
        bool isCollidable() const;

        friend std::ostream &operator<<(std::ostream &stream, const Point &point);
        friend std::ostream &operator<<(std::ostream &stream, const Ball &ball);
        
    private:
        Point m_center;
        Velocity m_velocity;
        Color m_color;
        double m_radius{};
        bool m_isCollidable{};
        double m_mass{};

};
