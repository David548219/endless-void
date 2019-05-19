// Copyright 2018 David Oganesian david548219@gmail.com

#include <SFML/Graphics.hpp>
#include <list>
#include "engine/object.hpp"
#include "engine/scene.hpp"
#include "engine/ui.hpp"

int main() {
  sf::Clock clock;
  sf::RenderWindow window(sf::VideoMode(1280, 720), "Endless void",
                          sf::Style::Titlebar | sf::Style::Close);
  window.setVerticalSyncEnabled(true);

  base::Scene objects;
  ui::Button b1([]() {}, []() {}, []() {}, sf::Vector2f(32.f, 32.f),
                sf::Color::Color(0x0A, 0x11, 0x1E),
                sf::Color::Color(0xAE, 0xB5, 0xC4), "Sample");
  objects.push_front(&b1);

  while (window.isOpen()) {
    clock.restart();
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) window.close();
    }

    base::UpdateTable table{
        sf::Vector2f(sf::Mouse::getPosition(window)),
        sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)};

    window.clear(sf::Color::Color(0x10, 0x24, 0x4F));

    for (base::Object* object : objects) {
      object->onUpdateWrapper(window, clock.getElapsedTime().asSeconds(),
                              table);
    }

    window.display();
  }
  return 0;
}
