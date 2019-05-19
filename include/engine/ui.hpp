// Copyright 2018 David Oganesian david548219@gmail.com

#ifndef INCLUDE_UI_HPP_
#define INCLUDE_UI_HPP_

#include <SFML/Graphics.hpp>
#include <engine/object.hpp>
#include <functional>
#include <string>

namespace ui {
using Callback = std::function<void()>;

class Button : public base::Object {
 public:
  Button(Callback onClick, Callback onMouseEnter, Callback onMouseLeave,
         sf::Vector2f pos, sf::Color bgColor, sf::Color textColor,
         std::string msg = std::string());

  virtual void onUpdate(sf::RenderWindow& window, float deltaTime,
                        const base::UpdateTable& table);

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

  void draw(sf::RenderWindow& window);
};

};  // namespace ui

#endif  // INCLUDE_UI_HPP_
