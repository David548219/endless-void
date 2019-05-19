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
                  sf::Vector2f(32.f, 32.f), sf::Color::Color(0x0A, 0x11, 0x1E),
                  sf::Color::Color(0xAE, 0xB5, 0xC4), "Sample");
    objects.push_back(b1);
    ui::Panel* p1 = new ui::Panel([]() { std::cout << "Panel Pressed" << std::endl; },
                 []() { std::cout << "Inside panel" << std::endl; },
                 []() { std::cout << "Outside panel" << std::endl; },
                 sf::Vector2f(32.f, 32.f), sf::Vector2f(32.f, 32.f),
                 sf::Color::Color(0xFF, 0xFF, 0xFF));
    objects.push_back(p1);
    isLoaded = true;
    enabled = true;
  }
};

#endif  // INCLUDE_LOOSESCENE_HPP_
