// Copyright 2018 David Oganesian david548219@gmail.com

#ifndef INCLUDE_BASE_HPP_
#define INCLUDE_BASE_HPP_

#include <functional>
#include <initializer_list>
#include <list>

namespace internal {
struct UpdateTable {
  sf::Vector2f mousePos;
  bool isMouseOneDown;
};

class Object {
 public:
  virtual void onUpdate(sf::RenderWindow& window, float deltaTime,
                        const UpdateTable& table) = 0;
  void onUpdateWrapper(sf::RenderWindow& window, float deltaTime,
                       const UpdateTable& table) {
    if (enabled) {
      onUpdate(window, deltaTime, table);
    }
  }
  ~Object() { unsubscribe(); }
  void subscribe(std::list<Object*>& e) {
    container = &e;
    (*container).push_front(this);
    it = container->begin();
  }

  void unsubscribe() {
    if (container != nullptr) {
      container->erase(it);
      container = nullptr;
    }
  }

 private:
  bool enabled = true;
  std::list<Object*>* container = nullptr;
  std::list<Object*>::iterator it;
};

class Scene {
 public:
  std::list<Object*>::iterator AddObject(Object* object) {
    objects.push_front(object);
    return objects.begin();
  }

  std::list<Object*>::iterator begin() { return objects.begin(); }
  std::list<Object*>::iterator end() { return objects.end(); }

 private:
  std::list<Object*> objects;
};

}  // namespace internal

#endif  // INCLUDE_BASE_HPP_
