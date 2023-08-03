#include "View.h"
#include <algorithm>
#include <cmath>

inline constexpr double maxZoom = 60.;
inline constexpr double initialZoom = 20;
inline constexpr double zoomCoef = 0.01;
inline constexpr double minScale = 0.005;

View::View(const Point& viewPoint, double screenWidth, double screenHeight,
           double scale)
    : zoomValue{initialZoom}, viewPoint{viewPoint}, screenWidth{screenWidth},
      screenHeight{screenHeight}, scale_{scale} {
    onZoom(0.);
}

Point View::toScreen(const Point& worldPos) const {
    // Not the most efficient but trivial implementation
    // transition from world coordinates to screen

    // clang-format off
    Point screenPos =
        // Offset worldPos relative to the observed point
        (worldPos - viewPoint)
        // scale
        * scale_
        // and center on the screen
        // (so that the observed point is in the center)
        + Point(screenWidth / 2., screenHeight / 2);
    // clang-format on

    // invert y axis
    screenPos.y = screenHeight - screenPos.y;
    return screenPos;
}

void View::onZoom(double step) {
    zoomValue = std::clamp(zoomValue + step, 1., maxZoom);
    scale_ = std::exp(zoomValue * zoomCoef) - 1. + minScale;
}

double View::scale() const {
    return scale_;
}
