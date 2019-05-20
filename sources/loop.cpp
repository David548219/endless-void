// Copyright 2018 David Oganesian david548219@gmail.com

#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>
#include <vector>
#include "engine/object.hpp"
#include "engine/scene.hpp"
#include "engine/ui.hpp"

#include "player.hpp"
#include "gameScene.hpp"
#include "looseScene.hpp"

int main() {
  sf::Clock clock;
  sf::RenderWindow window(sf::VideoMode(1280, 720), "Endless void",
                          sf::Style::Titlebar | sf::Style::Close);
  window.setVerticalSyncEnabled(true);

  std::vector<base::Scene*> scenes;
  LooseScene looseScene;
  scenes.push_back(&looseScene);
  GameScene gameScene;
  scenes.push_back(&gameScene);

  for (base::Scene* scene : scenes) {
    scene->loadScene();
  }

  PlayerContainer playerContainer;

  while (window.isOpen()) {
    
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) window.close();
    }
    
    base::UpdateTable table{
        &playerContainer,
        sf::Vector2f(sf::Mouse::getPosition(window)),
        sf::Mouse::isButtonPressed(sf::Mouse::Button::Left),
    };

    window.clear(sf::Color::Color(0x10, 0x24, 0x4F));

    for (base::Scene* scene : scenes) {
      scene->renderScene(window, clock.getElapsedTime().asSeconds(), table);
    }
    clock.restart();

    window.display();
  }
  return 0;
}
