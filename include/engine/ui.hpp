// Copyright 2018 David Oganesian david548219@gmail.com

#ifndef INCLUDE_UI_HPP_
#define INCLUDE_UI_HPP_

#include <SFML/Graphics.hpp>
#include <engine/object.hpp>
#include <functional>
#include <string>

namespace ui {
using Callback = std::function<void()>;
using IntCallback = std::function<void(int)>;
using UpdateCallback =
    std::function<void(sf::RenderWindow&, float, const base::UpdateTable&)>;

class ObjectUI : public base::Object {
 public:
  virtual void onUpdate(sf::RenderWindow& window, float deltaTime,
                        const base::UpdateTable& table);
  void setLateUpdateCallback(UpdateCallback onLateUpdate) {
    lateUpdateCallback = onLateUpdate;
  }

 protected:
  UpdateCallback lateUpdateCallback = [](sf::RenderWindow&, float,
                                         const base::UpdateTable&) {};
  Callback clickCallback;
  Callback mouseEnterCallback;
  Callback mouseLeaveCallback;
  bool wasClick = false;
  bool wasMouseEnter = false;
  bool wasMouseLeave = true;

  virtual sf::FloatRect getBounds() = 0;
  virtual void draw(sf::RenderWindow& window) = 0;
};

class Image : public ObjectUI {
 public:
  ~Image() { delete texture; }
  Image(sf::Vector2f pos, sf::Texture* texturePtr,
        sf::Color color = sf::Color::White, Callback onClick = []() {},
        Callback onMouseEnter = []() {}, Callback onMouseLeave = []() {});
  void setRectSize(const sf::Vector2i& size);
  sf::IntRect getRect() { return sprite.getTextureRect(); }
  void setColor(const sf::Color& color);

 private:
  sf::Sprite sprite;
  sf::Texture* texture;
  virtual sf::FloatRect getBounds() { return sprite.getGlobalBounds(); }
  virtual void draw(sf::RenderWindow& window) { window.draw(sprite); }
};

class Indicator : public Image {
 public:
  Indicator(sf::Vector2f pos, sf::Texture* texturePtr, int step, int max,
            bool isHorizontalOrientation, IntCallback onChange = [](int a) {},
            Callback onClick = []() {}, Callback onMouseEnter = []() {},
            Callback onMouseLeave = []() {});
  int getMax() { return maxMeasure; }
  void setIndicatorPos(int pos);
  void addToIndicatorPos(int delta) { setIndicatorPos(currentMeasure + delta); }

 private:
  IntCallback changeCallback;
  int stepInPx;
  int currentMeasure;
  int maxMeasure;
  bool isHorizontal;
};

class Button : public ObjectUI {
 public:
  Button(sf::Vector2f pos, sf::Color bgColor, sf::Color textColor,
         std::string msg, Callback onClick = []() {},
         Callback onMouseEnter = []() {}, Callback onMouseLeave = []() {});

 private:
  sf::Font font;
  sf::Text text;
  sf::RectangleShape sprite;

  virtual sf::FloatRect getBounds() { return sprite.getGlobalBounds(); }
  virtual void draw(sf::RenderWindow& window);
};

class Panel : public ObjectUI {
 public:
  Panel(sf::Vector2f pos, sf::Vector2f size, sf::Color bgColor,
        Callback onClick = []() {}, Callback onMouseEnter = []() {},
        Callback onMouseLeave = []() {});

  void setSize(sf::Vector2f size) { sprite.setSize(size); }
  sf::Vector2f getSize() { return sprite.getSize(); }

 private:
  sf::RectangleShape sprite;

  virtual sf::FloatRect getBounds() { return sprite.getGlobalBounds(); }
  virtual void draw(sf::RenderWindow& window) { window.draw(sprite); }
};

class ProgressBar : public Panel {
 public:
  ProgressBar(sf::Vector2f pos, sf::Vector2f size, sf::Color bgColor,
              bool isHorizontalOrientation, Callback onClick = []() {},
              Callback onMouseEnter = []() {}, Callback onMouseLeave = []() {});

  void setPercentage(float pr);

 private:
  float max;
  bool isHorizontal;
};

class Text : public ObjectUI {
 public:
  Text(sf::Vector2f pos, sf::Color textColor, std::string msg,
       Callback onClick = []() {}, Callback onMouseEnter = []() {},
       Callback onMouseLeave = []() {});

  void setText(const std::string& txt) { text.setString(txt); }
  void setColor(const sf::Color& color) { text.setFillColor(color); }

 private:
  sf::Font font;
  sf::Text text;

  virtual sf::FloatRect getBounds() { return text.getGlobalBounds(); }
  virtual void draw(sf::RenderWindow& window) { window.draw(text); }
};

};  // namespace ui

#endif  // INCLUDE_UI_HPP_
