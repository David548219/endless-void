// Copyright 2018 David Oganesian david548219@gmail.com

#ifndef INCLUDE_GAMESCENE_HPP_
#define INCLUDE_GAMESCENE_HPP_

#include "engine/scene.hpp"
#include "engine/ui.hpp"

class GameScene : public base::Scene {
 public:
  virtual void loadScene() {
    
    isLoaded = true;
    enabled = true;
  }
};

#endif  // INCLUDE_GAMESCENE_HPP_
