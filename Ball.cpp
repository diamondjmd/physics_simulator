#include "Ball.hpp"
#include <cmath>

Ball::Ball() = default;

Ball::Ball(const Point &center, const Velocity &velocity, const Color &color, const double radius, const bool isCollidable)
    : m_center{center}, m_velocity {velocity}, m_radius{radius}, m_isCollidable {isCollidable}, m_color{color} {}

Ball::Ball(const Point &center, const Velocity &velocity, const Color &color, const double radius, const bool isCollidable, const double mass)
    : m_center{center}, m_velocity {velocity}, m_radius{radius}, m_isCollidable {isCollidable}, m_color{color},  m_mass{mass} {}

/**
 * Sets the speed of the object
 * @param velocity new speed value
 */
void Ball::setVelocity(const Velocity& velocity) {
    m_velocity.setVector(velocity.vector());
}

/**
 * @return object speed
 */
Velocity Ball::getVelocity() const {
    // TODO: place for improvement
    return m_velocity;
}


/**
 * @brief Performs object rendering
 * @details the Ball object is abstracted from the specific
 * way pixels are displayed on the screen. It is only "familiar"
 * with the interface that Painter provides. 
 * Drawing is done by calling painter.draw(...)
 * @param painter render context
 */
void Ball::draw(Painter& painter) const {
    painter.draw(m_center, m_radius,m_color);
}

/**
 * Sets the coordinates of the object's center
 * @param center new facility center
 */
void Ball::setCenter(const Point& center) {
    m_center.x = center.x;
    m_center.y = center.y;

}

/**
 * @return object center
 */
Point Ball::getCenter() const {
    return m_center;
}


/**
 * @brief Returns the radius of an object
 * @details note that the setRadius() member function 
 * is not required
 */
double Ball::getRadius() const {
    // TODO: place for improvement
    return m_radius;
}

/**
 * @brief Returns the mass of an object
 * @details In our application, we assume that all balls
 * consist of the same material with a fixed
 * density. In this case, the mass in conventional units
 * equivalent to volume: PI * radius^3 * 4. / 3.
 */
double Ball::getMass() const {
    return m_mass;
}

Color Ball::getColor () const{
    return m_color;
 }

 bool Ball::isCollidable() const { 
    return m_isCollidable;
  }