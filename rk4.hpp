#ifndef RK4_HPP
#define RK4_HPP

#include <cmath>
#include <iostream>
#include <cassert>

#include "point.hpp"
// prende come argomenti l'incremento h, la funzione f(y, x) dell'ODE y'=f(y, x)

namespace numbers {
constexpr double e = 2.7182818284590452;
};

struct function {
  double x_n;
  double y_n;

  virtual double compute(double x, double y) const = 0;
  // corpo della funzione
  function(double x0, double y0) : x_n{x0}, y_n{y0} {};
  // il costruttore lo uso per dare le condizioni iniziali

  ~function() = default;

  double rk4(double const h) {
    auto k1 = compute(x_n, y_n);
    auto k2 = compute(x_n + h * 0.5, y_n + 0.5 * k1 * h);
    auto k3 = compute(x_n + h * 0.5, y_n + 0.5 * k2 * h);
    auto k4 = compute(x_n + h, y_n + k3 * h);

    auto y = h * (k1 + 2 * k2 + 2 * k3 + k4) / 6;

    return y;
  }
};

struct f1 : function {
  f1(double x0, double y0) : function(x0, y0){};
  ~f1() = default;

  double compute(double x, double y) const override { return y; };
};

struct f2 : function {
  f2(double x0, double y0) : function(x0, y0){};
  ~f2() = default;

  double compute(double x, double y) const override { return x; }
};
/*
// function che definisce la f(x, y) per l'equazione differenziale. il
// return, quindi, è la derivata, y', calcolata nel punto (x, y)
double f(double const x_n, double const y_n) {
  // definisco qui dentro l'equazione differenziale
  double const f{std::sin(y_n * x_n)};
  return f;
};

double g(double const x_n, double const y_n) {
  // definisco qui dentro l'equazione differenziale
  double const f{y_n};
  return f;
};
*/

/*
// la chiamo una volta e restituisce il singolo y_i+1
auto rk4(double const h, double const x_n, double const y_n) {
  auto k1 = f(x_n, y_n);
  auto k2 = f(x_n + h * 0.5, y_n + 0.5 * k1 * h);
  auto k3 = f(x_n + h * 0.5, y_n + 0.5 * k2 * h);
  auto k4 = f(x_n + h, y_n + k3 * h);

  // std::cout << "k1=" << k1 << ", k2=" << k2 << ", k3=" << k3
  //          << ", k4=" << k4 << '\n';
  auto y = h * (k1 + 2 * k2 + 2 * k3 + k4) / 6;

  return y;
}
*/

void draw(sf::RenderWindow& window, function& f, double const x_max,
          double const h) {
  std::vector<double> vec_x;
  std::vector<double> vec_y;
  double dx{};
  while (dx <= x_max) {
    // riempio il vettore di punti così poi posso riscalarli, siccome mi
    // serve la x_max e la y_max
    vec_x.push_back(f.x_n);
    vec_y.push_back(f.y_n);

    f.y_n += f.rk4(h);
    f.x_n += h;
    // lo aggiorno dopo altrimenti passo x_n aggiornato a rk4()

    std::cout << "dx = " << dx << '\n';
    std::cout << "(" << f.x_n << ", " << f.y_n << ")" << '\n';

    dx += h;
  }

  assert(vec_x.size() == vec_y.size());

  auto py_max = std::max_element(vec_y.begin(), vec_y.end());
  // trovo la y più grande

  double x_scale = window.getSize().x * 0.5 / x_max * 0.8;
  double y_scale = window.getSize().y * 0.5 / *py_max * 0.8;

  std::cout << "x_scale e y_scale: " << x_max << ' ' << *py_max << '\n';

  for (size_t i = 0; i != vec_x.size(); ++i) {
    vec_x[i] *= x_scale;
    vec_y[i] *= y_scale;

    Point point(vec_x[i], -1 * vec_y[i]);
    std::cout << "(" << point.x() << ", " << -1 * point.y() << ")" << '\n';

    point.draw(window);
  }

  window.display();
}

#endif