#ifndef __VECTOR2D_HPP__
#define __VECTOR2D_HPP__

#include <cmath>

enum VectorSign {
   VectorSign_clockwise,
   VectorSign_counterClockwise,
};

// Fast access to all variables
struct Vector2D {
   double x, y;

   Vector2D() : x(0.0), y(0.0) {};
   Vector2D(double x, double y) : x(x), y(y) {}

   inline void zero() {
      x = y = 0;
   }

   inline bool isZero() {
      return (!x && !y);
   }

   inline double length() const {
      return sqrt(x*x + y*y);
   }

   inline double lengthSquared() const {
      return (x*x + y*y);
   }

   inline double distance(const Vector2D & vector2d) const {
      return sqrt(((vector2d.x - x)*(vector2d.x - x)) + (vector2d.y - y)*(vector2d.y - y));
   }

   inline double distanceSquared(const Vector2D & vector2d) const {
      return ((vector2d.x - x)*(vector2d.x - x)) + (vector2d.y - y)*(vector2d.y - y);
   }

   inline void normalize() {
      x /= length();
      y /= length();
   }

   inline double dot(const Vector2D & vector2d) const {
      return (x * vector2d.x) + (y * vector2d.y);
   }

   inline VectorSign sign(const Vector2D & vector2d) const {
      if (y * vector2d.x > x * vector2d.y) {
         return VectorSign_clockwise;
      }
      return VectorSign_counterClockwise;
   }

   inline Vector2D perpendicularVector() const {
      return Vector2D(-y, x);
   }

   inline void truncate(double max) {
      if (length() > max) {
         normalize();
         *this *= max;
      }
   }

   inline Vector2D getReverse() const {
      return Vector2D(-x, -y);
   }

   // Operators
   inline const Vector2D & operator +=(const Vector2D & rightHandSide) {
      x += rightHandSide.x;
      y += rightHandSide.y;

      return *this;
   }

   inline const Vector2D & operator -=(const Vector2D & rightHandSide) {
      x -= rightHandSide.x;
      y -= rightHandSide.y;

      return *this;
   }

   inline const Vector2D & operator *=(const double & rightHandSide) {
      x *= rightHandSide;
      y *= rightHandSide;

      return *this;
   }

   inline const Vector2D & operator /=(const double & rightHandSide) {
      x /= rightHandSide;
      y /= rightHandSide;

      return *this;
   }

   inline bool operator ==(const Vector2D & rightHandSide) {
      return (x == rightHandSide.x && y == rightHandSide.y);
   }

   inline bool operator !=(const Vector2D & rightHandSide) {
      return (x != rightHandSide.x || y != rightHandSide.y);
   }
};


inline Vector2D operator*(const Vector2D &leftHandSide, double rightHandSide) {
   Vector2D ret(leftHandSide);
   ret *= rightHandSide;
   return ret;
}

inline Vector2D operator*(double leftHandSide, const Vector2D &rightHandSide) {
   Vector2D ret(rightHandSide);
   ret *= leftHandSide;
   return ret;
}

inline Vector2D operator-(const Vector2D &leftHandSide, const Vector2D &rightHandSide) {
   Vector2D ret(leftHandSide);
   ret -= rightHandSide;
   return ret;
}

inline Vector2D operator+(const Vector2D &leftHandSide, const Vector2D &rightHandSide) {
   Vector2D ret(leftHandSide);
   ret += leftHandSide;
   return ret;
}

inline Vector2D operator/(const Vector2D &leftHandSide, double value) {
   Vector2D ret(leftHandSide);
   ret /= value;
   return ret;
}

#endif
