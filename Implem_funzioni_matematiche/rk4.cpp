#include "rk4.hpp"

// prende come argomenti l'incremento h, la funzione f(y, x) dell'ODE y'=f(y, x)

function ::~function() = default;

function::function(double x0, double y0) : x_n{x0}, y_n{y0} {};
// il costruttore lo uso per dare le condizioni iniziali

double function::get_x() const { return x_n; };
double function::get_y() const { return y_n; };

void function::draw(sf::RenderWindow& window, double const x_max,
                    double const h) {
  std::vector<double> vec_x;
  std::vector<double> vec_y;
  double dx{};
  while (dx <= x_max) {
    // riempio il vettore di punti così poi posso riscalarli, siccome mi
    // serve la x_max e la y_max
    vec_x.push_back(x_n);
    vec_y.push_back(y_n);

    y_n += rk4(h);
    x_n += h;
    // lo aggiorno dopo altrimenti passo x_n aggiornato a rk4()

    // std::cout << "dx = " << dx << '\n';
    // std::cout << "(" << x_n << ", " << y_n << ")" << '\n';

    dx += h;
  }

  assert(vec_x.size() == vec_y.size());

  auto py_max = std::max_element(vec_y.begin(), vec_y.end());
  // trovo la y più grande

  double x_scale = window.getSize().x * 0.5 / x_max * 0.8;
  double y_scale = window.getSize().y * 0.5 / *py_max * 0.8;

  // std::cout << "x_scale e y_scale: " << x_max << ' ' << *py_max << '\n';

  for (size_t i = 0; i != vec_x.size(); ++i) {
    vec_x[i] *= x_scale;
    vec_y[i] *= y_scale;

    Point point(vec_x[i], -1 * vec_y[i]);
    // std::cout << "(" << point.x() << ", " << -1 * point.y() << ")" << '\n';

    point.draw(window);
  }

  window.display();
}

double function::rk4(double const h) {
  auto k1 = compute(x_n, y_n);
  auto k2 = compute(x_n + h * 0.5, y_n + 0.5 * k1 * h);
  auto k3 = compute(x_n + h * 0.5, y_n + 0.5 * k2 * h);
  auto k4 = compute(x_n + h, y_n + k3 * h);

  auto y = h * (k1 + 2 * k2 + 2 * k3 + k4) / 6;

  return y;
};

// function operator+(function& f1, function& f2) {
//   return (f1.compute(f1.get_x(), f1.get_y()) +
//           f2.compute(f2.get_x(), f2.get_y()));
// };

exponential::~exponential() = default;

exponential::exponential(double x0, double y0) : function(x0, y0){};

double exponential::compute(double x, double y) const { return y; };

int_power ::~int_power() = default;
int_power ::int_power(double expp, double x0, double y0)
    : function(x0, y0), exponent{expp} {};
double int_power ::compute(double x, double y) const {
  return std::pow(get_x(), exponent);
};

// custom_function::~custom_function() = default;
// custom_function(double x0, double y0) : function(x0, y0){};
// double custom_function::compute(double x, double y) const { return; };
