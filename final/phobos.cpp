#include "phobos.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

void PhobosGame::Phobos() {
  sf::RenderWindow window(sf::VideoMode({800, 600}), "Phobos Terminal");
  PhobosUI ui(&window);

  showMainMenu(window, ui);
};

void PhobosGame::showMainMenu(sf::RenderWindow &window, PhobosUI &ui) {
  ui.setTitle("PHOBOS TERMINAL");
  ui.setOptions({"New Game", "Load Game", "Exit"});

  while (window.isOpen()) {
    while (const std::optional event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>()) {
        window.close();
      }

      ui.handleInput(*event);

      if (event->is<sf::Event::KeyPressed>()) {
        auto key = event->getIf<sf::Event::KeyPressed>()->code;
        if (key == sf::Keyboard::Key::Enter) {
          int choice = ui.getSelectedOption();
          if (choice == 0) {
            // New Game
          } else if (choice == 1) {
            // Load Game
          } else if (choice == 2) {
            window.close();
          }
        }
      }
    }

    window.clear();
    ui.draw();
    window.display();
  }
}

PhobosUI::PhobosUI(sf::RenderWindow *win) : window(win), selectedOption(0) {
  if (!font.openFromFile("./assets/fonts/VT323-Regular.ttf")) {
    // Handle font loading error
  }
}

void PhobosUI::setTitle(const std::string &text) { title = text; }

void PhobosUI::setOptions(const std::vector<std::string> &opts) {
  options = opts;
  selectedOption = 0;
}

void PhobosUI::handleInput(const sf::Event &event) {
  if (event.is<sf::Event::KeyPressed>()) {
    auto key = event.getIf<sf::Event::KeyPressed>()->code;

    if (key == sf::Keyboard::Key::Up || key == sf::Keyboard::Key::Num8) {
      selectedOption = (selectedOption - 1 + options.size()) % options.size();
    } else if (key == sf::Keyboard::Key::Down ||
               key == sf::Keyboard::Key::Num2) {
      selectedOption = (selectedOption + 1) % options.size();
    }
  }
}

void PhobosUI::draw() {
  if (!title.empty()) {
    sf::Text titleText(font, title, 40);
    titleText.setPosition({50, 50});
    titleText.setFillColor(sf::Color::Green);
    window->draw(titleText);
  }

  for (int i = 0; i < static_cast<int>(options.size()); i++) {
    sf::Text optionText(font, options[i], 30);
    optionText.setPosition({100.0f, 150.0f + static_cast<float>(i) * 50.0f});

    if (i == selectedOption) {
      optionText.setFillColor(sf::Color::Yellow);
      sf::Text cursor(font, ">", 30);
      cursor.setPosition({70.0f, 150.0f + static_cast<float>(i) * 50.0f});
      cursor.setFillColor(sf::Color::Yellow);
      window->draw(cursor);
    } else {
      optionText.setFillColor(sf::Color::Green);
    }

    window->draw(optionText);
  }
}

int PhobosUI::getSelectedOption() const { return selectedOption; }
