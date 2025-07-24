#include "phobos.h"
#include <SFML/Graphics.hpp>

void PhobosGame::Phobos() {
  sf::RenderWindow window(sf::VideoMode({800, 600}), "Phobos Terminal");
  PhobosUI ui(&window);
  showMainMenu(window, ui);
}

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

void PhobosGame::newGame(sf::RenderWindow &window, PhobosUI &) {
  sf::Font font;
  if (!font.openFromFile("./assets/fonts/VT323-Regular.ttf")) {
    return;
  }

  showOpeningScroll(window, font);
  std::string playerName = getPlayerName(window, font);

  if (!playerName.empty()) {
    SaveFile saveFile("phobos_save.dat");
    saveFile.setPlayer(playerName, 1, 100, "Bridge");
    saveFile.setGame("newGame", 0);
    saveFile.create();
  }
}

void PhobosGame::loadGame(sf::RenderWindow &window, PhobosUI &) {
  SaveFile saveFile("phobos_save.dat");
  sf::Font font;
  if (!font.openFromFile("./assets/fonts/VT323-Regular.ttf")) {
    return;
  }

  if (!saveFile.exists()) {
    showErrorMessage(window, font, "No save file found.");
    return;
  }

  if (saveFile.load()) {
    showSaveData(window, font, saveFile);
  }
}
