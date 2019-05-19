// Copyright 2018 David Oganesian david548219@gmail.com

#ifndef INCLUDE_INTERFACES_HPP_
#define INCLUDE_INTERFACES_HPP_

#include "engine/base.hpp"
namespace internal {
class IUpdate {
 public:
  ~IUpdate() {}
  virtual void onUpdate(sf::RenderWindow& window, float deltaTime, const UpdateTable& table) = 0;
};

}  // namespace internal
#endif  // INCLUDE_INTERFACES_HPP_
