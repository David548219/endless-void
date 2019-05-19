// Copyright 2018 David Oganesian david548219@gmail.com

#include "engine/ui.hpp"
#include <SFML/Graphics.hpp>
#include <functional>
#include <iostream>
#include <string>

void ui::ObjectUI::onUpdate(sf::RenderWindow& window, float deltaTime,
                            const base::UpdateTable& table) {
  draw(window);
  if (getBounds().contains(table.mousePos)) {
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

ui::Panel::Panel(Callback onClick, Callback onMouseEnter, Callback onMouseLeave,
                 sf::Vector2f pos, sf::Vector2f size, sf::Color bgColor) {
  bg.setSize(size);
  bg.setPosition(pos);
  bg.setFillColor(bgColor);

  clickCallback = onClick;
  mouseEnterCallback = onMouseEnter;
  mouseLeaveCallback = onMouseLeave;
}

ui::Button::Button(Callback onClick, ui::Callback onMouseEnter,
                   Callback onMouseLeave, sf::Vector2f pos, sf::Color bgColor,
                   sf::Color textColor, std::string msg) {
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

  bg.setFillColor(bgColor);

  clickCallback = onClick;
  mouseEnterCallback = onMouseEnter;
  mouseLeaveCallback = onMouseLeave;
}

void ui::Button::draw(sf::RenderWindow& window) {
  window.draw(bg);
  window.draw(text);
}
