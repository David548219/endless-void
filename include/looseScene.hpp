// Copyright 2018 David Oganesian david548219@gmail.com

#ifndef INCLUDE_LOOSESCENE_HPP_
#define INCLUDE_LOOSESCENE_HPP_

#include "engine/scene.hpp"
#include "engine/ui.hpp"

class LooseScene : public base::Scene {
 public:
   virtual void loadScene() {
    ui::Button* b1 = new ui::Button([]() { std::cout << "Button Pressed" << std::endl; },
                  []() { std::cout << "Inside button" << std::endl; },
                  []() { std::cout << "Outside button" << std::endl; },
                  sf::Vector2f(432.f, 432.f), sf::Color::Color(0x0A, 0x11, 0x1E),
                  sf::Color::Color(0xAE, 0xB5, 0xC4), "Sample");
    objects.push_back(b1);
    isLoaded = true;
    enabled = true;
  }
};

#endif  // INCLUDE_LOOSESCENE_HPP_
