// story.cpp - Story and narrative display functions for Phobos game
// Handles opening scroll, player input, save data display, and error messages

#include "phobos.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

//---------------------------------------------------------------------
// OPENING STORY SCROLL
//---------------------------------------------------------------------

// Display animated opening story text
void showOpeningScroll(sf::RenderWindow &window, sf::Font &font) {
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
  size_t currentLine = 0;
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
    for (size_t i = 0; i < currentLine && i < scrawlLines.size(); i++) {
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
}

//---------------------------------------------------------------------
// PLAYER NAME INPUT
//---------------------------------------------------------------------

// Get player name input with blinking cursor
std::string getPlayerName(sf::RenderWindow &window, sf::Font &font) {
  std::string playerName = "";
  bool nameComplete = false;
  sf::Clock blinkClock;

  while (window.isOpen() && !nameComplete) {
    while (const std::optional event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>()) {
        window.close();
        return "";
      }

      if (event->is<sf::Event::TextEntered>()) {
        char typed = static_cast<char>(event->getIf<sf::Event::TextEntered>()->unicode);
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
      cursor.setPosition({50.0f + static_cast<float>(playerName.length() * 18), 250.0f});
      cursor.setFillColor(sf::Color::Yellow);
      window.draw(cursor);
    }

    sf::Text instruction(font, "Press ENTER to continue", 20);
    instruction.setPosition({50.0f, 350.0f});
    instruction.setFillColor(sf::Color::Cyan);
    window.draw(instruction);

    window.display();
  }

  return playerName;
}

//---------------------------------------------------------------------
// SAVE DATA DISPLAY
//---------------------------------------------------------------------

// Display loaded save file information
void showSaveData(sf::RenderWindow &window, sf::Font &font, SaveFile &saveFile) {
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

    sf::Text welcomeBack(font, "Welcome back, " + saveFile.getPlayerName(), 28);
    welcomeBack.setPosition({50.0f, 200.0f});
    welcomeBack.setFillColor(sf::Color::Green);
    window.draw(welcomeBack);

    sf::Text level(font, "Level: " + std::to_string(saveFile.getLevel()), 24);
    level.setPosition({50.0f, 250.0f});
    level.setFillColor(sf::Color::Yellow);
    window.draw(level);

    sf::Text health(font, "Health: " + std::to_string(saveFile.getHealth()), 24);
    health.setPosition({50.0f, 280.0f});
    health.setFillColor(sf::Color::Yellow);
    window.draw(health);

    sf::Text location(font, "Location: " + saveFile.getLastLocation(), 24);
    location.setPosition({50.0f, 310.0f});
    location.setFillColor(sf::Color::Yellow);
    window.draw(location);

    sf::Text gameState(font, "State: " + saveFile.getGameState(), 24);
    gameState.setPosition({50.0f, 340.0f});
    gameState.setFillColor(sf::Color::Yellow);
    window.draw(gameState);

    sf::Text playTime(font, "Time: " + std::to_string(saveFile.getPlayTime()) + "s", 24);
    playTime.setPosition({50.0f, 370.0f});
    playTime.setFillColor(sf::Color::Yellow);
    window.draw(playTime);

    window.display();
  }
}

//---------------------------------------------------------------------
// ERROR DISPLAY
//---------------------------------------------------------------------

// Display error message with timeout
void showErrorMessage(sf::RenderWindow &window, sf::Font &font, const std::string &message) {
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

    sf::Text errorMsg(font, message, 32);
    errorMsg.setPosition({50.0f, 250.0f});
    errorMsg.setFillColor(sf::Color::Red);
    window.draw(errorMsg);

    sf::Text instruction(font, "Press any key to return to menu", 20);
    instruction.setPosition({50.0f, 300.0f});
    instruction.setFillColor(sf::Color::Cyan);
    window.draw(instruction);

    window.display();
  }
}
