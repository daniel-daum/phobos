// ui.cpp - Terminal-style user interface for Phobos game
// Handles menu display, navigation, and input processing

#include "phobos.h"
#include <SFML/Graphics.hpp>

//---------------------------------------------------------------------
// CONSTRUCTOR
//---------------------------------------------------------------------

// Initialize UI with render window and load terminal font
PhobosUI::PhobosUI(sf::RenderWindow *win) : window(win), selectedOption(0) {
  if (!font.openFromFile("./assets/fonts/VT323-Regular.ttf")) {
    // Handle font loading error
  }
}

//---------------------------------------------------------------------
// MENU SETUP
//---------------------------------------------------------------------

// Set the title text for the menu
void PhobosUI::setTitle(const std::string &text) { 
  title = text; 
}

// Set menu options and reset selection
void PhobosUI::setOptions(const std::vector<std::string> &opts) {
  options = opts;
  selectedOption = 0;
}

//---------------------------------------------------------------------
// INPUT HANDLING
//---------------------------------------------------------------------

// Process keyboard input for menu navigation
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

//---------------------------------------------------------------------
// RENDERING
//---------------------------------------------------------------------

// Draw title and menu options with selection cursor
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

//---------------------------------------------------------------------
// ACCESSORS
//---------------------------------------------------------------------

// Get currently selected menu option
int PhobosUI::getSelectedOption() const { 
  return selectedOption; 
}
