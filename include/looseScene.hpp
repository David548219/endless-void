// Copyright 2018 David Oganesian david548219@gmail.com

#ifndef INCLUDE_LOOSESCENE_HPP_
#define INCLUDE_LOOSESCENE_HPP_

#include "engine/scene.hpp"
#include "engine/ui.hpp"

class LooseScene : public base::Scene {
 public:
  virtual void loadScene() {
    isLoaded = true;
    enabled = true;
  }
};

#endif  // INCLUDE_LOOSESCENE_HPP_
