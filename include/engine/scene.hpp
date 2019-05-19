// Copyright 2018 David Oganesian david548219@gmail.com

#ifndef INCLUDE_SCENE_HPP_
#define INCLUDE_SCENE_HPP_

#include <SFML/Graphics.hpp>
#include "engine/object.hpp"
#include <functional>
#include <list>

namespace base {
class Scene {
 public:
  std::list<Object*>::iterator push_front(Object* object);
  
  std::list<Object*>::iterator begin() { return objects.begin(); }
  std::list<Object*>::iterator end() { return objects.end(); }

 private:
  std::list<Object*> objects;
};

}  // namespace base

#endif  // INCLUDE_SCENE_HPP_
