#include "phobos.h"
#include <SFML/Graphics.hpp>

void PhobosGame::Phobos() {

  // Create the main window
  sf::RenderWindow window(sf::VideoMode({800, 600}), "SFML window");

  // Create a graphical text to display
  const sf::Font font("./assets/fonts/VT323-Regular.ttf");
  sf::Text text(font, "Phobos", 50);
  text.setPosition({400,300});

  // Start the game loop
  while (window.isOpen()) {
    // Process events
    while (const std::optional event = window.pollEvent()) {
      // Close window: exit
      if (event->is<sf::Event::Closed>())
        window.close();
    }

    // Clear screen
    window.clear();
    // Draw the string
    window.draw(text);
    // Update the window
    window.display();
  }
};

