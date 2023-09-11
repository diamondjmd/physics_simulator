#include "Ball.hpp"
#include <cmath>

Ball::Ball() = default;

Ball::Ball(const Point &center, const Velocity &velocity, const Color &color, const double radius, const bool isCollidable)
    : m_center{center}, m_velocity {velocity}, m_radius{radius}, m_isCollidable {isCollidable}, m_color{color} {}

Ball::Ball(const Point &center, const Velocity &velocity, const Color &color, const double radius, const bool isCollidable, const double mass)
    : m_center{center}, m_velocity {velocity}, m_radius{radius}, m_isCollidable {isCollidable}, m_color{color},  m_mass{mass} {}

Ball::Ball(const Ball &ball)
    : m_center{ball.m_center}, m_velocity {ball.m_velocity}, m_radius{ball.m_radius}, m_isCollidable {ball.m_isCollidable}, m_color{ball.m_color},  m_mass{ball.m_mass} {}

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

std::ostream &operator<<(std::ostream &stream, const Point &point){
        return stream << "(" << point.x << ", " << point.y << ")";
}
std::ostream &operator<<(std::ostream &stream, const Ball &ball){
    return stream << "\n=> center " << ball.getCenter() 
        << ", velocity " << ball.getVelocity().vector()
        << ", rgb (" << ball.getColor().red()  << ", " << ball.getColor().green()  << ", " << ball.getColor().blue()  << ")"
        << ", radius: " << ball.getRadius()
        << ", mass:" << ball.getMass()
        << ", " <<(ball.isCollidable()?  "collidable" : "NOT collidable");
}