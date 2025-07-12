#include "phobos_ui.h"
#include <fstream>
#include <iostream>
#include <string>

class Player {
public:
  std::string name;
  int health;
  int level;
  std::string ship_status;

  // constructor
  Player()
      : name("Unknown"), health(100), level(1), ship_status("Operational") {}

  // constructor with name
  Player(const std::string &playerName)
      : name(playerName), health(100), level(1), ship_status("Operational") {}
};

class GameLogic {
private:
  Player *currentPlayer; // pointer to current player

public:
  // constructor - allocates memory for player
  GameLogic() { currentPlayer = new Player(); }

  // destructor - cleans up memory
  ~GameLogic() { delete currentPlayer; }

  // saves player data to txt file
  void savePlayerData() {
    std::ofstream saveFile("player_data.txt");

    if (saveFile.is_open()) {

      saveFile << "Player Name: " << currentPlayer->name << std::endl;
      saveFile << "Health: " << currentPlayer->health << std::endl;
      saveFile << "Level: " << currentPlayer->level << std::endl;
      saveFile << "Ship Status: " << currentPlayer->ship_status << std::endl;
      saveFile.close();

      PhobosUI::slowPrint("Player data saved successfully.", 30);
    } else {
      PhobosUI::slowPrint("Error: Could not save player data.", 30);
    }
  }

  // loads player data from txt file
  void loadPlayerData() {
    std::ifstream loadFile("player_data.txt");
    if (loadFile.is_open()) {

      std::string line;
      while (getline(loadFile, line)) {

        if (line.find("Player Name: ") == 0) {

          currentPlayer->name = line.substr(13);
        } else if (line.find("Health: ") == 0) {

          currentPlayer->health = std::stoi(line.substr(8));
        } else if (line.find("Level: ") == 0) {

          currentPlayer->level = std::stoi(line.substr(7));
        } else if (line.find("Ship Status: ") == 0) {

          currentPlayer->ship_status = line.substr(13);
        }
      }
      loadFile.close();
      PhobosUI::slowPrint("Player data loaded successfully.", 30);

    } else {

      PhobosUI::slowPrint("No save file found. Starting fresh.", 30);
    }
  }

  // binary search algorithm  ship sectors
  int binarySearchSectors(std::string sectors[], int size, std::string target) {
    int left = 0;
    int right = size - 1;

    while (left <= right) {
      int mid = left + (right - left) / 2;

      // compare strings
      if (sectors[mid] == target) {
        return mid; // found the sector
      }

      if (sectors[mid] < target) {
        left = mid + 1;
      } else {
        right = mid - 1;
      }
    }

    return -1; // sector not found
  }

  // searching the  ship sectors
  void searchShipSectors() {
    // sorted array of ship sectors for binary search
    std::string shipSectors[8] = {"Bridge",       "Cargo Bay",   "Engine Room",
                                  "Life Support", "Medical Bay", "Navigation",
                                  "Security",     "Weapons Bay"};

    PhobosUI::printHeader("Ship Sector Search");
    PhobosUI::slowPrint("Available sectors:", 30);

    // display all sectors
    for (int i = 0; i < 8; i++) {
      std::cout << Colors::CYAN << "  " << shipSectors[i] << Colors::RESET
                << std::endl;
    }

    PhobosUI::printLines(1);
    PhobosUI::slowPrint("Enter sector name to search:", 30);

    std::string searchSector;
    std::cout << Colors::BRIGHT_CYAN << ">> " << Colors::RESET;
    std::cin.ignore();
    std::getline(std::cin, searchSector);

    // perform binary search
    int result = binarySearchSectors(shipSectors, 8, searchSector);

    if (result != -1) {
      PhobosUI::slowPrint("Sector found! Accessing " + searchSector + "...",
                          30);
      PhobosUI::slowPrint("Sector ID: " + std::to_string(result + 1), 20);
    } else {
      PhobosUI::slowPrint("Sector not found. Check spelling and try again.",
                          30);
    }

    PhobosUI::pressEnterToContinue();
  }

  // displays main game menu using array
  int showMainMenu() {

    // array of menu options
    std::string menuOptions[5] = {"Explore Ship Sectors", "Check Ship Systems",
                                  "Search Ship Database", "Save Game",
                                  "Exit to Main Menu"};

    PhobosUI::printHeader("Ship Command Interface");
    PhobosUI::slowPrint("Select an option:", 20);

    PhobosUI::printLines(1);

    // display menu options from array
    for (int i = 0; i < 5; i++) {

      std::cout << Colors::YELLOW << "  [" << (i + 1) << "] " << menuOptions[i]
                << Colors::RESET << std::endl;
    }

    PhobosUI::printLines(1);
    std::cout << Colors::BRIGHT_CYAN
              << ">> Enter choice (1-5): " << Colors::RESET;

    int choice;
    while (!(std::cin >> choice) || choice < 1 || choice > 5) {
      std::cout << Colors::RED
                << "Invalid input. Please enter 1-5: " << Colors::RESET;
      std::cin.clear();
      std::cin.ignore(10000, '\n');
    }

    return choice;
  }

  // displays player stats using pointer
  void displayPlayerStats() {
    PhobosUI::printHeader("Crew Member Profile");
    PhobosUI::slowPrint("Name: " + currentPlayer->name, 20);
    PhobosUI::slowPrint(
        "Health: " + std::to_string(currentPlayer->health) + "/100", 20);
    PhobosUI::slowPrint(
        "Security Level: " + std::to_string(currentPlayer->level), 20);
    PhobosUI::slowPrint("Ship Status: " + currentPlayer->ship_status, 20);
    PhobosUI::printLines(1);
  }

  // creates new player
  void createPlayer() {
    std::string playerName;
    PhobosUI::slowPrint("Enter your name for ship records:", 30);
    std::cout << Colors::BRIGHT_CYAN << ">> " << Colors::RESET;
    std::cin.ignore();
    std::getline(std::cin, playerName);

    // update player name [using pointer'[]
    currentPlayer->name = playerName;

    PhobosUI::slowPrint(
        "Welcome aboard the Phobos, " + currentPlayer->name + ".", 30);
    PhobosUI::printLines(1);
  }

  // gets pointer to current player
  Player *getCurrentPlayer() { return currentPlayer; }
};
