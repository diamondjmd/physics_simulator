#include "World.h"
#include "Painter.h"
#include <fstream>


// Duration of one simulation tick.
// See update() for details
// Should not be changed
static constexpr double timePerTick = 0.001;

/**
* Constructs a world object to simulate
 * @param worldFilePath path to world model file
 */
World::World(const std::string& worldFilePath) {
    std::ifstream stream(worldFilePath);
    /**
     * TODO: A good place to improve.
     * Reading world boundaries from model
     * Note that here and below we repeatedly
     * read into an object of type Point, sequentially
     * filling in the x and y coordinates. If we do something
     * repeatedly - it would be nice to put it in a function
     * and don't duplicate code...
     */
    stream >> topLeft.x >> topLeft.y >> bottomRight.x >> bottomRight.y;
    physics.setWorldBox(topLeft, bottomRight);

    /**
     * TODO: A good place to improve.
     * (x, y) and (vx, vy) are component parts of the object, also
     * as well as (red, green, blue). Again, you can simplify
     * this code, having learned to read at once Point, Color...
     */
    double x;
    double y;
    double vx;
    double vy;
    double radius;

    double red;
    double green;
    double blue;

    bool isCollidable;

    // Lacks error handling here, but on current
    // level of course completion suits us
    while (stream.peek(), stream.good()) {
        // Read the coordinates of the center of the ball (x, y) 
        //and its velocity vector (vx, vy)
        stream >> x >> y >> vx >> vy;
        // Read the three colors of the ball
        stream >> red >> green >> blue;
        // Read the radius of the ball
        stream >> radius;

        // Read the ball's isCollidable property, which
        //specifies whether to handle the intersection
        //balls as collision. If true - required.
        //In the base part of the task, this parameter
        stream >> std::boolalpha >> isCollidable;
        // TODO: A place to improve.
        //  The most important thing is missing here - creation
        //  object of class Ball with properties read
        //  above, and placing it in the balls container

        // After we somehow
        // construct a Ball ball object;
        // append it to the end of the container with a call
        // balls.push_back(ball);
    }
}

/// @brief Displays the state of the world
void World::show(Painter& painter) const {
    // Draw a white rectangle representing the border of the 
    // world
    painter.draw(topLeft, bottomRight, Color(1, 1, 1));

    // We call the drawing of each ball
    for (const Ball& ball : balls) {
        ball.draw(painter);
    }
}

/// @brief Updates the state of World
void World::update(double time) {
    /**
      * In the real world, time flows continuously. However
      * computers are discrete in nature. That's why
      * the simulation of the interaction of balls is performed by discrete
      * "ticks". Those. if since last simulation
      * time seconds elapsed, time / timePerTick update times
      * state of the world. Each such update - tick -
      * in physics.update() we move the balls and process
      * collisions - situations when as a result of moving
      * one ball intersects with another or with the border of the world.
      * In general, time is not divisible by
      * tick duration, save the remainder in restTime
      * and process at the next iteration.
     */

   // take into account the rest of the time that we did not "finish" during the last update
    time += restTime;
    const auto ticks = static_cast<size_t>(std::floor(time / timePerTick));
    restTime = time - double(ticks) * timePerTick;

    physics.update(balls, ticks);
}