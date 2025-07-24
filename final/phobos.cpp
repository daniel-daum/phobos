//======================================================
// phobos.cpp - Implementation file for Phobos terminal game
// A retro sci-fi terminal emulator game built with SFML
// Includes game logic, UI rendering, and save/load system
//======================================================

#include "phobos.h"
#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

//------------------------------------------------------
// GAME CONTROLLER FUNCTIONS
//------------------------------------------------------

// Main game entry point - creates window and starts menu
void PhobosGame::Phobos() {
  sf::RenderWindow window(sf::VideoMode({800, 600}), "Phobos Terminal");
  PhobosUI ui(&window);

  showMainMenu(window, ui);
};

// Display main menu and handle user selection
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
            newGame(window, ui);
          } else if (choice == 1) {
            loadGame(window, ui);
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

//------------------------------------------------------
// USER INTERFACE FUNCTIONS
//------------------------------------------------------

// Initialize UI with window reference and load font
PhobosUI::PhobosUI(sf::RenderWindow *win) : window(win), selectedOption(0) {
  if (!font.openFromFile("./assets/fonts/VT323-Regular.ttf")) {
    // Handle font loading error
  }
}

// Set the menu title text
void PhobosUI::setTitle(const std::string &text) { title = text; }

// Set menu options and reset selection
void PhobosUI::setOptions(const std::vector<std::string> &opts) {
  options = opts;
  selectedOption = 0;
}

// Handle keyboard input for menu navigation
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

// Draw UI elements to screen
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

// Return currently selected option index
int PhobosUI::getSelectedOption() const { return selectedOption; }

//------------------------------------------------------
// SAVE/LOAD SYSTEM FUNCTIONS
//------------------------------------------------------

// Initialize save file with default values
SaveFile::SaveFile(const std::string &file) : filename(file) {
  playerName = "Unknown";
  level = 1;
  health = 100;
  lastLocation = "Terminal";
}

// Set player data for saving
void SaveFile::setPlayerData(const std::string &name, int lvl, int hp,
                             const std::string &location) {
  playerName = name;
  level = lvl;
  health = hp;
  lastLocation = location;
}

// Save player data to file
bool SaveFile::save() {
  std::ofstream file(filename);
  if (!file.is_open()) {
    return false;
  }

  file << "PHOBOS_SAVE_V1\n";
  file << "NAME:" << playerName << "\n";
  file << "LEVEL:" << level << "\n";
  file << "HEALTH:" << health << "\n";
  file << "LOCATION:" << lastLocation << "\n";

  file.close();
  return true;
}

// Load player data from file
bool SaveFile::load() {
  std::ifstream file(filename);
  if (!file.is_open()) {
    return false;
  }

  std::string line;
  std::getline(file, line);
  if (line != "PHOBOS_SAVE_V1") {
    file.close();
    return false;
  }

  while (std::getline(file, line)) {
    if (line.find("NAME:") == 0) {
      playerName = line.substr(5);
    } else if (line.find("LEVEL:") == 0) {
      level = std::stoi(line.substr(6));
    } else if (line.find("HEALTH:") == 0) {
      health = std::stoi(line.substr(7));
    } else if (line.find("LOCATION:") == 0) {
      lastLocation = line.substr(9);
    }
  }

  file.close();
  return true;
}

// Getter functions for save data
std::string SaveFile::getPlayerName() const { return playerName; }
int SaveFile::getLevel() const { return level; }
int SaveFile::getHealth() const { return health; }
std::string SaveFile::getLastLocation() const { return lastLocation; }

// Check if save file exists
bool SaveFile::exists() {
  std::ifstream file(filename);
  return file.good();
}

//------------------------------------------------------
// STORY AND GAME FLOW FUNCTIONS
//------------------------------------------------------

// Start new game with opening story sequence
void PhobosGame::newGame(sf::RenderWindow &window, PhobosUI &ui) {
  sf::Font font;
  if (!font.openFromFile("./assets/fonts/VT323-Regular.ttf")) {
    return;
  }

  // Opening story text sequence
  std::vector<std::string> scrawlLines = {
      "It is 2179.",
      "Humanity has expanded across the solar system.",
      "Sovereign Celeste reigns over the imperium with absolute authority.",
      "We are at war.",
      "The covenant has launched an unprovoked and ruthless military",
      "campaign across the golden cities of mercury.",
      "Led by Octavia Al Lune, twelve billion sailors mounted",
      "an offensive strike against the enemy.",
      "There were no human survivors.",
      "In its desperation to counter this threat, the imperium",
      "has condemned you to hunt for any covenant weakness.",
      "Your last remaining lead has brought you to saturn's orbit;",
      "to a floating, derelict torch-ship called...",
      "PHOBOS"};

  sf::Clock clock;
  int currentLine = 0;
  float lineTimer = 0;
  bool scrawlComplete = false;

  while (window.isOpen() && !scrawlComplete) {
    float deltaTime = clock.restart().asSeconds();
    lineTimer += deltaTime;

    while (const std::optional event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>()) {
        window.close();
        return;
      }
      if (event->is<sf::Event::KeyPressed>()) {
        scrawlComplete = true;
      }
    }

    if (lineTimer > 2.0f && currentLine < scrawlLines.size()) {
      currentLine++;
      lineTimer = 0;
    }

    if (currentLine >= scrawlLines.size()) {
      scrawlComplete = true;
    }

    window.clear();

    float yPosition = 100.0f;
    for (int i = 0; i < currentLine && i < scrawlLines.size(); i++) {
      sf::Text text(font, scrawlLines[i], 24);
      text.setPosition({50.0f, yPosition});
      text.setFillColor(sf::Color::Green);

      if (i == scrawlLines.size() - 1) {
        text.setFillColor(sf::Color::Yellow);
        text.setCharacterSize(36);
        text.setPosition({300.0f, yPosition});
      }

      window.draw(text);
      yPosition += 35.0f;
    }

    window.display();
  }

  // Player name input sequence

  std::string playerName = "";
  bool nameComplete = false;
  sf::Clock blinkClock;

  while (window.isOpen() && !nameComplete) {
    while (const std::optional event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>()) {
        window.close();
        return;
      }

      if (event->is<sf::Event::TextEntered>()) {
        char typed =
            static_cast<char>(event->getIf<sf::Event::TextEntered>()->unicode);
        if (typed >= 32 && typed < 127 && playerName.length() < 20) {
          playerName += typed;
        }
      }

      if (event->is<sf::Event::KeyPressed>()) {
        auto key = event->getIf<sf::Event::KeyPressed>()->code;
        if (key == sf::Keyboard::Key::Backspace && !playerName.empty()) {
          playerName.pop_back();
        } else if (key == sf::Keyboard::Key::Enter && !playerName.empty()) {
          nameComplete = true;
        }
      }
    }

    window.clear();

    sf::Text prompt(font, "Enter your name for ship records:", 28);
    prompt.setPosition({50.0f, 200.0f});
    prompt.setFillColor(sf::Color::Green);
    window.draw(prompt);

    sf::Text nameText(font, playerName, 32);
    nameText.setPosition({50.0f, 250.0f});
    nameText.setFillColor(sf::Color::Yellow);
    window.draw(nameText);

    if (blinkClock.getElapsedTime().asMilliseconds() % 1000 < 500) {
      sf::Text cursor(font, "_", 32);
      cursor.setPosition(
          {50.0f + static_cast<float>(playerName.length() * 18), 250.0f});
      cursor.setFillColor(sf::Color::Yellow);
      window.draw(cursor);
    }

    sf::Text instruction(font, "Press ENTER to continue", 20);
    instruction.setPosition({50.0f, 350.0f});
    instruction.setFillColor(sf::Color::Cyan);
    window.draw(instruction);

    window.display();
  }

  // Create and save new game data
  SaveFile saveFile("phobos_save.dat");
  saveFile.setPlayerData(playerName, 1, 100, "Bridge");
  saveFile.save();
}

