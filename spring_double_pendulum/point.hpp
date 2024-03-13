#ifndef POINT_HPP
#define POINT_HPP

#include <SFML/Graphics.hpp>

class Point {
  sf::Vector2<double> pos_;
  sf::CircleShape s;

 public:
  Point(double const x, double const y);

  void draw(sf::RenderWindow &);

  double const x();
  double const y();

  void update_x(double const);
  void update_y(double const);

  void setFillColor(sf::Color);
  void setRadius(int);

};

#endif
