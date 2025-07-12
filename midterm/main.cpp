#include "phobos_logic.cpp"
#include "phobos_ui.h"

class Phobos {
private:
  GameLogic *gameLogic; // pointer to game logic

public:
  Phobos() { gameLogic = new GameLogic(); }

  ~Phobos() { delete gameLogic; }

  // main game loop
  void run() {
    PhobosUI::clearScreen();
    PhobosUI::introduction();
    PhobosUI::characterCreation();

    // character creation
    gameLogic->createPlayer();

    // try to load existing save data
    gameLogic->loadPlayerData();

    // main game loop
    bool gameRunning = true;
    while (gameRunning) {
      PhobosUI::clearScreen();
      gameLogic->displayPlayerStats();

      int choice = gameLogic->showMainMenu();

      switch (choice) {
      case 1:
        // explore ship sectors
        PhobosUI::clearScreen();
        PhobosUI::printHeader("Ship Exploration");
        PhobosUI::slowPrint(
            "You venture into the dark corridors of the Phobos...", 50);
        PhobosUI::slowPrint("The ship creaks ominously as you explore.", 50);
        PhobosUI::pressEnterToContinue();
        break;

      case 2:
        // check ship systems
        PhobosUI::clearScreen();
        PhobosUI::printHeader("Ship Systems Diagnostic");
        PhobosUI::slowPrint("Running full system diagnostic...", 50);
        PhobosUI::slowPrint("Life Support: Operational", 30);
        PhobosUI::slowPrint("Navigation: Offline", 30);
        PhobosUI::slowPrint("Weapons: Unknown", 30);
        PhobosUI::pressEnterToContinue();
        break;

      case 3:
        // search ship database
        PhobosUI::clearScreen();
        gameLogic->searchShipSectors();
        break;

      case 4:
        // save game
        PhobosUI::clearScreen();
        PhobosUI::printHeader("Save Game");
        gameLogic->savePlayerData();
        PhobosUI::pressEnterToContinue();
        break;

      case 5:
        // exit
        PhobosUI::clearScreen();
        PhobosUI::slowPrint("Logging out of ship systems...", 50);
        PhobosUI::slowPrint("Thank you for serving the Imperium.", 50);
        gameRunning = false;
        break;
      }
    }
  }
};

int main() {
  Phobos phobos;
  phobos.run();
  return 0;
}
