// Copyright 2018 David Oganesian david548219@gmail.com

#include "engine/scene.hpp"
#include "engine/object.hpp"

void base::Scene::renderScene(sf::RenderWindow& window, float deltaTime,
                              const UpdateTable& table) {
  if (enabled && isLoaded) {
    for (base::Object* object : objects) {
      object->onUpdateWrapper(window, deltaTime, table);
    }
  }
}

void base::Scene::unloadScene() {
  if (isLoaded) {
    for (base::Object* object : objects) {
      delete object;
    }
    objects.clear();
    enabled = false;
    isLoaded = false;
  }
}
