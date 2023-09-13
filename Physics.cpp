#include "Physics.h"

double dot(const Point& lhs, const Point& rhs) {
    return lhs.x * rhs.x + lhs.y * rhs.y;
}

Physics::Physics(double timePerTick) : timePerTick{timePerTick}, m_gen {std::random_device{}()} {}

void Physics::setWorldBox(const Point& topLeft, const Point& bottomRight) {
    this->topLeft = topLeft;
    this->bottomRight = bottomRight;
}

// overloading member function updated in order to not break 
void Physics::update(std::vector<Ball>& balls, std::vector<Dust> &dusts,  const size_t ticks) const {

    for (size_t i = 0; i < ticks; ++i) {
        move(balls);
        move(dusts);
        collideBalls(balls, dusts);
        collideWithBox(balls);
    }
} 

// member function updated 
void Physics::collideBalls(std::vector<Ball>& balls, std::vector<Dust> &dusts) const {
    for (auto a = balls.begin(); a != balls.end(); ++a) {
        if ( a->isCollidable()){

            for (auto b = std::next(a); b != balls.end(); ++b) {
                if ( b->isCollidable()){
                    const double distanceBetweenCenters2 =
                        distance2(a->getCenter(), b->getCenter());
                    const double collisionDistance = a->getRadius() + b->getRadius();
                    const double collisionDistance2 =
                        collisionDistance * collisionDistance;

                    if (distanceBetweenCenters2 < collisionDistance2) {
                        //processCollision(*a, *b, distanceBetweenCenters2, dusts);
                        createDust (*a, *b,dusts, 20);
                        b = balls.erase(b);
                        a = balls.erase(a);
                        break;
                    }
                }
            }
        }
    }
}

void Physics::collideWithBox(std::vector<Ball>& balls) const {
    std::vector<Ball> to_push_out;
    for (Ball& ball : balls) {
        // collapsable flag
        if (ball.isCollidable()){
            const Point p = ball.getCenter();
            const double r = ball.getRadius();
            // determines if v is in range (lo, hi) (not including bounds)
            auto isOutOfRange = [](double v, double lo, double hi) {
                return v < lo || v > hi;
            };

            if (isOutOfRange(p.x, topLeft.x + r, bottomRight.x - r)) {
                Point vector = ball.getVelocity().vector();
                vector.x = -vector.x;
                ball.setVelocity(vector);
            } else if (isOutOfRange(p.y, topLeft.y + r, bottomRight.y - r)) {
                Point vector = ball.getVelocity().vector();
                vector.y = -vector.y;
                ball.setVelocity(vector);
            }

        }
    }
}

void Physics::move(std::vector<Ball>& balls) const {
    for (Ball& ball : balls) {
        Point newPos =
            ball.getCenter() + ball.getVelocity().vector() * timePerTick;
        ball.setCenter(newPos);
    }
}

// Dust physics
// this a good example to use a template and not overloading this class just 
// for the object type, principle DRY
void Physics::move(std::vector<Dust>& dusts) const {
    for (auto dust = dusts.begin(); dust!=dusts.end();){
        if (dust->get_display_time() < 1){
            dust = dusts.erase(dust);
            continue;
        }

        Point newPos =
                dust->getCenter() + dust->getVelocity().vector() * timePerTick;
        dust->setCenter(newPos);

        dust->set_display_time(dust->get_display_time() -1);
        dust++;
    }
}

void Physics::processCollision(Ball& a, Ball& b,
                               double distanceBetweenCenters2,
                               std::vector<Dust> &dusts) const {
    createDust (a, b,dusts, 20);

    // normalized collision vector
    const Point normal =
        (b.getCenter() - a.getCenter()) / std::sqrt(distanceBetweenCenters2);

    // get the Velocity in vector
    const Point aV = a.getVelocity().vector();
    const Point bV = b.getVelocity().vector();

    // coefficient p takes into account the speed of both balls
    const double p =
        2 * (dot(aV, normal) - dot(bV, normal)) / (a.getMass() + b.getMass());

    // set new ball speeds after collision
    a.setVelocity(Velocity(aV - normal * p * a.getMass()));
    b.setVelocity(Velocity(bV + normal * p * b.getMass()));

}

void Physics::createDust(const Ball &a, const Ball &b,
                        std::vector<Dust> &dusts,
                        const size_t nParticles) const {
    
    Point midpointCenter = midPoint(a.getCenter(),b.getCenter());  
    const double midPointRadius = a.getRadius () + b.getRadius(); 

    double length, theta;

    //std::mt19937 gen(std::random_device {}()); 
    std::uniform_real_distribution<> dist(0.0, 1.0);
 
    for (size_t i=0; i< nParticles; i++){
        //theta = 2 * PI * (dist(gen));
        theta = 2 * PI * (dist(m_gen));
        //length = midPointRadius * std::sqrt(dist(gen));
        length = midPointRadius * std::sqrt(dist(m_gen));       
        Point pCenter(  midpointCenter.x + length * std::cos(theta), 
                        midpointCenter.y + length * std::sin(theta));
 
        Point maxVelocity(  std::max(a.getVelocity().vector().x, b.getVelocity().vector().x),
                            std::max(a.getVelocity().vector().y, b.getVelocity().vector().y));

        Point minVelocity(  std::min(a.getVelocity().vector().x, b.getVelocity().vector().x),
                            std::min(a.getVelocity().vector().y, b.getVelocity().vector().y));
        
        Point pVelocity(minVelocity.x + ((double) std::rand() /RAND_MAX * maxVelocity.x) ,
                        minVelocity.y + ((double) std::rand() /RAND_MAX * maxVelocity.y));

        dusts.push_back(Dust(pCenter, pVelocity, 400));
    }
}

