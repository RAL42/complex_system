// #include <iostream>

#include <sstream>

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "point.hpp"
#include "rk4.hpp"

std::string to_string_with_precision(const double a_value, const int n = 3) {
  // converte un double in string con n cifre decimali
  std::ostringstream out;
  out.precision(n);
  out << std::fixed << a_value;
  return std::move(out).str();
}

auto evolve(std::vector<double>& solutions, int steps, double const h) {
  for (int i{0}; i != steps; ++i) {
    solutions = ode_solver(solutions, h);
  }
  return solutions;
}

int main() {
  auto const h = 0.0001;
  // incremento
  int const fps{60};
  int steps{100000 / fps};

  // condizioni iniziali
  double const t1_0 = pi/2;
  double const t2_0 = pi;
  double const t1d_0 = 0.;
  double const t2d_0 = 0.;

  std::vector<double> solutions{t1_0, t2_0, t1d_0, t2d_0};

  double x1 = l * std::sin(solutions[0]);
  double y1 = -1 * (-2 * l + l * (2 - std::cos(solutions[0])));
  double x2 = l * (std::sin(solutions[0]) + std::sin(solutions[1]));
  double y2 =
      -1 * (-2 * l + l * (2 - std::cos(solutions[0]) - std::cos(solutions[1])));

  std::cout << "m1_xy = (" << x1 << ", " << y1 << ") \n";
  std::cout << "m2_xy = (" << x2 << ", " << y2 << ") \n";

  Point fixed(0., 0.);
  // punto fisso
  Point m1(x1, y1);
  m1.setFillColor(sf::Color::Green);
  m1.setRadius(9);
  // prima massa
  Point m2(x2, y2);
  m2.setFillColor(sf::Color::Red);
  // seconda massa

  sf::Font font;
  font.loadFromFile("./font/fresco_stamp.ttf");
  sf::Text en_string;
  en_string.setFont(font);
  en_string.setCharacterSize(25);
  en_string.setFillColor(sf::Color::White);
  en_string.setPosition(200, -250);

  unsigned const display_width = 0.6 * sf::VideoMode::getDesktopMode().width;
  unsigned const display_height = 0.6 * sf::VideoMode::getDesktopMode().height;

  sf::RenderWindow window(sf::VideoMode(display_width, display_height),
                          "Double Pendulum");
  // creo la finestra di SFML
  window.setFramerateLimit(fps);
  window.setPosition(sf::Vector2i(700, 200));

  sf::Vector2f window_size(window.getSize());
  // getsize prende width e height della window

  sf::View view{sf::Vector2f{0., 0.}, window_size};
  window.setView(view);
  // sf::View permette di cambiare l'origine del sistema di riferimento, il
  // primo vettore è l'origine, il secondo è la size della window

  // creo gli assi cartesiani
  sf::Vertex x_axis[] = {sf::Vertex(sf::Vector2f(-10000, 0.)),
                         sf::Vertex(sf::Vector2f(10000, 0.))};
  sf::Vertex y_axis[] = {sf::Vertex(sf::Vector2f(0., -10000)),
                         sf::Vertex(sf::Vector2f(0, 10000))};

  bool start = false;
  // per far partire l'evoluzione
  bool first = true;
  // per far stampare a schermo la condizione iniziale

  std::cout << "----------------- fine init ----------------- \n";

  while (window.isOpen()) {
    window.setKeyRepeatEnabled(true);
    // permette di "ripremere" il pulsante tenendolo premuto

    sf::Event event;
    while (window.pollEvent(event)) {
      // comandi per variare alcune grandezze in real-time

      if (event.type == sf::Event::Closed) window.close();
      /*if (event.type == sf::Event::KeyPressed &&
          event.key.code == sf::Keyboard::Space)
        window.close();
        */
      if (event.type == sf::Event::KeyPressed &&
          event.key.code == sf::Keyboard::Enter) {
        start = true;
        first = false;
        std::cout << "partito\n";
      }
      if (event.type == sf::Event::KeyPressed &&
          event.key.code == sf::Keyboard::Escape) {
        start = false;
      }
      if (event.type == sf::Event::KeyPressed &&
          event.key.code == sf::Keyboard::D)
        ++steps;
      if (event.type == sf::Event::KeyPressed &&
          event.key.code == sf::Keyboard::A && steps != 0)
        --steps;
    }

    if (first) {
      // disegno la condizione iniziale e le varie stringhe finche non premo
      // invio
      window.clear(sf::Color::Black);

      sf::Vertex seg1[] = {sf::Vertex(sf::Vector2f(fixed.x(), fixed.y())),
                           sf::Vertex(sf::Vector2f(m1.x(), m1.y()))};
      sf::Vertex seg2[] = {sf::Vertex(sf::Vector2f(m1.x(), m1.y())),
                           sf::Vertex(sf::Vector2f(m2.x(), m2.y()))};

      window.draw(seg1, 2, sf::Lines);
      window.draw(seg2, 2, sf::Lines);
      window.draw(x_axis, 2, sf::Lines);
      window.draw(y_axis, 2, sf::Lines);

      fixed.setFillColor(sf::Color::Magenta);
      fixed.setRadius(6);
      fixed.draw(window);
      m1.draw(window);
      m2.draw(window);

      window.display();
    }
    if (start) {
      // se premo invio parte la simulazione
      window.clear(sf::Color::Black);

      solutions = evolve(solutions, steps, h);
      // calcola l'evoluzione della chain e restituisce la chain evoluta dopo
      // steps_per_evolution

      en_string.setString("tot energy is " +
                          to_string_with_precision(tot_energy(solutions)));
      window.draw(en_string);

      x1 = l * std::sin(solutions[0]);
      y1 = -1 * (-2 * l + l * (2 - std::cos(solutions[0])));
      x2 = l * (std::sin(solutions[0]) + std::sin(solutions[1]));
      y2 = -1 *
           (-2 * l + l * (2 - std::cos(solutions[0]) - std::cos(solutions[1])));

      m1.update_x(x1);
      m1.update_y(y1);
      m2.update_x(x2);
      m2.update_y(y2);
      sf::Vertex seg1[] = {sf::Vertex(sf::Vector2f(fixed.x(), fixed.y())),
                           sf::Vertex(sf::Vector2f(m1.x(), m1.y()))};
      sf::Vertex seg2[] = {sf::Vertex(sf::Vector2f(m1.x(), m1.y())),
                           sf::Vertex(sf::Vector2f(m2.x(), m2.y()))};

      /*std::cout << "\nnel main \n";
      std::cout << "m1_xy = (" << m1.x()/100 << ", " << m1.y()/100 << ") \n";
      std::cout << "m2_xy = (" << m2.x()/100 << ", " << m2.y()/100 << ") \n";
      */
      window.draw(seg1, 2, sf::Lines);
      window.draw(seg2, 2, sf::Lines);
      window.draw(x_axis, 2, sf::Lines);
      window.draw(y_axis, 2, sf::Lines);

      fixed.draw(window);
      m1.draw(window);
      m2.draw(window);

      window.display();
    }
  }
}