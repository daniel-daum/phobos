#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

class PhobosUI;

class PhobosGame {
private:
  static void showMainMenu(sf::RenderWindow &window, PhobosUI &ui);

public:
  static void Phobos();
};

class PhobosText {};

class PhobosUI {
private:
  sf::RenderWindow *window;
  sf::Font font;
  std::vector<std::string> options;
  int selectedOption;
  std::string title;

public:
  PhobosUI(sf::RenderWindow *win);
  void setTitle(const std::string &text);
  void setOptions(const std::vector<std::string> &opts);
  void handleInput(const sf::Event &event);
  void draw();
  int getSelectedOption() const;
};
