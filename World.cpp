#include "World.h"
#include "Painter.h"
#include <fstream>


std::istream &operator>>(std::istream& stream, Point &point){
        stream >> point.x >> point.y;
        return stream;
}
    
std::istream &operator>>(std::istream& stream, Color &color){
        double r,g,b;
        stream >> r >> g >> b;
        color.setRed(r);
        color.setGreen(g);
        color.setBlue(b);
        return stream;
}

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

    //stream >> topLeft.x >> topLeft.y >> bottomRight.x >> bottomRight.y;
    stream >> topLeft >> bottomRight;
    physics.setWorldBox(topLeft, bottomRight);

    Point center, velocity;
    double radius;
    Color color;
    bool isCollidable;

    while (stream.peek(), stream.good()) {
        // Read the coordinates of the center of the ball (x, y) 
        //and its velocity vector (vx, vy)
        stream >> center >> velocity;

        // Read the three colors of the ball
        stream >> color;
        // Read the radius of the ball
        stream >> radius;

        // Read the ball's isCollidable property, which
        // specifies whether to handle the intersection
        // balls as collision. If true - required.
        stream >> std::boolalpha >> isCollidable;


        // balls.push_back(Ball(Point(x, y), radius, isCollidable, Color(red, green, blue) ,Velocity(vx, vy)));
        balls.push_back(Ball(center, velocity, color, radius ,isCollidable));
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

    for (const Dust& dust: dusts) {
        dust.draw(painter);
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

    physics.update(balls, dusts, ticks);
}