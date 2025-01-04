#include <iostream>
#include <iomanip>
#include <cmath>
#include "2DMotion.h"

using namespace std;

//Point class with x and y coordinates.

Point::Point() : x{0}, y{0} {} //initializes point at origin.

Point::Point(float valueofx, float valueofy) : x(valueofx), y(valueofy) {} // Constructor that initializes point at given x and y.

istream& operator>>(istream& in, Point& p) { //to read point coordinates.
    in >> p.x >> p.y;
    return in;
}

ostream& operator<<(ostream& out, const Point& p) { //to print point coordinates.
    out << fixed << setprecision(2);
    out << "(" << p.x << ", " << p.y << ")";
    return out;
}

float Point::get_forx() const { return x; } // Getter for x-coordinate.
float Point::get_fory() const { return y; } // Getter for y-coordinate.

// Force class with an angle and magnitude.

Force::Force() : angle{0}, magnitude{0} {} //initializes force with direction and magnitude.

Force::Force(float angle_val, float magnitude_val) : angle(angle_val), magnitude(magnitude_val) {} // Constructor that initializes force with given angle and magnitude.

istream& operator>>(istream& in, Force& f) { //to read force angle and magnitude.
    in >> f.angle >> f.magnitude;
    return in;
}

ostream& operator<<(ostream& out, const Force& f) { //to print force angle and magnitude.
    out << fixed << setprecision(2);
    out << f.angle << " degrees with magnitude of " << f.magnitude;
    return out;
}

float Force::get_angle() const { return angle; } 
float Force::get_magnitude() const { return magnitude; } 

Force Force::operator*(int scalar) const { 
    return Force(angle, magnitude * scalar);
}

int Point::quadrant() const { //determine which quadrant the point is in.
    if (x >= 0 && y >= 0)
        return 1;
    else if (x < 0 && y >= 0)
        return 2;
    else if (x <= 0 && y < 0)
        return 3;
    else if (x > 0 && y <= 0)
        return 4;
    else
        return 0; // Origin
}

Point operator+(const Point& p, const Force& f) { //apply force to point.
    float radians = f.get_angle() * PI / 180.0; // Convert angle to radians.
    float delta_x = f.get_magnitude() * cos(radians); 
    float delta_y = f.get_magnitude() * sin(radians); 

    return Point(p.get_forx() + delta_x, p.get_fory() + delta_y); 
}
