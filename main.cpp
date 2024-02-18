#include <SFML/Graphics.hpp>
#include <algorithm>
#include <cmath>
#include <fstream>
#include <vector>

#include "rk4.hpp"

int main() {
  // std::ofstream outputfile("punti.txt");

  double constexpr h = 0.01;
  double constexpr x_max = 10.;

  unsigned const display_width = 0.85 * sf::VideoMode::getDesktopMode().width;
  unsigned const display_height = 0.85 * sf::VideoMode::getDesktopMode().height;

  sf::RenderWindow window(sf::VideoMode(display_width, display_height),
                          "Runge kutta");
  // creo la finestra di SFML
  window.setPosition(sf::Vector2i(100, 100));

  sf::Vector2f window_size(window.getSize());
  // getsize prende width e height della window

  sf::View view{sf::Vector2f{0, 0}, window_size};
  window.setView(view);
  // sf::View permette di cambiare l'origine del sistema di riferimento, il
  // primo vettore è l'origine, il secondo è la size della window

  // creo gli assi cartesiani
  sf::Vertex x_axis[] = {sf::Vertex(sf::Vector2f(-window_size.x, 0)),
                         sf::Vertex(sf::Vector2f(window_size.x, 0))};
  sf::Vertex y_axis[] = {sf::Vertex(sf::Vector2f(0, -window_size.y / 2)),
                         sf::Vertex(sf::Vector2f(0, window_size.y / 2))};

  bool first = true;

  while (window.isOpen()) {
    window.setKeyRepeatEnabled(false);
    // permette di "ripremere" il pulsante tenendolo premuto

    sf::Event event;
    while (window.pollEvent(event)) {
      // comandi per variare alcune grandezze in real-time

      if (event.type == sf::Event::Closed) window.close();
      if (event.type == sf::Event::KeyPressed &&
          event.key.code == sf::Keyboard::Space)
        window.close();
    }

    window.draw(x_axis, 2, sf::Lines);
    window.draw(y_axis, 2, sf::Lines);
    window.display();

    if (first) {
      first = false;
      window.clear(sf::Color::Black);
      f1 f(-5, std::pow(numbers::e, -5));
      draw(window, f, x_max, h);

      f2 g(-5, 5);
      draw(window, g, x_max, h);
    }
    window.display();
  }
}