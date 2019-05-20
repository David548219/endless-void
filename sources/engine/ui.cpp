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
  lateUpdateCallback(window, deltaTime, table);
}

ui::Image::Image(sf::Vector2f pos, sf::Texture* texturePtr, sf::Color color,
                 Callback onClick, Callback onMouseEnter,
                 Callback onMouseLeave) {
  if (texturePtr != nullptr) {
    texture = texturePtr;
    sprite.setTexture(*texturePtr);
  }
  sprite.setPosition(pos);
  sprite.setColor(color);

  clickCallback = onClick;
  mouseEnterCallback = onMouseEnter;
  mouseLeaveCallback = onMouseLeave;
}

void ui::Image::setRectSize(const sf::Vector2i& size) {
  sprite.setTextureRect(sf::IntRect(sprite.getTextureRect().left,
                                    sprite.getTextureRect().left, size.x,
                                    size.y));
}

void ui::Image::setColor(const sf::Color& color) { sprite.setColor(color); }

ui::Indicator::Indicator(sf::Vector2f pos, sf::Texture* texturePtr, int step,
                         int max, bool isHorizontalOrientation,
                         IntCallback onChange, Callback onClick,
                         Callback onMouseEnter, Callback onMouseLeave)
    : ui::Image(pos, texturePtr, sf::Color::White, onClick, onMouseEnter,
                onMouseLeave) {
  texturePtr->setRepeated(true);
  changeCallback = onChange;
  stepInPx = step;
  currentMeasure = 1;
  maxMeasure = max;
  isHorizontal = isHorizontalOrientation;

  setIndicatorPos(maxMeasure);
}

void ui::Indicator::setIndicatorPos(int pos) {
  if (pos < 0 || pos > maxMeasure) {
    std::cerr << "Can not set indicator to negative or too high value"
              << std::endl;
    return;
  }

  if (isHorizontal) {
    setRectSize(sf::Vector2i(
        getRect().width - (currentMeasure - pos) * stepInPx, getRect().height));
  } else {
    setRectSize(sf::Vector2i(
        getRect().width, getRect().height - (currentMeasure - pos) * stepInPx));
  }
  currentMeasure = pos;
  changeCallback(currentMeasure);
}

ui::Button::Button(sf::Vector2f pos, sf::Color bgColor, sf::Color textColor,
                   std::string msg, Callback onClick, Callback onMouseEnter,
                   Callback onMouseLeave) {
  if (!font.loadFromFile("Data/arial.ttf")) {
    std::cerr << "Could not load ~/Data/arial.ttf";
  }

  text.setFont(font);
  text.setFillColor(textColor);
  text.setString(msg);
  text.setPosition(pos);
  sprite.setSize(sf::Vector2f(text.getGlobalBounds().width + 12.f,
                              text.getGlobalBounds().height + 12.f));
  sprite.setPosition(sf::Vector2f(text.getGlobalBounds().left - 6.f,
                                  text.getGlobalBounds().top - 6.f));

  sprite.setFillColor(bgColor);

  clickCallback = onClick;
  mouseEnterCallback = onMouseEnter;
  mouseLeaveCallback = onMouseLeave;
}

void ui::Button::draw(sf::RenderWindow& window) {
  window.draw(sprite);
  window.draw(text);
}

ui::Panel::Panel(sf::Vector2f pos, sf::Vector2f size, sf::Color bgColor,
                 Callback onClick, Callback onMouseEnter,
                 Callback onMouseLeave) {
  sprite.setSize(size);
  sprite.setPosition(pos);

  sprite.setFillColor(bgColor);

  clickCallback = onClick;
  mouseEnterCallback = onMouseEnter;
  mouseLeaveCallback = onMouseLeave;
}

ui::ProgressBar::ProgressBar(sf::Vector2f pos, sf::Vector2f size,
                             sf::Color bgColor, bool isHorizontalOrientation,
                             Callback onClick, Callback onMouseEnter,
                             Callback onMouseLeave)
    : Panel(pos, size, bgColor, onClick, onMouseEnter, onMouseLeave) {
  isHorizontal = isHorizontalOrientation;
  if (isHorizontal) {
    max = size.x;
  } else {
    max = size.y;
  }
}

void ui::ProgressBar::setPercentage(float pr) {
  if (isHorizontal) {
    setSize(sf::Vector2f(max * pr, getSize().y));
  } else {
    setSize(sf::Vector2f(getSize().x, max * pr));
  }
}

ui::Text::Text(sf::Vector2f pos, sf::Color textColor, std::string msg,
               Callback onClick, Callback onMouseEnter, Callback onMouseLeave) {
  if (!font.loadFromFile("Data/arial.ttf")) {
    std::cerr << "Could not load ~/Data/arial.ttf";
  }

  text.setFont(font);
  text.setFillColor(textColor);
  text.setString(msg);
  text.setPosition(pos);

  clickCallback = onClick;
  mouseEnterCallback = onMouseEnter;
  mouseLeaveCallback = onMouseLeave;
}
