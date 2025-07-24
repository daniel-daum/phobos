// save.cpp - JSON save file management for Phobos game
// Handles creating, loading, updating save data in JSON format

#include "phobos.h"
#include <fstream>
#include <sstream>

//---------------------------------------------------------------------
// CONSTRUCTOR
//---------------------------------------------------------------------

// Initialize save file with default values
SaveFile::SaveFile(const std::string &file) : filename(file) {
  playerName = "Unknown";
  level = 1;
  health = 100;
  lastLocation = "Terminal";
  gameState = "menu";
  playTime = 0;
}

//---------------------------------------------------------------------
// JSON GENERATION
//---------------------------------------------------------------------

// Convert current save data to formatted JSON string
std::string SaveFile::toJson() {
  std::ostringstream json;
  json << "{\n";
  json << "  \"version\": \"PHOBOS_SAVE_V2\",\n";
  json << "  \"player\": {\n";
  json << "    \"name\": \"" << playerName << "\",\n";
  json << "    \"level\": " << level << ",\n";
  json << "    \"health\": " << health << ",\n";
  json << "    \"location\": \"" << lastLocation << "\"\n";
  json << "  },\n";
  json << "  \"gameData\": {\n";
  json << "    \"state\": \"" << gameState << "\",\n";
  json << "    \"playTime\": " << playTime << "\n";
  json << "  }\n";
  json << "}";
  return json.str();
}

//---------------------------------------------------------------------
// JSON PARSING
//---------------------------------------------------------------------

// Find and extract value for given key from JSON string
std::string SaveFile::findValue(const std::string &json, const std::string &key) {
  std::string pattern = "\"" + key + "\":";
  size_t pos = json.find(pattern);
  if (pos == std::string::npos) return "";
  
  pos = json.find(':', pos) + 1;
  while (pos < json.size() && (json[pos] == ' ' || json[pos] == '\t')) pos++;
  
  if (json[pos] == '"') {
    pos++;
    size_t end = json.find('"', pos);
    return json.substr(pos, end - pos);
  } else {
    size_t end = json.find_first_of(",\n}", pos);
    return json.substr(pos, end - pos);
  }
}

// Parse JSON string and populate save data
void SaveFile::fromJson(const std::string &json) {
  playerName = findValue(json, "name");
  lastLocation = findValue(json, "location");
  gameState = findValue(json, "state");
  
  std::string val = findValue(json, "level");
  if (!val.empty()) level = std::stoi(val);
  
  val = findValue(json, "health");
  if (!val.empty()) health = std::stoi(val);
  
  val = findValue(json, "playTime");
  if (!val.empty()) playTime = std::stoi(val);
}

//---------------------------------------------------------------------
// FILE OPERATIONS
//---------------------------------------------------------------------

// Create new save file with current data
bool SaveFile::create() {
  std::ofstream file(filename);
  if (!file.is_open()) return false;
  file << toJson();
  return true;
}

// Load save data from file
bool SaveFile::load() {
  std::ifstream file(filename);
  if (!file.is_open()) return false;
  
  std::string content((std::istreambuf_iterator<char>(file)),
                      std::istreambuf_iterator<char>());
  fromJson(content);
  return true;
}

// Update existing save file
bool SaveFile::update() {
  return create();
}

// Delete save file
bool SaveFile::remove() {
  return std::remove(filename.c_str()) == 0;
}

// Check if save file exists
bool SaveFile::exists() {
  std::ifstream file(filename);
  return file.good();
}

//---------------------------------------------------------------------
// DATA SETTERS
//---------------------------------------------------------------------

// Set player data
void SaveFile::setPlayer(const std::string &name, int lvl, int hp, const std::string &location) {
  playerName = name;
  level = lvl;
  health = hp;
  lastLocation = location;
}

// Set game state data
void SaveFile::setGame(const std::string &state, int time) {
  gameState = state;
  playTime = time;
}

//---------------------------------------------------------------------
// DATA GETTERS
//---------------------------------------------------------------------

std::string SaveFile::getPlayerName() const { return playerName; }
int SaveFile::getLevel() const { return level; }
int SaveFile::getHealth() const { return health; }
std::string SaveFile::getLastLocation() const { return lastLocation; }
std::string SaveFile::getGameState() const { return gameState; }
int SaveFile::getPlayTime() const { return playTime; }
