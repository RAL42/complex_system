#include "point.hpp"

#include <SFML/Graphics.hpp>

Point::Point(double const x, double const y) : pos_{x, y} { s.setRadius(6); };

void Point::draw(sf::RenderWindow& wind) {
  s.setOrigin(s.getRadius(), s.getRadius());
  s.setPosition(sf::Vector2f(pos_.x, pos_.y));
  wind.draw(s);
};

double const Point::x() { return pos_.x; };
double const Point::y() { return pos_.y; };

void Point::update_x(double const x) { pos_.x = x; };
void Point::update_y(double const y) { pos_.y = y; };

void Point::setFillColor(sf::Color col) { s.setFillColor(col); };
void Point::setRadius(int r) { s.setRadius(r); };

