// Copyright 2018 David Oganesian david548219@gmail.com

#ifndef INCLUDE_UI_HPP_
#define INCLUDE_UI_HPP_

#include <SFML/Graphics.hpp>
#include <engine/base.hpp>
#include <engine/interfaces.hpp>
#include <functional>
#include <iostream>
#include <stdexcept>
#include <string>

namespace ui {
using Callback = std::function<void()>;

class Button : public internal::Object {
 public:
  Button(Callback onClick, Callback onMouseEnter, Callback onMouseLeave,
         sf::Vector2f pos, sf::Color bgColor, sf::Color textColor, std::string msg = std::string()) {
    if (!msg.empty()) {
        if (!font.loadFromFile("Data/arial.ttf")) {
        std::cerr << "Could not load ~/Data/arial.ttf";
      }

      text.setFont(font);
      text.setFillColor(textColor);
      text.setString(msg);
      text.setPosition(pos);

      bg.setSize(sf::Vector2f(text.getGlobalBounds().width + 12.f,
                                    text.getGlobalBounds().height + 12.f));
      bg.setPosition(sf::Vector2f(text.getGlobalBounds().left - 6.f,
                                        text.getGlobalBounds().top - 6.f));
    } else {
      bg.setSize(sf::Vector2f(128.f, 64.f));
      bg.setPosition(pos);
    }

    bg.setFillColor(bgColor);

    clickCallback = onClick;
    mouseEnterCallback = onMouseEnter;
    mouseLeaveCallback = onMouseLeave;
  }

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

  virtual void unSubscribe() { return; }
};

};  // namespace ui

#endif  // INCLUDE_UI_HPP_
