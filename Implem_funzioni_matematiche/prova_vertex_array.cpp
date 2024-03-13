#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <iostream>

int main() {
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
  sf::Vertex x_axis[] = {sf::Vertex(sf::Vector2f(-10000, 0)),
                         sf::Vertex(sf::Vector2f(10000, 0))};
  sf::Vertex y_axis[] = {sf::Vertex(sf::Vector2f(0, -10000 / 2)),
                         sf::Vertex(sf::Vector2f(0, 10000 / 2))};
/* 
  x_axis[0].position += sf::Vector2f(0., 2.);
  x_axis[1].position += sf::Vector2f(0., 2.);
  x_axis[0].position += sf::Vector2f(0., 2.);
  x_axis[1].position += sf::Vector2f(0., 2.);
*/
  while (window.isOpen()) {
    window.setKeyRepeatEnabled(true);
    // permette di "ripremere" il pulsante tenendolo premuto

    sf::Event event;
    while (window.pollEvent(event)) {
      // comandi per variare alcune grandezze in real-time

      if (event.type == sf::Event::Closed) window.close();
      if (event.type == sf::Event::KeyPressed &&
          event.key.code == sf::Keyboard::Escape)
        window.close();
      if (event.type == sf::Event::KeyPressed &&
          event.key.code == sf::Keyboard::W) {
        view.move(0, 5);
        window.setView(view);

      };
      if (event.type == sf::Event::KeyPressed &&
          event.key.code == sf::Keyboard::S) {
        view.move(0, -5);
        window.setView(view);

      };
      if (event.type == sf::Event::KeyPressed &&
          event.key.code == sf::Keyboard::D) {
        view.move(-5, 0);
        window.setView(view);

      };

      if (event.type == sf::Event::KeyPressed &&
          event.key.code == sf::Keyboard::A) {
        view.move(5, 0);
        window.setView(view);
     
      };
      if (event.type == sf::Event::KeyPressed &&
          event.key.code == sf::Keyboard::P) {
       // view.zoom(factor += 0.05);
        window.setView(view);
      };
      if (event.type == sf::Event::KeyPressed &&
          event.key.code == sf::Keyboard::M) {
       // view.zoom(factor -= 0.05);
        window.setView(view);
      };
    }

sf::CircleShape s;
s.setRadius(10);
s.setFillColor(sf::Color::Green);
s.setPosition(10., 0.);

sf::Vertex graph[];
 


window.clear(sf::Color::Black);
window.draw(s);
window.draw(x_axis, 2, sf::Lines);
window.draw(y_axis, 2, sf::Lines);
window.display();

  }
}