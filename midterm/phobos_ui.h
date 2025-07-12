#pragma once

#include <chrono>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

class PhobosUI {

public:
  // UI
  static void printBorder();
  static void printHeader();
  static void printHeader(const std::string &title);
  static void printMenu(const std::vector<std::string> &options);

  // Utilities
  static void slowPrint(const std::string &text, int delay_ms = 50);
  static void slowPrintSpaced(const std::string &text, int delay_ms,
                              int space_before, int space_after);
  static void wait(int milliseconds);
  static void printTitle();
  static void printCentered(const std::string &text);
  static void pressEnterToContinue();
  static void clearScreen();
  static void printLines(int count);
  static void slowPrintCrawlCenteredSpaced(const std::string &text);

  // game text
  static void openingScrawl();
  static void introduction();
  static void characterCreation();

  // game logic integration
  static void runGameLoop();
  static int getUserChoice(int max_options);

private:
  static const int SCREEN_WIDTH = 80;
  static const std::string BORDER_CHAR;
  static const std::string SCANNER_CHAR;
};

// colors for term -> guide from stack overflow
namespace Colors {
const std::string RESET = "\033[0m";
const std::string GREEN = "\033[32m";
const std::string CYAN = "\033[36m";
const std::string YELLOW = "\033[33m";
const std::string RED = "\033[31m";
const std::string BLUE = "\033[34m";
const std::string MAGENTA = "\033[35m";
const std::string BRIGHT_GREEN = "\033[92m";
const std::string BRIGHT_CYAN = "\033[96m";
const std::string DIM = "\033[2m";
const std::string BOLD = "\033[1m";
const std::string BLINK = "\033[5m";
} // namespace Colors
