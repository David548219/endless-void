// Copyright 2018 David Oganesian david548219@gmail.com

#include "engine/scene.hpp"
#include "engine/object.hpp"

std::list<base::Object*>::iterator base::Scene::push_front(Object* object) {
  objects.push_front(object);
  return objects.begin();
}
