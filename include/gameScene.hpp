// Copyright 2018 David Oganesian david548219@gmail.com

#ifndef INCLUDE_GAMESCENE_HPP_
#define INCLUDE_GAMESCENE_HPP_

#include "engine/scene.hpp"
#include "engine/ui.hpp"

class GameScene : public base::Scene {
 public:
  virtual void loadScene() {
    sf::Texture* uiBackground = new sf::Texture;
    if (!uiBackground->loadFromFile("Data/ui_background.png")) {
      std::cerr << "Could not load ~/Data/ui_background.png";
    }
    ui::Image* background = new ui::Image(sf::Vector2f(0, 0), uiBackground);
    objects.push_back(background);

    sf::Texture* uiShip = new sf::Texture;
    if (!uiShip->loadFromFile("Data/ui_ship.png")) {
      std::cerr << "Could not load ~/Data/ui_ship.png";
    }
    ui::Image* ship_panel = new ui::Image(sf::Vector2f(150, 200), uiShip);
    objects.push_back(ship_panel);

    sf::Texture* uiEnemyPanel = new sf::Texture;
    if (!uiEnemyPanel->loadFromFile("Data/ui_enemyPanel.png")) {
      std::cerr << "Could not load ~/Data/ui_enemyPanel.png";
    }
    ui::Image* enemy_panel = new ui::Image(sf::Vector2f(860, 80), uiEnemyPanel);
    objects.push_back(enemy_panel);

    sf::Texture* uiShieldBubble = new sf::Texture;
    if (!uiShieldBubble->loadFromFile("Data/ui_shieldBubble.png")) {
      std::cerr << "Could not load ~/Data/ui_shieldBubble.png";
    }
    uiShieldBubble->setRepeated(true);
    ui::Image* shield_bubbles =
        new ui::Image(sf::Vector2f(20 + 123, 20 + 64), uiShieldBubble);
    shield_bubbles->setRectSize(sf::Vector2i(140, 28));
    objects.push_back(shield_bubbles);

    sf::Texture* uiHealthPoint = new sf::Texture;
    if (!uiHealthPoint->loadFromFile("Data/ui_HealthPoint.png")) {
      std::cerr << "Could not load ~/Data/ui_HealthPoint.png";
    }
    uiHealthPoint->setRepeated(true);
    ui::Image* health_points =
        new ui::Image(sf::Vector2f(20 + 9, 20 + 8), uiHealthPoint);
    health_points->setRectSize(sf::Vector2i(510, 48));
    health_points->setColor(sf::Color(0x02, 0x92, 0x00));
    objects.push_back(health_points);

    sf::Texture* uiMainBar = new sf::Texture;
    if (!uiMainBar->loadFromFile("Data/ui_mainBar.png")) {
      std::cerr << "Could not load ~/Data/ui_mainBar.png";
    }
    ui::Image* main_bar = new ui::Image(sf::Vector2f(20, 20), uiMainBar);
    objects.push_back(main_bar);

    isLoaded = true;
    enabled = true;
  }

 private:

};

#endif  // INCLUDE_GAMESCENE_HPP_
