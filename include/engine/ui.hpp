// Copyright 2018 David Oganesian david548219@gmail.com

#ifndef INCLUDE_UI_HPP_
#define INCLUDE_UI_HPP_

#include <SFML/Graphics.hpp>
#include <engine/interfaces.hpp>
#include <functional>
#include <iostream>
#include <stdexcept>

namespace ui {
using Callback = std::function<void()>;

class Button : public internal::IUpdate {
 public:
  Button(Callback onClick, Callback onMouseEnter, Callback onMouseLeave,
         sf::Vector2f pos) {
    if (!font.loadFromFile("Data/arial.ttf")) {
      throw std::runtime_error("Could not load arial.ttf");
    }

    clickCallback = onClick;
    mouseEnterCallback = onMouseEnter;
    mouseLeaveCallback = onMouseLeave;

    text.setFont(font);
    text.setFillColor(sf::Color::Color(0xAE, 0xB5, 0xC4));
    text.setString("Play");
    text.setPosition(pos);

    bg.setSize(sf::Vector2<float>(text.getGlobalBounds().width + 12.f,
                                  text.getGlobalBounds().height + 12.f));
    bg.setPosition(sf::Vector2<float>(text.getGlobalBounds().left - 6.f,
                                      text.getGlobalBounds().top - 6.f));
    bg.setFillColor(sf::Color::Color(0x0A, 0x11, 0x1E));
  }
  ~Button() = default;

  virtual void onUpdate(sf::RenderWindow& window, float deltaTime,
                        const internal::UpdateTable& table) {
    draw(window);
    if (bg.getGlobalBounds().contains(table.mousePos)) {
      wasMouseLeave = false;
      
      if (!wasMouseEnter) {
        mouseEnterCallback();
        wasMouseEnter = true;
      }

      if (table.isMouseOneDown) {
        if (!wasClick) {
          clickCallback();
          wasClick = true;
        }
      } else {
        wasClick = false;
      }
    } else {
      wasMouseEnter = false;

      if (!wasMouseLeave) {
        mouseLeaveCallback();
        wasMouseLeave = true;
      }
    }
  }

 private:
  Callback clickCallback;
  Callback mouseEnterCallback;
  Callback mouseLeaveCallback;
  bool wasClick = false;
  bool wasMouseEnter = false;
  bool wasMouseLeave = true;
  sf::Font font;
  sf::Text text;
  sf::RectangleShape bg;

  void draw(sf::RenderWindow& window) {
    window.draw(bg);
    window.draw(text);
  }
};

};  // namespace ui

#endif  // INCLUDE_UI_HPP_
