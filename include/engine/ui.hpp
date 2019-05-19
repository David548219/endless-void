// Copyright 2018 David Oganesian david548219@gmail.com

#ifndef INCLUDE_UI_HPP_
#define INCLUDE_UI_HPP_

#include <SFML/Graphics.hpp>
#include <engine/object.hpp>
#include <functional>
#include <string>

namespace ui {
using Callback = std::function<void()>;

class ObjectUI : public base::Object {
 public:
  virtual void onUpdate(sf::RenderWindow& window, float deltaTime,
                        const base::UpdateTable& table);

 protected:
  Callback clickCallback;
  Callback mouseEnterCallback;
  Callback mouseLeaveCallback;
  bool wasClick = false;
  bool wasMouseEnter = false;
  bool wasMouseLeave = true;

  virtual sf::FloatRect getBounds() = 0;
  virtual void draw(sf::RenderWindow& window) = 0;
};

class Indicator : public base::Object {};

class Panel : public ObjectUI {
 public:
  Panel(Callback onClick, Callback onMouseEnter, Callback onMouseLeave,
        sf::Vector2f pos, sf::Vector2f size, sf::Color bgColor);

 private:
  sf::RectangleShape bg;

  virtual sf::FloatRect getBounds() { return bg.getGlobalBounds(); }
  virtual void draw(sf::RenderWindow& window) { window.draw(bg); }
};

class Button : public ObjectUI {
 public:
  Button(Callback onClick, Callback onMouseEnter, Callback onMouseLeave,
         sf::Vector2f pos, sf::Color bgColor, sf::Color textColor,
         std::string msg);

 private:
  sf::Font font;
  sf::Text text;
  sf::RectangleShape bg;

  virtual sf::FloatRect getBounds() { return bg.getGlobalBounds(); }
  virtual void draw(sf::RenderWindow& window);
};

};  // namespace ui

#endif  // INCLUDE_UI_HPP_
