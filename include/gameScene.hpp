// Copyright 2018 David Oganesian david548219@gmail.com

#ifndef INCLUDE_GAMESCENE_HPP_
#define INCLUDE_GAMESCENE_HPP_

#include "engine/scene.hpp"
#include "engine/ui.hpp"

class GameScene : public base::Scene {
 public:
  virtual void loadScene() {
    sf::Texture* uiShieldBubble = new sf::Texture;
    if (!uiShieldBubble->loadFromFile("Data/ui_shieldBubble.png")) {
      std::cerr << "Could not load ~/Data/ui_shieldBubble.png";
    }
    uiShieldBubble->setRepeated(true);
    ui::Image* shield_bubbles = new ui::Image(
        []() {}, []() {}, []() {}, sf::Vector2f(20 + 8, 20 + 64), uiShieldBubble);
    shield_bubbles->setRectSize(sf::Vector2i(140, 28));
    objects.push_back(shield_bubbles);

    sf::Texture* uiHealthPoint = new sf::Texture;
    if (!uiHealthPoint->loadFromFile("Data/ui_HealthPoint.png")) {
      std::cerr << "Could not load ~/Data/ui_HealthPoint.png";
    }
    uiHealthPoint->setRepeated(true);
    ui::Image* health_points =
        new ui::Image([]() {}, []() {}, []() {}, sf::Vector2f(20 + 8, 20 + 8),
                      uiHealthPoint);
    health_points->setRectSize(sf::Vector2i(510, 48));
    health_points->setColor(sf::Color(0x02, 0x92, 0x00));
    objects.push_back(health_points);

    sf::Texture* uiHull = new sf::Texture;
    if (!uiHull->loadFromFile("Data/ui_hull.png")) {
      std::cerr << "Could not load ~/Data/ui_hull.png";
    }
    ui::Image* hull_panel =
        new ui::Image([]() {}, []() {}, []() {}, sf::Vector2f(20, 20), uiHull);
    objects.push_back(hull_panel);

    isLoaded = true;
    enabled = true;
  }
};

#endif  // INCLUDE_GAMESCENE_HPP_
