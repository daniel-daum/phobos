// phobos.h - Phobos terminal game header
// Class declarations and function prototypes for the Phobos space exploration game

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

//---------------------------------------------------------------------
// FORWARD DECLARATIONS
//---------------------------------------------------------------------

class PhobosUI;
class SaveFile;

//---------------------------------------------------------------------
// MAIN GAME CONTROLLER
//---------------------------------------------------------------------

// PhobosGame - Main game controller and state manager
class PhobosGame {
private:
  static void showMainMenu(sf::RenderWindow &window, PhobosUI &ui);  // Display main menu
  static void newGame(sf::RenderWindow &window, PhobosUI &ui);       // Start new game
  static void loadGame(sf::RenderWindow &window, PhobosUI &ui);      // Load existing save

public:
  static void Phobos();  // Main game entry point
};

class PhobosText {};  // Placeholder for future text rendering

//---------------------------------------------------------------------
// USER INTERFACE
//---------------------------------------------------------------------

// PhobosUI - Terminal-style user interface manager
class PhobosUI {
private:
  sf::RenderWindow *window;         // SFML render window
  sf::Font font;                    // Terminal font
  std::vector<std::string> options; // Menu options
  int selectedOption;               // Currently selected option
  std::string title;                // Menu title

public:
  PhobosUI(sf::RenderWindow *win);                              // Initialize UI with window
  void setTitle(const std::string &text);                       // Set menu title
  void setOptions(const std::vector<std::string> &opts);        // Set menu options
  void handleInput(const sf::Event &event);                     // Process input events
  void draw();                                                   // Render UI elements
  int getSelectedOption() const;                                 // Get selected option index
};

//---------------------------------------------------------------------
// STORY AND NARRATIVE FUNCTIONS
//---------------------------------------------------------------------

void showOpeningScroll(sf::RenderWindow &window, sf::Font &font);               // Display opening story
std::string getPlayerName(sf::RenderWindow &window, sf::Font &font);            // Get player name input
void showSaveData(sf::RenderWindow &window, sf::Font &font, SaveFile &saveFile); // Display save info
void showErrorMessage(sf::RenderWindow &window, sf::Font &font,                 // Show error message
                      const std::string &message);

//---------------------------------------------------------------------
// JSON SAVE FILE MANAGEMENT
//---------------------------------------------------------------------

// SaveFile - JSON-based save file manager
class SaveFile {
private:
  std::string filename;     // Save file path
  std::string playerName;   // Player character name
  int level;                // Player level
  int health;               // Player health
  std::string lastLocation; // Last known location
  std::string gameState;    // Current game state
  int playTime;             // Total play time in seconds

  std::string findValue(const std::string &json, const std::string &key); // Parse JSON value
  std::string toJson();                                                    // Generate JSON string
  void fromJson(const std::string &json);                                 // Parse JSON data

public:
  SaveFile(const std::string &file);  // Initialize with filename
  
  // File operations
  bool create();  // Create new save file
  bool load();    // Load save from file
  bool update();  // Update existing save
  bool remove();  // Delete save file
  bool exists();  // Check if save exists
  
  // Data setters
  void setPlayer(const std::string &name, int lvl, int hp, const std::string &location); // Set player data
  void setGame(const std::string &state, int time);                                       // Set game data
  
  // Data getters
  std::string getPlayerName() const;   // Get player name
  int getLevel() const;                // Get player level
  int getHealth() const;               // Get player health
  std::string getLastLocation() const; // Get last location
  std::string getGameState() const;    // Get game state
  int getPlayTime() const;             // Get play time
};