// Load existing save file and display player data
void PhobosGame::loadGame(sf::RenderWindow &window, PhobosUI &ui) {
  SaveFile saveFile("phobos_save.dat");
  sf::Font font;
  if (!font.openFromFile("./assets/fonts/VT323-Regular.ttf")) {
    return;
  }

  if (!saveFile.exists()) {
    sf::Clock clock;

    while (window.isOpen() && clock.getElapsedTime().asSeconds() < 2.0f) {
      while (const std::optional event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
          window.close();
          return;
        }
        if (event->is<sf::Event::KeyPressed>()) {
          return;
        }
      }

      window.clear();

      sf::Text errorMsg(font, "No save file found.", 32);
      errorMsg.setPosition({50.0f, 250.0f});
      errorMsg.setFillColor(sf::Color::Red);
      window.draw(errorMsg);

      sf::Text instruction(font, "Press any key to return to menu", 20);
      instruction.setPosition({50.0f, 300.0f});
      instruction.setFillColor(sf::Color::Cyan);
      window.draw(instruction);

      window.display();
    }
    return;
  }

  if (saveFile.load()) {
    sf::Clock clock;

    while (window.isOpen() && clock.getElapsedTime().asSeconds() < 3.0f) {
      while (const std::optional event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
          window.close();
          return;
        }
        if (event->is<sf::Event::KeyPressed>()) {
          return;
        }
      }

      window.clear();

      sf::Text welcomeBack(font, "Welcome back, " + saveFile.getPlayerName(),
                           28);
      welcomeBack.setPosition({50.0f, 200.0f});
      welcomeBack.setFillColor(sf::Color::Green);
      window.draw(welcomeBack);

      sf::Text level(font, "Level: " + std::to_string(saveFile.getLevel()), 24);
      level.setPosition({50.0f, 250.0f});
      level.setFillColor(sf::Color::Yellow);
      window.draw(level);

      sf::Text health(font, "Health: " + std::to_string(saveFile.getHealth()),
                      24);
      health.setPosition({50.0f, 280.0f});
      health.setFillColor(sf::Color::Yellow);
      window.draw(health);

      sf::Text location(font, "Location: " + saveFile.getLastLocation(), 24);
      location.setPosition({50.0f, 310.0f});
      location.setFillColor(sf::Color::Yellow);
      window.draw(location);

      window.display();
    }
  }
}
