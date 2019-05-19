// Copyright 2018 David Oganesian david548219@gmail.com

#include "engine/object.hpp"
#include <functional>
#include <list>

void base::Object::onUpdateWrapper(sf::RenderWindow& window, float deltaTime,
                                   const UpdateTable& table) {
  if (enabled) {
    onUpdate(window, deltaTime, table);
  }
}
