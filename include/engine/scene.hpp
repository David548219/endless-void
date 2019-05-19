// Copyright 2018 David Oganesian david548219@gmail.com

#ifndef INCLUDE_SCENE_HPP_
#define INCLUDE_SCENE_HPP_

#include <SFML/Graphics.hpp>
#include <functional>
#include <vector>
#include "engine/object.hpp"

namespace base {
class Scene {
 public:
  ~Scene() { unloadScene(); }

  void renderScene(sf::RenderWindow& window, float deltaTime,
                   const UpdateTable& table);
  virtual void loadScene() = 0;
  void unloadScene();

 protected:
  std::vector<Object*> objects;
  bool isLoaded = false;
  bool enabled = false;
};

}  // namespace base

#endif  // INCLUDE_SCENE_HPP_
