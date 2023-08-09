#pragma once

#include <istream>
class Color {
  public:
    Color();
    Color(double red, double green, double blue);
    double red() const;
    double green() const;
    double blue() const;

    void setRed(const double value);
    void setGreen(const double value);
    void setBlue(const double value);
    
  private:
    double r{};
    double g{};
    double b{};
};
