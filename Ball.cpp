#include "Ball.hpp"
#include <cmath>

/**
 * Sets the speed of the object
 * @param velocity new speed value
 */
void Ball::setVelocity(const Velocity& velocity) {
    // TODO: place for improvement
}

/**
 * @return object speed
 */
Velocity Ball::getVelocity() const {
    // TODO: place for improvement
    return {};
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
    // TODO: place for improvement
}

/**
 * Sets the coordinates of the object's center
 * @param center new facility center
 */
void Ball::setCenter(const Point& center) {
    // TODO: place for improvement
}

/**
 * @return object center
 */
Point Ball::getCenter() const {
    // TODO: place for improvement
    return {};
}


/**
 * @brief Returns the radius of an object
 * @details note that the setRadius() member function 
 * is not required
 */
double Ball::getRadius() const {
    // TODO: place for improvement
    return {};
}

/**
 * @brief Returns the mass of an object
 * @details In our application, we assume that all balls
 * consist of the same material with a fixed
 * density. In this case, the mass in conventional units
 * equivalent to volume: PI * radius^3 * 4. / 3.
 */
double Ball::getMass() const {
    // TODO: place for improvement
    return {};
}
