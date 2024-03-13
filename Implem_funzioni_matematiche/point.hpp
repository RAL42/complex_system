#ifndef POINT_HPP
#define POINT_HPP

#include <SFML/Graphics.hpp>

class Point {
  sf::Vector2<double> pos_;
  sf::CircleShape s;

 public:
  Point(double const x, double const y) : pos_{x, y} {
    s.setRadius(1.5);
  };

  void draw(sf::RenderWindow &wind) {
    s.setPosition(sf::Vector2f(pos_.x , pos_.y));
    wind.draw(s);
  };

  double const x() { return pos_.x;};
  double const y() { return pos_.y;};
};

#endif
