//======================================================
// phobos.h - Header file for Phobos terminal game
// Contains class declarations for game components:
// - PhobosGame: Main game controller
// - PhobosUI: Terminal-style user interface
// - SaveFile: Save/load game data system
//======================================================

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

class PhobosUI;

//------------------------------------------------------
// PhobosGame - Main game controller class
//------------------------------------------------------
class PhobosGame {
private:
  // Display main menu with options
  static void showMainMenu(sf::RenderWindow &window, PhobosUI &ui);
  // Start new game with opening story
  static void newGame(sf::RenderWindow &window, PhobosUI &ui);
  // Load existing save file
  static void loadGame(sf::RenderWindow &window, PhobosUI &ui);

public:
  // Main game entry point
  static void Phobos();
};

//------------------------------------------------------
// PhobosText - Placeholder text class
//------------------------------------------------------
class PhobosText {};

//------------------------------------------------------
// PhobosUI - Terminal-style user interface
//------------------------------------------------------
class PhobosUI {
private:
  sf::RenderWindow *window;
  sf::Font font;
  std::vector<std::string> options;
  int selectedOption;
  std::string title;

public:
  // Initialize UI with window reference
  PhobosUI(sf::RenderWindow *win);
  // Set menu title text
  void setTitle(const std::string &text);
  // Set menu option list
  void setOptions(const std::vector<std::string> &opts);
  // Handle keyboard input for navigation
  void handleInput(const sf::Event &event);
  // Draw UI elements to screen
  void draw();
  // Get currently selected option index
  int getSelectedOption() const;
};

//------------------------------------------------------
// SaveFile - Game save/load system
//------------------------------------------------------
class SaveFile {
private:
  std::string filename;
  std::string playerName;
  int level;
  int health;
  std::string lastLocation;

public:
  // Initialize save file with filename
  SaveFile(const std::string &file);
  // Set player data for saving
  void setPlayerData(const std::string &name, int lvl, int hp,
                     const std::string &location);
  // Save data to file
  bool save();
  // Load data from file
  bool load();
  // Get player name from loaded data
  std::string getPlayerName() const;
  // Get player level from loaded data
  int getLevel() const;
  // Get player health from loaded data
  int getHealth() const;
  // Get last location from loaded data
  std::string getLastLocation() const;
  // Check if save file exists
  bool exists();
};
