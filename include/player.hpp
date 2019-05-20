// Copyright 2018 David Oganesian david548219@gmail.com

#ifndef INCLUDE_PLAYER_HPP_
#define INCLUDE_PLAYER_HPP_

#include <functional>
#include "engine/object.hpp"
#include "engine/ui.hpp"

class PlayerContainer {
 public:
  void SetCallback(ui::Callback onDeath) { deathCallback = onDeath; }

  int GetHealth() { return health; }
  void SetHealth(int h) {
    if (h > 30) {
      return;
    } else if (h < 0) {
      deathCallback;
    }
    health = h;
  }
  void AddHealth(int delta) { SetHealth(health + delta); }

  int GetShields() { return shields; }
  void SetShields(int s) {
    if (s < 0 || s > 5) {
      return;
    }
    shields = s;
  }
  void AddShields(int delta) { SetShields(shields + delta); }

 private:
  ui::Callback deathCallback;
  int health = 30;
  int shields = 5;
};

#endif  // INCLUDE_PLAYER_HPP_