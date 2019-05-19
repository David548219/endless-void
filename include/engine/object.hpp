// Copyright 2018 David Oganesian david548219@gmail.com

#ifndef INCLUDE_OBJECT_HPP_
#define INCLUDE_OBJECT_HPP_

#include <SFML/Graphics.hpp>
#include <list>

namespace base {
struct UpdateTable {
  sf::Vector2f mousePos;
  bool isMouseOneDown;
};

class Object {
 public:
  virtual void onUpdate(sf::RenderWindow& window, float deltaTime,
                        const UpdateTable& table) = 0;
  void onUpdateWrapper(sf::RenderWindow& window, float deltaTime,
                       const UpdateTable& table);

  virtual ~Object() {}

 private:
  bool enabled = true;
};

}  // namespace base

#endif  // INCLUDE_OBJECT_HPP_
