// Copyright 2018 David Oganesian david548219@gmail.com

#ifndef INCLUDE_GAMESCENE_HPP_
#define INCLUDE_GAMESCENE_HPP_

#include "engine/scene.hpp"
#include "engine/ui.hpp"

#include "player.hpp"

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
    ui::Indicator* shield_bubbles = new ui::Indicator(
        sf::Vector2f(20 + 123, 20 + 64), uiShieldBubble, 28, 5, true);
    shield_bubbles->setLateUpdateCallback(
        [shield_bubbles](sf::RenderWindow& window, float deltaTime,
                         const base::UpdateTable& table) {
          shield_bubbles->setIndicatorPos(table.playerContainer->GetShields());
        });
    objects.push_back(shield_bubbles);

    sf::Texture* uiHealthPoint = new sf::Texture;
    if (!uiHealthPoint->loadFromFile("Data/ui_HealthPoint.png")) {
      std::cerr << "Could not load ~/Data/ui_HealthPoint.png";
    }
    ui::Indicator* health_points = new ui::Indicator(
        sf::Vector2f(20 + 9, 20 + 8), uiHealthPoint, 17, 30, true,
        [health_points](int v) {
          float p = static_cast<float>(v) / health_points->getMax();
          if (p > 0.6f) {
            health_points->setColor(sf::Color(0x02, 0x92, 0x00));
          } else if (p > 0.25) {
            health_points->setColor(sf::Color(0xEF, 0xCF, 0x06));
          } else {
            health_points->setColor(sf::Color(0xDD, 0x17, 0x17));
          }
        });
    health_points->setColor(sf::Color(0x02, 0x92, 0x00));
    health_points->setLateUpdateCallback(
        [health_points](sf::RenderWindow& window, float deltaTime,
                        const base::UpdateTable& table) {
          health_points->setIndicatorPos(table.playerContainer->GetHealth());
        });
    objects.push_back(health_points);

    sf::Texture* uiMainBar = new sf::Texture;
    if (!uiMainBar->loadFromFile("Data/ui_mainBar.png")) {
      std::cerr << "Could not load ~/Data/ui_mainBar.png";
    }
    ui::Image* main_bar = new ui::Image(sf::Vector2f(20, 20), uiMainBar);
    objects.push_back(main_bar);

    ui::Text* fps_counter =
        new ui::Text(sf::Vector2f(0, 685), sf::Color::Red, "0");
    fps_counter->setLateUpdateCallback(
        [fps_counter](sf::RenderWindow& window, float deltaTime,
                      const base::UpdateTable& table) {
          static float time;
          time += deltaTime;
          if (time > 0.5f) {
            long fps = std::lround(1.f / deltaTime);
            if (fps >= 60) {
              fps_counter->setColor(sf::Color::Green);
            } else if (fps >= 30) {
              fps_counter->setColor(sf::Color::Yellow);
            } else {
              fps_counter->setColor(sf::Color::Red);
            }
            fps_counter->setText(std::to_string(fps));
            time = 0.f;
          }
        });
    objects.push_back(fps_counter);

    isLoaded = true;
    enabled = true;
  }

 private:
};

#endif  // INCLUDE_GAMESCENE_HPP_
