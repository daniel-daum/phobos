#include "phobos_ui.h"
#include <chrono>
#include <iostream>
#include <thread>

// clears the screen
void PhobosUI::clearScreen() {
#ifdef _WIN32
  system("cls");
#else
  system("clear");
#endif
}

// prints blank lines for spacing
void PhobosUI::printLines(int count) {
  for (int i = 0; i < count; i++) {
    std::cout << std::endl;
  }
}

// delays for a set amount of time
void PhobosUI::wait(int milliseconds) {
  std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}

// slowly prints text
void PhobosUI::slowPrint(const std::string &text, int delay_ms) {
  std::cout << Colors::GREEN;
  for (char c : text) {
    std::cout << c << std::flush;
    wait(delay_ms);
  }
  std::cout << Colors::RESET << std::endl;
}

void PhobosUI::slowPrintSpaced(const std::string &text, int delay_ms,
                               int space_before, int space_after) {
  std::cout << Colors::GREEN;
  printLines(space_before);
  for (char c : text) {
    std::cout << c << std::flush;
    wait(delay_ms);
  }
  std::cout << Colors::RESET << std::endl;
  printLines(space_after);
}

// prints the title -> this was hard :( | ascii blocks: ╚ ═ ╝ █ ╗
void PhobosUI::printTitle() {
  std::cout << Colors::BRIGHT_CYAN << std::endl;
  std::cout << "██████╗ ██╗  ██╗  ██████╗ ██████╗  ██████╗ ███████╗"<< std::endl;
  std::cout << "██╔══██╗██║  ██║ ██╔═══██ ██╔══██╗██╔═══██╗██╔════╝"<< std::endl;
  std::cout << "██████╔╝███████║ ██║   ██╗██████╔╝██║   ██║███████╗" << std::endl;
  std::cout << "██╔═══╝ ██╔══██║ ██║   ██║██═══██ ██║   ██║╚════██║"<< std::endl;
  std::cout << "██║     ██║  ██║ ╚██████╔╝██   ██ ╚██████╔╝███████║"<< std::endl;
  std::cout << "╚═╝     ╚═╝  ╚═╝  ╚═════╝ ╚████╝     ╚═════╝ ╚══════╝" << std::endl;
  std::cout << Colors::RESET << std::endl;
}

// prints text centered
void PhobosUI::printCentered(const std::string &text) {
  int padding = (SCREEN_WIDTH - text.length()) / 2;
  for (int i = 0; i < padding; i++) {
    std::cout << " ";
  }
  std::cout << Colors::CYAN << text << Colors::RESET << std::endl;
}

// waits fo user to press enter
void PhobosUI::pressEnterToContinue() {
  std::cout << Colors::DIM << std::endl
            << "Press Enter to continue..." << Colors::RESET;

  // re-look cin
  std::cin.ignore();
  std::cin.get();
}

// ascii blocks
const std::string PhobosUI::BORDER_CHAR = "═";
const std::string PhobosUI::SCANNER_CHAR = "▓";

// prints a thin border
void PhobosUI::printBorder() {
  std::cout << Colors::CYAN;
  for (int i = 0; i < SCREEN_WIDTH; i++) {
    std::cout << BORDER_CHAR;
  }
  std::cout << Colors::RESET << std::endl;
}

//  prints a header in a border
void PhobosUI::printHeader(const std::string &title) {
  printBorder();
  std::cout << Colors::BRIGHT_CYAN << Colors::BOLD;

  // Center the title
  int padding = (SCREEN_WIDTH - title.length()) / 2;
  for (int i = 0; i < padding; i++) {
    std::cout << " ";
  }
  std::cout << title << Colors::RESET << std::endl;

  printBorder();
}

// print an option menu to the screen
void PhobosUI::printMenu(const std::vector<std::string> &options) {
  std::cout << Colors::YELLOW << std::endl;
  for (size_t i = 0; i < options.size(); i++) {
    std::cout << "  [" << (i + 1) << "] " << options[i] << std::endl;
  }
  std::cout << Colors::RESET << std::endl;
}

void PhobosUI::openingScrawl() {
  PhobosUI::wait(500);
  PhobosUI::slowPrintSpaced("it is 2179.", 75, 1, 1);
  PhobosUI::wait(500);
  PhobosUI::slowPrintSpaced("humanity has expanded across the solar system", 75,
                            1, 1);
  PhobosUI::wait(500);
  PhobosUI::slowPrintSpaced(
      "Sovereign Celeste reigns over the imperium with absolute authority", 75,
      1, 1);
  PhobosUI::wait(800);
  PhobosUI::slowPrintSpaced("we are at war.", 100, 1, 1);
  PhobosUI::wait(500);
  PhobosUI::slowPrintSpaced(
      "the covenant... has launched an unprovoked and ruthless military "
      "campaign across the golden cities of mercury",
      75, 1, 1);
  PhobosUI::wait(500);
  PhobosUI::slowPrintSpaced("led by octavia al lune, twelve billion sailors "
                            "mounted an offensive strike against the enemy",
                            75, 1, 1);
  PhobosUI::wait(500);
  PhobosUI::slowPrintSpaced("there were no human survivors", 75, 1, 1);
  PhobosUI::wait(500);
  PhobosUI::slowPrintSpaced(
      "in its desperation to counter this threat, the imperium has condemend "
      "you to hunt for any covenant weakness",
      75, 1, 1);
  PhobosUI::wait(500);
  PhobosUI::slowPrintSpaced(
      "your last remaining lead has brought you to saturn's orbit; to a "
      "floating, derelict torch-ship called...",
      75, 1, 1);
}

//  introduction
void PhobosUI::introduction() {
  PhobosUI::clearScreen();
  PhobosUI::openingScrawl();
  PhobosUI::wait(2000);
  PhobosUI::clearScreen();
  PhobosUI::printTitle();
  PhobosUI::wait(800);
  PhobosUI::pressEnterToContinue();
};

// Character creation
void PhobosUI::characterCreation() {
  PhobosUI::printCentered("Terminal Initializing...");
  PhobosUI::clearScreen();
  PhobosUI::printHeader("Current Location - Torchship Phobos");
}

// gets user choice for menus
int PhobosUI::getUserChoice(int max_options) {
  int choice;
  std::cout << Colors::BRIGHT_CYAN << ">> Enter choice (1-" << max_options
            << "): " << Colors::RESET;

    
    // std:count << Colors -}|
        
  while (!(std::cin >> choice) || choice < 1 || choice > max_options) {
    std::cout << Colors::RED
              << "Invalid input. Please enter a number between 1 and "
              << max_options << ": " << Colors::RESET;
    std::cin.clear();
    std::cin.ignore(10000, '\n');
  }

  return choice;
}

// main game loop
void PhobosUI::runGameLoop() {
  PhobosUI::slowPrint("Accessing ship systems...", 50);
  PhobosUI::wait(1000);
  PhobosUI::clearScreen();
  PhobosUI::printHeader("Ship Systems Online");
  PhobosUI::slowPrint("All systems operational. Awaiting orders.", 30);
  PhobosUI::printLines(2);
  PhobosUI::pressEnterToContinue();
}
