#ifndef RK4_HPP
#define RK4_HPP

#include <cassert>
#include <cmath>
#include <iostream>

#include "point.hpp"
// prende come argomenti l'incremento h, la funzione f(y, x) dell'ODE y'=f(y, x)

using x_y_arrays = std::array<std::array<sf::Vertex>>; 

namespace numbers {
constexpr double e = 2.7182818284590452;
};

class function {
  double x_n;
  double y_n;

 public:
  ~function();

  virtual double compute(double , double ) const = 0;
  // corpo della funzione
  function(double, double);
  // il costruttore lo uso per dare le condizioni iniziali

  virtual double get_x() const ;
  virtual double get_y() const ;

  double rk4(double const) ;

  virtual sf::Vertex [] 

  virtual void draw(sf::RenderWindow&, double const, double const);

};

// function operator+(function& f1, function& f2) {};

class exponential : public function {
 public:
  ~exponential();

  exponential(double, double) ;

  double compute(double, double) const override;
};

class int_power : public function {
  double exponent;

 public:
  ~int_power();
  int_power(double, double, double) ;
  double compute(double, double ) const override;
};

class custom_function : public function {
 public:
  ~custom_function();
  // custom_function(double x0, double y0) : function(x0, y0){};
  double compute(double, double) const override;
};

#endif