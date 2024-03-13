#include "rk4.hpp"

double f(double t1, double t2, double t1d, double t2d) {
  return (w2 * (std::sin(t2) * std::cos(t1 - t2) - 2 * std::sin(t1)) -
          0.5 * std::sin(2 * (t1 - t2)) * t1d * t1d -
          std::sin(t1 - t2) * t2d * t2d);
}

double g(double t1, double t2, double t1d, double t2d) {
  return (2 * w2 * (std::sin(t1) * std::cos(t1 - t2) - std::sin(t2)) +
          2 * std::sin(t1 - t2) * t1d * t1d +
          0.5 * std::sin(2 * (t1 - t2)) * t2d * t2d);
}

// risolve l'ODE data la f(t, x), ossia calcola il punto successivo a quello
// dato
std::vector<double> ode_solver(std::vector<double> sols, double const h) {
  // std::vector<double> sols_copy = sols;
  double t1 = sols[0];
  double t2 = sols[1];
  double t1d = sols[2];
  double t2d = sols[3];

  double const D = 2 - std::cos(t1 - t2) * std::cos(t1 - t2);

  double k1 = h * t1d;
  double l1 = h * t2d;
  double m1 = h * f(t1, t2, t1d, t2d) / D;
  double n1 = h * g(t1, t2, t1d, t2d) / D;

  double k2 = h * (t1d + m1 * 0.5);
  double l2 = h * (t2d + n1 * 0.5);
  double m2 =
      h * f(t1 + k1 * 0.5, t2 + l1 * 0.5, t1d + m1 * 0.5, t2d + n1 * 0.5) / D;
  double n2 =
      h * g(t1 + k1 * 0.5, t2 + l1 * 0.5, t1d + m1 * 0.5, t2d + n1 * 0.5) / D;

  double k3 = h * (t1d + m2 * 0.5);
  double l3 = h * (t2d + n2 * 0.5);
  double m3 =
      h * f(t1 + k2 * 0.5, t2 + l2 * 0.5, t1d + m2 * 0.5, t2d + n2 * 0.5) / D;
  double n3 =
      h * g(t1 + k2 * 0.5, t2 + l2 * 0.5, t1d + m2 * 0.5, t2d + n2 * 0.5) / D;

  double k4 = h * (t1d + m3);
  double l4 = h * (t2d + n3);
  double m4 = h * f(t1 + k3, t2 + l3, t1d + m3, t2d + n3) / D;
  double n4 = h * g(t1 + k3, t2 + l3, t1d + m3, t2d + n3) / D;

  t1 += (k1 + 2 * k2 + 2 * k3 + k4) / 6;
  t2 += (l1 + 2 * l2 + 2 * l3 + l4) / 6;
  t1d += (m1 + 2 * m2 + 2 * m3 + m4) / 6;
  t2d += (n1 + 2 * n2 + 2 * n3 + n4) / 6;

  return std::vector<double>{t1, t2, t1d, t2d};
}

double tot_energy(std::vector<double> solutions) {
  double x1 = l * std::sin(solutions[0]);
  double y1 = -1 * (-2 * l + l * (2 - std::cos(solutions[0])));
  double x2 = l * (std::sin(solutions[0]) + std::sin(solutions[1]));
  double y2 =
      -1 * (-2 * l + l * (2 - std::cos(solutions[0]) - std::cos(solutions[1])));

  double const kin =
      l * l *
      (solutions[2] + 0.5 * solutions[3] * solutions[3] +
       std::cos(solutions[0] - solutions[1]) * solutions[2] * solutions[3]);
  double const pot = 9.81 * (y1 + y2);
  return kin + pot;
}