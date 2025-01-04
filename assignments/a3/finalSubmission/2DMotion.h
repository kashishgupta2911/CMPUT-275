#ifndef MOTION2D
#define MOTION2D

#include <iostream>

#define PI 3.14159265

// Forward declaration of Force class.
class Force;

class Point {
private:
    float x;
    float y;

public:
    // Constructors
    Point();
    Point(float valueofx, float valueofy);

    // Friend functions
    friend std::istream& operator>>(std::istream& in, Point& p);
    friend std::ostream& operator<<(std::ostream& out, const Point& p);
    friend Point operator+(const Point& p, const Force& f);

    // Public member functions
    int quadrant() const;
    float get_forx() const;
    float get_fory() const;
};

class Force {
private:
    float angle;
    float magnitude;

public:
    // Constructors
    Force();
    Force(float angle_val, float magnitude_val);

    // Friend functions
    friend std::istream& operator>>(std::istream& in, Force& f);
    friend std::ostream& operator<<(std::ostream& out, const Force& f);

    // Public member functions
    Force operator*(int scalar) const;
    float get_angle() const;
    float get_magnitude() const;
};

#endif